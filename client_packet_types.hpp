#ifndef PACKET_TYPES_HPP
#define PACKET_TYPES_HPP

#include <variant>
#include <enet/enet.h>
#include <cstring>
#include <spdlog/spdlog.h>
#include "../networked_character_data/networked_character_data.hpp"

using UniqueIDPacket = uint64_t;
using PacketData = std::variant<UniqueIDPacket, NetworkedCharacterData>;

PacketData parse_packet(ENetPacket *packet);

#endif // PACKET_TYPES_HPP