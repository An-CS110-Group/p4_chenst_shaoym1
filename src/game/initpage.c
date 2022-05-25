#include "game/initpage.h"
#include "generateMap.h"
#include "lcd/img.h"
#include "lcd/lcd.h"
#include "utils.h"
#include <math.h>
#include <stdbool.h>

int score;
double dinoH;
int speedH;// +1000 = up 1 pixel per second
int status;
/* 0 - Walking, on the ground
 * 1 - Jumping, upward
 * 2 - Jumping, downward
 * 3 - Jumping, accelerate downward
 * 4 - Crawling
 * */
bool leg;// T for left, F for right
int gravity;
double jumpSpeed;
float difficulty;
int obstacles[5] = {0, 0, 0, 0, 0};    // Prepare 5 obstacles at a time. It stores center hit-time of an obstacle.
int obstacleTypes[5] = {0, 0, 0, 0, 0};//0 for nothing, 1 for cactus1, 2 for cactus2, 3 for pter.

int initPage() {
    LCD_ShowString(60, 20, (u8 *) "Dino!", BLUE);
    LCD_ShowString(30, 50, (u8 *) "Play", MAGENTA);
    LCD_ShowString(88, 50, (u8 *) "Settings", MAGENTA);
    delay_1ms(200);
    while (1) {
        if (Get_Button(0)) return 0;
        if (Get_Button(1)) return 1;
    }
}

int settings() {
    LCD_Clear(BLACK);
    LCD_ShowString(40, 20, (u8 *) "Difficulty", MAGENTA);
    LCD_ShowString(20, 50, (u8 *) "Easy", WHITE40);
    LCD_ShowString(100, 50, (u8 *) "Hard", WHITE40);
    delay_1ms(500);
    while (1) {
        if (Get_Button(0)) return 500;
        if (Get_Button(1)) return 1000;
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
        gravity *= 4;
        //        speedH *= 2;
    } else if (status == 1) {
        status = 3;
        speedH = 0;
        gravity *= 4;
        //        speedH *= 2;
    } else if (status == 2) {
        status = 3;
        gravity *= 4;
        //        speedH *= 2;
    }
}

static void uncrawl() {
    if (status == 3) {
        gravity /= 4;
        //        speedH /= 2;
        status = 2;
    } else if (status == 4) {
        status = 0;
        gravity /= 4;
        //        speedH /= 2;
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

static void obstacleInit() {
    obstacleTypes[0] = rand() % 3 + 1;
    obstacles[0] = 200;
    for (int i = 1; i < 5; ++i) {
        obstacleTypes[i] = 0;
        obstacles[i] = 0;
    }
}

static void refreshObstacle() {
    for (int i = 0; i < 5; ++i) {
        if (score - obstacles[i] > 30) obstacleTypes[i] = 0;
    }

    for (int i = 0; i < 5; ++i) {
        if (obstacleTypes[i] == 0) {
            obstacleTypes[i] = rand() % 3 + 1;
            obstacles[i] = getNextObs(obstacles[(i + 4) % 5], difficulty);
        }
    }
}

static void refreshAndDrawObstacle() {
    refreshObstacle();
    for (int i = 0; i < 5; ++i) {
        if (obstacles[i] - score > 140 || obstacles[i] - score < -10) continue;// Only display what's in the picture
        switch (obstacleTypes[i]) {
            case 1:
                LCD_ShowPic(obstacles[i] - score, 45, obstacles[i] - score + 11, 64, cactus1);
                break;
            case 2:
                LCD_ShowPic(obstacles[i] - score, 45, obstacles[i] - score + 11, 64, cactus2);
                break;
            case 3:
                if (leg) {
                    { LCD_ShowPic(obstacles[i] - score, 25, obstacles[i] - score + 19, 44, pter1); }
                } else {
                    LCD_ShowPic(obstacles[i] - score, 25, obstacles[i] - score + 19, 44, pter2);
                }
                break;
        }
    }
}

static void cleanForObstacle() {
    LCD_Fill(0, 16, 24, 64, BLACK);
    LCD_Fill(52, 16, 160, 64, BLACK);
}

static bool collideDetect() {
    for (int i = 0; i < 5; ++i) {
        LCD_ShowNum(0, 0, (u16) (dinoH), 10, BLACK, BLUE);
        switch (obstacleTypes[i]) {
            case 1:
                if (score + 20 + 25 >= obstacles[i] + 8 && score + 25 < obstacles[i] + 10 && dinoH <= 16) return true;
                break;
            case 2:
                if (score + 20 + 25 >= obstacles[i] + 8 && score + 25 < obstacles[i] + 6 && dinoH <= 16) return true;
                break;
            case 3:
                if (score + 20 + 25 >= obstacles[i] + 5 && score + 25 < obstacles[i] + 6 && status != 4) return true;
                break;
        }
    }
    return false;
}

static void InitValues(float settings) {
    score = 0;
    dinoH = 0.0f;
    speedH = 0;// +1000 = up 1 pixel per second
    status = 0;
    leg = false;// T for left, F for right
    gravity = 500;
    jumpSpeed = 6000.0;
    difficulty = settings;
    for (int i = 0; i < 5; ++i) {
        obstacles[i] = 0;
        obstacleTypes[i] = 0;
    }
}

int startGame(float settings) {
    InitValues(settings);

    LCD_Clear(BLACK);
    delay_1ms(100);
    LCD_Fill(0, 66, 159, 67, WHITE60);
    obstacleInit();
    while (1) {
        // Calculate in loop
        delay_1ms(25);
        if (score % 60 == 0 && difficulty > 0.5f) difficulty *= 0.95f;
        score += 5;
        if (score % 20 == 0) { leg = !leg; }

        // FSM
        calculatePositionAndStatus();
        if (Get_Button(0)) { jump(); }
        if (Get_Button(1)) {
            crawl();
        } else {
            uncrawl();
        }

        if (collideDetect()) { return score; }

        // Draw
        cleanForObstacle();
        drawDino();
        refreshAndDrawObstacle();
        showScore();
    }
}

void finishGame(int highscore) {
    LCD_Clear(BLACK);
    LCD_ShowString(20, 20, (u8 *) "Score:", MAGENTA);
    LCD_ShowNum(20 + 48, 20, highscore, 7, BLACK, RED);
    LCD_ShowString(0, 45, (u8 *) "Back to main menu", WHITE40);
    delay_1ms(500);
    while (1) {
        if (Get_Button(0)) return;
        if (Get_Button(1)) return;
    }
}