#ifndef ENTITY_H
#define ENTITY_H

#include "sprite.h"

#include <raylib.h>
#include <stdio.h>

typedef struct entity {
    unsigned int id;

    sprite_t* sprite;
    animated_sprite_t* anim_sprite;
    Vector2 sprite_offset; // percentage (0.0 to 1.0) offset value

    Vector2 position;
    Vector2 scale;
    float rotation;
    int height; // height is an integer-based "level", rather than a gradual value like position
} entity;

entity* create_entity(void) { return (entity*)malloc(sizeof(entity)); }

void entity_calculate_offset(Vector2* offset_out, entity* ent) {
    offset_out->x = ent->sprite_offset.x * ent->sprite->rect_dst.width * ent->scale.x;
    offset_out->y = ent->sprite_offset.y * ent->sprite->rect_dst.height * ent->scale.y;
}

void entity_update(entity* ent) {
    if (ent->sprite != 0) {
        Vector2* offset;
        entity_calculate_offset(offset, ent);
        ent->sprite->rect_dst.x = ent->position.x + offset->x;
        ent->sprite->rect_dst.y = ent->position.y + offset->y;
    } else if (ent->anim_sprite != 0) {
        Vector2* offset;
        entity_calculate_offset(offset, ent);
        ent->anim_sprite->rect_dst.x = ent->position.x + offset->x;
        ent->anim_sprite->rect_dst.y = ent->position.y + offset->y;
    y
}

#endif