/**
 * @ Author: Paul Creze
 * @ Description: Scheduler
 */

#pragma once

#include <vector>
#include <string>
#include <chrono>

#include "Types.hpp"

#include "HardwareModule.hpp"
#include "NetworkModule.hpp"

/** @brief The scheduler is responsible to coordinate each module in time */
class alignas(CacheLineSize * 4) Scheduler
{
public:
    /** @brief Global connection state */
    enum class State : bool {
        Disconnected,
        Connected
    };

    /** @brief Construct the scheduler */
    Scheduler(std::vector<std::string> &&arguments);
    
    /** @brief Destruct the scheduler */
    ~Scheduler(void);


    /** @brief Run scheduler in blocking mode */
    void run(Scheduler &instance);

    /** @brief Call tick on each module */
    void tick(Scheduler &instance) noexcept;


    /** @brief Get the connection state */
    [[nodiscard]] const State state(void) noexcept { return _state; }

    /** @brief Change the connection state of the scheduler */
    void setState(const State state) noexcept { _state = state; }


    /** @brief Get the internal hardware module */
    [[nodiscard]] HardwareModule &hardwareModule(void) noexcept { return _hardwareModule; }

    /** @brief Get the internal network module */
    [[nodiscard]] NetworkModule &networkModule(void) noexcept { return _networkModule; }

private:
    struct alignas(CacheLineSize)
    {
        State _state { State::Disconnected };
        Chrono::Timestamp _timestamp { 0u };
        Chrono::Duration _tickRate { 1000000000 };
    };

    HardwareModule _hardwareModule;
    NetworkModule _networkModule;
};

static_assert(sizeof(Scheduler) == CacheLineSize * 4, "Scheduler must take 4 cachelines");
static_assert(alignof(Scheduler) == CacheLineSize * 4, "Scheduler must be aligned to 4 cachelins");

#include "HardwareModule.ipp"
#include "NetworkModule.ipp"
#include "Scheduler.ipp"