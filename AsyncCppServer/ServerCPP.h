#pragma once
#include <boost/shared_ptr.hpp>
#include <Server.h>

class PacketManager;
class UDPManager;

class ServerCPP : public Server
{
public:
	ServerCPP(const boost::asio::ip::tcp& ipVersion);

	virtual void createManagers() override;
	virtual void run(uint16_t port) override;
	virtual void run(uint16_t tcpPort, uint16_t udpPort);

	virtual boost::shared_ptr<HeaderManager> createHeaderManager() override;
	virtual ClientPtr createClient(boost::shared_ptr<TCPConnection> tcpConnection, IDType id) override;
	virtual boost::shared_ptr<UDPManager> getUDPManager()
	{
		return udpManager;
	}

	virtual void destroyManagers() override;

	virtual void shutdownIO() override;

	virtual ~ServerCPP();

protected:
	boost::shared_ptr<UDPManager> udpManager;
};
