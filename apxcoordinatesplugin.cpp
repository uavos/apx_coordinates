#include "apxcoordinatesplugin.h"

#include "apxcoordinates.h"

ApxCoordinatesPlugin::ApxCoordinatesPlugin()
{
}

QObject *ApxCoordinatesPlugin::createControl()
{
    return new ApxCoordinates();
}
