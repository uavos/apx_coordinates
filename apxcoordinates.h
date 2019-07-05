#ifndef APXCOORDINATES_H
#define APXCOORDINATES_H

#include "Fact/Fact.h"
#include <memory>

class ApxCoordinates: public Fact
{
public:
    ApxCoordinates(Fact *parent = nullptr);

private:
    std::shared_ptr<Fact> m_yawPosVar;
    std::shared_ptr<Fact> m_pitchPosVar;
    std::shared_ptr<Fact> m_targetLatVar;
    std::shared_ptr<Fact> m_targetLonVar;
    std::shared_ptr<FactAction> m_apply;
    QTimer m_calculationTimer;

    void calculate();

private slots:
    void onApplyTriggered();
};

#endif // APXCOORDINATES_H
