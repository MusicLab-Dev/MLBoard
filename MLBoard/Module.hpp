/*
** EPITECH PROJECT, 2020
** board_implementation
** File description:
** Module
*/

#pragma once

#include "Types.hpp"

class Module
{
    public:
        Module(void);
        ~Module(void);

        Duration discoveryRate(void);
        Timestamp lastDiscoveryTimestamp(void);

        void setDiscoveryRate(const Duration duration);
        void setLastDiscoveryTimestamp(const Timestamp timestamp);

    private:
        Duration _discoveryRate;
        Timestamp _lastDiscoveryTimestamp;
};