#include "UDPManager.h"
#include "HeaderManagerCPP.h"
#include "ServerCPP.h"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <ServicePool.h>
#include <ClientManager.h>
#include <Client.h>
#include <PacketManager.h>
#include <IPacket.h>
#include <iostream>
using namespace boost::asio::ip;

UDPManager::UDPManager(ServerCPP* server)
	:server(server), socket(nullptr), receiveData(nullptr)
{
	hm = server->createHeaderManager();
}

void UDPManager::detach(uint16_t port)
{
	try
	{
		if (server->getIPVersion() == boost::asio::ip::tcp::v6())
		{
			socket = boost::make_shared<udp::socket>(server->getServicePool()->getNextIOService(), udp::endpoint(boost::asio::ip::udp::v6(), port));
		}
		else
		{
			socket = boost::make_shared<udp::socket>(server->getServicePool()->getNextIOService(), udp::endpoint(boost::asio::ip::udp::v4(), port));
		}
		read();
	}
	catch (boost::system::system_error sysError)
	{
		std::cerr << sysError.code() << std::endl;
	}
}

void UDPManager::read()
{
	if (receiveData == nullptr)
	{
		receiveData = new std::vector<unsigned char>(MAX_UDP_DATA_SIZE);
	}
	socket->async_receive_from(boost::asio::buffer(*receiveData, MAX_UDP_DATA_SIZE), receiveEP, boost::bind(&UDPManager::asyncReceive, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void UDPManager::close()
{
		if (socket != nullptr)
		{
				socket->shutdown(boost::asio::ip::udp::socket::shutdown_both);
				socket->close();
		}
}

void UDPManager::asyncReceive(const boost::system::error_code& error, unsigned int nBytes)
{
	if (error)
	{
		if (error == boost::asio::error::connection_reset)
		{
				std::cout << "Connection Closed" << std::endl;
				ClientPtr sender = server->getClientManager()->getClient(receiveEP.address().to_string(), receiveEP.port());
				if (sender != nullptr)
				{
				server->getClientManager()->removeClient(sender->getID());
				}
				else
				{
				std::cerr << "Could not find the address of client when closing connection" << std::endl;
				}
				return;
		}
		std::cerr << "Error occured in UDP Reading: " << error << " - " << error.message() << std::endl;
		return;
	}
	int bytesProcessed = 0;
	while (bytesProcessed < nBytes)
	{
		ClientPtr sender = server->getClientManager()->getClient(receiveEP.address().to_string(), receiveEP.port());
		if (sender != nullptr)
		{
			if (bytesProcessed + HeaderManagerCPP::HSI_IN_SIZE > nBytes)
			{
				std::cerr << "Bytes processed exceeded nBytes" << std::endl;
				break;
			}
			uint16_t headerPackSize = ((HeaderManagerCPP*)hm)->getHSI(receiveData->data() + bytesProcessed);
			bytesProcessed += HeaderManagerCPP::HSI_IN_SIZE;
			if (bytesProcessed + headerPackSize > nBytes)
			{
				std::cerr << "Bytes processed exceeded nBytes" << std::endl;
				break;
			}
			boost::shared_ptr<IPacket> iPack = hm->decryptHeader(receiveData->data() + bytesProcessed, headerPackSize, sender);
			bytesProcessed += headerPackSize;
			uint32_t mainDataSize = iPack->getDataSize();
			if (bytesProcessed + mainDataSize > nBytes)
			{
				std::cerr << "Bytes processed exceeded nBytes" << std::endl;
				break;
			}
			if (mainDataSize > 0)
			{
				iPack->setData(receiveData->begin() + bytesProcessed, receiveData->begin() + bytesProcessed + mainDataSize);
			}
			else
			{
				std::vector <unsigned char> mainData;
				iPack->setData(mainData.begin(), mainData.end());
			}
			bytesProcessed += mainDataSize;
			server->getPacketManager()->process(iPack);
		}
		else
		{
			std::cerr << "Could not match IP of sender with client" << std::endl;
			break;
		}
	}
	read();
}

void UDPManager::send(const udp::endpoint* remoteEP, boost::shared_ptr<std::vector<unsigned char>> sendData)
{
	if (sendData->size() > MAX_UDP_DATA_SIZE)
	{
		std::cerr << "The size of send data was greater than the MAX_UDP_DATA_SIZE" << std::endl;
		throw  std::invalid_argument("Size of sendData exceeded the MAX_UDP_DATA_SIZE");
	}
	sendingMutex.lock();
	if (!sending)
	{
		sending = true;
		sendingMutex.unlock();
		socket->async_send_to(boost::asio::buffer(*sendData, sendData->size()), *remoteEP, boost::bind(&UDPManager::asyncSend, shared_from_this(), boost::asio::placeholders::error, sendData));
	}
	else
	{
		queueSendDataMutex.lock();
		sendingMutex.unlock();
		queueSendData.push(std::make_pair(remoteEP, sendData));
		queueSendDataMutex.unlock();
	}
}

void UDPManager::send(const udp::endpoint* remoteEP, boost::shared_ptr<OPacket> oPack)
{
	boost::shared_ptr<std::vector<unsigned char>> sendData = hm->encryptHeader(oPack);
	if (sendData->size() > MAX_UDP_DATA_SIZE)
	{
		std::cerr << "The size of send data was greater than the MAX_UDP_DATA_SIZE" << std::endl;
		throw  std::invalid_argument("Size of sendData exceeded the MAX_UDP_DATA_SIZE");
	}
	sendingMutex.lock();
	if (!sending)
	{
		sending = true;
		sendingMutex.unlock();
		socket->async_send_to(boost::asio::buffer(*sendData, sendData->size()), *remoteEP, boost::bind(&UDPManager::asyncSend, shared_from_this(), boost::asio::placeholders::error, sendData));
	}
	else
	{
		queueSendDataMutex.lock();
		sendingMutex.unlock();
		queueSendData.push(std::make_pair(remoteEP, sendData));
		queueSendDataMutex.unlock();
	}
}

void UDPManager::asyncSend(const boost::system::error_code& error, boost::shared_ptr<std::vector<unsigned char>> sendData)
{
		sendingMutex.lock();
		sending = false;
		sendingMutex.unlock();
		if (error)
		{
				std::cerr << "Error occured in UDP Sending: " << error.message() << std::endl;
		}
		queueSendDataMutex.lock();
		while (!queueSendData.empty())
		{
				std::cout << "Queue used" << std::endl;
				boost::shared_ptr<std::vector <unsigned char>> sendData = queueSendData.front().second;
				const udp::endpoint* remoteEP = queueSendData.front().first;
				queueSendData.pop();
				socket->send_to(boost::asio::buffer(*sendData, sendData->size()), *remoteEP);
		}
		queueSendDataMutex.unlock();
}

UDPManager::~UDPManager()
{
		if (hm != nullptr) {
				delete hm;
				hm = nullptr;
		}
		if (receiveData != nullptr)
		{
				delete receiveData;
				receiveData = nullptr;
		}
}
