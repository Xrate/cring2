#ifndef CSEXTUPOLE_H
#define CSEXTUPOLE_H

#include "../CDevice.h"
#include "../DeviceParameters.h"

class CSextupole : public CDevice
{
public:
	CSextupole(const string& name, const DeviceParameters& params);
	virtual void initMatrices() override;
private:
	double force;
};


#endif // CSEXTUPOLE_H
