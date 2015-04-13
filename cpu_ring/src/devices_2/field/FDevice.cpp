#include "FDevice.h"
#include "field_map/DeviceFieldMap.h"
#include "field_map/ExtendedDeviceFieldMap.h"
#include <devices_2/common/DeviceParameters.h>

FDevice::FDevice(const DeviceParameters& params)
: Device(params)
{
    fieldMapName = params.mapFileName_;
    fieldMap = make_shared<ExtendedDeviceFieldMap>(geometry, fieldMapName, &curr_step);
}

bool FDevice::spotFieldDevice(const FDevice* prev, const FDevice* next)
{
    auto extendedFieldMap = dynamic_cast<ExtendedDeviceFieldMap*>(fieldMap.get());
    if (prev != nullptr)
        extendedFieldMap->setPrevMap(this->geometry, prev->geometry, prev->fieldMapName);
    if (next != nullptr)
        extendedFieldMap->setNextMap(this->geometry, next->geometry, next->fieldMapName);

    if (extendedFieldMap->prev_device_map == nullptr &&
        extendedFieldMap->next_device_map == nullptr)
    {
        auto newFieldMap = new DeviceFieldMap(extendedFieldMap);
        fieldMap.reset();
        fieldMap = shared_ptr<DeviceFieldMap>(newFieldMap);

        if (fieldMap->device_map == nullptr)
            return false;
    }
    return true;
}

void FDevice::affectParticle(Particle& p) const
{
    fieldMap->updateParticle(p);
}