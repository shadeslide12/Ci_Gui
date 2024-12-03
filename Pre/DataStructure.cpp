#include "DataStructure.h"

void MonitorVariableTable::clearMonTable() {
    inlet.pTotal.clear();
    inlet.tTotal.clear();
    inlet.vAxial.clear();
    inlet.vTheta.clear();
    inlet.pStatic.clear();
    inlet.mDot.clear();

    outlet.pTotal.clear();
    outlet.tTotal.clear();
    outlet.vAxial.clear();
    outlet.vTheta.clear();
    outlet.pStatic.clear();
    outlet.mDot.clear();

    perform.pRatio.clear();
    perform.tRatio.clear();
    perform.efficiency.clear();
    perform.turning.clear();
    perform.qInlet.clear();
    perform.qOutlet.clear();
}