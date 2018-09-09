#include "ServerCPP.h"
#include "TCPAcceptor.h"
#include "HeaderManagerCPP.h"
#include "ClientCPP.h"
#include "ClientManagerCPP.h"
#include "UDPManager.h"
#include "TCPConnection.h"
#include <ServicePool.h>
#include <PacketManager.h>

ServerCPP::ServerCPP(const boost::asio::ip::tcp& ipVersion)
	:Server(ipVersion), udpManager(nullptr)
{
}

void ServerCPP::createManagers()
{
	Server::createManagers();
	udpManager = boost::make_shared<UDPManager>(this);
}

boost::shared_ptr<HeaderManager> ServerCPP::createHeaderManager()
{
	return boost::make_shared<HeaderManagerCPP>([&]() {
		return createIPacket();
	});
}

void ServerCPP::run(uint16_t port)
{
	Server::run(port);
	udpManager->detach(port);
}

void ServerCPP::run(uint16_t tcpPort, uint16_t udpPort)
{
	Server::run(tcpPort);
	udpManager->detach(udpPort);
}

ClientPtr ServerCPP::createClient(boost::shared_ptr<TCPConnection> tcpConnection, IDType id)
{
	return boost::make_shared<ClientCPP>(id, tcpConnection, packetManager);
}

void ServerCPP::destroyManagers() {
	Server::destroyManagers();
	udpManager = nullptr;
}

void ServerCPP::shutdownIO()
{
	Server::shutdownIO();
	if (udpManager != nullptr) {
			udpManager->close();
	}
}

ServerCPP::~ServerCPP()
{
		
}
