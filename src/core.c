#include <raylib.h>

#include "core.h"
#include "entity.h"
#include "terrain.h"
#include "sprite.h"

#include <stdio.h>
#include <stdlib.h>

struct game {
    float screen_width;
    float screen_height;

    Texture2D tileset;

    Camera2D camera;
} game;

entity* player;
terrain_t grass[9];

void core_run(void)
{
    core_init();
    core_load_resources();

    while (!WindowShouldClose()) {
        core_update();
        core_draw();
    }

    core_shutdown();
}

void core_init(void)
{
    game.screen_width = 800;
    game.screen_height = 600;

    InitWindow(game.screen_width, game.screen_height, "[XV]");

    // Setup the player
    player = create_entity();
    player->world_pos = (Vector2){0.0f, 0.0f};
    player->sprite_scale = (Vector2){2.0f, 2.0f};
    player->rotation = 0;
    player->grid_level = 0;
    player->sprite = 0;
    player->anim_sprite = 0;
    player->sprite_offset = (Vector2){-0.5f, -0.5f};


    for (int i = 0; i < 9; i++) {
        grass[i].world_pos = (Vector2){50.0f * i, 50.0f * i};
        grass[i].sprite_scale = (Vector2){2.0f, 2.0f};
        grass[i].grid_x = 10;
        grass[i].grid_y = 10;
        grass[i].grid_level = 0;
        grass[i].sprite = 0;
        grass[i].anim_sprite = 0;
        grass[i].sprite_offset = (Vector2){-0.5f, -0.5f};
    }

    game.camera = (Camera2D){0};
    game.camera.target = player->world_pos;
    game.camera.rotation = 0.0f;
    game.camera.zoom = 1.0f;

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
}

void core_load_resources(void)
{
    game.tileset = LoadTexture("res/tileset.png");

    Rectangle player_rect = {80.0f, 16.0f, 16, 16};
    player->anim_sprite = create_animated_sprite(player_rect, player->sprite_offset, player->sprite_scale, 3, 4);

    for (int i = 0; i < 9; i++) {
        Rectangle grass_rect = {16.0f * (i % 3), 16.0f * (i % 3), 16, 16};
        grass[i].sprite = create_sprite(grass_rect, grass[i].sprite_offset, grass[i].sprite_scale);
    }
}

void core_update(void)
{
    // Player movement
    if (IsKeyDown(KEY_RIGHT)) {
        player->world_pos.x += 2;
    } else if (IsKeyDown(KEY_LEFT)) {
        player->world_pos.x -= 2;
    } else if (IsKeyDown(KEY_UP)) {
        player->world_pos.y -= 2;
    } else if (IsKeyDown(KEY_DOWN)) {
        player->world_pos.y += 2;
    }

    Vector2 mouse_position = GetMousePosition();
    if (IsMouseButtonPressed(0)) {
        player->world_pos = mouse_position;
    }

    entity_update_sprite(player);

    for (int i = 0; i < 9; i++) {
        terrain_update_sprite(grass[i]);
    }

    // Camera target follows player
    // game.camera.target = (Vector2){player->world_pos.x, player->world_pos.y};

    /*
    // Camera zoom controls
    if (IsKeyPressed(KEY_R)) { // Camera reset (zoom and rotation)
        game.camera.zoom = 1.0f;
        game.camera.rotation = 0.0f;
    }
    game.camera.zoom += ((float)GetMouseWheelMove() * 0.05f);
    if (game.camera.zoom > 3.0f) { // max 3
        game.camera.zoom = 3.0f;
    } else if (game.camera.zoom < 0.1f) { // min 0.1
        game.camera.zoom = 0.1f;
    }
    */

    sprite_animate(player->anim_sprite);
}

void core_draw(void)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    BeginMode2D(game.camera);

    DrawTexturePro(game.tileset, player->anim_sprite->rect_src, player->anim_sprite->rect_dst, (Vector2){0.0f, 0.0f}, player->rotation, WHITE);

    for (int i = 0; i < 9; i++) {
        DrawTexturePro(game.tileset, grass[i].sprite->rect_src, grass[i].sprite->rect_dst, grass[i].sprite_offset, 0.0f, WHITE);
    }

    EndMode2D();

    DrawText(FormatText("Player Position: {%f, %f}", player->world_pos.x, player->world_pos.y), 10,
             30, 10, BLACK);
    DrawFPS(10, 10);
    EndDrawing();
}

void core_shutdown(void)
{
    UnloadTexture(game.tileset);

    free(player->anim_sprite);
    free(player);

    CloseWindow();
}