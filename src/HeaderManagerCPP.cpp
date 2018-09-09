#include "HeaderManagerCPP.h"
#include "PackFW.pb.h"
#include <boost/make_shared.hpp>
#include <OPacket.h>
#include <IPacket.h>

HeaderManagerCPP::HeaderManagerCPP(GenIPacketHandler handler)
	:HeaderManager(handler, HSI_IN_SIZE), parseStage(0), activeIPack(nullptr)
{

}

boost::shared_ptr<std::vector<unsigned char>> HeaderManagerCPP::serializePacket(boost::shared_ptr<OPacket> oPack)
{
	ProtobufPackets::PackHeaderOut phOut;
	phOut.set_lockey(oPack->getLocKey());
	phOut.set_sentfromid(oPack->getSenderID());
	phOut.set_datasize(oPack->getData()->size());
	std::string headerPackStr = phOut.SerializeAsString();
	boost::shared_ptr<std::vector<unsigned char>> dataOut = boost::make_shared<std::vector<unsigned char>>(HSI_OUT_SIZE + headerPackStr.size() + oPack->getData()->size());
	if (bEndian) {
		dataOut->at(0) = headerPackStr.size() & 0xff;
		dataOut->at(1) = (headerPackStr.size() >> 8) & 0xff;
	}
	else {
		dataOut->at(1) = headerPackStr.size() & 0xff;
		dataOut->at(0) = (headerPackStr.size() >> 8) & 0xff;
	}
	std::copy(headerPackStr.begin(), headerPackStr.end(), dataOut->begin() + HSI_OUT_SIZE);
	std::copy(oPack->getData()->begin(), oPack->getData()->end(), dataOut->begin() + HSI_OUT_SIZE + headerPackStr.size());
	return dataOut;
}

boost::shared_ptr<IPacket> HeaderManagerCPP::parsePacket(unsigned char * data, std::size_t size, unsigned int & bytesToReceive)
{
	if (parseStage == 0) {
		parseStage++;
		activeIPack = genIPacketHandler();
		bytesToReceive = getHSI(data);
		return nullptr;
	}
	if (parseStage == 1) {
		ProtobufPackets::PackHeaderIn phIn;
		phIn.ParseFromArray(data, size);
		activeIPack->setLocKey(phIn.lockey());
		activeIPack->setServerRead(phIn.serverread());
		std::vector<IDType> sendToIDs(phIn.sendtoids().begin(), phIn.sendtoids().end());
		activeIPack->setSendToClients(sendToIDs);
		if (phIn.datasize() == 0) {
			parseStage = 0;
			activeIPack->setData(boost::make_shared<std::string>());
			bytesToReceive = getInitialReceiveSize();
			auto iPack = activeIPack;
			activeIPack = nullptr;
			return iPack;
		}
		else {
			parseStage++;
			bytesToReceive = phIn.datasize();
			return nullptr;
		}
	}
	if (parseStage == 2) {
		parseStage = 0;
		activeIPack->setData(boost::make_shared<std::string>((char*)data, size));
		boost::shared_ptr<IPacket> iPack = activeIPack;
		activeIPack = nullptr;
		bytesToReceive = getInitialReceiveSize();
		return iPack;
	}
	return nullptr;
}

HeaderManagerCPP::~HeaderManagerCPP()
{
}

uint16_t HeaderManagerCPP::getHSI(unsigned char* data)
{
	if (bEndian)
	{
		return ((data[1] & 0xff) << 8) | (data[0] & 0xff);
	}
	else
	{
		return ((data[0] & 0xff) << 8) | (data[1] & 0xff);
	}
}
