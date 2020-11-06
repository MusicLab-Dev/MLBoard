/**
 * @ Author: Paul Creze
 * @ Description: Network module
 */

#pragma once

#include <cstring>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "MLCore/Vector.hpp"
#include "MLProtocol/Protocol.hpp"

#include "Types.hpp"
#include "Module.hpp"

/** @brief Board module responsible of network communication */
class alignas(CacheLineSize) NetworkModule : public Module
{
public:
    /** @brief Size of the ring buffer cache */
    static constexpr std::uint32_t RingBufferSize { 4096 };

    /** @brief Data of a connected client */
    struct alignas(CacheLineSize / 2) Client
    {
        ~Client(void) noexcept = default;

        Protocol::BoardID id;
        Net::Socket socket;
        Core::Vector<Client, std::uint16_t> clients;
    };

    /** @brief Construct the network module */
    NetworkModule(void);

    /** @brief Destruct the network module */
    ~NetworkModule(void);


    /** @brief Tick called at tick rate */
    void tick(Scheduler &scheduler) noexcept;

    /** @brief Discovery functions */
    void discovery_scan(Scheduler &scheduler) noexcept;
    void discovery_emit(Scheduler &scheduler) noexcept;

    /** @brief Listen to connected boards in client mode */
    void process_clients(Scheduler &scheduler) noexcept;

    /** @brief Tries to add data to the ring buffer */
    [[nodiscard]] bool write(const std::uint8_t *data, std::size_t size) noexcept;

private:
    Protocol::BoardID _boardID { 0u };
    alignas(2) Protocol::NodeDistance _nodeDistance { 0u };
    alignas(2) Protocol::ConnectionType _connectionType { Protocol::ConnectionType::None };

    Net::Socket _usbBroadcastSocket { -1 };
    Net::Socket _masterSocket { -1 };

    Core::Vector<Client, std::uint16_t> _clients;
    Core::Vector<std::uint8_t, std::uint16_t> _buffer; // To replace by ringbuffer
};

static_assert(sizeof(NetworkModule) == CacheLineSize, "NetworkModule must be the size of cacheline");
static_assert(alignof(NetworkModule) == CacheLineSize, "NetworkModule must be aligned to cacheline size");