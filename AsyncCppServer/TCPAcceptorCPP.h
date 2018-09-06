#pragma once
#include <TCPAcceptor.h>

class ServerCPP;

class TCPAcceptorCPP : public TCPAcceptor
{
public:
	TCPAcceptorCPP(ServerCPP* server);
	void asyncAcceptHandler(const boost::system::error_code& error) override;
	~TCPAcceptorCPP();
};

