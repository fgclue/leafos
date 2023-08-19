#pragma once

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f


// Colors
#define BLACK_ON_WHITE 0x0F
#define WOB_GREEN 0x0A
#define WOB_RED 0x04
#define WOB_BLUE 0x01
#define WOB_CYAN 0x03
#define WOB_MAGENTA 0x05
#define WOB_YELLOW 0x06
#define ROW 0x4F

/* Screen i/o ports */
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

/* Public kernel API */
void print_string(char *string);

void print_string_color(char *string, int color2);

void print_nl();

void clear_screen();

int scroll_ln(int offset);

void print_backspace();
