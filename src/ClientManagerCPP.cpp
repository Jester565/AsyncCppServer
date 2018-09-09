#include "ClientManagerCPP.h"
#include "ClientCPP.h"
#include "ServerCPP.h"
#include "UDPManager.h"
#include <TCPConnection.h>
#include <OPacket.h>
#include <iostream>

ClientManagerCPP::ClientManagerCPP(boost::shared_ptr<UDPManager> udpManager)
	:udpManager(udpManager)
{
}

ClientPtr ClientManagerCPP::getClient(boost::asio::ip::udp::endpoint * remoteEP)
{
	for (auto it = clients.begin(); it != clients.end(); it++)
	{
		if (boost::static_pointer_cast<ClientCPP>(it->second)->getUDPRemoteEP() == remoteEP)
		{
			return it->second;
		}
	}
	return nullptr;
}

void ClientManagerCPP::sendUDP(boost::shared_ptr<OPacket> oPack)
{
	for (int i = 0; i < oPack->getSendToIDs().size(); i++)
	{
		auto sendToClient = boost::static_pointer_cast<ClientCPP>(ClientManager::getClient(oPack->getSendToIDs().at(i)));
		udpManager->send(sendToClient->getUDPRemoteEP(), oPack);
	}
}

void ClientManagerCPP::sendToAllExceptUDP(boost::shared_ptr<OPacket> oPack, IDType excludeID)
{
	boost::shared_lock <boost::shared_mutex> lock(clientMapMutex);
	for (auto iter = clients.begin(); iter != clients.end(); iter++)
	{
		if (iter->first != excludeID)
		{
			send(oPack, iter->second);
		}
	}
}

ClientManagerCPP::~ClientManagerCPP()
{
}
