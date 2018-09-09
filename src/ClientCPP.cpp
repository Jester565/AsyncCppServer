#include "ClientCPP.h"
#include <TCPConnection.h>

using namespace boost::asio::ip;

ClientCPP::ClientCPP(IDType cID, boost::shared_ptr<TCPConnection> tcpConnection, boost::shared_ptr<PacketManager> packetManager, ClientDisconnectHandler handler)
	:Client(cID, tcpConnection, packetManager, handler), udpRemoteEP(nullptr)
{
	udpRemoteEP = new udp::endpoint(tcpConnection->getSocket()->remote_endpoint().address(), tcpConnection->getSocket()->remote_endpoint().port());
}

ClientCPP::~ClientCPP()
{
	delete udpRemoteEP;
	udpRemoteEP = nullptr;
}
