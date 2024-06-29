/*
 * pacman.c
 *
 *  Created on: Jun 26, 2024
 *      Author: kleme
 */
#include "main.h"
#include "pacman.h"

char high_score[8];
char score[8];
int loopPlayer = 0;
int loopGhost = 0;

void Draw_Start(GameData *data){
	Draw_Map_Static();
	PositionReset(data);
	Draw_Map_Dynamic(data);
	UTIL_LCD_DrawVLine(212, 121, 16, COLOR_BG);
	UTIL_LCD_DisplayStringAt(212,121,"START", LEFT_MODE);
	data->refresh = Press_To_Start;
}

void Clear_Text(){
	UTIL_LCD_DrawHLine(212, 121, 60, COLOR_BG);
	UTIL_LCD_DrawHLine(212, 122, 60, COLOR_BG);
	UTIL_LCD_DrawHLine(212, 123, 60, COLOR_BG);
	UTIL_LCD_DrawHLine(212, 124, 60, COLOR_BG);
	UTIL_LCD_DrawHLine(212, 125, 60, COLOR_BG);
	UTIL_LCD_DrawHLine(212, 126, 60, COLOR_BG);
	UTIL_LCD_DrawHLine(212, 127, 60, COLOR_BG);
	UTIL_LCD_DrawHLine(212, 128, 60, COLOR_BG);
	UTIL_LCD_DrawHLine(212, 129, 60, COLOR_BG);
	UTIL_LCD_DrawHLine(212, 130, 60, COLOR_BG);
	UTIL_LCD_DrawHLine(212, 131, 60, COLOR_BG);
	UTIL_LCD_DrawHLine(212, 132, 60, COLOR_BG);
	UTIL_LCD_DrawHLine(212, 133, 60, COLOR_BG);
	UTIL_LCD_DrawHLine(212, 134, 60, COLOR_BG);
	UTIL_LCD_DrawHLine(212, 135, 60, COLOR_BG);
	UTIL_LCD_DrawVLine(212, 113, 30, COLOR_WALL);
	UTIL_LCD_DrawVLine(215, 116, 24, COLOR_WALL);
	UTIL_LCD_DrawVLine(264, 116, 24, COLOR_WALL);
	UTIL_LCD_DrawVLine(267, 113, 30, COLOR_WALL);
}

void Game_Over(GameData *data){
	UTIL_LCD_DrawVLine(212, 121, 16, COLOR_BG);
	UTIL_LCD_DisplayStringAt(213,121,"RETRY", LEFT_MODE);
	if (data->touch_x < 128) {
			data->player.cdir_x = -1;
	} else if (data->touch_x > 128 && data->touch_x < 352
		 && data->touch_y > 0 && data->touch_y < data->screen_y){
		loopPlayer = 0;
		Clear_Text();
		GameReset(data);
	} else if (data->touch_x < data->screen_x){
		data->player.cdir_x = 1;
	}
}

void Press_To_Start(GameData *data){
	loopPlayer++;

	if (data->touch_x < 128) {
		data->player.cdir_x = -1;
	}else if (data->touch_x > 128 && data->touch_x < 352
			&& data->touch_y > 0 && data->touch_y < data->screen_y) {
		loopPlayer = 0;
		Clear_Text();
		data->refresh = Draw_Map_Dynamic;
	} else if (data->touch_x < data->screen_x){
		data->player.cdir_x = 1;
	}

	if(loopPlayer == 300) UTIL_LCD_DisplayStringAt(213,121,"PRESS", LEFT_MODE);
	else if(loopPlayer == 600) {
		Clear_Text();
		UTIL_LCD_DisplayStringAt(230,121,"TO", LEFT_MODE);
	}
	else if(loopPlayer == 900) {
		UTIL_LCD_DrawVLine(212, 121, 16, COLOR_BG);
		UTIL_LCD_DisplayStringAt(213,121,"START", LEFT_MODE);
		loopPlayer = 0;
	}
}


void Draw_Fruit(GameData *data){}
void (*Fruit)(struct GameData *data) = Draw_Fruit;
uint16_t timer_start;

void Fruit_Clear(){
	UTIL_LCD_DrawHLine(236, 148, 8, COLOR_BG);
	UTIL_LCD_DrawHLine(236, 149, 8, COLOR_BG);
	UTIL_LCD_DrawHLine(236, 150, 8, COLOR_BG);
	UTIL_LCD_DrawHLine(236, 151, 8, COLOR_BG);
	UTIL_LCD_DrawHLine(236, 152, 8, COLOR_BG);
	UTIL_LCD_DrawHLine(236, 153, 8, COLOR_BG);
	UTIL_LCD_DrawHLine(236, 154, 8, COLOR_BG);
	UTIL_LCD_DrawHLine(236, 155, 8, COLOR_BG);
	Fruit = Draw_Fruit;
}

