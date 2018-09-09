#pragma once
#include <ClientManager.h>
#include <boost/asio/ip/udp.hpp>

class UDPManager;

class ClientManagerCPP : public ClientManager
{
public:
	ClientManagerCPP(boost::shared_ptr<UDPManager> udpManager);

	ClientPtr getClient(boost::asio::ip::udp::endpoint* remoteEP);

	void sendUDP(boost::shared_ptr<OPacket> oPack);

	void sendToAllExceptUDP(boost::shared_ptr<OPacket> oPack, IDType excludeID);

	~ClientManagerCPP();

protected:
	boost::shared_ptr<UDPManager> udpManager;
};

