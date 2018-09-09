#pragma once
#include <Client.h>
#include <boost/asio/ip/udp.hpp>
class ClientCPP : public Client
{
public:
	ClientCPP(IDType cID, boost::shared_ptr<TCPConnection> tcpConnection, boost::shared_ptr<PacketManager> packetManager, ClientDisconnectHandler handler = nullptr);
	const boost::asio::ip::udp::endpoint* getUDPRemoteEP() const
	{
		return udpRemoteEP;
	}
	virtual ~ClientCPP();

protected:
	boost::asio::ip::udp::endpoint* udpRemoteEP;
};
