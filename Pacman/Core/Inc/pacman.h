/*
 * pacman.h
 *
 *  Created on: Jun 26, 2024
 *      Author: kleme
 */
#ifndef INC_PACMAN_H_
#define INC_PACMAN_H_

#define GRID_ROWS 31
#define GRID_COLS 28

#define COLOR_BG UTIL_LCD_COLOR_BLACK
#define COLOR_WALL UTIL_LCD_COLOR_BLUE
#define COLOR_DOOR UTIL_LCD_COLOR_DARKBLUE
#define COLOR_FOOD UTIL_LCD_COLOR_WHITE
#define COLOR_POWERUP UTIL_LCD_COLOR_WHITE
#define COLOR_TEXT UTIL_LCD_COLOR_WHITE

#define COLOR_PLAYER UTIL_LCD_COLOR_YELLOW
#define COLOR_GHOST_1 UTIL_LCD_COLOR_RED
#define COLOR_GHOST_2 UTIL_LCD_COLOR_LIGHTMAGENTA
#define COLOR_GHOST_3 UTIL_LCD_COLOR_CYAN
#define COLOR_GHOST_4 UTIL_LCD_COLOR_ORANGE

#define FRUIT_DESPAWN 9000
#define GHOST_IMMUNITY 9000

typedef struct Player {
	int8_t dir_x;
	int8_t dir_y;
	int8_t cdir_x;
	int8_t cdir_y;
	uint16_t pos_x;
	uint16_t pos_y;
	uint32_t color;
	void (*ghostDraw)(struct GameData *data, struct Player *ghost);
} Player;

static uint8_t ghost_points[5] = {200, 400, 800, 1600, 3000};

typedef struct GameData {
	Player player;
	Player ghost1;
	Player ghost2;
	Player ghost3;
	Player ghost4;
	uint32_t screen_x;
	uint32_t screen_y;
	uint16_t max_score;
	uint16_t score;
	uint16_t touch_x;
	uint16_t touch_y;
	uint16_t timer_start;
	uint16_t timer;
	uint8_t ghost;
	uint8_t fruit;
	uint8_t collectables;
	uint8_t level;
	int speedPlayer;
	int speedGhost;
	uint8_t grid[GRID_ROWS][GRID_COLS];
	void (*refresh)(struct GameData *data);
	void (*Ghost2)(struct GameData *data, Player *ghost);
	void (*Ghost3)(struct GameData *data, Player *ghost);
	void (*Ghost4)(struct GameData *data, Player *ghost);


} GameData;

extern void Draw_Map_Dynamic(GameData *data);
extern void Draw_Start(GameData *data);
extern void Press_To_Start(GameData *data);
extern void Draw_Map_Static(void);
void Ghost_Enable(GameData *data, Player *ghost);
void Ghost_Disable(GameData *data, Player *ghost);
extern void Ghost_Logic(GameData *data, Player *ghost);
extern void GhostWait2(GameData *data, Player *ghost);
extern void GhostWait3(GameData *data, Player *ghost);
extern void GhostWait4(GameData *data, Player *ghost);
extern void Draw_Grid();

static uint8_t grid_data_init[GRID_ROWS][GRID_COLS] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,2,2,2,2,2,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,2,2,2,2,2,0},
		{0,2,0,0,0,0,2,0,0,0,0,0,2,0,0,2,0,0,0,0,0,2,0,0,0,0,2,0},
		{0,3,0,0,0,0,2,0,0,0,0,0,2,0,0,2,0,0,0,0,0,2,0,0,0,0,3,0},
		{0,2,0,0,0,0,2,0,0,0,0,0,2,0,0,2,0,0,0,0,0,2,0,0,0,0,2,0},
		{0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0},
		{0,2,0,0,0,0,2,0,0,2,0,0,0,0,0,0,0,0,2,0,0,2,0,0,0,0,2,0},
		{0,2,0,0,0,0,2,0,0,2,0,0,0,0,0,0,0,0,2,0,0,2,0,0,0,0,2,0},
		{0,2,2,2,2,2,2,0,0,2,2,2,2,0,0,2,2,2,2,0,0,2,2,2,2,2,2,0},
		{0,0,0,0,0,0,2,0,0,0,0,0,1,0,0,1,0,0,0,0,0,2,0,0,0,0,0,0},
		{0,0,0,0,0,0,2,0,0,0,0,0,1,0,0,1,0,0,0,0,0,2,0,0,0,0,0,0},
		{0,0,0,0,0,0,2,0,0,1,1,1,1,1,1,1,1,1,1,0,0,2,0,0,0,0,0,0},
		{0,0,0,0,0,0,2,0,0,1,0,0,0,0,0,0,0,0,1,0,0,2,0,0,0,0,0,0},
		{0,0,0,0,0,0,2,0,0,1,0,0,0,0,0,0,0,0,1,0,0,2,0,0,0,0,0,0},
		{1,1,1,1,1,1,2,1,1,1,0,0,0,0,0,0,0,0,1,1,1,2,1,1,1,1,1,1},
		{0,0,0,0,0,0,2,0,0,1,0,0,0,0,0,0,0,0,1,0,0,2,0,0,0,0,0,0},
		{0,0,0,0,0,0,2,0,0,1,0,0,0,0,0,0,0,0,1,0,0,2,0,0,0,0,0,0},
		{0,0,0,0,0,0,2,0,0,1,1,1,1,1,1,1,1,1,1,0,0,2,0,0,0,0,0,0},
		{0,0,0,0,0,0,2,0,0,1,0,0,0,0,0,0,0,0,1,0,0,2,0,0,0,0,0,0},
		{0,0,0,0,0,0,2,0,0,1,0,0,0,0,0,0,0,0,1,0,0,2,0,0,0,0,0,0},
		{0,2,2,2,2,2,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,2,2,2,2,2,0},
		{0,2,0,0,0,0,2,0,0,0,0,0,2,0,0,2,0,0,0,0,0,2,0,0,0,0,2,0},
		{0,2,0,0,0,0,2,0,0,0,0,0,2,0,0,2,0,0,0,0,0,2,0,0,0,0,2,0},
		{0,3,2,2,0,0,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,0,0,2,2,3,0},
		{0,0,0,2,0,0,2,0,0,2,0,0,0,0,0,0,0,0,2,0,0,2,0,0,2,0,0,0},
		{0,0,0,2,0,0,2,0,0,2,0,0,0,0,0,0,0,0,2,0,0,2,0,0,2,0,0,0},
		{0,2,2,2,2,2,2,0,0,2,2,2,2,0,0,2,2,2,2,0,0,2,2,2,2,2,2,0},
		{0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0},
		{0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0},
		{0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	};

