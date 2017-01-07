#pragma once

static const int MAP_WIDTH 			= 17;
static const int MAP_HEIGHT 		= 13;
static const int TILE_WIDTH 		= 32;
static const int TILE_HEIGHT 		= 32;
static const int MAP_OFFSET_X       = -16;
static const int MAP_OFFSET_Y       = -16;
static const int MENU_WIDTH 		= 15;
static const int STATS_HEIGHT       = 2;
static const int WINDOW_WIDTH 		= (MAP_WIDTH  + MENU_WIDTH) * TILE_WIDTH;
static const int WINDOW_HEIGHT 		= (MAP_HEIGHT + STATS_HEIGHT)* TILE_HEIGHT;
static const int FRAMES_PER_SECOND	= 30;
static const int TIME_TO_PREPARE    = 30;
static const int START_MONEY        = 1000;
static const int START_LIVES        = 10;