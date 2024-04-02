#include "map_utils.hpp"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/bit_map.hpp>
#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/ref.hpp>
#include "trace_skeleton.cpp"

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
    UtilityFunctions::print("Processing map");

    // Convert image into byte buffer that can be read by opencv.
    Ref<Image> temp_image = map->convert_to_image();
    PackedByteArray buffer = temp_image->get_data();

    skeleton_tracer_t* T = new skeleton_tracer_t();
    T->W = 1024;
    T->H = 1024;

    T->im = (unsigned char*)malloc(sizeof(unsigned char)*T->W*T->H);
    memcpy(T->im, buffer.ptrw(), buffer.size());

    skeleton_tracer_t::polyline_t* p =  (skeleton_tracer_t::polyline_t*)T->trace_skeleton(0, 0, T->W, T->H, 0);

    // https://github.com/LingDong-/skeleton-tracing/blob/master/cpp/example2.cpp
    int count = 0;
    skeleton_tracer_t::polyline_t* it = p; //iterator
    while(it){
        skeleton_tracer_t::point_t* jt = it->head;
        while(jt){
            UtilityFunctions::print(jt->x, " ", jt->y);
         count++;
        jt = jt->next;
        }
        it = it->next;
    }

    unsigned char first = buffer.ptr()[0];
    unsigned char last = buffer.ptr()[1024*1024];
    UtilityFunctions::print("polyline count: ", count, " first ", first, " last ", last);
    
    // TODO cleanup.
}
