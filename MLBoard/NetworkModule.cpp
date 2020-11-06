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
    _usbBroadcastSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (_usbBroadcastSocket < 0) {
        perror("Discovery: socket: ");
        abort();
    }
    if (setsockopt(_usbBroadcastSocket, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) == -1) {
        perror("Discovery: setsockopt: ");
        abort();
    }
    if (bind(_usbBroadcastSocket, (const struct sockaddr *)&usb_broadcast_address, sizeof(usb_broadcast_address)) < 0) {
        perror("Discovery: bind: ");
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

    while (1) {

        auto size = recvfrom(_usbBroadcastSocket, received_message_buffer, sizeof(received_message_buffer), MSG_WAITALL, 
            (struct sockaddr *)&usb_sender_address, (socklen_t *)&usb_sender_address_len);

        if (size == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
            std::cout << "Nothing to read on the socket" << std::endl;
            return;
        }
        if (size == -1) {
            perror("Discovery: recvfrom: ");
            return;
        }

        // Convert sender address structure to string
        char sender_address_string[100];
        std::memset(sender_address_string, 0, 100);
        inet_ntop(AF_INET, &(usb_sender_address.sin_addr), sender_address_string, 100);

        // Fill the DiscoveryPacket with the received message
        Protocol::DiscoveryPacket received_packet;
        received_packet.link_type = static_cast<Protocol::ConnectionType>(received_message_buffer[0]);

        std::cout << "Connection type value: " << static_cast<int>(received_packet.link_type) << std::endl;
    }
}

void NetworkModule::discovery_emit(Scheduler &scheduler) noexcept
{
    std::cout << "Network module discovery_emit function" << std::endl;
    // send broadcast message

    Protocol::DiscoveryPacket packet;

    packet.link_type = _connectionType;
    packet.distance = _nodeDistance;

    std::uint8_t discovery_buffer[sizeof(Protocol::DiscoveryPacket)];
    std::memcpy(discovery_buffer, &packet, sizeof(Protocol::DiscoveryPacket));

    send(_usbBroadcastSocket, discovery_buffer, sizeof(Protocol::DiscoveryPacket), 0);
}

void NetworkModule::process_clients(Scheduler &scheduler) noexcept
{
    std::cout << "Network module process_clients function" << std::endl;
}