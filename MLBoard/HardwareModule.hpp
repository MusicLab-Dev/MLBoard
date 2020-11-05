/**
 * @ Author: Paul Creze
 * @ Description: Hardware module
 */

#pragma once

#include "MLCore/FlatVector.hpp"
#include "MLProtocol/Protocol.hpp"

#include "Module.hpp"

class Scheduler;

/** @brief Board module responsible of hardware communication */
class alignas(CacheLineSize) HardwareModule : public Module
{
public:
    /** @brief Construct the hardware module */
    HardwareModule(void) noexcept;

    /** @brief Destruct the hardware module */
    ~HardwareModule(void) noexcept;


    /** @brief Tick called at tick rate */
    void tick(Scheduler &scheduler) noexcept;

    /** @brief Discover called at discover rate */
    void discover(Scheduler &scheduler) noexcept;

private:
    Core::FlatVector<Protocol::Control> _controls {};
    std::uint32_t _multiplexers { 0 };
};

static_assert(sizeof(HardwareModule) == CacheLineSize, "HardwareModule must take CacheLineSize bytes");
static_assert(alignof(HardwareModule) == CacheLineSize, "HardwareModule must be aligned to CacheLineSize bytes");