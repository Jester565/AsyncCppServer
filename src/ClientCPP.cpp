#include "ClientCPP.h"
#include <TCPConnection.h>

using namespace boost::asio::ip;

ClientCPP::ClientCPP(boost::shared_ptr<TCPConnection> tcpConnection, Server* server, IDType id)
	:Client(tcpConnection, server, id), udpRemoteEP(nullptr)
{
	udpRemoteEP = new udp::endpoint(tcpConnection->getSocket()->remote_endpoint().address(), tcpConnection->getSocket()->remote_endpoint().port());
}

ClientCPP::~ClientCPP()
{
	delete udpRemoteEP;
	udpRemoteEP = nullptr;
}
