#ifndef ENTITY_H
#define ENTITY_H

#include "sprite.h"

#include <raylib.h>
#include <stdio.h>

typedef struct entity {
    unsigned int id;

    Vector2 position;
    Vector2 scale;
    float rotation;

    sprite_t* sprite;
    animated_sprite_t* anim_sprite;
} entity;

entity* create_entity(void) { return (entity*)malloc(sizeof(entity)); }

#endif