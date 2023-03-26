#include <stdio.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdbool.h>

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int TILE_SIZE = 64;
int MAX_MAP_X ;//so cot cua mang 2 chieu map
int MAX_MAP_Y ;//so hang cua mang 2 chieu map
int map_pos_x = 0;//vi tri x cua map 
int map_pos_y = 0;// vi tri y cua map
//
SDL_Window* window = NULL; //create a window
SDL_Surface* screen = NULL; //screen
SDL_Texture* Texture = NULL;
SDL_Texture* Tile_Map_Texture[4040];
SDL_Texture* Image_Texture = NULL;
SDL_Renderer* render = NULL;
TTF_Font* font = NULL;
//
//SDL_Rect title_srcRect;
//SDL_Rect title_desRect;
SDL_Rect play_game_srcRect;
SDL_Rect play_game_desRect;
SDL_Rect exit_srcRect;
SDL_Rect exit_desRect;
SDL_Rect instruction_srcRect;
SDL_Rect instruction_desRect;
SDL_RendererFlip flip;
int map[410][20];
int pl, pm;
//


int MOB_RANGE = 30;

typedef struct 
{
	int start_x;
	int start_y;
	int max_x;
	int max_y;
	int tile[500][500];
	char* str_name;
}Map;
typedef struct {
	SDL_Rect rect;
	int speed;
	SDL_Texture* texture ;
	int jump_time;
	int x_pos;       // player's horizontal position
	int x_velocity;  // player's horizontal velocity
	int y_pos;       // player's vertical position
	int y_velocity;  // player's vertical velocity
} Player;
Map* map1,map2,map3;
//
// Define the mob's properties
typedef struct {
	int x, y;       // Position
	int speed;      // Speed
	int health;     // Health
	int damage;     // Damage
	SDL_Rect sprite;    // Sprite
} Mob;


double distance(double x1, double y1, double x2, double y2) {
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

// Load the mob's graphics
SDL_Texture* mobImage = NULL;
// Create the mob's animation
void animateMob(Mob* mob) {
	// Your animation code here
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
	SDL_Rect dest = { mob->x, mob->y, mob->sprite.w, mob->sprite.h };
	SDL_RenderCopy(renderer, mobImage, &mob->sprite, &dest);
}

SDL_Texture* load_image(char* file_path) {
	SDL_Texture* newTexture = NULL;
	SDL_Surface* image_tmp = IMG_Load(file_path);
	newTexture = SDL_CreateTextureFromSurface(render, image_tmp);
	SDL_FreeSurface(image_tmp);
	return newTexture;
}

bool init()
{
	
	bool check = true ; 
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		printf("Init failed! SDL_Error: %s\n", SDL_GetError());
		check = false;
	}
	else
	{
		window = SDL_CreateWindow("Hunter Vengeance", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	}
	if (TTF_Init() < 0)
	{
		SDL_Log("%s", TTF_GetError());
		check = false; 
	}
	mobImage = load_image("image_save/mob.png");
	return check;
}
void close()
{
	SDL_DestroyWindow(window);
	SDL_DestroyTexture(Texture);
	SDL_DestroyTexture(Image_Texture);
	SDL_DestroyRenderer(render);
	TTF_Quit();
	SDL_Quit();
}

void show_text_on_screen(char* str_text, char* str_color, SDL_Rect m_srcRect, SDL_Rect m_desRect)
{
	SDL_Surface* textSurface = NULL;
	if (strcmp(str_color, "black") == 0)
	{
		SDL_Color color = { 144,77,55,255 };
		textSurface = TTF_RenderText_Solid(font, str_text, color);
	}
	else
	{
		SDL_Color color = { 0,0,0,255 };
		textSurface = TTF_RenderText_Solid(font, str_text, color);
	}
	Texture = SDL_CreateTextureFromSurface(render, textSurface);
	SDL_FreeSurface(textSurface);
	TTF_SizeText(font, str_text, &m_srcRect.w, &m_srcRect.h);
	pl = m_desRect.w = m_srcRect.w;
	pm = m_desRect.h = m_srcRect.h;
	SDL_RenderCopy(render, Texture, &m_srcRect, &m_desRect);//Copy a portion of the texture to the current rendering target.				
}
void pos_text_menu() //vi tri cua cac dong text menu
{
	/*title_srcRect.x = 0;
	title_srcRect.y = 0;
	title_desRect.x = 400;
	title_desRect.y = 50;*/
	//
	play_game_srcRect.x = 0;
	play_game_srcRect.y = 0;
	play_game_desRect.x = 50;
	play_game_desRect.y = 200;
	//
	instruction_srcRect.x = 0;
	instruction_srcRect.y = 0;
	instruction_desRect.x = 50;
	instruction_desRect.y = 250;
	//
	exit_srcRect.x = 0;
	exit_srcRect.y = 0;
	exit_desRect.x = 50;
	exit_desRect.y = 300;
	//
}
void showmenu(char* play_game_color,char* instruction_color, char* exit_color)
{
	pos_text_menu();
	Image_Texture = load_image("image_save/bg0.png");//background menu
	SDL_RenderClear(render);// clear the window to black
	SDL_RenderCopy(render, Image_Texture, NULL, NULL);
	show_text_on_screen("Play Game", play_game_color, play_game_srcRect, play_game_desRect);
	play_game_desRect.w = pl;
	play_game_desRect.h = pm;
	show_text_on_screen("Instruction", instruction_color, instruction_srcRect, instruction_desRect);
	instruction_desRect.w = pl;
	instruction_desRect.h = pm;
	show_text_on_screen("Exit", exit_color, exit_srcRect, exit_desRect);
	exit_desRect.w = pl;
	exit_desRect.h = pm;
	SDL_RenderPresent(render);//draw to screen
}


char str[50] = "image_save/map/map@/bg@.png";

//loadtiles
char file_img[150] = "image_save/map/map#/@.png";
char save_file_img[150] = "image_save/map/map#/@.png";


Map* gen_map(char* str_name, char type) {

	size_t len = strlen(str);
	char* p = str;
	for (size_t i = 0; i < len; i++, p++) {
		if (*p == '@') {
			*p = type;
		}
	}

	Map* map = (Map*)malloc(sizeof(Map));

	//load map text
	FILE* fp = NULL;
	fopen_s(&fp, str_name, "rb");
	if (fp == NULL) {
		return map;
	}
	else {

		map->max_y = 0;
		map->max_x = 0;
		fscanf_s(fp, "%d %d", &MAX_MAP_X, &MAX_MAP_Y);
		//printf("%d %d\n", MAX_MAP_X, MAX_MAP_Y);
		for (int i = 0; i < MAX_MAP_Y; i++) {
			for (int j = 0; j < MAX_MAP_X; j++) {
				fscanf_s(fp, "%d", &map->tile[i][j]);
				//printf("%d ", map->tile[i][j]);
				if (map->tile[i][j] <= 0) continue;
				if (j > map->max_x) {
					map->max_x = j;
				}
				if (i > map->max_y) {
					map->max_y = i;
				}
			}
			//printf("\n");
		}
		map->max_x = (map->max_x + 1) * TILE_SIZE;
		map->max_y = (map->max_y + 1) * TILE_SIZE;
	}
	map->start_x = map_pos_x;
	map->start_y = map_pos_y;
	fclose(fp);

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < strlen(file_img); j++) {
			if (file_img[j] == '@') {
				char g = i + '0';
				save_file_img[j] = g;
			}
			if (file_img[j] == '#') {
				save_file_img[j] = type;
			}
		}
		fopen_s(&fp, save_file_img, "rb");
		if (fp == NULL) {
			//printf("%d\n",i);
			continue;
		}
		fclose(fp);
		Tile_Map_Texture[i] = load_image(save_file_img);
	}
	return map;
}

