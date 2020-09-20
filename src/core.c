#include <raylib.h>

#include "core.h"
#include "entity.h"
#include "sprite.h"

#include <stdio.h>
#include <stdlib.h>

struct game {
    float screen_width;
    float screen_height;

    Texture2D* all_tilesets;
    unsigned int num_tiles;

    Camera2D camera;
} game;

entity* player;

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
    player->position = (Vector2){0.0f, 0.0f};
    player->scale = (Vector2){3.0f, 3.0f};
    player->rotation = 0;
    player->height = 0;
    player->sprite = 0;
    player->anim_sprite = 0;
    player->sprite_offset = (Vector2){0.5f, 0.5f};

    game.camera = (Camera2D){0};
    game.camera.target = player->position;
    // game.camera.offset = (Vector2){game.screen_width / 2, game.screen_height / 2};
    game.camera.rotation = 0.0f;
    game.camera.zoom = 1.0f;

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
}

void core_load_resources(void)
{
    game.num_tiles = 0;
    game.all_tilesets = (Texture2D*)malloc(sizeof(Texture2D) * MAX_TILESETS);
    game.all_tilesets[0] = LoadTexture("res/tileset.png");
    game.num_tiles++;

    Rectangle rect = {128.0f, 16.0f, 16, 16};
    player->anim_sprite = create_animated_sprite(rect, player->sprite_offset, player->scale, 3, 8);
    player->anim_sprite->tileset_id = 0;
}

void core_update(void)
{
    // Player movement
    if (IsKeyDown(KEY_RIGHT)) {
        player->position.x += 2;
    } else if (IsKeyDown(KEY_LEFT)) {
        player->position.x -= 2;
    } else if (IsKeyDown(KEY_UP)) {
        player->position.y -= 2;
    } else if (IsKeyDown(KEY_DOWN)) {
        player->position.y += 2;
    }

    Vector2 mouse_position = GetMousePosition();
    if (IsMouseButtonPressed(0)) {
        player->position = mouse_position;
    }

    entity_update(player);

    // Camera target follows player
    // game.camera.target = (Vector2){player->position.x, player->position.y};

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

    sprite_animate(player->anim_sprite);
}

void core_draw(void)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    BeginMode2D(game.camera);

    for (int i = 0; i < game.num_tiles; i++) {
        DrawTexturePro(game.all_tilesets[i], player->anim_sprite->rect_src,
                       player->anim_sprite->rect_dst, (Vector2){0.0, 0.0}, player->rotation, WHITE);

        // Debug rect
        DrawRectangleLines(player->position.x, player->position.y,
                           player->anim_sprite->rect_dst.width,
                           player->anim_sprite->rect_dst.height, LIME);
    }

    EndMode2D();

    DrawText(FormatText("Player Position: {%f, %f}", player->position.x, player->position.y), 10,
             30, 10, BLACK);
    DrawFPS(10, 10);
    EndDrawing();
}

void core_shutdown(void)
{
    for (int i = 0; i < game.num_tiles; i++) {
        UnloadTexture(game.all_tilesets[i]);
    }

    free(player->anim_sprite);
    free(player);

    CloseWindow();
}