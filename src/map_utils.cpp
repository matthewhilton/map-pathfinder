#include "map_utils.hpp"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/bit_map.hpp>
#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/a_star2d.hpp>
#include "trace_skeleton.cpp"

using namespace godot;

void MapUtils::_bind_methods()
{
    ClassDB::bind_static_method("MapUtils", D_METHOD("process_map", "map"), &MapUtils::process_map);
    ClassDB::bind_static_method("MapUtils", D_METHOD("convert_to_astar", "polylines"), &MapUtils::convert_to_astar);
}

MapUtils::MapUtils()
{
}

MapUtils::~MapUtils()
{
}

Ref<AStar2D> MapUtils::convert_to_astar(Array polylines) {
    Ref<AStar2D> temp;
    temp.instantiate();

    int id_count = 0;

    for(int i = 0; i < polylines.size(); i++) {
        Array line_points = polylines[i];
        
        for(int j = 0; j < line_points.size(); j++) {
            // Add point, and connect to previous.
            Vector2i map_point = line_points[j];
            temp->add_point(id_count, Vector2(map_point));
            
            if (j != 0) {
                temp->connect_points(id_count - 1, id_count);
            }

            id_count++;
        }
    }

    // TODO find any ends are near each other, and connect them as well.

    return temp;
}

Array MapUtils::process_map(Ref<BitMap> map) {
    UtilityFunctions::print("Processing map");
    skeleton_tracer_t* T = new skeleton_tracer_t();
    T->W = map->get_size().x;
    T->H = map->get_size().y;

    T->im = (unsigned char*)malloc(sizeof(unsigned char)*T->W*T->H);

    // memcpy does not seem to work, but reading the bits directly does.
    for(int x = 0; x < T->W; x++){
        for(int y = 0; y < T->H; y++) {
            T->im[y * T->W + x] = map->get_bit(x,y);
        }
    }
    T->thinning_zs();

    skeleton_tracer_t::polyline_t* p =  (skeleton_tracer_t::polyline_t*)T->trace_skeleton(0, 0, T->W, T->H, 0);

    // Based off https://github.com/LingDong-/skeleton-tracing/blob/master/cpp/example2.cpp
    Array polyline_array = Array();
    skeleton_tracer_t::polyline_t* it = p;
    while(it){
        skeleton_tracer_t::point_t* jt = it->head;
        Array points = Array();
        while(jt){
            Vector2 point = Vector2(jt->x, jt->y);
            points.append(point);
            jt = jt->next;
        }
        polyline_array.append(points);
        it = it->next;
    }

    // Cleanup.
    std::free(T->im);
    T->destroy_polylines(p);
    T->destroy_rects();

    return polyline_array;
}