void load_map(Map* game_map) {
	//load background map

	Image_Texture = load_image(str); //background 
	SDL_RenderCopy(render, Image_Texture, NULL, NULL);
	
	//draw map
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;
	int map_x = 0;
	int map_y = 0;
	map_x = game_map->start_x / TILE_SIZE;
	map_y = game_map->start_y / TILE_SIZE;
	x1 = (game_map->start_x % TILE_SIZE) * (-1);
	x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);
	y1 = (game_map->start_y % TILE_SIZE) * (-1);
	y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);
    //printf("%d %d %d %d ::::::\n", x1, x2, y1, y2);
	for (int i = y1; i < y2; i += TILE_SIZE) {
		map_x = game_map->start_x / TILE_SIZE;
		for (int j = x1; j < x2; j += TILE_SIZE) {
			int t = game_map->tile[map_y][map_x];
			//printf("%d ", t);
			if (t > 0) {
				SDL_Rect srcRect;
				SDL_Rect desRect;
				srcRect.x = srcRect.y = 0;;
				srcRect.w = srcRect.h = desRect.w = desRect.h = 64;
				desRect.x = j;
				desRect.y = i;
				SDL_RenderCopy(render, Tile_Map_Texture[t], &srcRect, &desRect);
			}
			map_x++;
		}
	    //printf("\n");
		map_y++;
	}
}
void instruction_game() {
	SDL_Rect srcpos,despos;
	srcpos.x = 0;
	srcpos.y = 0;
	srcpos.w = 1043;
	srcpos.h = 443;
	despos.w = 1043;
	despos.h = 443;
	despos.x = 50;
	despos.y = 50;
	Image_Texture = load_image("image_save/instruction.png");
	SDL_RenderClear(render);
	SDL_RenderCopy(render, Image_Texture, &srcpos, &despos);
	SDL_RenderPresent(render); //draw to screen
}
void handleInput(Player* player)
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) 
	{
		switch (event.type) {
		case SDL_QUIT:
			exit(0);
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_LEFT:
				// Move left when the left arrow key is pressed
				map_pos_x -= 15;//map move left when the left arrow key is pressed
				if (map_pos_x < 0)
				{
					map_pos_x = 0;
				}
				player->x_velocity = -5;
				flip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_RIGHT:
				// Move right when the right arrow key is pressed
				map_pos_x += 15;// map move right when the right arrow key is pressed
				player->x_velocity = 5;
				flip = SDL_FLIP_NONE;
				break;
			case SDLK_SPACE:
				// Jump when the spacebar is pressed
				if (player->jump_time >= 2) break;
				player->y_velocity = -15;
				player->jump_time++;
				break;
			}
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym) {
			case SDLK_LEFT:
				map_pos_x -= 15;//map move left when the left arrow key is pressed
				if (map_pos_x < 0)
				{
					map_pos_x = 0;
				}
				flip = SDL_FLIP_HORIZONTAL;
			case SDLK_RIGHT:
				// Stop moving when the left or right arrow key is released
				map_pos_x += 15;// map move right when the right arrow key is pressed
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
	}
	// Update player position based on vertical velocity
	player->y_pos += player->y_velocity;
	// Apply gravity to the player
	player->y_velocity += 1;
	// Keep player on the ground
	if (player->y_pos >= 500) {
		player->y_pos = 500;
		player->y_velocity = 0;
	}
	//check if player if on the ground
	if (player->y_pos == 500) {
		player->jump_time = 0;
	}
	// Update player rectangle position
	player->rect.x = player->x_pos;
	player->rect.y = player->y_pos;
}
void game_render(SDL_Renderer* render, Player* player) {
	// Clear the screen
	SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
	SDL_RenderClear(render);
	load_map(map1);
	// Render the player
	SDL_RenderCopyEx(render, player->texture, NULL, &player->rect, 0, NULL, flip);
	// Update the screen
	SDL_RenderPresent(render);
}
void game() {
	/*Image_Texture = load_image("image_save/bg4.png");
	SDL_RenderClear(render);// clear the window to black
	SDL_RenderCopy(render, Image_Texture, NULL, NULL);
	SDL_RenderPresent(render);//draw to screen
	SDL_Delay(2000);*/
	Player player;
	player.jump_time = 0;
	player.texture = load_image("image_save/player.png");
	player.rect.w = 64;
	player.rect.h = 64;
	player.x_pos = 400;
	player.y_pos = 400;
	player.speed = 2;
	// Game loop
	int running = 1;
	while (running) {
		handleInput(&player);
		update(&player);
		game_render(render, &player);
	}
	SDL_DestroyTexture(player.texture);
}

