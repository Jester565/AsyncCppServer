#pragma once
#include <ClientManager.h>
#include <boost/asio/ip/udp.hpp>

class ClientManagerCPP : public ClientManager
{
public:
	ClientManagerCPP(Server* server);

	Client* getClient(boost::asio::ip::udp::endpoint* remoteEP);

	void sendUDP(boost::shared_ptr<OPacket> oPack);

	~ClientManagerCPP();
};

