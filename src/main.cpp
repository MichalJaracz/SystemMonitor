#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include "WindowsMonitor.h"


int main() {
    std::cout << "Uruchamianie monitora systemu...\n";
    
    std::unique_ptr<ISystemMonitor> monitor = std::make_unique<WindowsMonitor>();

    while (true) {
        monitor->update();

        std::cout << "CPU: " << monitor->getCpuUsage() << "%\n";
        std::cout << "RAM: " << monitor->getRamUsage() << "MB / "
            << monitor->getTotalRam() << "MB\n";


        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}