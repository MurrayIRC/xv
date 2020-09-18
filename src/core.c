#include "core.h"
#include "entity.h"
#include "sprite.h"

#include <stdio.h>
#include <stdlib.h>

#include <raylib.h>

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
    player->scale = (Vector2){5.0f, 5.0f};
    player->rotation = 0;

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

    Rectangle rect = {128.0f, 0.0f, 16, 32};
    player->anim_sprite = create_animated_sprite(rect, player->scale, 3, 8);
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
        DrawTexturePro(game.all_tilesets[i], player->anim_sprite->frame_rect,
                       player->anim_sprite->dest_rect, player->position, player->rotation, WHITE);

        // Debug rect
        DrawRectangleLines(player->position.x, player->position.y,
                           player->anim_sprite->dest_rect.width,
                           player->anim_sprite->dest_rect.height, LIME);
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