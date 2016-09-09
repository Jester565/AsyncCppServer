#include "UDPManager.h"
#include <HeaderManager.h>
#include <boost/asio/buffer.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/bind.hpp>
#include <ServicePool.h>
#include <ClientManager.h>
#include <Client.h>
#include <Server.h>
#include <iostream>
using namespace boost::asio::ip;

UDPManager::UDPManager(Server* server)
	:server(server), errorMode(DEFAULT_ERROR_MODE), socket(nullptr), receiveData(nullptr)
{
	hm = server->createHeaderManager();
}

void UDPManager::detach(uint16_t port)
{
	try
	{
		if (server->getIPVersion() == boost::asio::ip::tcp::v6())
		{
			socket = new udp::socket(server->getServicePool()->getNextIOService(), udp::endpoint(boost::asio::ip::udp::v6(), port));
		}
		else
		{
			socket = new udp::socket(server->getServicePool()->getNextIOService(), udp::endpoint(boost::asio::ip::udp::v4(), port));
		}
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
	socket->async_receive_from(boost::asio::buffer(receiveData, MAX_UDP_DATA_SIZE), receiveEP, boost::bind(&UDPManager::asyncReceive, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void UDPManager::asyncReceive(const boost::system::error_code& error, unsigned int nBytes)
{
	if (error)
	{
		if (error == boost::asio::error::connection_reset)
		{
			std::cout << "Connection Closed" << std::endl;
			Client* sender = server->getClientManager()->getClient(receiveEP.address().to_string(), receiveEP.port());
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
		switch (errorMode)
		{
		case THROW_ON_ERROR:
			throw error;
			break;
		case RETURN_ON_ERROR:
			return;
		case RECALL_ON_ERROR:
			read();
			return;
		};
	}
	Client* sender = server->getClientManager()->getClient(receiveEP.address().to_string(), receiveEP.port());
	if (sender != nullptr)
	{
		hm->decryptHeader(receiveData, nBytes, sender->getID());
	}
	else
	{
		std::cerr << "Could not match IP of sender with client" << std::endl;
	}
	read();
}

void UDPManager::send(const udp::endpoint* remoteEP, boost::shared_ptr<std::vector<unsigned char>> sendData)
{
	socket->async_send_to(boost::asio::buffer(*sendData, sendData->size()), *remoteEP, boost::bind(&UDPManager::asyncSend, shared_from_this(), boost::asio::placeholders::error, sendData));
}

void UDPManager::send(const udp::endpoint* remoteEP, boost::shared_ptr<OPacket> oPack)
{
	std::cout << "UDPRemoteEP: " << remoteEP->address().to_string() << " : " << remoteEP->port() << " : " << remoteEP->address().is_v6() << std::endl;
	std::cout << "UDPLocalEP: " << socket->local_endpoint().address().to_string() << " : " << socket->local_endpoint().port() << " : " << socket->local_endpoint().address().is_v6() << std::endl;
	boost::shared_ptr<std::vector<unsigned char>> sendData = hm->encryptHeader(oPack);
	socket->async_send_to(boost::asio::buffer(*sendData, sendData->size()), *remoteEP, boost::bind(&UDPManager::asyncSend, shared_from_this(), boost::asio::placeholders::error, sendData));
}

void UDPManager::asyncSend(const boost::system::error_code& error, boost::shared_ptr<std::vector<unsigned char>> sendData)
{
	if (error)
	{
		std::cerr << "Error occured in UDP Sending: " << error.message() << std::endl;
		switch (errorMode)
		{
		case THROW_ON_ERROR:
			throw error;
			break;
		case RETURN_ON_ERROR:
			return;
			break;
		case RECALL_ON_ERROR:
			return;
		};
	}
}

UDPManager::~UDPManager()
{
	delete hm;
	hm = nullptr;
	if (socket != nullptr)
	{
		boost::system::error_code ec;
		socket->shutdown(boost::asio::ip::udp::socket::shutdown_both, ec);
		if (ec)
		{
			std::cerr << "Error when closing UDP Socket: " << ec.message() << std::endl;
		}
		socket->close();
		delete socket;
		socket = nullptr;
	}
	if (receiveData != nullptr)
	{
		delete receiveData;
		receiveData = nullptr;
	}
}
