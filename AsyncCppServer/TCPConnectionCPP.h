#pragma once
#include <TCPConnection.h>

class TCPConnectionCPP : public TCPConnection
{
public:
	TCPConnectionCPP(Server* server, boost::asio::ip::tcp::socket* boundSocket);

	~TCPConnectionCPP();
};
