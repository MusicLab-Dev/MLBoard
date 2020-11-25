/**
 * @ Author: Paul Creze
 * @ Description: Network module
 */

#pragma once

#include <cstring>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>

#include <MLCore/Vector.hpp>
#include <MLProtocol/Protocol.hpp>

#include "Types.hpp"
#include "Module.hpp"

/** @brief Board module responsible of network communication */
class alignas_cacheline NetworkModule : public Module
{
public:
    struct Endpoint
    {
        Net::IP address { 0u };
        Protocol::ConnectionType connectionType { Protocol::ConnectionType::None };
        Protocol::NodeDistance distance { 0u };
    };

    /** @brief Size of the ring buffer cache */
    static constexpr std::uint32_t RingBufferSize { 4096 };

    /** @brief Data of a connected client */
    struct alignas_half_cacheline Client
    {
        ~Client(void) noexcept = default;

        Protocol::BoardID id { 0u };
        Net::Socket socket { 0 };
        Core::Vector<Client, std::uint16_t> clients {};
    };

    static_assert_fit_half_cacheline(Client);


    /** @brief Construct the network module */
    NetworkModule(void);

    /** @brief Destruct the network module */
    ~NetworkModule(void);


    /** @brief Tick called at tick rate */
    void tick(Scheduler &scheduler) noexcept;

    /** @brief Start discovery */
    void discover(Scheduler &scheduler) noexcept;

    /** @brief Tries to add data to the ring buffer */
    [[nodiscard]] bool write(const std::uint8_t *data, std::size_t size) noexcept;

private:
    Protocol::BoardID _boardID { 0u };
    Protocol::ConnectionType _connectionType { Protocol::ConnectionType::None };
    Protocol::NodeDistance _nodeDistance { 0u };

    Net::Socket _usbBroadcastSocket { -1 };
    Net::Socket _masterSocket { -1 };
    Core::Vector<Client, std::uint16_t> _clients;
    Core::Vector<std::uint8_t, std::uint16_t> _buffer; // To replace by ringbuffer

    /** @brief Listen to connected boards that are in client mode */
    void processClients(Scheduler &scheduler) noexcept;

    /** @brief Discovery function that read and process near board message */
    void discoveryScan(Scheduler &scheduler);

    /** @brief Discovery function that emit on usb broadcast address */
    void discoveryEmit(Scheduler &scheduler) noexcept;

    /** @brief Analyse every available usb endpoints */
    void analyzeUsbEndpoints(const std::vector<Endpoint> &usbEndpoints, Scheduler &scheduler) noexcept;

    /** @brief Init a new connection to a new master (server) endpoint */
    void initNewMasterConnection(const Endpoint &masterEndpoint, Scheduler &scheduler) noexcept;
};

static_assert_fit_cacheline(NetworkModule);