#include "TCPAcceptorCPP.h"
#include "TCPConnectionCPP.h"
#include <Server.h>
#include <ClientManager.h>
#include <boost/make_shared.hpp>
#include <iostream>

TCPAcceptorCPP::TCPAcceptorCPP(Server* server)
	:TCPAcceptor(server)
{
}

void TCPAcceptorCPP::asyncAcceptHandler(const boost::system::error_code& error)
{
	std::cout << "Accepted" << std::endl;
	if (error)
	{
		std::cerr << "Error occured in TCPAcceptor: " << error.message() << std::endl;
		switch (errorMode)
		{
		case THROW_ON_ERROR:
			throw error;
			break;
		case RETURN_ON_ERROR:
			return;
			break;
		case RECALL_ON_ERROR:
			runAccept();
			return;
		};
	}
	boost::shared_ptr<TCPConnection> tcpConnection = boost::make_shared<TCPConnectionCPP>(server, tempSocket);
	tcpConnection->start();
	server->getClientManager()->addClient(tcpConnection);
	runAccept();
}

TCPAcceptorCPP::~TCPAcceptorCPP()
{
}
