#include "TCPConnectionCPP.h"
#include "ServerCPP.h"
#include "ClientManagerCPP.h"
#include "HeaderManagerCPP.h"
#include "Client.h"
#include <IPacket.h>
#include <PacketManager.h>
#include <boost/bind.hpp>
#include <boost/asio/placeholders.hpp>
#include <iostream>


TCPConnectionCPP::TCPConnectionCPP(ServerCPP* server, boost::shared_ptr<boost::asio::ip::tcp::socket> boundSocket)
	:TCPConnection(server, boundSocket)
{

}

void TCPConnectionCPP::read()
{
	if (alive)
	{
		if (receiveStorage == nullptr)
		{
			receiveStorage = new std::vector<unsigned char>();
			receiveStorage->resize(HeaderManagerCPP::HSI_IN_SIZE);
		}
		socket->async_read_some(boost::asio::buffer(*receiveStorage, HeaderManagerCPP::HSI_IN_SIZE), boost::bind(&TCPConnectionCPP::asyncReceiveHandlerCPP, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	}
}

TCPConnectionCPP::~TCPConnectionCPP()
{

}


void TCPConnectionCPP::asyncReceiveHandlerCPP(const boost::system::error_code& error, unsigned int nBytes)
{
	if (error)
	{
		if (error == boost::asio::error::connection_reset)
		{
			std::cout << "Connection Closed" << std::endl;
			server->getClientManager()->removeClient(sender->getID());
			return;
		}
		std::cerr << "Error occured in TCP Reading: " << error << " - " << error.message() << std::endl;
		return;
	}
		uint16_t headerPackSize = ((HeaderManagerCPP*)hm)->getHSI(receiveStorage->data());
		std::vector <unsigned char> headerPackData(headerPackSize);
		socket->read_some(boost::asio::buffer(headerPackData, headerPackSize));
		boost::shared_ptr<IPacket> iPack = hm->decryptHeader(headerPackData.data(), headerPackSize, sender);
		uint32_t mainDataSize = iPack->getDataSize();
		if (mainDataSize > 0)
		{
				std::vector <unsigned char> mainData(mainDataSize);
				socket->read_some(boost::asio::buffer(mainData, mainDataSize));
				iPack->setData(mainData.begin(), mainData.end());
		}
		else
		{
				std::vector <unsigned char> mainData;
				iPack->setData(mainData.begin(), mainData.end());
		}
		if (iPack != nullptr)
		{
				((ServerCPP*)server)->getPacketManager()->process(iPack);
		}
	read(); 
}
