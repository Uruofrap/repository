#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define N_X_TILES 28
#define N_Y_TILES 29

#define PACMAN_SIZE 32

enum tile_type_e {
    WALL = 0,
    PATH,
    PACMAN_START,
};

int main()
{
    /* The map.
     * Not using WALL, PATH, ... to make it shorter */
    enum tile_type_e map[N_Y_TILES][N_X_TILES] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    int ret;
    int is_running = 1;
    const int tile_size = PACMAN_SIZE+8;
    const int window_width = N_X_TILES*tile_size;
    const int window_height = N_Y_TILES*tile_size;

    // SDL initialisation with video support
    ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret != 0)
    {
        fprintf(stderr, "Could not init SDL: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Create the window
    SDL_Window *screen = SDL_CreateWindow(
        "Pacman",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        window_width, window_height,
        0
    );
    if (!screen)
    {
        fprintf(stderr, "Could not create SDL screen: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Create the renderer, can be seen as a paint brush
    SDL_Renderer *renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_SOFTWARE);
    if (!renderer)
    {
        fprintf(stderr, "Could not create SDL renderer: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Rect pacman_position = {
        .w = PACMAN_SIZE,
        .h = PACMAN_SIZE,
    };

    SDL_Rect map_position = {
        .x = 0,
        .y = 0,
        .w = window_width,
        .h = window_height,
    };

    // Create a texture for the map, can be seen as a layer
    SDL_Texture* map_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        window_width,
        window_height
    );

    // Now, the paint brush `renderer` will paint on the layer `map_texture`
    SDL_SetRenderTarget(renderer, map_texture);

    // Select color of the paint brush (R, G, B, alpha)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    // Paint the the whole target of the paint brush (`map_texture` now)
    SDL_RenderClear(renderer);

    // Now, let's paint the maze walls in blue:
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    for (int y = 0; y < N_Y_TILES; y++)
    {
        for (int x = 0; x < N_X_TILES; x++)
        {
            if (map[y][x] == WALL)
            {
                SDL_Rect rectangle = {
                    .x = x*tile_size,
                    .y = y*tile_size,
                    .w = tile_size,
                    .h = tile_size,
                };
                SDL_RenderFillRect(renderer, &rectangle);
            }
            else if (map[y][x] == PACMAN_START)
            {
                // While we are at it, save what is the initial position of Pac-Man
                pacman_position.x = x*tile_size + (tile_size-PACMAN_SIZE)/2;
                pacman_position.y = y*tile_size + (tile_size-PACMAN_SIZE)/2;

                /* Don't forget to change the map tile type to consider it as a
                 * path (can be done probably in a better way, for instance
                 * with a bit fields) */
                map[y][x] = PATH;
            }
        }
    }

    // Draw back to window's renderer (ie the paint brush draws on the window now):
    SDL_SetRenderTarget(renderer, NULL);

    // Load the image as a texture
    SDL_Texture* pacman_texture = IMG_LoadTexture(renderer, "images/pacman-left.png");
    if (!pacman_texture)
    {
        fprintf(stderr, "Could not load image: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }


    int move_direction = 0;

    while (is_running)
    {
        // Fetch event
        SDL_Event event;
        SDL_PollEvent(&event);

        switch (event.type)
        {
            case SDL_QUIT:
                is_running = 0;
                break;

            case SDL_KEYDOWN:
                // A keyboard key was pressed down
                switch (event.key.keysym.sym)
                {
                    // It was a `q`, quit the program by exiting this loop
                    case SDLK_q:
                        is_running = 0;
                        break;

                    // It was an arrow key, save which one
                    case SDLK_UP:
                    case SDLK_DOWN:
                    case SDLK_LEFT:
                    case SDLK_RIGHT:
                        move_direction = event.key.keysym.sym;
                        break;
                }
                break;
        }

        // Move the pacman according to the requested direction
        switch (move_direction)
        {
            case SDLK_UP:
                pacman_position.y--;
                break;
            case SDLK_DOWN:
                pacman_position.y++;
                break;
            case SDLK_LEFT:
                pacman_position.x--;
                break;
            case SDLK_RIGHT:
                pacman_position.x++;
                break;
        }

        // Clear the window: remove everything that was drawn
        SDL_RenderClear(renderer);
        // Draw the map texture in the window
        SDL_RenderCopy(renderer, map_texture, NULL, &map_position);
        // Draw the pacman texture on top of what was previously drawn
        SDL_RenderCopy(renderer, pacman_texture, NULL, &pacman_position);
        // Really show on the screen what we drew so far
        SDL_RenderPresent(renderer);

        // Wait 2 ms (reduce a bit processor usage and regulates speed of Pac-Man)
        SDL_Delay(2);
    }

    // Free all created resources
    SDL_DestroyTexture(pacman_texture);
    SDL_DestroyTexture(map_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(screen);

    // Quit the SDL program
    SDL_Quit();

    return EXIT_SUCCESS;
}
