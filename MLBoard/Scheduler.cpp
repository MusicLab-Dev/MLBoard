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

void Scheduler::run(Scheduler &instance)
{
    std::cout << "MLBoard running" << std::endl;

    std::chrono::steady_clock::time_point prev_time = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point current_time;

    while (1) {
        current_time = std::chrono::steady_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(current_time - prev_time).count();

        if (elapsed_time > _tickRate) {
            tick(instance);
            prev_time = current_time;
        }
    }
}

void Scheduler::tick(Scheduler &instance) noexcept
{
    std::cout << "Scheduler tick function" << std::endl;

    _networkModule.tick(instance);
}