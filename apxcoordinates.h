#ifndef APXCOORDINATES_H
#define APXCOORDINATES_H

#include "Fact/Fact.h"
#include <memory>

class ApxCoordinates: public Fact
{
public:
    ApxCoordinates(Fact *parent = nullptr);

private:
    Fact *m_yawPosVar;
    Fact *m_pitchPosVar;
    Fact *m_targetLatVar;
    Fact *m_targetLonVar;
    Fact *m_apply;
    QTimer m_calculationTimer;

    void calculate();

private slots:
    void onApplyTriggered();
};

#endif // APXCOORDINATES_H