int main(int argc, char* argv[]) {
	if (init()==false)
	{
		printf("Init again! SDL_Error: \n%s", SDL_GetError());
		return 1;
	}
	else {
		map1 = gen_map("image_save/map/map1/map_text.txt", '1');

		font = TTF_OpenFont("font_save/Freedom-10eM.ttf", 40);
		if (font == NULL )
		{
			printf("Failed to load font!!!! \n%s", SDL_GetError());
		}
		else
		{
			int xm = 0;
			int ym = 0;
			showmenu("black", "black", "black");
			renderMob(mob, render);
			while (true)
			{
				SDL_Event m_event;	
				while (SDL_PollEvent(&m_event))
				{
					switch (m_event.type)
					{
					case SDL_QUIT:
						return 1;
					case SDL_MOUSEMOTION:
					{
						xm = m_event.motion.x;//toa do x cua chuot
						ym = m_event.motion.y;//toa do y cua chuot
						if ((xm >= play_game_desRect.x) && (xm <= play_game_desRect.x + play_game_desRect.w)
							&& (ym >= play_game_desRect.y) && ym <= play_game_desRect.y + play_game_desRect.h)
						{
							showmenu("red", "black","black");
						}
						else
							if ((xm >= instruction_desRect.x) && (xm <= instruction_desRect.x + instruction_desRect.w)
								&& (ym >= instruction_desRect.y) && ym <= instruction_desRect.y + instruction_desRect.h)
							{
								showmenu("black", "red", "black");
							}
							else if ((xm >= exit_desRect.x) && (xm <= exit_desRect.x + exit_desRect.w)
								&& (ym >= exit_desRect.y) && ym <= exit_desRect.y + exit_desRect.h)
							{
								showmenu("black", "black", "red");
							}
							else
							{
								showmenu("black", "black", "black");
							}

						break;
					}
					case SDL_MOUSEBUTTONDOWN:
					{
						xm = m_event.motion.x;//toa do x cua chuot
						ym = m_event.motion.y;//toa do y cua chuot
						if ((xm >= play_game_desRect.x) && (xm <= play_game_desRect.x + play_game_desRect.w)
							&& (ym >= play_game_desRect.y) && ym <= play_game_desRect.y + play_game_desRect.h)
						{
							game();
						}
						else if ((xm >= instruction_desRect.x) && (xm <= instruction_desRect.x + instruction_desRect.w)
								&& (ym >= instruction_desRect.y) && ym <= instruction_desRect.y + instruction_desRect.h)
							{
								instruction_game();
							}
							else if ((xm >= exit_desRect.x) && (xm <= exit_desRect.x + exit_desRect.w)
								&& (ym >= exit_desRect.y) && ym <= exit_desRect.y + exit_desRect.h)
							{
								return 1;
							}
						break;
					}
				    }
				}
			}	
		}
	}
	close();
	return 0;
}