void Draw_Fruit_1(GameData *data){
	if(data->timer - timer_start > FRUIT_DESPAWN){
		Fruit_Clear();
		return;
	}
	if(data->player.pos_x > 236 && data->player.pos_x < 244
	   && data->player.pos_y > 148 && data->player.pos_y < 156){
		data->score+=10;
		Fruit_Clear();
		return;
	}

	UTIL_LCD_DrawHLine(237, 150, 4, UTIL_LCD_COLOR_RED);
	UTIL_LCD_DrawHLine(236, 151, 6, UTIL_LCD_COLOR_RED);
	UTIL_LCD_DrawHLine(236, 152, 6, UTIL_LCD_COLOR_RED);
	UTIL_LCD_DrawHLine(237, 153, 4, UTIL_LCD_COLOR_RED);
}

void Draw_Fruit_2(GameData *data){
	if(data->timer - timer_start > FRUIT_DESPAWN){
		Fruit_Clear();
		return;
	}
	if(data->player.pos_x > 236 && data->player.pos_x < 244
	   && data->player.pos_y > 148 && data->player.pos_y < 156){
		data->score+=30;
		Fruit_Clear();
		return;
	}

	UTIL_LCD_DrawHLine(237, 149, 4, UTIL_LCD_COLOR_GREEN);
	UTIL_LCD_DrawHLine(236, 150, 6, UTIL_LCD_COLOR_RED);
	UTIL_LCD_DrawHLine(236, 151, 6, UTIL_LCD_COLOR_RED);
	UTIL_LCD_DrawHLine(237, 152, 4, UTIL_LCD_COLOR_RED);
	UTIL_LCD_DrawHLine(237, 153, 4, UTIL_LCD_COLOR_RED);
	UTIL_LCD_DrawHLine(238, 154, 2, UTIL_LCD_COLOR_RED);
}

void Draw_Fruit_3(GameData *data){
	if(data->timer - timer_start > FRUIT_DESPAWN){
		Fruit_Clear();
		return;
	}
	if(data->player.pos_x > 236 && data->player.pos_x < 244
	   && data->player.pos_y > 148 && data->player.pos_y < 156){
		data->score+=50;
		Fruit_Clear();
		return;
	}

	UTIL_LCD_DrawHLine(238, 149, 2, UTIL_LCD_COLOR_GREEN);
	UTIL_LCD_DrawHLine(237, 150, 4, UTIL_LCD_COLOR_ORANGE);
	UTIL_LCD_DrawHLine(236, 151, 6, UTIL_LCD_COLOR_ORANGE);
	UTIL_LCD_DrawHLine(236, 152, 6, UTIL_LCD_COLOR_ORANGE);
	UTIL_LCD_DrawHLine(237, 153, 4, UTIL_LCD_COLOR_ORANGE);
}

void Draw_Fruit_4(GameData *data){
	if(data->timer - timer_start > FRUIT_DESPAWN){
		Fruit_Clear();
		return;
	}
	if(data->player.pos_x > 236 && data->player.pos_x < 244
	   && data->player.pos_y > 148 && data->player.pos_y < 156){
		data->score+=70;
		Fruit_Clear();
		return;
	}

	UTIL_LCD_DrawHLine(237, 149, 4, UTIL_LCD_COLOR_RED);
	UTIL_LCD_DrawHLine(236, 150, 6, UTIL_LCD_COLOR_RED);
	UTIL_LCD_DrawHLine(236, 151, 6, UTIL_LCD_COLOR_RED);
	UTIL_LCD_DrawHLine(236, 152, 6, UTIL_LCD_COLOR_RED);
	UTIL_LCD_DrawHLine(237, 153, 4, UTIL_LCD_COLOR_RED);
	UTIL_LCD_DrawHLine(238, 154, 2, UTIL_LCD_COLOR_RED);
}

void Draw_Fruit_5(GameData *data){
	if(data->timer - timer_start > FRUIT_DESPAWN){
		Fruit_Clear();
		return;
	}
	if(data->player.pos_x > 236 && data->player.pos_x < 244
	   && data->player.pos_y > 148 && data->player.pos_y < 156){
		data->score+=100;
		Fruit_Clear();
		return;
	}
	UTIL_LCD_DrawHLine(237, 149, 4, UTIL_LCD_COLOR_GREEN);
	UTIL_LCD_DrawHLine(236, 150, 6, UTIL_LCD_COLOR_GREEN);
	UTIL_LCD_DrawHLine(236, 151, 6, UTIL_LCD_COLOR_GREEN);
	UTIL_LCD_DrawHLine(236, 152, 6, UTIL_LCD_COLOR_GREEN);
	UTIL_LCD_DrawHLine(237, 153, 4, UTIL_LCD_COLOR_GREEN);
	UTIL_LCD_DrawHLine(238, 154, 2, UTIL_LCD_COLOR_GREEN);
}

void Draw_Fruit_6(GameData *data){
	if(data->timer - timer_start > FRUIT_DESPAWN){
		Fruit_Clear();
		return;
	}
	if(data->player.pos_x > 236 && data->player.pos_x < 244
	   && data->player.pos_y > 148 && data->player.pos_y < 156){
		data->score+=200;
		Fruit_Clear();
		return;
	}
	UTIL_LCD_DrawHLine(238, 149, 2, UTIL_LCD_COLOR_RED);
	UTIL_LCD_DrawHLine(237, 150, 4, UTIL_LCD_COLOR_RED);
	UTIL_LCD_DrawHLine(236, 151, 6, UTIL_LCD_COLOR_RED);
	UTIL_LCD_DrawHLine(236, 152, 6, UTIL_LCD_COLOR_YELLOW);
	UTIL_LCD_DrawHLine(237, 153, 4, UTIL_LCD_COLOR_YELLOW);
	UTIL_LCD_DrawHLine(236, 154, 6, UTIL_LCD_COLOR_BLUE);
}

