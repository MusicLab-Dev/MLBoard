/*
** EPITECH PROJECT, 2020
** board_implementation
** File description:
** HardwareModule
*/

#pragma once

#include <vector> // the use of vector will be replaced by Core::FlatVector

#include "Module.hpp"
#include "Protocol.hpp"

class HardwareModule : Module
{
    public:
        HardwareModule(void);
        ~HardwareModule(void);

        void tick(Scheduler &scheduler);
        void discoverer(Scheduler &scheduler);

    private:
        std::vector<Protocol::Control> _controls;
        std::uint32_t _multiplexers;
};