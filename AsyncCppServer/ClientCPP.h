#pragma once
#include <Client.h>
#include <boost/asio/ip/udp.hpp>
class ClientCPP : public Client
{
public:
	ClientCPP(boost::shared_ptr<TCPConnection> tcpConnection, Server* server, IDType cID);
	const boost::asio::ip::udp::endpoint* getUDPRemoteEP() const
	{
		return udpRemoteEP;
	}
	virtual ~ClientCPP();

protected:
	boost::asio::ip::udp::endpoint* udpRemoteEP;
};