void Draw_Fruit_7(GameData *data){
	if(data->timer - timer_start > FRUIT_DESPAWN){
		Fruit_Clear();
		return;
	}
	if(data->player.pos_x > 236 && data->player.pos_x < 244
	   && data->player.pos_y > 148 && data->player.pos_y < 156){
		data->score+=300;
		Fruit_Clear();
		return;
	}
	UTIL_LCD_DrawHLine(238, 149, 2, UTIL_LCD_COLOR_YELLOW);
	UTIL_LCD_DrawHLine(237, 150, 4, UTIL_LCD_COLOR_YELLOW);
	UTIL_LCD_DrawHLine(237, 151, 4, UTIL_LCD_COLOR_YELLOW);
	UTIL_LCD_DrawHLine(246, 152, 6, UTIL_LCD_COLOR_YELLOW);
	UTIL_LCD_DrawHLine(246, 153, 6, UTIL_LCD_COLOR_YELLOW);
	UTIL_LCD_DrawHLine(247, 154, 4, UTIL_LCD_COLOR_LIGHTBLUE);
}

void Draw_Fruit_8(GameData *data){
	if(data->timer - timer_start > FRUIT_DESPAWN){
		Fruit_Clear();
		return;
	}
	if(data->player.pos_x > 236 && data->player.pos_x < 244
	   && data->player.pos_y > 148 && data->player.pos_y < 156){
		data->score+=500;
		Fruit_Clear();
		return;
	}
	UTIL_LCD_DrawHLine(238, 149, 2, UTIL_LCD_COLOR_LIGHTBLUE);
	UTIL_LCD_DrawHLine(237, 150, 4, UTIL_LCD_COLOR_LIGHTBLUE);
	UTIL_LCD_DrawHLine(236, 151, 6, UTIL_LCD_COLOR_GRAY);
	UTIL_LCD_DrawHLine(246, 152, 6, UTIL_LCD_COLOR_GRAY);
	UTIL_LCD_DrawHLine(247, 153, 4, UTIL_LCD_COLOR_GRAY);
	UTIL_LCD_DrawHLine(248, 154, 1, UTIL_LCD_COLOR_GRAY);
}


static void (*fruits[])(struct GameData *data) = {Draw_Fruit_1, Draw_Fruit_2, Draw_Fruit_3, Draw_Fruit_4, Draw_Fruit_5, Draw_Fruit_6, Draw_Fruit_7, Draw_Fruit_8};

void GhostWait2(GameData *data, Player *ghost){
	if(data->collectables == 150){
		Draw_Ghost(ghost->pos_x, ghost->pos_y, COLOR_BG);
		ghost->pos_x = 240;
		ghost->pos_y = 104;
		data->Ghost2 = Ghost_Logic;
	}else Ghost_Logic(data, ghost);
}

void GhostWait3(GameData *data, Player *ghost){
	if(data->collectables == 100){
		Draw_Ghost(ghost->pos_x, ghost->pos_y, COLOR_BG);
		ghost->pos_x = 240;
		ghost->pos_y = 104;
		data->Ghost3 = Ghost_Logic;
	}else Ghost_Logic(data, ghost);
}

void GhostWait4(GameData *data, Player *ghost){
	if(data->collectables == 50){
		Draw_Ghost(ghost->pos_x, ghost->pos_y, COLOR_BG);
		ghost->pos_x = 240;
		ghost->pos_y = 104;
		data->Ghost4 = Ghost_Logic;
	}else Ghost_Logic(data, ghost);
}



void Draw_Map_Dynamic(GameData *data){
	Player_Touch_Controls(data);

	if(data->collectables == 0) {
		GridReset(data);
	}else if(data->collectables==174 || data->collectables == 74){
		timer_start = data->timer;
		Fruit=fruits[data->fruit];
	}
	sprintf(score, "%d0", data->score);
	sprintf(high_score, "%d0", data->max_score);
	UTIL_LCD_DisplayStringAt(9,29,(uint8_t *)score, LEFT_MODE);
	UTIL_LCD_DisplayStringAt(360,29,(uint8_t *)high_score, LEFT_MODE);

	loopGhost++;
	loopPlayer++;
	if(loopGhost == data->speedGhost){
		loopGhost = 0;
		Ghost_Logic(data, &data->ghost1);
		data->Ghost2(data, &data->ghost2);
		data->Ghost3(data, &data->ghost3);
		data->Ghost4(data, &data->ghost4);
	}
	Fruit(data);
	if(loopPlayer == data->speedPlayer) {
		loopPlayer = 0;
		Player_Logic(data);
	}

}

