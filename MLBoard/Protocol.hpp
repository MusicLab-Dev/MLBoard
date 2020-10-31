/*
** EPITECH PROJECT, 2020
** board_implementation
** File description:
** Protocol
*/

#pragma once

#include "Types.hpp"

namespace Protocol
{
    using NodeDistance = std::uint8_t;
    using BoardID = std::uint32_t;

    enum ConnectionType : std::uint8_t {
        None,
        USB,
        WIFI
    };

    struct Control {
        enum Type : std::uint8_t {
            None,
            Button,
            Potentiometer
        };

        Type type;
        std::uint8_t value1;
        std::uint8_t value2;
        std::uint8_t value3;
    };
};