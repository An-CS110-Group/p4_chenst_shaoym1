#include "game/initpage.h"
#include "generateMap.h"
#include "lcd/img.h"
#include "lcd/lcd.h"
#include "utils.h"
#include <stdbool.h>

int score = 0;
double dinoH = 0.0f;
int speedH = 0;// +1000 = up 1 pixel per second
int status = 0;
/* 0 - Walking, on the ground
 * 1 - Jumping, upward
 * 2 - Jumping, downward
 * 3 - Jumping, accelerate downward
 * 4 - Crawling
 * */
bool leg = false;// T for left, F for right
int gravity = 4500;
double jumpSpeed = 16000.0;
int obstacles[5];    // Prepare 5 obstacles at a time.
int obstacleTypes[5];//0 for nothing, 1 for cactus1, 2 for cactus2, 3 for pter.

int initPage() {
    LCD_ShowString(60, 20, "Dino!", BLUE);
    LCD_ShowString(30, 50, "Play", MAGENTA);
    LCD_ShowString(88, 50, "Settings", MAGENTA);
    while (1) {
        if (Get_Button(0)) return 0;
        if (Get_Button(1)) return 1;
    }
}

int settings() {
    LCD_Clear(BLACK);
    LCD_ShowString(40, 20, "Difficulty", MAGENTA);
    LCD_ShowString(20, 50, "Easy", WHITE40);
    LCD_ShowString(100, 50, "Hard", WHITE40);
    delay_1ms(500);
    while (1) {
        if (Get_Button(0)) return 0;
        if (Get_Button(1)) return 1;
    }
}

static void showScore() { LCD_ShowNum(96, 0, score, 7, WHITE40, WHITE80); }

static void drawDino() {
    switch (status) {
        case 0:
            LCD_Fill(25, 0, 51, 45, BLACK);
            LCD_Fill(44, 0, 51, 65, BLACK);
            if (leg) LCD_ShowPic(25, 45 - (int) dinoH, 44, 64 - (int) dinoH, trex1);
            else
                LCD_ShowPic(25, 45 - (int) dinoH, 44, 64 - (int) dinoH, trex2);
            break;
        case 1:
        case 2:
            LCD_Fill(25, 0, 51, 65, BLACK);
            LCD_ShowPic(25, 45 - (int) dinoH, 44, 64 - (int) dinoH, trex3);
            break;
        case 3:
            LCD_Fill(25, 0, 51, 65, BLACK);
            if (leg) LCD_ShowPic(25, 45 - (int) dinoH, 51, 64 - (int) dinoH, trex4);
            else
                LCD_ShowPic(25, 45 - (int) dinoH, 51, 64 - (int) dinoH, trex5);
            break;
        case 4:
            LCD_Fill(25, 0, 51, 45, BLACK);
            if (leg) LCD_ShowPic(25, 45 - (int) dinoH, 51, 64 - (int) dinoH, trex4);
            else
                LCD_ShowPic(25, 45 - (int) dinoH, 51, 64 - (int) dinoH, trex5);
            break;
        default:
            break;
    }
}

static void jump() {
    if (status == 0) {
        status = 1;
        speedH = (int) jumpSpeed;
    }
}

static void crawl() {
    if (status == 0) {
        status = 4;
        gravity *= 2;
        speedH *= 2;
    } else if (status == 1) {
        status = 3;
        speedH = 0;
        gravity *= 2;
        speedH *= 2;
    } else if (status == 2) {
        status = 3;
        gravity *= 2;
        speedH *= 2;
    }
}

static void uncrawl() {
    if (status == 3) {
        gravity /= 2;
        speedH /= 2;
        status = 2;
    } else if (status == 4) {
        status = 0;
        gravity /= 2;
        speedH /= 2;
    }
}

static void calculatePositionAndStatus() {
    switch (status) {
        case 0:
            dinoH = 0.0f;
            break;
        case 1:
            dinoH += speedH / 1000.0;
            speedH -= gravity;
            if (speedH < 0) status = 2;
            break;
        case 2:
            dinoH += speedH / 1000.0;
            speedH -= gravity;
            if (dinoH < 0) {
                dinoH = 0.0f;
                status = 0;
                speedH = 0;
            }
            break;
        case 3:
            dinoH += speedH / 1000.0;
            speedH -= gravity;
            if (dinoH < 0) {
                dinoH = 0;
                status = 4;
                speedH = 0;
            }
            break;
        case 4:
            dinoH = 0.0f;
            break;
        default:
            dinoH = 0.0f;
    }
}

int startGame() {
    LCD_Clear(BLACK);
    delay_1ms(200);
    LCD_Fill(0, 66, 159, 67, WHITE60);
    while (1) {
        score++;
        showScore();
        //        LCD_ShowNum(0, 0, gravity, 5, WHITE40, WHITE80);
        calculatePositionAndStatus();
        if (Get_Button(0)) { jump(); }
        if (Get_Button(1)) {
            crawl();
        } else {
            uncrawl();
        }
        drawDino();
        leg = !leg;
        delay_1ms(50);
    }
}