void Ghost_Logic(GameData *data, Player *ghost){

	int normalized_x = (ghost->pos_x - 125);
	int normalized_y = (ghost->pos_y - 9);
	int cx = (normalized_x / 8);
	int cy = (normalized_y / 8);

	if (normalized_x%8 > 5 && normalized_y%8 > 5){
		if(ghost->cdir_x != 0){
			if(rand()%2 == 0 || data->grid[cy][cx+ghost->cdir_x]==0){
				if(rand()%2 == 0 && data->grid[cy+1][cx]>0){
					ghost->cdir_x = 0;
					ghost->cdir_y = 1;
				}else if(data->grid[cy-1][cx]>0){
					ghost->cdir_x = 0;
					ghost->cdir_y = -1;
				}
			}
		}else{
			if(rand()%2 == 0 || data->grid[cy+ghost->cdir_y][cx]==0){
				if(rand()%2 == 0 && data->grid[cy][cx+1]>0){
					ghost->cdir_x = 1;
					ghost->cdir_y = 0;
				}else if(data->grid[cy][cx-1]>0){
					ghost->cdir_x = -1;
					ghost->cdir_y = 0;
				}
			}
		}
	}
	int x = cx + ghost->cdir_x;
	int y = cy + ghost->cdir_y;
	Draw_Ghost(ghost->pos_x, ghost->pos_y, COLOR_BG);

	if(ghost->cdir_x<0 || ghost->cdir_y<0) Draw_GridCell(data, cy, cx);
	else Draw_GridCell(data, cy-ghost->cdir_y, cx-ghost->cdir_x);

	if(x == GRID_COLS){
		ghost->pos_x+=ghost->cdir_x;
	}
	else if(x==-1){
		ghost->pos_x = 27*8+125;
		x = GRID_COLS-1;
	}
	else if (x == GRID_COLS+1) {
		ghost->pos_x = 128;
		x = 0;
	}
	if(data->grid[y][x]>0){
		ghost->pos_x+=ghost->cdir_x;
		ghost->pos_y+=ghost->cdir_y;
	}else if(ghost->cdir_x == 1 && normalized_x%8 < 6){
		ghost->pos_x+=ghost->cdir_x;
	}else if(ghost->cdir_y == 1 && normalized_y%8 < 6) {
		ghost->pos_y+=ghost->cdir_y;
	}


	ghost->ghostDraw(data, ghost);
}

void Ghost_Enable(GameData *data, Player *ghost){
	if (abs(data->player.pos_x - ghost->pos_x)<8
		&& abs(data->player.pos_y - ghost->pos_y)<8){
		data->refresh = Game_Over;
	}
	Draw_Ghost(ghost->pos_x, ghost->pos_y, ghost->color);

}

void Ghost_Disable(GameData *data, Player *ghost){
	if (data->timer - data->timer_start > GHOST_IMMUNITY){
			GhostEnable(data);
	}
	if (abs(data->player.pos_x - ghost->pos_x)<10
		&& abs(data->player.pos_y - ghost->pos_y)<10){
		data->score+=ghost_points[data->ghost];
		data->ghost++;
		if(data->ghost == 4){
			data->score+=ghost_points[data->ghost];
			data->ghost = 0;
		}
		ResetGhost(ghost);
	}
	Draw_Ghost(ghost->pos_x, ghost->pos_y, UTIL_LCD_COLOR_LIGHTGRAY);
}

void Draw_Ghost(uint32_t Xpos, uint32_t Ypos, uint32_t Color){
	Xpos-=3;
	Ypos-=4;
	UTIL_LCD_DrawHLine(Xpos+1, Ypos++, 5, Color);
	UTIL_LCD_DrawHLine(Xpos, Ypos++, 7, Color);
	UTIL_LCD_DrawHLine(Xpos, Ypos++, 7, Color);
	UTIL_LCD_DrawHLine(Xpos, Ypos++, 7, Color);
	UTIL_LCD_DrawHLine(Xpos, Ypos++, 7, Color);
	UTIL_LCD_DrawHLine(Xpos, Ypos++, 7, Color);
	UTIL_LCD_DrawHLine(Xpos, Ypos++, 7, Color);
	UTIL_LCD_DrawHLine(Xpos, Ypos, 7, Color);
}

void Player_Touch_Controls(GameData *data){
	if (data->touch_x < 128) {
		if(data->touch_y > 41) {
			if(data->touch_y > 119) {
				if(data->touch_y > 189) {
					data->player.dir_x = 0;
					data->player.dir_y=1;
				}else if(data->touch_y < data->screen_y)  {
					data->player.dir_x=-1;
					data->player.dir_y=0;
				}else {
					data->player.dir_x=0;
					data->player.dir_y=0;
				}
			} else {
				data->player.dir_x=0;
				data->player.dir_y=-1;
			}
		}else {
			data->player.dir_x=0;
			data->player.dir_y=0;
		}
	} else if (data->touch_x > 352 && data->touch_x < data->screen_x) {
		if(data->touch_y > 41) {
			if(data->touch_y > 119) {
				if(data->touch_y > 189) {
					data->player.dir_x=0;
					data->player.dir_y=1;
				}else if(data->touch_y < data->screen_y) {
					data->player.dir_x=1;
					data->player.dir_y=0;
				}else {
					data->player.dir_x=0;
					data->player.dir_y=0;
				}
			} else {
				data->player.dir_x=0;
				data->player.dir_y=-1;
			}
		}else {
			data->player.dir_x=0;
			data->player.dir_y=0;
		}
	} else {
		data->player.dir_x=0;
		data->player.dir_y=0;
	}
}

