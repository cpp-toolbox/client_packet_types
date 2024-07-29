#include "client_packet_types.hpp"

PacketData parse_packet(ENetPacket *packet) {
    if (packet->dataLength == sizeof(UniqueIDPacket)) {
        spdlog::warn("Received unique id packet", packet->dataLength);
        UniqueIDPacket unique_id_packet;
        std::memcpy(&unique_id_packet, packet->data, sizeof(UniqueIDPacket));
        return unique_id_packet;
    } else if (packet->dataLength == sizeof(NetworkedCharacterData)) {
        spdlog::warn("Received networked character data", packet->dataLength);
        NetworkedCharacterData networked_character_data;
        std::memcpy(&networked_character_data, packet->data, sizeof(NetworkedCharacterData));
        return networked_character_data;
    } else {
        spdlog::warn("Received unknown packet type with size: {}", packet->dataLength);
        // Handle unexpected packet sizes
        return {};
    }
}
