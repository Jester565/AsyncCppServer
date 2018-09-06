#pragma once
#include <TCPConnection.h>

class ServerCPP;

class TCPConnectionCPP : public TCPConnection
{
public:
	TCPConnectionCPP(ServerCPP* server, boost::shared_ptr<boost::asio::ip::tcp::socket> boundSocket);

	virtual void read() override;

	~TCPConnectionCPP();

protected:
	void asyncReceiveHandlerCPP(const boost::system::error_code& error, unsigned int bytes);
};
