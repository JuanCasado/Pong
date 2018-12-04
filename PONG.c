/*******************************************************************************************
*
*   raylib game: FINAL PONG - game template
*
*   developed by [STUDENT NAME HERE]
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (Ray San)
*
********************************************************************************************/

#include "PONG.h"

int main(){
    GameScreen screen = LOGO;
    
    int secondsCounter = 99;
    int framesCounter = 0;
    int gameResult = -1;
    Rectangle playerRect;
    Rectangle aiRect;
    Vector2 ballVect;
    
    Player player;
    Player ai;
    player.x = BAR_X;
    ai.x = SCREEN_W - BAR_X;
    player.c = BLUE;
    ai.c = GREEN;
    player.y = ai.y = SCREEN_H/2 - BAR_H/2;
    player.w = ai.w = BAR_W;
    player.h = ai.h = BAR_H;
    player.lives = ai.lives = LIVES;
    player.s = PLAYER_S;
    ai.s = AI_S;
    player.score = ai.score = 0;
    Ball ball;
    resetBall(&ball);
    ball.c = RED;
    ball.r = BALL_R;
    float logo = 0;
    int txt_anim = 0;
    bool pause = false;
    
    InitWindow(SCREEN_W, SCREEN_H, "PONG");
    SetTargetFPS(60);
    while (!WindowShouldClose()){
        switch(screen){
            case LOGO:{
                if (framesCounter++ == secondsCounter){
                    screen=TITLE;
                    framesCounter = 0;
                    secondsCounter = 10;
                    logo = 0;
                }else{
                    logo+=0.3;
                }
            } break;
            case TITLE:{
                if (framesCounter++ == secondsCounter){
                    framesCounter = 0;
                    txt_anim ++;
                }
                if(IsKeyDown(KEY_ENTER)){
                        screen = GAMEPLAY;
                        framesCounter = 0;
                        secondsCounter = 99;
                        txt_anim = 0;
                }
            } break;
            case GAMEPLAY:{ 
                if (!pause){
                    playerRect.x = player.x;
                    playerRect.y = player.y;
                    playerRect.width = player.w;
                    playerRect.height =player.h;
                    aiRect.x = ai.x;
                    aiRect.y = ai.y;
                    aiRect.width = ai.w;
                    aiRect.height =ai.h;
                    ballVect.x = ball.x;
                    ballVect.y = ball.y;
                    if (!(framesCounter++%60)){
                        secondsCounter --;
                    }
                    if(ball.y < ai.y+ai.h/2) if(ai.y > FIELD) ai.y -= ai.s;
                    if(ball.y > ai.y+ai.h/2) if(ai.y + BAR_H < SCREEN_H) ai.y += ai.s;
                    if(CheckCollisionCircleRec(ballVect, ball.r, aiRect)){
                        ball.sx *= -1.1;
                        ball.sy -= ai.s/4;
                        ball.x += ball.sx;
                        ball.y += ball.sy;
                    }
                    if(CheckCollisionCircleRec(ballVect, ball.r, playerRect)){
                        ball.sx *= -1.1;
                        ball.sy -= player.s/4;
                        ball.x += ball.sx;
                        ball.y += ball.sy;
                    }
                    if((ball.y < FIELD) || (ball.y > SCREEN_H)){
                        ball.sx *= 1.05;
                        ball.sy *= -1.05;
                        ball.x += ball.sx;
                        ball.y += ball.sy;
                    }
                    if(IsKeyDown(KEY_UP)) if(player.y > FIELD) player.y -= player.s;
                    if(IsKeyDown(KEY_DOWN)) if(player.y + BAR_H < SCREEN_H) player.y += player.s;
                    ball.x += ball.sx;
                    ball.y += ball.sy;
                    if(ball.x < 0){ 
                        player.lives--;
                        resetBall(&ball);
                    }
                    if(ball.x > SCREEN_W) {
                        ai.lives--;
                        resetBall(&ball);
                    }
                    if (ai.lives < 0){
                        gameResult = 1;
                        screen = ENDING;
                    }else if (player.lives < 0){
                        gameResult = 0;
                        screen = ENDING;
                    }else if (secondsCounter < 0){
                        if (ai.lives > player.lives){
                            gameResult = 0;
                        } else if (ai.lives < player.lives){
                            gameResult = 1;
                        }else{
                            gameResult = -1;
                        }
                        screen = ENDING;
                    }
                }
                if(IsKeyDown(KEY_SPACE)){
                        pause = !pause;
                }                
            } break;
            case ENDING: {
                if (framesCounter++ == secondsCounter){
                    framesCounter = 0;
                    txt_anim ++;
                }
                if(IsKeyDown(KEY_ENTER)){
                    screen = GAMEPLAY;
                    txt_anim = 0;
                    resetBall(&ball);
                    player.lives = LIVES;
                    ai.lives = LIVES;
                    secondsCounter = 99;
                }
            } break;
            default: break;
        }
        BeginDrawing();
            ClearBackground(BLACK);
            switch(screen) {
                case LOGO: {
                    DrawCircle(SCREEN_W/2, SCREEN_H/2 + LOGO_S/2 + logo, LOGO_S*2 + logo*2, YELLOW);
                    DrawCircle(SCREEN_W/2, SCREEN_H/2 + LOGO_S/2 + logo, LOGO_S + logo*2, BLACK);
                    DrawRectangle(0, SCREEN_H/2 + LOGO_S/2 + logo - (LOGO_S*2 + logo*2) -1, SCREEN_W, LOGO_S*2 + logo*2, BLACK);
                    DrawCircle(SCREEN_W/2 + LOGO_S + logo, SCREEN_H/2 - LOGO_S*3 - logo, LOGO_S/3 + logo, YELLOW);
                    DrawCircle(SCREEN_W/2 - LOGO_S - logo, SCREEN_H/2 - LOGO_S*3 - logo, -LOGO_S/3 - logo, YELLOW);
                    DrawCircle(SCREEN_W/2 + LOGO_S + logo, SCREEN_H/2 - LOGO_S - logo, LOGO_S/3 + logo, YELLOW);
                    DrawCircle(SCREEN_W/2 - LOGO_S - logo, SCREEN_H/2 - LOGO_S - logo, -LOGO_S/3 - logo, YELLOW);
                    DrawRectangle(SCREEN_W/2 + LOGO_S + logo -(LOGO_S/3 + logo), SCREEN_H/2 - LOGO_S*3 - logo, (LOGO_S/3 + logo)*2, SCREEN_H/2 - LOGO_S - logo -(SCREEN_H/2 - LOGO_S*3 - logo), YELLOW);
                    DrawRectangle(SCREEN_W/2 - LOGO_S - logo -(LOGO_S/3 + logo), SCREEN_H/2 - LOGO_S*3 - logo, (LOGO_S/3 + logo)*2, SCREEN_H/2 - LOGO_S - logo -(SCREEN_H/2 - LOGO_S*3 - logo), YELLOW);
                } break;
                case TITLE: 
                {
                    DrawText("PONG", SCREEN_W/2 - 70, SCREEN_H/2, 50, YELLOW); 
                    switch(txt_anim%4){
                        case 0:
                        DrawText("press Enter", SCREEN_W/2 - 70, SCREEN_H/2 +100, 20, YELLOW);  
                        break;
                        case 1:
                        DrawText(".press Enter", SCREEN_W/2 - 70, SCREEN_H/2 +100, 20, YELLOW);  
                        break;
                        case 2:
                        DrawText("..press Enter", SCREEN_W/2 - 70, SCREEN_H/2 +100, 20, YELLOW);   
                        break;
                        case 3:
                        DrawText("...press Enter", SCREEN_W/2 - 70, SCREEN_H/2 +100, 20, YELLOW);  
                        break;
                    }
                } break;
                case GAMEPLAY:
                { 
                    DrawRectangle(SCREEN_W/2-1, 50, 3, SCREEN_H, WHITE);
                    DrawRectangle(0, FIELD-1, SCREEN_W, 3, WHITE);
                    DrawRectangle(player.x,player.y,player.w,player.h,player.c);
                    DrawRectangle(ai.x,ai.y,ai.w,ai.h,ai.c);
                    DrawCircle(ball.x,ball.y,ball.r,ball.c);
                    for (int x = 0; x < LIVES; x++){
                        if (player.lives > x){
                            DrawCircle(100 + x*50,40,20,RED);
                        }else{
                            DrawCircleLines(100 + x*50,40,20,RED);
                        }
                        if (ai.lives > x){
                            DrawCircle(SCREEN_W - 100 - x*50,40,20,RED);
                        }else{
                            DrawCircleLines(SCREEN_W - 100 - x*50,40,20,RED);
                        }
                    }
                    if (!pause){
                        DrawText(FormatText("%i", secondsCounter), SCREEN_W/2 - 20, 10 , 40, YELLOW);
                    }else{
                        DrawText("PAUSED", SCREEN_W/2 - 80, 10 , 40, YELLOW);
                    }
                } break;
                case ENDING: 
                {
                    DrawText("PONG", SCREEN_W/2 - 70, SCREEN_H/2 , 50, YELLOW);
                    if (gameResult == 1)
                        DrawText("YOU WON", SCREEN_W/2 - 100, SCREEN_H/2 +200 , 50, YELLOW);
                    else if (gameResult == 0)
                        DrawText("YOU LOOSE", SCREEN_W/2 - 130, SCREEN_H/2 +200 , 50, YELLOW);
                    else{
                        DrawText("TIE", SCREEN_W/2 - 50, SCREEN_H/2 +200 , 50, YELLOW);
                    }
                    switch(txt_anim%4){
                        case 0:
                        DrawText("press Enter to play again", SCREEN_W/2 - 120, SCREEN_H/2 +100, 20, YELLOW);  
                        break;
                        case 1:
                        DrawText(".press Enter to play again", SCREEN_W/2 - 120, SCREEN_H/2 +100, 20, YELLOW);  
                        break;
                        case 2:
                        DrawText("..press Enter to play again", SCREEN_W/2 - 120, SCREEN_H/2 +100, 20, YELLOW);   
                        break;
                        case 3:
                        DrawText("...press Enter to play again", SCREEN_W/2 - 120, SCREEN_H/2 +100, 20, YELLOW);  
                        break;
                    }
                } break;
                default: break;
            }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

void resetBall (Ball *ball){
    ball->x = SCREEN_W/2;
    ball->y = SCREEN_H/2;
    if (GetRandomValue(-1, 1) > 0){
        ball->sx = GetRandomValue(2, BALL_S-2);
        ball->sy = BALL_S - ball->sx;
    }else{
        ball->sx = GetRandomValue(-BALL_S+2, -2);
        ball->sy = -BALL_S + ball->sx;
    }
}