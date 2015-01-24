#ifndef CDIPOLE_H
#define CDIPOLE_H

#include "../CDevice.h"
#include "../DeviceParameters.h"

class CDipole : public CDevice
{
public:
	explicit CDipole(shared_ptr<const DeviceParameters> params);
    virtual void initMatrices() override;

private:
    double angle;
};

#endif // CDIPOLE_H