static inline void GridReset(GameData *data){
	data->level++;
	if(data->level < 4) data->fruit++;
	else if(data->level < 14 && data->level%2 == 1){
		data->fruit++;
	}
	if(data->level == 2 || data->level == 5){
		data->speedPlayer--;
		data->speedGhost--;
	}else if(data->level == 21){
		data->speedGhost--;
		data->speedPlayer++;
	}
	data->collectables = 244;
	memcpy(data->grid, grid_data_init, sizeof(data->grid));
	Draw_Grid();
}

static inline void GameReset(GameData *data){
	UTIL_LCD_Clear(UTIL_LCD_COLOR_BLACK);
	data->level = 0;
	data->speedPlayer = 5;
	data->speedGhost = 6;
	data->score = 0;
	data->ghost = 0;
	data->fruit = -1;
	data->refresh = Draw_Start;
	data->Ghost2 = GhostWait2;
	data->Ghost3 = GhostWait3;
	data->Ghost4 = GhostWait4;
	GridReset(data);
}

static inline void ResetGhost(Player *data){
	data->pos_x = 240;
	data->pos_y = 104;
	data->cdir_x = -1;
	data->cdir_y = 0;
	data->ghostDraw = Ghost_Enable;
}

static inline void GhostDisable(GameData *data){
	data->ghost1.ghostDraw = Ghost_Disable;
	data->ghost2.ghostDraw = Ghost_Disable;
	data->ghost3.ghostDraw = Ghost_Disable;
	data->ghost4.ghostDraw = Ghost_Disable;
}


static inline void GhostEnable(GameData *data){
	data->ghost = 0;
	data->ghost1.ghostDraw = Ghost_Enable;
	data->ghost2.ghostDraw = Ghost_Enable;
	data->ghost3.ghostDraw = Ghost_Enable;
	data->ghost4.ghostDraw = Ghost_Enable;
}

static inline void PositionReset(GameData *data){
	data->player.pos_x = 240;
	data->player.pos_y = 200;
	data->player.dir_x = 0;
	data->player.dir_y = 0;
	data->player.cdir_x = -1;
	data->player.cdir_y = 0;
	data->player.color = COLOR_PLAYER;

	GhostEnable(data);

	data->ghost1.pos_x = 240;
	data->ghost1.pos_y = 104;
	data->ghost1.cdir_x = -1;
	data->ghost1.cdir_y = 0;
	data->ghost1.color = COLOR_GHOST_1;

	data->ghost2.pos_x = 223;
	data->ghost2.pos_y = 124;
	data->ghost2.cdir_x = -1;
	data->ghost2.cdir_y = 0;
	data->ghost2.color = COLOR_GHOST_2;

	data->ghost3.pos_x = 240;
	data->ghost3.pos_y = 124;
	data->ghost3.cdir_x = -1;
	data->ghost3.cdir_y = 0;
	data->ghost3.color = COLOR_GHOST_3;

	data->ghost4.pos_x = 257;
	data->ghost4.pos_y = 124;
	data->ghost4.cdir_x = -1;
	data->ghost4.cdir_y = 0;
	data->ghost4.color = COLOR_GHOST_4;
}


static inline GameData GameData_Init(uint32_t max_score){
	GameData data;
	data.max_score = max_score;
	return data;
}


#endif /* INC_PACMAN_H_ */
