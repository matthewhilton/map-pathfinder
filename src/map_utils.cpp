#include "map_utils.hpp"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/bit_map.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/ref.hpp>

using namespace godot;

void MapUtils::_bind_methods()
{
    ClassDB::bind_static_method("MapUtils", D_METHOD("process_map"), &MapUtils::process_map);
}

MapUtils::MapUtils()
{
}

MapUtils::~MapUtils()
{
}

void MapUtils::process_map(Ref<BitMap> map) {
    UtilityFunctions::print("TODO process map");
}
