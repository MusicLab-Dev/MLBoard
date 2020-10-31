/**
 * @ Author: Paul Creze
 * @ Description: Module
 */

#pragma once

#include "Types.hpp"

/** @brief Abstraction of a board module */
class alignas(8) Module
{
public:
    /** @brief Get the discovery rate duration */
    [[nodiscard]] Chrono::Duration discoveryRate(void) noexcept { return _discoveryRate; }

    /** @brief Set the discovery rate duration */
    void setDiscoveryRate(const Chrono::Duration discoveryRate) noexcept { _discoveryRate = discoveryRate; }


    /** @brief Get the last discovery timestamp */
    [[nodiscard]] Chrono::Timestamp lastDiscoveryTimestamp(void) noexcept { return _lastDiscoveryTimestamp; }

    /** @brief Set the last discovery timestamp */
    void setLastDiscoveryTimestamp(const Chrono::Timestamp lastDiscoveryTimestamp) noexcept { _lastDiscoveryTimestamp = lastDiscoveryTimestamp; }

private:
    Chrono::Duration _discoveryRate { 0u };
    Chrono::Timestamp _lastDiscoveryTimestamp { 0u };
};

static_assert(sizeof(Module) == 8u, "Module must take 8 bytes");
static_assert(alignas(Module) == 8u, "Module must be aligned to 8 bytes");