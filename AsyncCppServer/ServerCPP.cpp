#include "ServerCPP.h"
#include "TCPAcceptorCPP.h"
#include "HeaderManagerCPP.h"
#include "ClientCPP.h"
#include "ClientManagerCPP.h"
#include "UDPManager.h"
#include <ServicePool.h>
#include <PacketManager.h>

ServerCPP::ServerCPP(const boost::asio::ip::tcp& ipVersion)
	:Server(ipVersion), udpManager(nullptr)
{
}

void ServerCPP::createManagers()
{
	servicePool = new ServicePool();
	pm = new PacketManager(this);
	cm = new ClientManagerCPP(this);
}

HeaderManager* ServerCPP::createHeaderManager()
{
	return new HeaderManagerCPP(this);
}

void ServerCPP::run(uint16_t port)
{
	tcpAcceptor = boost::make_shared<TCPAcceptorCPP>(this);
	tcpAcceptor->detach(port);
	udpManager = boost::make_shared<UDPManager>(this);
	udpManager->detach(port);
	servicePool->run();
}

void ServerCPP::run(uint16_t tcpPort, uint16_t udpPort)
{
		tcpAcceptor = boost::make_shared<TCPAcceptorCPP>(this);
		tcpAcceptor->detach(tcpPort);
		udpManager = boost::make_shared<UDPManager>(this);
		udpManager->detach(udpPort);
		servicePool->run();
}

Client* ServerCPP::createClient(boost::shared_ptr<TCPConnection> tcpConnection, IDType id)
{
	return new ClientCPP(tcpConnection, this, id);
}

void ServerCPP::destroyManagers() {
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
