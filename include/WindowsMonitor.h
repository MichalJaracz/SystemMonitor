#pragma once
#include "ISystemMonitor.h"
#include "windows.h"

class WindowsMonitor : public ISystemMonitor {
private:
    double totalRamMB;
    double usedRamMB;
    double cpuUsage;

    ULONGLONG prevTotalTicks;
    ULONGLONG prevIdleTicks;

    ULONGLONG FileTimeToInt(const FILETIME& ft);

public:
    WindowsMonitor();

    void update() override;
    double getCpuUsage() override;
    double getRamUsage() override;
    double getTotalRam() override;
};
