#include "rpg.h"

SFML_DEFINE_DISCRETE_GPU_PREFERENCE

int main(void)
{
    sfRenderWindow *window = sfRenderWindow_create((sfVideoMode)
        {1920, 1080,32}, "RPG",
        sfResize | sfClose, NULL);
    sfRenderWindow_setFramerateLimit(window, 60);
    sfEvent evt;
    sfTexture *texture = sfTexture_createFromFile("isometric_0053.png", NULL);
    const float scale_x = 0.1483198146f;
    const float scale_y = 0.128514056225f;
    const int half_tilew = sfTexture_getSize(texture).x * 0.5 * scale_x;
    const int half_tileh = sfTexture_getSize(texture).y * 0.5 * scale_y;
    const int half_screen = 1920 / 2;
    const int map_size = 10;
    sfSprite *floortile[10][10];

    for (int i = 0; i < map_size; i++) {
        for (int j = 0; j < map_size; j++) {
            floortile[i][j] = sfSprite_create();
            sfSprite_setTexture(floortile[i][j], texture, sfTrue);
            sfSprite_setScale(floortile[i][j], (sfVector2f){scale_x, scale_y});
            float x = (i - j) * half_tilew - half_tilew + half_screen;
            float y = (i + j) * half_tileh * 0.5;
            sfSprite_setPosition(floortile[i][j], (sfVector2f){x, y});
        }
    }


    while (sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &evt)) {
            if (evt.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }
        for (int i = 0; i < map_size; i++) {
            for (int j = 0; j < map_size; j++) {
                sfRenderWindow_drawSprite(window, floortile[i][j], NULL);
            }
        }
        sfRenderWindow_display(window);
        sfRenderWindow_clear(window, sfWhite);
    }


    for (int i = 0; i < map_size; i++) {
        for (int j = 0; j < map_size; j++) {
            sfSprite_destroy(floortile[i][j]);
        }
    }

    sfRenderWindow_destroy(window);
    sfTexture_destroy(texture);

    return 0;
}