void Player_Logic(GameData *data){
	int normalized_x = (data->player.pos_x - 125);
	int normalized_y = (data->player.pos_y - 9);
	int cx = (normalized_x / 8);
	int cy = (normalized_y / 8);

	if ((data->player.dir_x != 0 && data->player.cdir_x == -data->player.dir_x)
		|| (data->player.dir_y  != 0 && data->player.cdir_y == -data->player.dir_y)
		|| ((data->player.dir_x != 0 || data->player.dir_y != 0) && normalized_x%8 > 5 && normalized_y%8 > 5 && data->grid[cy+data->player.dir_y][cx+data->player.dir_x] > 0)){
		data->player.cdir_x = data->player.dir_x;
		data->player.cdir_y = data->player.dir_y;
	}


	int x = cx + data->player.cdir_x;
	int y = cy + data->player.cdir_y;
	UTIL_LCD_FillCircle(data->player.pos_x, data->player.pos_y, 5, COLOR_BG);
	if(x == GRID_COLS){
		data->player.pos_x+=data->player.cdir_x;
	}
	else if(x==-1){
		data->player.pos_x = 27*8+125;
		x = GRID_COLS-1;
	}
	else if (x == GRID_COLS+1) {
		data->player.pos_x = 128;
		x = 0;
	}
	if(data->grid[y][x]>0){
		if (data->grid[y][x] == 2) {
			data->score+=10;
			data->collectables--;
		}else if (data->grid[y][x] == 3) {
			data->collectables--;
			data->score+=50;
			data->timer_start = data->timer;
			GhostDisable(data);
		}
		if (data->max_score < data->score) {
			data->max_score = data->score;
		}
		data->grid[y][x] = 1;
		data->player.pos_x+=data->player.cdir_x;
		data->player.pos_y+=data->player.cdir_y;
	}else if(data->player.cdir_x == 1 && normalized_x%8 < 6){
		data->player.pos_x+=data->player.cdir_x;
	}else if(data->player.cdir_y == 1 && normalized_y%8 < 6) {
		data->player.pos_y+=data->player.cdir_y;
	}
	UTIL_LCD_FillCircle(data->player.pos_x, data->player.pos_y, 5, data->player.color);
}



void Draw_GridCell(GameData *data, int i, int j){
	int x,y;
	switch(data->grid[i][j]){
		case 2:
			x = 8*j+132;
			y = 8*i+15;
			UTIL_LCD_DrawVLine(x--, y, 2, COLOR_FOOD);
			UTIL_LCD_DrawVLine(x, y, 2, COLOR_FOOD);
			break;
		case 3:
			x = 8*j+128;
			y = 8*i+14;
			UTIL_LCD_DrawVLine(x++, y--, 4, COLOR_POWERUP);
			UTIL_LCD_DrawVLine(x++, y--, 6, COLOR_POWERUP);
			UTIL_LCD_DrawVLine(x++, y, 8, COLOR_POWERUP);
			UTIL_LCD_DrawVLine(x++, y, 8, COLOR_POWERUP);
			UTIL_LCD_DrawVLine(x++, y, 8, COLOR_POWERUP);
			UTIL_LCD_DrawVLine(x++, y++, 8, COLOR_POWERUP);
			UTIL_LCD_DrawVLine(x++, y++, 6, COLOR_POWERUP);
			UTIL_LCD_DrawVLine(x, y, 4, COLOR_POWERUP);
			break;
	}
}

void Draw_Grid(){
	int x, y;
	for (int i = 1; i < GRID_ROWS-1; i++) {
		for (int j = 1; j < GRID_COLS-1; j++) {
			switch(grid_data_init[i][j]){
				case 2:
					x = 8*j+132;
					y = 8*i+15;
					UTIL_LCD_DrawVLine(x--, y, 2, COLOR_FOOD);
					UTIL_LCD_DrawVLine(x, y, 2, COLOR_FOOD);
					break;
				case 3:
					x = 8*j+128;
					y = 8*i+14;
					UTIL_LCD_DrawVLine(x++, y--, 4, COLOR_POWERUP);
					UTIL_LCD_DrawVLine(x++, y--, 6, COLOR_POWERUP);
					UTIL_LCD_DrawVLine(x++, y, 8, COLOR_POWERUP);
					UTIL_LCD_DrawVLine(x++, y, 8, COLOR_POWERUP);
					UTIL_LCD_DrawVLine(x++, y, 8, COLOR_POWERUP);
					UTIL_LCD_DrawVLine(x++, y++, 8, COLOR_POWERUP);
					UTIL_LCD_DrawVLine(x++, y++, 6, COLOR_POWERUP);
					UTIL_LCD_DrawVLine(x, y, 4, COLOR_POWERUP);
					break;
			}

		}
	}
}


