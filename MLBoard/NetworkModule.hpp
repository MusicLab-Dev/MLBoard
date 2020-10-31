/*
** EPITECH PROJECT, 2020
** board_implementation
** File description:
** NetworkModule
*/

#pragma once

#include <vector> // the use of vector will be replaced by Core::FlatVector & Core::RingBuffer

#include "Types.hpp"

#include "Module.hpp"
#include "Protocol.hpp"

class NetworkModule : Module
{
    struct Client {
        Protocol::BoardID id;
        Socket socket;
        std::vector<Client> clients;

        char padding[4];
    };

    public:
        NetworkModule(void);
        ~NetworkModule(void);

        void tick(Scheduler &scheduler);
        void discover(Scheduler &scheduler);

        void write(const std::uint8_t *data, std::size_t size);

    private:
        Protocol::BoardID _boardID = 0;
        Protocol::NodeDistance _nodeDistance = 0;
        Protocol::ConnectionType _connectionType = Protocol::ConnectionType::None;

        Socket _usbBroadcastSocket = -1;
        Socket _masterSocket = -1;

        char _padding[2];

        std::vector<Client> _clients;
        std::vector<std::uint8_t> _buffer;
};