#include "DataStructure.h"

void MonitorVariableTable::clearMonTable() {
    // Clear dynamic monitor data
    for (MonitorFileData& mon : monitors) {
        mon.clear();
    }
    monitors.clear();

    // Clear fixed perf data
    perform.pRatio.clear();
    perform.tRatio.clear();
    perform.efficiency.clear();
    perform.turning.clear();
    perform.qInlet.clear();
    perform.qOutlet.clear();
}