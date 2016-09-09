#include "TCPConnectionCPP.h"
#include "ServerCPP.h"
#include <boost/bind.hpp>
#include <boost/asio/placeholders.hpp>
#include <iostream>


TCPConnectionCPP::TCPConnectionCPP(Server* server, boost::asio::ip::tcp::socket* boundSocket)
	:TCPConnection(server, boundSocket)
{

}

TCPConnectionCPP::~TCPConnectionCPP()
{
}
