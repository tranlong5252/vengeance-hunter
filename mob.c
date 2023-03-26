#include <SDL.h>
#include "main.c"

// Define the mob's properties
typedef struct {
    int x, y;       // Position
    int speed;      // Speed
    int health;     // Health
    int damage;     // Damage
    SDL_Rect rect;    // Sprite
} Mob;


void animateMob(Mob* mob, int frame, SDL_Renderer* renderer, int mobX, int mobY) {
    // Determine which image to use based on the frame number
    SDL_Surface* mobImage = NULL;
    if (frame < 10) {
        mobImage = IMG_Load("mob_1.png");
    }
    else if (frame < 20) {
        mobImage = IMG_Load("mob_2.png");
    }
    else {
        mobImage = IMG_Load("mob_3.png");
    }

    // Convert the image to a texture
    SDL_Texture* mobTexture = SDL_CreateTextureFromSurface(renderer, mobImage);
    SDL_FreeSurface(mobImage);

    // Set the position and dimensions of the mob's rectangle
    SDL_Rect mobRect = { mobX, mobY, mob->rect.w, mob->rect.h };

    // Render the mob on the screen
    SDL_RenderCopy(renderer, mobTexture, NULL, &mobRect);

    // Clean up the texture
    SDL_DestroyTexture(mobTexture);
}


// Create the mob's attack behavior
void attackPlayer(Mob* mob, Player* player) {
    // Your attack code here
}

// Update the mob's position and behavior
void updateMob(Mob* mob, Player* player) {
    // Check if the player is in range
    if (distance(mob->x, mob->y, player->x_pos, player->y_pos) < MOB_RANGE) {
        // Attack the player
        attackPlayer(mob, player);
    }
    else {
        // Move towards the player
        if (mob->x < player->x_pos) mob->x += mob->speed;
        if (mob->y < player->y_pos) mob->y += mob->speed;
        animateMob(mob);
    }
}

// Render the mob to the screen
void renderMob(Mob* mob, SDL_Renderer* renderer) {
    SDL_Rect dest = { mob->x, mob->y, mob->rect.w, mob->rect.h };
    SDL_RenderCopy(renderer, mobImage, &mob->rect, &dest);
}
