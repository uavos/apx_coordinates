#ifndef APXCOORDINATESPLUGIN_H
#define APXCOORDINATESPLUGIN_H

#include "ApxPluginInterface.h"

class ApxCoordinatesPlugin: public ApxPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.uavos.gcs.ApxPluginInterface/1.0")
    Q_INTERFACES(ApxPluginInterface)
public:
    ApxCoordinatesPlugin();
    QObject *createControl();
};

#endif // APXCOORDINATESPLUGIN_H
