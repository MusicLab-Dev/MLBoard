/**
 * @ Author: Paul Creze
 * @ Description: Network module
 */

#pragma once

#include <MLBoard/FlatVector.hpp>
#include <MLProtocol/Protocol.hpp>

#include "Types.hpp"
#include "Module.hpp"

namespace Core // TO DELETE LATER
{
    template<typename Type>
    using RingBuffer = std::vector<Type>;
}

/** @brief Board module responsible of network communication */
class alignas(32) NetworkModule : public Module
{
public:
    /** @brief Size of the ring buffer cache */
    static constexpr std::uint32_t RingBufferSize { 4096 };

    /** @brief Data of a connected client */
    struct alignas(16) Client
    {
        Protocol::BoardID id;
        Net::Socket socket;
        Core::FlatVector<Client> clients;
    };

    /** @brief Construct the network module */
    NetworkModule(void);

    /** @brief Destruct the network module */
    ~NetworkModule(void);


    /** @brief Tick called at tick rate */
    void tick(Scheduler &scheduler) noexcept;

    /** @brief Discover called at discover rate */
    void discover(Scheduler &scheduler) noexcept;


    /** @brief Tries to add data to the ring buffer */
    [[nodiscard]] bool write(const std::uint8_t *data, std::size_t size) noexcept;

private:
    Protocol::BoardID _boardID { 0u };
    alignas(2) Protocol::NodeDistance _nodeDistance { 0u };
    alignas(2) Protocol::ConnectionType _connectionType { Protocol::ConnectionType::None };

    Net::Socket _usbBroadcastSocket { -1 };
    Net::Socket _masterSocket { -1 };

    Core::FlatVector<Client> _clients;
    Core::RingBuffer<std::uint8_t, RingBufferSize> _buffer;
};

static_assert(sizeof(NetworkModule) == 32u, "NetworkModule must take 32 bytes");
static_assert(alignas(NetworkModule) == 32u, "NetworkModule must be aligned to 32 bytes");