void Draw_Map_Static(){

	UTIL_LCD_SetTextColor(COLOR_TEXT);
	UTIL_LCD_SetBackColor(COLOR_BG);

	UTIL_LCD_SetFont(&arrows);
	UTIL_LCD_DisplayChar(52,78,32);
	UTIL_LCD_DisplayChar(52,152,34);
	UTIL_LCD_DisplayChar(52,226,33);


	UTIL_LCD_DisplayChar(410,78,32);
	UTIL_LCD_DisplayChar(410,152,35);
	UTIL_LCD_DisplayChar(410,226,33);

	UTIL_LCD_SetFont(&Font16);

	UTIL_LCD_DisplayStringAt(9,12,"SCORE", LEFT_MODE);
	UTIL_LCD_DisplayStringAt(360,12,"HIGH SCORE", LEFT_MODE);

	UTIL_LCD_DrawHLine(232, 113, 16, COLOR_DOOR);
	UTIL_LCD_DrawHLine(232, 114, 16, COLOR_DOOR);

	UTIL_LCD_DrawHLine(129, 12, 222, COLOR_WALL);

	UTIL_LCD_DrawHLine(132, 15, 105, COLOR_WALL);
	UTIL_LCD_DrawHLine(244, 15, 105, COLOR_WALL);

	UTIL_LCD_DrawHLine(149, 32, 22, COLOR_WALL);
	UTIL_LCD_DrawHLine(189, 32, 30, COLOR_WALL);
	UTIL_LCD_DrawHLine(261, 32, 30, COLOR_WALL);
	UTIL_LCD_DrawHLine(309, 32, 22, COLOR_WALL);

	UTIL_LCD_DrawHLine(149, 47, 22, COLOR_WALL);
	UTIL_LCD_DrawHLine(189, 47, 30, COLOR_WALL);
	UTIL_LCD_DrawHLine(237, 47, 6, COLOR_WALL);
	UTIL_LCD_DrawHLine(261, 47, 30, COLOR_WALL);
	UTIL_LCD_DrawHLine(309, 47, 22, COLOR_WALL);

	UTIL_LCD_DrawHLine(149, 64, 22, COLOR_WALL);
	UTIL_LCD_DrawHLine(189, 64, 6, COLOR_WALL);
	UTIL_LCD_DrawHLine(213, 64, 54, COLOR_WALL);
	UTIL_LCD_DrawHLine(285, 64, 6, COLOR_WALL);
	UTIL_LCD_DrawHLine(309, 64, 22, COLOR_WALL);

	UTIL_LCD_DrawHLine(149, 71, 22, COLOR_WALL);
	UTIL_LCD_DrawHLine(213, 71, 23, COLOR_WALL);
	UTIL_LCD_DrawHLine(244, 71, 23, COLOR_WALL);
	UTIL_LCD_DrawHLine(309, 71, 22, COLOR_WALL);

	UTIL_LCD_DrawHLine(132, 88, 39, COLOR_WALL);
	UTIL_LCD_DrawHLine(196, 88, 23, COLOR_WALL);
	UTIL_LCD_DrawHLine(261, 88, 23, COLOR_WALL);
	UTIL_LCD_DrawHLine(309, 88, 39, COLOR_WALL);

	UTIL_LCD_DrawHLine(129, 91, 40, COLOR_WALL);
	UTIL_LCD_DrawHLine(312, 91, 40, COLOR_WALL);

	UTIL_LCD_DrawHLine(196, 95, 23, COLOR_WALL);
	UTIL_LCD_DrawHLine(237, 95, 6, COLOR_WALL);
	UTIL_LCD_DrawHLine(261, 95, 23, COLOR_WALL);

	UTIL_LCD_DrawHLine(212, 112, 20, COLOR_WALL);
	UTIL_LCD_DrawHLine(248, 112, 20, COLOR_WALL);

	UTIL_LCD_DrawHLine(215, 115, 17, COLOR_WALL);
	UTIL_LCD_DrawHLine(248, 115, 17, COLOR_WALL);

	UTIL_LCD_DrawHLine(128, 116, 40, COLOR_WALL);
	UTIL_LCD_DrawHLine(312, 116, 40, COLOR_WALL);

	UTIL_LCD_DrawHLine(128, 119, 43, COLOR_WALL);
	UTIL_LCD_DrawHLine(189, 119, 6, COLOR_WALL);
	UTIL_LCD_DrawHLine(285, 119, 6, COLOR_WALL);
	UTIL_LCD_DrawHLine(309, 119, 43, COLOR_WALL);

	UTIL_LCD_DrawHLine(128, 136, 43, COLOR_WALL);
	UTIL_LCD_DrawHLine(189, 136, 6, COLOR_WALL);
	UTIL_LCD_DrawHLine(285, 136, 6, COLOR_WALL);
	UTIL_LCD_DrawHLine(309, 136, 43, COLOR_WALL);

	UTIL_LCD_DrawHLine(128, 139, 40, COLOR_WALL);
	UTIL_LCD_DrawHLine(312, 139, 40, COLOR_WALL);

	UTIL_LCD_DrawHLine(215, 140, 50, COLOR_WALL);
	UTIL_LCD_DrawHLine(212, 143, 56, COLOR_WALL);

	UTIL_LCD_DrawHLine(213, 160, 54, COLOR_WALL);

	UTIL_LCD_DrawHLine(129, 164, 39, COLOR_WALL);
	UTIL_LCD_DrawHLine(312, 164, 39, COLOR_WALL);

	UTIL_LCD_DrawHLine(132, 167, 39, COLOR_WALL);
	UTIL_LCD_DrawHLine(189, 167, 6, COLOR_WALL);
	UTIL_LCD_DrawHLine(213, 167, 23, COLOR_WALL);
	UTIL_LCD_DrawHLine(244, 167, 23, COLOR_WALL);
	UTIL_LCD_DrawHLine(285, 167, 6, COLOR_WALL);
	UTIL_LCD_DrawHLine(309, 167, 39, COLOR_WALL);

	UTIL_LCD_DrawHLine(149, 184, 22, COLOR_WALL);
	UTIL_LCD_DrawHLine(189, 184, 30, COLOR_WALL);
	UTIL_LCD_DrawHLine(261, 184, 30, COLOR_WALL);
	UTIL_LCD_DrawHLine(309, 184, 22, COLOR_WALL);

	UTIL_LCD_DrawHLine(149, 191, 15, COLOR_WALL);
	UTIL_LCD_DrawHLine(189, 191, 30, COLOR_WALL);
	UTIL_LCD_DrawHLine(237, 191, 6, COLOR_WALL);
	UTIL_LCD_DrawHLine(261, 191, 30, COLOR_WALL);
	UTIL_LCD_DrawHLine(316, 191, 15, COLOR_WALL);

	UTIL_LCD_DrawHLine(132, 208, 15, COLOR_WALL);
	UTIL_LCD_DrawHLine(189, 208, 6, COLOR_WALL);
	UTIL_LCD_DrawHLine(213, 208, 54, COLOR_WALL);
	UTIL_LCD_DrawHLine(285, 208, 6, COLOR_WALL);
	UTIL_LCD_DrawHLine(333, 208, 15, COLOR_WALL);

	UTIL_LCD_DrawHLine(132, 215, 15, COLOR_WALL);
	UTIL_LCD_DrawHLine(165, 215, 6, COLOR_WALL);
	UTIL_LCD_DrawHLine(213, 215, 23, COLOR_WALL);
	UTIL_LCD_DrawHLine(244, 215, 23, COLOR_WALL);
	UTIL_LCD_DrawHLine(309, 215, 6, COLOR_WALL);
	UTIL_LCD_DrawHLine(333, 215, 15, COLOR_WALL);

	UTIL_LCD_DrawHLine(149, 232, 39, COLOR_WALL);
	UTIL_LCD_DrawHLine(196, 232, 23, COLOR_WALL);
	UTIL_LCD_DrawHLine(261, 232, 23, COLOR_WALL);
	UTIL_LCD_DrawHLine(292, 232, 39, COLOR_WALL);

	UTIL_LCD_DrawHLine(149, 239, 70, COLOR_WALL);
	UTIL_LCD_DrawHLine(237, 239, 6, COLOR_WALL);
	UTIL_LCD_DrawHLine(261, 239, 70, COLOR_WALL);

	UTIL_LCD_DrawHLine(132, 256, 216, COLOR_WALL);

	UTIL_LCD_DrawHLine(129, 259, 222, COLOR_WALL);

//--------------------------------------------------------//



	UTIL_LCD_DrawVLine(128, 13, 78, COLOR_WALL);
	UTIL_LCD_DrawVLine(128, 165, 94, COLOR_WALL);

	UTIL_LCD_DrawVLine(131, 16, 72, COLOR_WALL);
	UTIL_LCD_DrawVLine(131, 168, 40, COLOR_WALL);
	UTIL_LCD_DrawVLine(131, 216, 40, COLOR_WALL);

	UTIL_LCD_DrawVLine(147, 209, 6, COLOR_WALL);

	UTIL_LCD_DrawVLine(148, 33, 14, COLOR_WALL);
	UTIL_LCD_DrawVLine(148, 65, 6, COLOR_WALL);
	UTIL_LCD_DrawVLine(148, 185, 6, COLOR_WALL);
	UTIL_LCD_DrawVLine(148, 233, 6, COLOR_WALL);

	UTIL_LCD_DrawVLine(164, 192, 23, COLOR_WALL);

	UTIL_LCD_DrawVLine(168, 92, 24, COLOR_WALL);
	UTIL_LCD_DrawVLine(168, 140, 24, COLOR_WALL);

	UTIL_LCD_DrawVLine(171, 33, 14, COLOR_WALL);
	UTIL_LCD_DrawVLine(171, 65, 6, COLOR_WALL);
	UTIL_LCD_DrawVLine(171, 89, 30, COLOR_WALL);
	UTIL_LCD_DrawVLine(171, 137, 30, COLOR_WALL);
	UTIL_LCD_DrawVLine(171, 185, 30, COLOR_WALL);

	UTIL_LCD_DrawVLine(188, 33, 14, COLOR_WALL);
	UTIL_LCD_DrawVLine(188, 65, 54, COLOR_WALL);
	UTIL_LCD_DrawVLine(188, 137, 30, COLOR_WALL);
	UTIL_LCD_DrawVLine(188, 185, 6, COLOR_WALL);
	UTIL_LCD_DrawVLine(188, 209, 23, COLOR_WALL);

	UTIL_LCD_DrawVLine(195, 65, 23, COLOR_WALL);
	UTIL_LCD_DrawVLine(195, 96, 23, COLOR_WALL);
	UTIL_LCD_DrawVLine(195, 137, 30, COLOR_WALL);
	UTIL_LCD_DrawVLine(195, 209, 23, COLOR_WALL);

	UTIL_LCD_DrawVLine(212, 65, 6, COLOR_WALL);
	UTIL_LCD_DrawVLine(212, 113, 30, COLOR_WALL);
	UTIL_LCD_DrawVLine(212, 161, 6, COLOR_WALL);
	UTIL_LCD_DrawVLine(212, 209, 6, COLOR_WALL);

	UTIL_LCD_DrawVLine(215, 116, 24, COLOR_WALL);

	UTIL_LCD_DrawVLine(219, 33, 14, COLOR_WALL);
	UTIL_LCD_DrawVLine(219, 89, 6, COLOR_WALL);
	UTIL_LCD_DrawVLine(219, 185, 6, COLOR_WALL);
	UTIL_LCD_DrawVLine(219, 233, 6, COLOR_WALL);

	UTIL_LCD_DrawVLine(231, 113, 2, COLOR_WALL);

	UTIL_LCD_DrawVLine(236, 16, 31, COLOR_WALL);
	UTIL_LCD_DrawVLine(236, 72, 23, COLOR_WALL);
	UTIL_LCD_DrawVLine(236, 168, 23, COLOR_WALL);
	UTIL_LCD_DrawVLine(236, 216, 23, COLOR_WALL);

//--------------------------------------------------------//

	UTIL_LCD_DrawVLine(243, 16, 31, COLOR_WALL);
	UTIL_LCD_DrawVLine(243, 72, 23, COLOR_WALL);
	UTIL_LCD_DrawVLine(243, 168, 23, COLOR_WALL);
	UTIL_LCD_DrawVLine(243, 216, 23, COLOR_WALL);

	UTIL_LCD_DrawVLine(248, 113, 2, COLOR_WALL);

	UTIL_LCD_DrawVLine(260, 233, 6, COLOR_WALL);
	UTIL_LCD_DrawVLine(260, 185, 6, COLOR_WALL);
	UTIL_LCD_DrawVLine(260, 89, 6, COLOR_WALL);
	UTIL_LCD_DrawVLine(260, 33, 14, COLOR_WALL);

	UTIL_LCD_DrawVLine(264, 116, 24, COLOR_WALL);

	UTIL_LCD_DrawVLine(267, 209, 6, COLOR_WALL);
	UTIL_LCD_DrawVLine(267, 161, 6, COLOR_WALL);
	UTIL_LCD_DrawVLine(267, 113, 30, COLOR_WALL);
	UTIL_LCD_DrawVLine(267, 65, 6, COLOR_WALL);

	UTIL_LCD_DrawVLine(284, 209, 23, COLOR_WALL);
	UTIL_LCD_DrawVLine(284, 137, 30, COLOR_WALL);
	UTIL_LCD_DrawVLine(284, 96, 23, COLOR_WALL);
	UTIL_LCD_DrawVLine(284, 65, 23, COLOR_WALL);

	UTIL_LCD_DrawVLine(291, 209, 23, COLOR_WALL);
	UTIL_LCD_DrawVLine(291, 185, 6, COLOR_WALL);
	UTIL_LCD_DrawVLine(291, 137, 30, COLOR_WALL);
	UTIL_LCD_DrawVLine(291, 65, 54, COLOR_WALL);
	UTIL_LCD_DrawVLine(291, 33, 14, COLOR_WALL);

	UTIL_LCD_DrawVLine(308, 185, 30, COLOR_WALL);
	UTIL_LCD_DrawVLine(308, 137, 30, COLOR_WALL);
	UTIL_LCD_DrawVLine(308, 89, 30, COLOR_WALL);
	UTIL_LCD_DrawVLine(308, 65, 6, COLOR_WALL);
	UTIL_LCD_DrawVLine(308, 33, 14, COLOR_WALL);

	UTIL_LCD_DrawVLine(311, 140, 24, COLOR_WALL);
	UTIL_LCD_DrawVLine(311, 92, 24, COLOR_WALL);

	UTIL_LCD_DrawVLine(315, 192, 23, COLOR_WALL);

	UTIL_LCD_DrawVLine(331, 233, 6, COLOR_WALL);
	UTIL_LCD_DrawVLine(331, 185, 6, COLOR_WALL);
	UTIL_LCD_DrawVLine(331, 65, 6, COLOR_WALL);
	UTIL_LCD_DrawVLine(331, 33, 14, COLOR_WALL);

	UTIL_LCD_DrawVLine(332, 209, 6, COLOR_WALL);

	UTIL_LCD_DrawVLine(348, 216, 40, COLOR_WALL);
	UTIL_LCD_DrawVLine(348, 168, 40, COLOR_WALL);
	UTIL_LCD_DrawVLine(348, 16, 72, COLOR_WALL);

	UTIL_LCD_DrawVLine(351, 165, 94, COLOR_WALL);
	UTIL_LCD_DrawVLine(351, 13, 78, COLOR_WALL);
}
