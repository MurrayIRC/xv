#ifndef ENTITY_H
#define ENTITY_H

#include "sprite.h"

#include <raylib.h>
#include <stdio.h>

typedef struct entity {
    unsigned int id;

    Vector2 world_pos;
    Vector2 move_direction;
    float move_speed;
    float rotation;
    int grid_level;
    int grid_x;
    int grid_y;

    sprite_t* sprite;
    animated_sprite_t* anim_sprite;
    Vector2 sprite_offset;
    Vector2 sprite_scale;
} entity;

entity* create_entity(void) { return (entity*)malloc(sizeof(entity)); }

void entity_update_sprite(entity* ent) {
    if (ent->sprite != 0) {
        ent->sprite->rect_dst.x = ent->world_pos.x + (ent->sprite_offset.x * ent->sprite->rect_dst.width * ent->sprite_scale.x);
        ent->sprite->rect_dst.y = ent->world_pos.y + (ent->sprite_offset.y * ent->sprite->rect_dst.height * ent->sprite_scale.y);
    } else if (ent->anim_sprite != 0) {
        ent->anim_sprite->rect_dst.x = ent->world_pos.x + (ent->sprite_offset.x * ent->anim_sprite->rect_dst.width * ent->sprite_scale.x);
        ent->anim_sprite->rect_dst.y = ent->world_pos.y + (ent->sprite_offset.y * ent->anim_sprite->rect_dst.height * ent->sprite_scale.y);
    }
}

#endif