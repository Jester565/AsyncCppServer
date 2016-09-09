#pragma once
#include <HeaderManager.h>

class Server;

class HeaderManagerCPP : public HeaderManager
{
public:
	const static uint8_t HSI_OUT_SIZE = 2;
	const static uint8_t HSI_IN_SIZE = 2;
	HeaderManagerCPP(Server* server);

	~HeaderManagerCPP();

protected:
	virtual boost::shared_ptr<std::vector<unsigned char>> encryptHeaderAsBigEndian(boost::shared_ptr<OPacket> pack) override;

	virtual boost::shared_ptr<std::vector<unsigned char>> encryptHeaderToBigEndian(boost::shared_ptr<OPacket> pack) override;

	virtual boost::shared_ptr<IPacket> decryptHeaderAsBigEndian(std::vector<unsigned char>* data, unsigned int size, IDType cID) override;

	virtual boost::shared_ptr<IPacket> decryptHeaderFromBigEndian(std::vector<unsigned char>* data, unsigned int size, IDType cID) override;
};

