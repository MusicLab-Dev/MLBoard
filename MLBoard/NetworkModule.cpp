/**
 * @ Author: Paul Creze
 * @ Description: Network module
 */

#include <iostream>
#include <cstring>
#include <cerrno>

#include "Scheduler.hpp"

NetworkModule::NetworkModule(void)
{
    std::cout << "NetworkModule constructor" << std::endl;
    
    // defining broadcast address
    sockaddr_in usbBroadcastAddress {
        .sin_family = AF_INET,
        .sin_port = htons(420),
        .sin_addr = {
            .s_addr = inet_addr("169.254.255.255")
        }
    };

    // opening UDP broadcast socket
    int broadcast = 1;
    _usbBroadcastSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (_usbBroadcastSocket < 0)
        throw std::runtime_error(strerror(errno));
    if (setsockopt(_usbBroadcastSocket, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0)
        throw std::runtime_error(strerror(errno));
    if (bind(_usbBroadcastSocket, (const struct sockaddr *)&usbBroadcastAddress, sizeof(usbBroadcastAddress)) < 0)
        throw std::runtime_error(strerror(errno));
}

NetworkModule::~NetworkModule(void)
{
    std::cout << "NetworkModule destructor" << std::endl;
}

void NetworkModule::tick(Scheduler &scheduler) noexcept
{
    if (scheduler.state() != Scheduler::State::Connected)
        return;
    std::cout << "Network module tick function" << std::endl;
    processClients(scheduler);
    // send hardware module data
}

void NetworkModule::discover(Scheduler &scheduler) noexcept
{
    if (scheduler.state() == Scheduler::State::Connected) /* Emmit broadcast packet only if board is connected */
        discoveryEmit(scheduler);
    discoveryScan(scheduler);
}

void NetworkModule::analyzeUsbEndpoints(const std::vector<Endpoint> &usbEndpoints) noexcept
{
    std::cout << "Netork module analyzeUsbEndpoints function" << std::endl;

    std::size_t index = 0;
    std::size_t i = 0;

    for (const auto &endpoint : usbEndpoints) {
        if (usbEndpoints.at(index).connectionType != Protocol::ConnectionType::USB &&
                endpoint.connectionType == Protocol::ConnectionType::USB) {
            index = i;
        } else if (endpoint.distance < usbEndpoints.at(index).distance) {
            index = i;
        }
        i++;
    }
    // Replace master endpoint if a better has been found
}

void NetworkModule::discoveryScan(Scheduler &scheduler)
{
    std::cout << "Network module discoveryScan function" << std::endl;

    sockaddr_in usbSenderAddress;
    int usbSenderAddressLength = sizeof(usbSenderAddress);
    std::vector<Endpoint> usbEndpoints;
    Protocol::DiscoveryPacket packet;

    while (1) {
        const auto size = ::recvfrom(
            _usbBroadcastSocket,
            &packet, 
            sizeof(Protocol::DiscoveryPacket),
            MSG_WAITALL | MSG_DONTWAIT, /* MSG_WAITALL wait for the entire message */
            reinterpret_cast<sockaddr *>(&usbSenderAddress), 
            reinterpret_cast<socklen_t *>(&usbSenderAddressLength)
        );

        if (size == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) { /* loop end condition, until read buffer is empty */
            std::cout << "nothing remaining on the socket" << std::endl;
            if (scheduler.state() != Scheduler::State::Connected && !usbEndpoints.empty())
                analyzeUsbEndpoints(usbEndpoints);
            return;
        } else if (size == -1) { /* recvfrom error */
            throw std::runtime_error(strerror(errno));
            return;
        }

        if (packet.magicKey != Protocol::DiscoveryPacketMagicKey) // Discard unkown packets
            continue;

        // Also check if this is our own discovery packet !!

        // [DEBUG START]
        char senderAddressString[100];
        std::memset(senderAddressString, 0, 100);
        ::inet_ntop(AF_INET, &(usbSenderAddress.sin_addr), senderAddressString, 100);
        std::cout << "usb discovery packet received from " << senderAddressString << std::endl;
        // [DEBUG END]

        Endpoint endpoint {
            .address = usbSenderAddress.sin_addr.s_addr,
            .connectionType = packet.connectionType, 
            .distance = packet.distance
        };
        usbEndpoints.push_back(endpoint);
    }
}

void NetworkModule::discoveryEmit(Scheduler &scheduler) noexcept
{
    std::cout << "Network module discoveryEmit function" << std::endl;

    Protocol::DiscoveryPacket packet {
        .connectionType = _connectionType,
        .distance = _nodeDistance
    };
    sockaddr_in usbBroadcastAddress {
        .sin_family = AF_INET,
        .sin_port = htons(420),
        .sin_addr = {
            .s_addr = inet_addr("169.254.255.255")
        }
    };
    ::sendto(
        _usbBroadcastSocket, 
        &packet, 
        sizeof(Protocol::DiscoveryPacket), 
        0, 
        reinterpret_cast<const sockaddr *>(&usbBroadcastAddress), sizeof(usbBroadcastAddress)
    );
}

void NetworkModule::processClients(Scheduler &scheduler) noexcept
{
    std::cout << "Network module processClients function" << std::endl;
}