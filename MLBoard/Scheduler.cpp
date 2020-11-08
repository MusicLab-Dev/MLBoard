/**
 * @ Author: Paul Creze
 * @ Description: Scheduler
 */

#include <iostream>

#include "Scheduler.hpp"

Scheduler::Scheduler(std::vector<std::string> &&arguments)
{

}

Scheduler::~Scheduler(void)
{

}

void Scheduler::run(void)
{
    constexpr auto ProcessDiscovery = [](Scheduler &scheduler, auto &mod, const auto currentTime) {

        const auto elapsedTime = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - mod.lastDiscoveryTimestamp()).count();

        if (elapsedTime >= mod.discoveryRate()) {
            mod.setLastDiscoveryTimestamp(currentTime);
            mod.discover(scheduler);
        }
    };

    std::cout << "MLBoard running" << std::endl;

    std::chrono::steady_clock::time_point prevTime = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point currentTime;

    while (1) {
        currentTime = std::chrono::steady_clock::now();

        // Process tick of each module if needed
        auto elapsedTime = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - prevTime).count();
        if (elapsedTime > _tickRate) {
            tick();
            prevTime = currentTime;
        }

        // Process discovery of each module if needed
        ProcessDiscovery(*this, _hardwareModule, currentTime);
        ProcessDiscovery(*this, _networkModule, currentTime);
    }
}