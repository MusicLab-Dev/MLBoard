/**
 * @ Author: Paul Creze
 * @ Description: Network module
 */

#include <iostream>

#include "Scheduler.hpp"

NetworkModule::NetworkModule(void)
{
    std::cout << "NetworkModule constructor" << std::endl;
    
    // defining broadcast address
    struct sockaddr_in usb_broadcast_address;

    usb_broadcast_address.sin_family = AF_INET;
    usb_broadcast_address.sin_port = htons(420);
    usb_broadcast_address.sin_addr.s_addr = inet_addr("169.254.255.255");

    // opening UDP broadcast socket
    int broadcast = 1;
    _usbBroadcastSocket = socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0);
    if (_usbBroadcastSocket < 0) {
        perror("socket");
        abort();
    }
    if (setsockopt(_usbBroadcastSocket, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) == -1) {
        perror("setsockopt");
        abort();
    }
    if (bind(_usbBroadcastSocket, (const struct sockaddr *)&usb_broadcast_address, sizeof(usb_broadcast_address)) < 0) {
        perror("bind");
        abort();
    }
}

NetworkModule::~NetworkModule(void)
{
    std::cout << "NetworkModule destructor" << std::endl;
}

void NetworkModule::tick(Scheduler &scheduler) noexcept
{
    std::cout << "Network module tick function" << std::endl;

    if (scheduler.state() == Scheduler::State::Connected) /* Emmit broadcast packet only is board is connected */
        discovery_emit(scheduler);
    discovery_scan(scheduler);
}

void NetworkModule::discovery_scan(Scheduler &scheduler) noexcept
{
    std::cout << "Network module discovery_scan function" << std::endl;
    // scan for broadcast message

    struct sockaddr_in usb_sender_address;
    int usb_sender_address_len = sizeof(usb_sender_address);

    std::int8_t received_message_buffer[1024];
    std::memset(received_message_buffer, 0, 1024);

    std::vector<Endpoint> usb_endpoints;

    while (1) {

        auto size = recvfrom(_usbBroadcastSocket, received_message_buffer, sizeof(received_message_buffer), MSG_WAITALL, /* MSG_WAITALL wait for the entire message */
            (struct sockaddr *)&usb_sender_address, (socklen_t *)&usb_sender_address_len);

        if (size == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) { /* loop end condition, until read buffer is empty */
            std::cout << "nothing remaining on the socket" << std::endl;
            if (scheduler.state() == Scheduler::State::Connected && usb_endpoints.size() < 2)
                return;
            else if (!usb_endpoints.empty())
                analyze_usb_endpoints(usb_endpoints);
            return;
        }
        if (size == -1) { /* recvfrom error */
            perror("recvfrom");
            return;
        }

        // [DEBUG START]
        char sender_address_string[100];
        std::memset(sender_address_string, 0, 100);
        inet_ntop(AF_INET, &(usb_sender_address.sin_addr), sender_address_string, 100);
        std::cout << "usb discovery packet received from " << sender_address_string;
        // [DEBUG END]

        Endpoint endpoint { 
            usb_sender_address.sin_addr.s_addr, 
            static_cast<Protocol::ConnectionType>(received_message_buffer[0]), 
            static_cast<Protocol::NodeDistance>(received_message_buffer[1])
        };

        usb_endpoints.push_back(endpoint);
    }
}

void NetworkModule::analyze_usb_endpoints(std::vector<Endpoint> &usbEndpoints) noexcept
{
    std::cout << "Netork module analyze_usb_endpoints function" << std::endl;
    
    std::size_t index = 0;
    std::size_t i = 0;

    for (const auto &endpoint : usbEndpoints) {
        if (usbEndpoints.at(index).conn_type != Protocol::ConnectionType::USB && 
                endpoint.conn_type == Protocol::ConnectionType::USB) {
            index = i;
        }
        else if (endpoint.distance < usbEndpoints.at(index).distance) {
            index = i;
        }
        i++;
    }
    // Replace master endpoint if a better has been found
}

void NetworkModule::discovery_emit(Scheduler &scheduler) noexcept
{
    std::cout << "Network module discovery_emit function" << std::endl;
    // send broadcast message

    Protocol::DiscoveryPacket packet;

    packet.conn_type = _connectionType;
    packet.distance = _nodeDistance;

    std::uint8_t discovery_buffer[sizeof(Protocol::DiscoveryPacket)];
    std::memcpy(discovery_buffer, &packet, sizeof(Protocol::DiscoveryPacket));

    struct sockaddr_in usb_broadcast_address;
    usb_broadcast_address.sin_family = AF_INET;
    usb_broadcast_address.sin_port = htons(420);
    usb_broadcast_address.sin_addr.s_addr = inet_addr("169.254.255.255");

    sendto(_usbBroadcastSocket, discovery_buffer, sizeof(Protocol::DiscoveryPacket), 0, (const struct sockaddr *)&usb_broadcast_address, sizeof(usb_broadcast_address));
}

void NetworkModule::process_clients(Scheduler &scheduler) noexcept
{
    std::cout << "Network module process_clients function" << std::endl;
}