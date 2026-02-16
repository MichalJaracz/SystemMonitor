#include "WindowsMonitor.h"

WindowsMonitor::WindowsMonitor() {
   totalRamMB = 0;
   usedRamMB = 0;
   cpuUsage = 0; 
}

ULONGLONG WindowsMonitor::FileTimeToInt(const FILETIME& ft) {
    ULARGE_INTEGER uli;
    uli.LowPart = ft.dwLowDateTime;
    uli.HighPart = ft.dwHighDateTime;
    return uli.QuadPart;
}   

void WindowsMonitor::update() {
    // get RAM data
    MEMORYSTATUSEX meminfo;
    meminfo.dwLength = sizeof(MEMORYSTATUSEX);

    // address to structure
    GlobalMemoryStatusEx(&meminfo);

    totalRamMB = meminfo.ullTotalPhys / (1024.0 * 1024.0);

    DWORDLONG usedPhysMem = meminfo.ullTotalPhys - meminfo.ullAvailPhys;
    usedRamMB = usedPhysMem / (1024.0 * 1024.0);

    // get CPU data
    FILETIME idleTime, kernelTime, userTime;

    if (GetSystemTimes(&idleTime, &kernelTime, &userTime)) {
        ULONGLONG idleTicks = FileTimeToInt(idleTime);
        ULONGLONG kernelTicks = FileTimeToInt(kernelTime);
        ULONGLONG userTicks = FileTimeToInt(userTime);
    
        ULONGLONG totalTicks = kernelTicks + userTicks;
        
        ULONGLONG totalTicksSinceLast = totalTicks - prevTotalTicks;
        ULONGLONG idleTicksSinceLast = idleTicks - prevIdleTicks;
    
        //warn devide 0
        if (totalTicksSinceLast > 0 && prevTotalTicks > 0) {
            ULONGLONG workingTicks = totalTicksSinceLast - idleTicksSinceLast;
            cpuUsage = (workingTicks * 100.0) / totalTicksSinceLast;
        }

        prevTotalTicks = totalTicks;
        prevIdleTicks = idleTicks;
    }



}

double WindowsMonitor::getCpuUsage() { return cpuUsage; };
double WindowsMonitor::getTotalRam() { return totalRamMB; };
double WindowsMonitor::getRamUsage() { return usedRamMB; };