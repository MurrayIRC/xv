#ifndef TERRAIN_H
#define TERRAIN_H

#include "sprite.h"

#include <raylib.h>
#include <stdio.h>

typedef struct terrain_t {
    unsigned int id;

    Vector2 world_pos;
    int grid_level;
    int grid_x;
    int grid_y;

    sprite_t* sprite;
    animated_sprite_t* anim_sprite;
    Vector2 sprite_offset;
    Vector2 sprite_scale;
} terrain_t;

terrain_t* create_terrain(void) { return (terrain_t*)malloc(sizeof(terrain_t)); }

void terrain_update_sprite(terrain_t terrain) {
    if (terrain.sprite != 0) {
        terrain.sprite->rect_dst.x = terrain.world_pos.x + (terrain.sprite_offset.x * terrain.sprite->rect_dst.width * terrain.sprite_scale.x);
        terrain.sprite->rect_dst.y = terrain.world_pos.y + (terrain.sprite_offset.y * terrain.sprite->rect_dst.height * terrain.sprite_scale.y);
    } else if (terrain.anim_sprite != 0) {
        terrain.anim_sprite->rect_dst.x = terrain.world_pos.x + (terrain.sprite_offset.x * terrain.anim_sprite->rect_dst.width * terrain.sprite_scale.x);
        terrain.anim_sprite->rect_dst.y = terrain.world_pos.y + (terrain.sprite_offset.y * terrain.anim_sprite->rect_dst.height * terrain.sprite_scale.y);
    }
}

#endif