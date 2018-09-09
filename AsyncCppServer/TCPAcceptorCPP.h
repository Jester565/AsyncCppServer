#pragma once
#include <TCPAcceptor.h>

class ServerCPP;

class TCPAcceptorCPP : public TCPAcceptor
{
public:
	TCPAcceptorCPP(boost::shared_ptr<ServicePool> servicePool, boost::asio::ip::tcp& tcpVersion, ConnectionHandler handler);
	void asyncAcceptHandler(const boost::system::error_code& error) override;
	~TCPAcceptorCPP();
};

