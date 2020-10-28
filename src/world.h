#ifndef WORLD_H
#define WORLD_H

#include "entity.h"

typedef struct worldspace {
    int x;
    int y;
    int level;
    entity* entities[];
} worldspace;

typedef struct world {
    int width;
    int height;
    int num_levels;
    worldspace* spaces;
} world;

world* world_init(int width, int height, int num_levels) {
    world* w = (world*)malloc(sizeof(world));
    w->width = width;
    w->height = height;
    w->num_levels = num_levels;

    // calculate the world's "volume", or the number of spaces in all positions at all levels
    int world_volume = width * height * num_levels;

    // allocate memory for all the world spaces
    w->spaces = (worldspace*)malloc(sizeof(worldspace) * world_volume);

    // allocate memory for all the entities that can be held within a singular world space
    
    return w;
}

void world_generate(world* world) {

}

#endif