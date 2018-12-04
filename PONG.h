#include "raylib.h"
#define SCREEN_W 1000
#define SCREEN_H 600
#define BAR_W 10
#define BAR_H 60
#define BAR_X 50
#define BALL_R 8
#define LOGO_S 10
#define LIVES 4
#define FIELD 75
#define PLAYER_S 2.2
#define AI_S 2.8
#define BALL_S 3

typedef enum GameScreen { LOGO, TITLE, GAMEPLAY, ENDING } GameScreen;
typedef struct Player{
    float x;
    float y;
    float h;
    float w;
    Color c;
    float s;
    int lives;
    int score;
}Player;
typedef struct Ball{
    float x;
    float y;
    float sx;
    float sy;
    int r;
    int lives;
    Color c;
}Ball;

void resetBall (Ball *ball);