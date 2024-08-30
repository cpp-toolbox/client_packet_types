#include "client_packet_types.hpp"
#include <stdexcept>

PacketData parse_packet(ENetPacket *packet) {
    if (packet->dataLength == sizeof(ClientID)) {
        spdlog::info("Received unique id packet", packet->dataLength);
        ClientID unique_id_packet;
        std::memcpy(&unique_id_packet, packet->data, sizeof(ClientID));
        return unique_id_packet;
    } else if (true) {
        // need a better way of checking type above.
        spdlog::info("Received game update");

        size_t game_update_size = packet->dataLength;
        size_t num_entries = game_update_size / sizeof(NetworkedCharacterData);

        // Ensure the packet size is a multiple of the size of NetworkedCharacterData, because it's a vector of these
        if (game_update_size % sizeof(NetworkedCharacterData) != 0) {
            spdlog::get("network")->error("Received packet size is not a multiple of NetworkedCharacterData size");
            throw std::runtime_error("Received packet size is not a multiple of NetworkedCharacterData size");
        }

        // Create a vector to hold the reconstructed game data
        std::vector<NetworkedCharacterData> game_update(num_entries);

        // Copy the raw data from the packet into the vector
        std::memcpy(game_update.data(), packet->data, game_update_size);
        return game_update;
    } else {
        spdlog::warn("Received unknown packet type with size: {}", packet->dataLength);
        // Handle unexpected packet sizes
        return {};
    }
}
