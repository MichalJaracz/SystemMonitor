#pragma once

class ISystemMonitor
{
public:
    virtual ~ISystemMonitor() = default;

    virtual void update() = 0;

    virtual double getCpuUsage() = 0;
    virtual double getRamUsage() = 0;
    virtual double getTotalRam() = 0;

};

