#include "TCPAcceptorCPP.h"
#include "TCPConnectionCPP.h"
#include "ServerCPP.h"
#include <ClientManager.h>
#include <boost/make_shared.hpp>
#include <iostream>

TCPAcceptorCPP::TCPAcceptorCPP(ServerCPP* server)
	:TCPAcceptor(server)
{
}

void TCPAcceptorCPP::asyncAcceptHandler(const boost::system::error_code& error)
{
	std::cout << "Accepted" << std::endl;
	if (error)
	{
		std::cerr << "Error occured in TCPAcceptor: " << error.message() << std::endl;
	}
	boost::shared_ptr<TCPConnection> tcpConnection = boost::make_shared<TCPConnectionCPP>((ServerCPP*)server, tempSocket);
	tcpConnection->start();
	server->getClientManager()->addClient(tcpConnection);
	runAccept();
}

TCPAcceptorCPP::~TCPAcceptorCPP()
{
}
