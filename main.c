#include <SDL.h>
#include <SDL_image.h>

typedef struct {
  SDL_Rect rect;
  int speed;
  SDL_Texture* texture;
  int jump_time;
  int x_pos;       // player's horizontal position
  int x_velocity;  // player's horizontal velocity
  int y_pos;       // player's vertical position
  int y_velocity;  // player's vertical velocity
} Player;


void handleInput(Player* player) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        exit(0);
        break;
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
          case SDLK_LEFT:
            // Move left when the left arrow key is pressed
            player->x_velocity = -2;
            break;
          case SDLK_RIGHT:
            // Move right when the right arrow key is pressed
            player->x_velocity = 2;
            break;
          case SDLK_SPACE:
            // Jump when the spacebar is pressed
            if (player->jump_time >= 2) break;
            player->y_velocity = -10;
            player->jump_time++;
            break;
        }
        break;
      case SDL_KEYUP:
        switch (event.key.keysym.sym) {
          case SDLK_LEFT:
          case SDLK_RIGHT:
            // Stop moving when the left or right arrow key is released
            player->x_velocity = 0;
            break;
        }
        break;
    }
  }
}


void update(Player* player) {
  // Update player position based on horizontal velocity
  player->x_pos += player->x_velocity;

  // Keep player within the screen bounds
  if (player->x_pos < 0) {
    player->x_pos = 0;
  } else if (player->x_pos > 800 - player->rect.w) {
    player->x_pos = 800 - player->rect.w;
  }

  // Update player position based on vertical velocity
  player->y_pos += player->y_velocity;

  // Apply gravity to the player
  player->y_velocity += 1;

  // Keep player on the ground
  if (player->y_pos >= 400) {
    player->y_pos = 400;
    player->y_velocity = 0;
  }

  //check if player if on the ground
  if (player->y_pos == 400) {
    player->jump_time = 0;
  }


  // Update player rectangle position
  player->rect.x = player->x_pos;
  player->rect.y = player->y_pos;
}


void render(SDL_Renderer* renderer, Player* player) {
  // Clear the screen
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  // Render the player
  SDL_RenderCopy(renderer, player->texture, NULL, &player->rect);

  // Update the screen
  SDL_RenderPresent(renderer);
}

SDL_Texture* load_texture(SDL_Renderer* renderer, const char* file_path) {
  SDL_Surface* surface = IMG_Load(file_path);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
  return texture;
}


int main(int argc, char* argv[]) {
  // Initialize SDL
  SDL_Init(SDL_INIT_VIDEO);

  // Create a window and renderer
  SDL_Window* window =
      SDL_CreateWindow("Vengeance Hunter", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
  SDL_Renderer* renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  // Load the player texture
  Player player;
  player.jump_time = 0;
  player.texture = load_texture(renderer, "../../include/player.png");
  player.rect.w = 32;
  player.rect.h = 64;
  player.x_pos = 400;
  player.y_pos = 400;
  player.speed = 1;

  // Game loop
  int running = 1;
  while (running) {
    handleInput(&player);
    update(&player);
    render(renderer, &player);
    SDL_Delay(1000 / 60);
  }

  // Cleanup
  SDL_DestroyTexture(player.texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
