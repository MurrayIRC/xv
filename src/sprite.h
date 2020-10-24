#ifndef SPRITE_H
#define SPRITE_H

#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct sprite_t {
    Vector2 tileset_position;
    Rectangle rect_src;
    Rectangle rect_dst;
    Color tint;
} sprite_t;

typedef struct animated_sprite_t {
    Vector2 tileset_position;
    Rectangle rect_src;
    Rectangle rect_dst;
    Color tint;

    int frame_counter;
    int current_frame;
    int frame_speed;
    int anim_length;
} animated_sprite_t;

sprite_t* create_sprite(Rectangle tileset_position_rect, Vector2 offset, Vector2 scale)
{
    sprite_t* out = (sprite_t*)malloc(sizeof(sprite_t));

    float offset_x = offset.x * out->rect_src.width * scale.x;
    float offset_y = offset.y * out->rect_src.height * scale.y;

    out->rect_src = tileset_position_rect;
    out->rect_dst = (Rectangle){offset_x, offset_y, out->rect_src.width * scale.x, out->rect_src.height * scale.y};

    out->tileset_position = (Vector2){tileset_position_rect.x, tileset_position_rect.y};
    return out;
}

animated_sprite_t* create_animated_sprite(Rectangle tileset_position_rect, Vector2 offset, Vector2 scale, int length, int speed)
{
    animated_sprite_t* out = (animated_sprite_t*)malloc(sizeof(animated_sprite_t));

    float offset_x = offset.x * out->rect_src.width * scale.x;
    float offset_y = offset.y * out->rect_src.height * scale.y;

    out->rect_src = tileset_position_rect;
    out->rect_dst =
        (Rectangle){offset_x, offset_y, out->rect_src.width * scale.x, out->rect_src.height * scale.y};

    out->tileset_position = (Vector2){tileset_position_rect.x, tileset_position_rect.y};

    out->frame_counter = 0;
    out->current_frame = 0;
    out->frame_speed = speed;
    out->anim_length = length;
    return out;
}

void sprite_animate(animated_sprite_t* sprite)
{
    sprite->frame_counter++;

    if (sprite->frame_counter >= (60 / sprite->frame_speed)) {
        sprite->frame_counter = 0;
        sprite->current_frame++;

        if (sprite->current_frame > 3) {
            sprite->current_frame = 0;
        }

        sprite->rect_src.x =
            sprite->tileset_position.x + (float)(sprite->current_frame * sprite->rect_src.width);
    }
}

#endif