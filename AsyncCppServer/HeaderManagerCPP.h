#pragma once
#include <HeaderManager.h>

class Server;

class HeaderManagerCPP : public HeaderManager
{
public:
	const static uint8_t HSI_OUT_SIZE = 2;
	const static uint8_t HSI_IN_SIZE = 2;
	HeaderManagerCPP(Server* server);

	uint16_t getHSI(unsigned char* receiveData);

	~HeaderManagerCPP();

protected:
	virtual boost::shared_ptr<std::vector<unsigned char>> encryptHeaderAsBigEndian(boost::shared_ptr<OPacket> pack) override;

	virtual boost::shared_ptr<std::vector<unsigned char>> encryptHeaderToBigEndian(boost::shared_ptr<OPacket> pack) override;

	virtual boost::shared_ptr<IPacket> decryptHeaderAsBigEndian(unsigned char* data, unsigned int size, ClientPtr client) override;

	virtual boost::shared_ptr<IPacket> decryptHeaderFromBigEndian(unsigned char* data, unsigned int size, ClientPtr client) override;
};

