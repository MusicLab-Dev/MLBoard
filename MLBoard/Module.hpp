/**
 * @ Author: Paul Creze
 * @ Description: Module
 */

#pragma once

#include "Types.hpp"

/** @brief Abstraction of a board module */
class alignas_cacheline_eighth Module
{
public:
    /** @brief Get the discovery rate duration */
    [[nodiscard]] Chrono::Duration discoveryRate(void) const noexcept { return _discoveryRate; }

    /** @brief Set the discovery rate duration */
    void setDiscoveryRate(const Chrono::Duration discoveryRate) noexcept { _discoveryRate = discoveryRate; }


    /** @brief Get the last discovery timestamp */
    [[nodiscard]] Chrono::Timestamp lastDiscoveryTimestamp(void) const noexcept { return _lastDiscoveryTimestamp; }

    /** @brief Set the last discovery timestamp */
    void setLastDiscoveryTimestamp(const Chrono::Timestamp lastDiscoveryTimestamp) noexcept { _lastDiscoveryTimestamp = lastDiscoveryTimestamp; }

private:
    Chrono::Duration _discoveryRate { 1000000000 };
    Chrono::Timestamp _lastDiscoveryTimestamp { std::chrono::steady_clock::duration::zero() };
};

static_assert_fit_eighth(Module);
