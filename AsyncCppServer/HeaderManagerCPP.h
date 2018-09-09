#pragma once
#include <HeaderManager.h>

class Server;

class HeaderManagerCPP : public HeaderManager
{
public:
	const static uint8_t HSI_OUT_SIZE = 2;
	const static uint8_t HSI_IN_SIZE = 2;
	HeaderManagerCPP(GenIPacketHandler handler);

	//Given an oPacket, output bytes representing the entire packet (this will call encryptHeaderAsBigEndian or littleEndian depending on your machine)
	virtual boost::shared_ptr<std::vector<unsigned char>> serializePacket(boost::shared_ptr<OPacket> pack);

	//Given bytes, output an IPacket (this will call decryptHeaderAsLittleEndian or decryptHeaderAsBigEndian depending on your machine)
	virtual boost::shared_ptr<IPacket> parsePacket(unsigned char* data, std::size_t size, unsigned int& bytesToReceive);

	~HeaderManagerCPP();

protected:
	uint16_t getHSI(unsigned char* receiveData);

	boost::shared_ptr<IPacket> activeIPack;
	unsigned int parseStage;
};

