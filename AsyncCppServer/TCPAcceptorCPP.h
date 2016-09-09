#pragma once
#include <TCPAcceptor.h>

class TCPAcceptorCPP : public TCPAcceptor
{
public:
	TCPAcceptorCPP(Server* server);
	void asyncAcceptHandler(const boost::system::error_code& error) override;
	~TCPAcceptorCPP();
};

