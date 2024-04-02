#pragma once

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/bit_map.hpp>
#include <godot_cpp/classes/ref.hpp>

using namespace godot;

class MapUtils : public Resource {
    GDCLASS(MapUtils, Resource);

protected:
    static void _bind_methods();

public:
    MapUtils();
    ~MapUtils();

    static Array process_map(Ref<BitMap> map);
};