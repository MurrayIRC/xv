#ifndef CORE_H
#define CORE_H

#define MAX_TILESETS 100
#define MAX_SPRITES 100

void core_run(void);
void core_init(void);
void core_load_resources(void);
void core_update(void);
void core_draw(void);
void core_shutdown(void);

#endif