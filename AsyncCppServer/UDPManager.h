#pragma once
#include <Macros.h>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/thread/mutex.hpp>
#include <queue>
#include <vector>

class OPacket;
class ServerCPP;
class HeaderManager;

class UDPManager : public boost::enable_shared_from_this<UDPManager>
{
public:
	static const unsigned int MAX_UDP_DATA_SIZE = 1024;
	UDPManager(ServerCPP* server);

	void detach(uint16_t port);
	void send(const boost::asio::ip::udp::endpoint* remoteEP, boost::shared_ptr<std::vector<unsigned char>> sendData);
	void send(const boost::asio::ip::udp::endpoint* remoteEP, boost::shared_ptr<OPacket> oPack);
	void read();
	void close();

	~UDPManager();

private:
	void asyncReceive(const boost::system::error_code& error, unsigned int nBytes);
	void asyncSend(const boost::system::error_code& error, boost::shared_ptr<std::vector<unsigned char>> sendData);
	std::vector<unsigned char>* receiveData;
	std::queue <std::pair <const boost::asio::ip::udp::endpoint*, boost::shared_ptr<std::vector <unsigned char>>>> queueSendData;
	boost::asio::ip::udp::endpoint receiveEP;
	boost::shared_ptr<boost::asio::ip::udp::socket> socket;
	HeaderManager* hm;
	ServerCPP* server;
	boost::mutex sendingMutex;
	boost::mutex queueSendDataMutex;
	bool sending;
	int errorMode;
};
