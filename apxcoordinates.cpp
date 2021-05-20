#include "apxcoordinates.h"

#include <assert.h>
#include "Dictionary/DictMandala.h"
#include "Vehicles/Vehicles.h"
#include "Vehicles/Vehicle.h"
#include <QMessageBox>
#include <QQuaternion>

ApxCoordinates::ApxCoordinates(Fact *parent):
    Fact(parent, "apx_coordinates", "GSG140 coordinates", "GSG140 target coordinates", Group),
    m_yawPosVar(new Fact(this, "yaw_pos_var", "Gimbal yaw position var", "", Text)),
    m_pitchPosVar(new Fact(this, "pitch_pos_var", "Gimbal pitch position var", "", Text)),
    m_targetLatVar(new Fact(this, "target_lat_var", "Target latitude var", "", Text)),
    m_targetLonVar(new Fact(this, "target_lon_var", "Target longitude var", "", Text)),
    m_apply(new Fact(this, "apply", "Apply", "", Action))
{
    m_yawPosVar->setValue("radar_dy");
    m_pitchPosVar->setValue("radar_dz");
    m_targetLatVar->setValue("VM1");
    m_targetLonVar->setValue("VM2");

    m_calculationTimer.setInterval(10);
    m_calculationTimer.setSingleShot(false);
    m_calculationTimer.start();

    connect(m_apply, &Fact::triggered, this, &ApxCoordinates::onApplyTriggered);
    connect(&m_calculationTimer, &QTimer::timeout, this, &ApxCoordinates::calculate);
}

void ApxCoordinates::calculate()
{
    auto vehicle = Vehicles::instance()->current();

    if(vehicle)
    {
        auto mandala = vehicle->f_mandala;
        auto camYawVar = vehicle->f_mandala->factByName(m_yawPosVar->value().toString());
        auto camPitchVar = vehicle->f_mandala->factByName(m_pitchPosVar->value().toString());
        auto targetLatVar = vehicle->f_mandala->factByName(m_targetLatVar->value().toString());
        auto targetLonVar = vehicle->f_mandala->factByName(m_targetLonVar->value().toString());
        if(camYawVar && camPitchVar && targetLatVar && targetLonVar)
        {
            const float UAV_YAW = mandala->valueByName("yaw").toFloat();
            const float UAV_PITCH = mandala->valueByName("pitch").toFloat();
            const float UAV_ROLL = mandala->valueByName("roll").toFloat();
            const float UAV_LAT = mandala->valueByName("gps_lat").toFloat();
            const float UAV_LON = mandala->valueByName("gps_lon").toFloat();
            const float CAM_YAW = camYawVar->value().toFloat();
            const float CAM_PITCH = camPitchVar->value().toFloat();

            const float ALTITUDE = mandala->valueByName("altitude").toFloat();

            QVector3D v(1.0, 0.0, 0.0);

            QQuaternion uavyq = QQuaternion::fromEulerAngles(0, 0, CAM_YAW/* + UAV_YAW*/);

            QQuaternion camrq = QQuaternion::fromEulerAngles(UAV_ROLL, 0, 0);
            QQuaternion campq = QQuaternion::fromEulerAngles(0, CAM_PITCH/* + UAV_PITCH*/, 0);

            QQuaternion globalq = uavyq * camrq * campq;

            QVector3D rotated = globalq.rotatedVector(v);

            if(rotated.z() > 0)
            {
                const double lat_meters = rotated.x() / rotated.z() * ALTITUDE;
                const double lon_meters = rotated.y() / rotated.z() * ALTITUDE;

                const double gps_point_lat = UAV_LAT + (lat_meters / 6371000.0) * (180.0 / M_PI);
                const double gps_point_lon = UAV_LON +
                        (180.0 / M_PI) * lon_meters / (6371000.0 * qCos(qDegreesToRadians(UAV_LAT)));

                targetLatVar->setValueLocal(gps_point_lat);
                targetLonVar->setValueLocal(gps_point_lon);
            }
            else
            {
                targetLatVar->setValueLocal(0);
                targetLonVar->setValueLocal(0);
            }
        }
    }
}

void ApxCoordinates::onApplyTriggered()
{
    DictMandala m;
    if(!m.names.contains(m_yawPosVar->value().toString()) ||
            !m.names.contains(m_pitchPosVar->value().toString()) ||
            !m.names.contains(m_targetLatVar->value().toString()) ||
            !m.names.contains(m_targetLonVar->value().toString()))
    {
        QMessageBox::warning(nullptr, "Warning", "Unknown var, please check it", QMessageBox::Ok);
    }
}
