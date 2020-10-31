/*
** EPITECH PROJECT, 2020
** board_implementation
** File description:
** Scheduler
*/

#pragma once

#include "Types.hpp"

#include "HardwareModule.hpp"
#include "NetworkModule.hpp"

class Scheduler
{
    enum State : bool {
        Disconnected,
        Connected
    };

    public:
        Scheduler(void);
        ~Scheduler(void);

        void run(void);
        void tick(void);

        const State state(void);
        bool setState(const State state);

        HardwareModule &hardwareModule(void);
        NetworkModule &networkModule(void);

    private:
        State _state = State::Disconnected;

        Timestamp _timestamp;
        Duration _tickRate;

        char _padding[20];

        HardwareModule _hardwareModule;
        NetworkModule _networkModule;
};