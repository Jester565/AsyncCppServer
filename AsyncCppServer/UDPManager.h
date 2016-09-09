#pragma once
#include <Macros.h>
#include <vector>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio/ip/udp.hpp>

class OPacket;
class Server;
class HeaderManager;

class UDPManager : public boost::enable_shared_from_this<UDPManager>
{
public:
	static const unsigned int MAX_UDP_DATA_SIZE = 1024;
	UDPManager(Server* server);

	void detach(uint16_t port);
	void send(const boost::asio::ip::udp::endpoint* remoteEP, boost::shared_ptr<std::vector<unsigned char>> sendData);
	void send(const boost::asio::ip::udp::endpoint* remoteEP, boost::shared_ptr<OPacket> oPack);
	void read();

	~UDPManager();

private:
	void asyncReceive(const boost::system::error_code& error, unsigned int nBytes);
	void asyncSend(const boost::system::error_code& error, boost::shared_ptr<std::vector<unsigned char>> sendData);
	std::vector<unsigned char>* receiveData;
	boost::asio::ip::udp::endpoint receiveEP;
	boost::asio::ip::udp::socket* socket;
	HeaderManager* hm;
	Server* server;
	int errorMode;
};
