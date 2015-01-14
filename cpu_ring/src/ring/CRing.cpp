﻿#include "CRing.h"

CRing* CRing::instance = nullptr;

CRing * CRing::getInstance(RingConf config)
{
	if (!instance)
		instance = new CRing(config);
	return instance;
}

CRing * CRing::getInstance()
{
	if (instance)
		return instance;
	throw exception("CRing: Try to access null CRing");
}

void CRing::setConf(const RingConf& config)
{
	auto deviceMap = config.getDevicesMap();
	for (string name : config.getStructure())
	{
		auto deviceParams = deviceMap.at(name);
		devices.push_back(CDevice::createDevice(deviceParams));
	}
	numDevices = devices.size();
}

const vector<CDevice*>& CRing::getDevices() const
{
	return devices;
}

void CRing::affectBeam(CBeam* beam)
{
	for (CDevice* device : devices)
	{
		device->affectBeam(beam);
	}
}

CRing::CRing(const RingConf& config)
{
	setConf(config);
}