#include "HeaderManagerCPP.h"
#include "Packets/PackFW.pb.h"
#include <boost/make_shared.hpp>
#include <OPacket.h>
#include <IPacket.h>

HeaderManagerCPP::HeaderManagerCPP(Server* server)
	:HeaderManager(server)
{

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
	std::string headerPackStr = phOut.SerializeAsString();
	boost::shared_ptr<std::vector<unsigned char>> dataOut = boost::make_shared<std::vector<unsigned char>>(HSI_OUT_SIZE + headerPackStr.size() + oPack->getData()->size());
	dataOut->at(0) = headerPackStr.size() & 0xff;
	dataOut->at(1) = (headerPackStr.size() >> 8) & 0xff;
	std::copy(headerPackStr.begin(), headerPackStr.end(), dataOut->begin() + HSI_IN_SIZE);
	std::copy(oPack->getData()->begin(), oPack->getData()->end(), dataOut->begin() + HSI_IN_SIZE + headerPackStr.size());
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
	std::string headerPackStr = phOut.SerializeAsString();
	boost::shared_ptr<std::vector<unsigned char>> dataOut = boost::make_shared<std::vector<unsigned char>>(HSI_OUT_SIZE + headerPackStr.size() + oPack->getData()->size());
	dataOut->at(1) = headerPackStr.size() & 0xff;
	dataOut->at(0) = (headerPackStr.size() >> 8) & 0xff;
	std::copy(headerPackStr.begin(), headerPackStr.end(), dataOut->begin() + HSI_IN_SIZE);
	std::copy(oPack->getData()->begin(), oPack->getData()->end(), dataOut->begin() + HSI_IN_SIZE + headerPackStr.size());
	return dataOut;
}

boost::shared_ptr<IPacket> HeaderManagerCPP::decryptHeaderAsBigEndian(std::vector<unsigned char>* data, unsigned int size, IDType cID)
{
	boost::shared_ptr<IPacket> iPack = boost::make_shared<IPacket>();
	unsigned int headerPackSize = ((data->at(1) & 0xff) << 8) | (data->at(0) & 0xff);
	ProtobufPackets::PackHeaderIn phIn;
	phIn.ParseFromArray(data->data() + HSI_IN_SIZE, headerPackSize);
	std::vector<IDType> sendToIDs(phIn.sendtoids().begin(), phIn.sendtoids().end());
	unsigned int mainPackDataSize = size - headerPackSize - HSI_IN_SIZE;
	boost::shared_ptr<std::string> mainPackDataStr = boost::make_shared<std::string>(data->begin() + HSI_IN_SIZE + headerPackSize, data->begin() + size);
	setIPack(iPack, const_cast<char*>(phIn.lockey().c_str()), cID, sendToIDs, mainPackDataStr, phIn.serverread());
	return iPack;
}

boost::shared_ptr<IPacket> HeaderManagerCPP::decryptHeaderFromBigEndian(std::vector<unsigned char>* data, unsigned int size, IDType cID)
{
	boost::shared_ptr<IPacket> iPack = boost::make_shared<IPacket>();
	unsigned int headerPackSize = ((data->at(0) & 0xff) << 8) | (data->at(1) & 0xff);
	ProtobufPackets::PackHeaderIn phIn;
	phIn.ParseFromArray(data->data() + HSI_IN_SIZE, headerPackSize);
	std::vector<IDType> sendToIDs(phIn.sendtoids().begin(), phIn.sendtoids().end());
	unsigned int mainPackDataSize = size - headerPackSize - HSI_IN_SIZE;
	boost::shared_ptr<std::string> mainPackDataStr = boost::make_shared<std::string>(data->begin() + HSI_IN_SIZE + headerPackSize, data->begin() + size);
	setIPack(iPack, const_cast<char*>(phIn.lockey().c_str()), cID, sendToIDs, mainPackDataStr, phIn.serverread());
	return iPack;
}
