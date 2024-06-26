#pragma once

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/bit_map.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/a_star2d.hpp>

using namespace godot;

class MapUtils : public Resource {
    GDCLASS(MapUtils, Resource);

protected:
    static void _bind_methods();

public:
    MapUtils();
    ~MapUtils();

    static Array process_map(Ref<Image> map);
    static Ref<AStar2D> convert_to_astar(Array polylines);
};