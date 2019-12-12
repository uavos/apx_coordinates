#ifndef APXCOORDINATESPLUGIN_H
#define APXCOORDINATESPLUGIN_H

#include "App/PluginInterface.h"

class ApxCoordinatesPlugin: public PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.uavos.gcs.PluginInterface/1.0")
    Q_INTERFACES(PluginInterface)
public:
    ApxCoordinatesPlugin();
    QObject *createControl();
};

#endif // APXCOORDINATESPLUGIN_H
