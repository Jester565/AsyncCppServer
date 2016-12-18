#include "HeaderManagerCPP.h"
#include "Packets/PackFW.pb.h"
#include <boost/make_shared.hpp>
#include <OPacket.h>
#include <IPacket.h>

HeaderManagerCPP::HeaderManagerCPP(Server* server)
	:HeaderManager(server)
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

HeaderManagerCPP::~HeaderManagerCPP()
{
}

boost::shared_ptr<std::vector<unsigned char>> HeaderManagerCPP::encryptHeaderAsBigEndian(boost::shared_ptr<OPacket> oPack)
{
	if (oPack->getData() == nullptr)
	{
		throw std::invalid_argument("No Data in the OPacket");
	}
	ProtobufPackets::PackHeaderOut phOut;
	phOut.set_lockey(oPack->getLocKey());
	phOut.set_sentfromid(oPack->getSenderID());
	phOut.set_datasize(oPack->getData()->size());
	std::string headerPackStr = phOut.SerializeAsString();
	boost::shared_ptr<std::vector<unsigned char>> dataOut = boost::make_shared<std::vector<unsigned char>>(HSI_OUT_SIZE + headerPackStr.size() + oPack->getData()->size());
	dataOut->at(0) = headerPackStr.size() & 0xff;
	dataOut->at(1) = (headerPackStr.size() >> 8) & 0xff;
	std::copy(headerPackStr.begin(), headerPackStr.end(), dataOut->begin() + HSI_OUT_SIZE);
	std::copy(oPack->getData()->begin(), oPack->getData()->end(), dataOut->begin() + HSI_OUT_SIZE + headerPackStr.size());
	return dataOut;
}

boost::shared_ptr<std::vector<unsigned char>> HeaderManagerCPP::encryptHeaderToBigEndian(boost::shared_ptr<OPacket> oPack)
{
	if (oPack->getData() == nullptr)
	{
		throw std::invalid_argument("No Data in the OPacket");
	}
	ProtobufPackets::PackHeaderOut phOut; 
	phOut.set_lockey(oPack->getLocKey());
	phOut.set_sentfromid(oPack->getSenderID());
	phOut.set_datasize(oPack->getData()->size());
	std::string headerPackStr = phOut.SerializeAsString();
	boost::shared_ptr<std::vector<unsigned char>> dataOut = boost::make_shared<std::vector<unsigned char>>(HSI_OUT_SIZE + headerPackStr.size() + oPack->getData()->size());
	dataOut->at(1) = headerPackStr.size() & 0xff;
	dataOut->at(0) = (headerPackStr.size() >> 8) & 0xff;
	std::copy(headerPackStr.begin(), headerPackStr.end(), dataOut->begin() + HSI_OUT_SIZE);
	std::copy(oPack->getData()->begin(), oPack->getData()->end(), dataOut->begin() + HSI_OUT_SIZE + headerPackStr.size());
	return dataOut;
}

boost::shared_ptr<IPacket> HeaderManagerCPP::decryptHeaderAsBigEndian(unsigned char* data, unsigned int size, IDType cID)
{
	boost::shared_ptr<IPacket> iPack = boost::make_shared<IPacket>();
	ProtobufPackets::PackHeaderIn phIn;
	phIn.ParseFromArray(data, size);
	std::vector<IDType> sendToIDs(phIn.sendtoids().begin(), phIn.sendtoids().end());
	uint32_t mainDataSize = phIn.datasize();
	//boost::shared_ptr<std::string> mainPackDataStr = boost::make_shared<std::string>(mainDataSize);
	setIPack(iPack, const_cast<char*>(phIn.lockey().c_str()), cID, sendToIDs, nullptr, phIn.serverread());
	iPack->setDataSize(mainDataSize);
	return iPack;
}

boost::shared_ptr<IPacket> HeaderManagerCPP::decryptHeaderFromBigEndian(unsigned char* data, unsigned int size, IDType cID)
{
	boost::shared_ptr<IPacket> iPack = boost::make_shared<IPacket>();
	ProtobufPackets::PackHeaderIn phIn;
	phIn.ParseFromArray(data, size);
	std::vector<IDType> sendToIDs(phIn.sendtoids().begin(), phIn.sendtoids().end());
	uint32_t mainDataSize = phIn.datasize();
	//boost::shared_ptr<std::string> mainPackDataStr = boost::make_shared<std::string>(data->begin() + HSI_IN_SIZE + headerPackSize, data->begin() + size);
	setIPack(iPack, const_cast<char*>(phIn.lockey().c_str()), cID, sendToIDs, nullptr, phIn.serverread());
	iPack->setDataSize(mainDataSize);
	return iPack;
}
