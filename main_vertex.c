#include "rpg.h"

SFML_DEFINE_DISCRETE_GPU_PREFERENCE

int main(void)
{
    sfRenderWindow *window = sfRenderWindow_create((sfVideoMode){1920, 1080,
                                                                 32}, "RPG",
                                                   sfResize | sfClose, NULL);
    sfEvent evt;
    sfTexture *texture = sfTexture_createFromFile("isometric_0053.png", NULL);
    const float scale_x = 0.1483198146f;
    const float scale_y = 0.128514056225f;
    const unsigned tilew = sfTexture_getSize(texture).x;
    const unsigned tileh = sfTexture_getSize(texture).y;
    const int half_tilew = sfTexture_getSize(texture).x * 0.5 * scale_x;
    const int half_tileh = sfTexture_getSize(texture).y * 0.5 * scale_y;

    sfVertexArray *vertexArray = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(vertexArray, sfQuads);
    sfVertexArray_resize(vertexArray, tileh * tilew * 4);

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            float x = (i - j) * half_tilew - half_tilew;
            float y = (i + j) * half_tileh * 0.5;

            sfVertex *vertex = sfVertexArray_getVertex(vertexArray, (i + j *
            10) * 4);

            vertex[0].position = (sfVector2f){x, y};
            vertex[1].position = (sfVector2f){x + tilew, y};
            vertex[2].position = (sfVector2f){x + tilew, y + tileh};
            vertex[3].position = (sfVector2f){x, y + tileh};

            vertex[0].texCoords = (sfVector2f){0, 0};
            vertex[1].texCoords = (sfVector2f){tilew, 0};
            vertex[2].texCoords = (sfVector2f){tilew, tileh};
            vertex[3].texCoords = (sfVector2f){0, tileh};
        }
    }

    sfRenderStates state; state.shader = NULL;
    state.texture = texture;
    state.transform = sfTransform_Identity;
//    sfTransform_scale(&state.transform, scale_x, scale_y);
    sfRenderWindow_setFramerateLimit(window, 60);

    while (sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &evt)) {
            if (evt.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }
        sfRenderWindow_drawVertexArray(window, vertexArray, &state);
        sfRenderWindow_display(window);
        sfRenderWindow_clear(window, sfWhite);
    }

    sfVertexArray_destroy(vertexArray);
}
