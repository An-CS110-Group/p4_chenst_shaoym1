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
int obstacleTypes[5] = {0, 0, 0, 0, 0};// 0 for nothing, 1 for cactus1, 2 for cactus2, 3 for pter.
int ground[180][2];                    // Random ground

void initGnd() {
    ground[0][0] = 0;
    ground[0][1] = 0;
    for (int i = 1; i < 180; ++i) {
        if (ground[i - 1][0] == 0) {
            if (rand() > RAND_MAX / 10 * 9) ground[i][0] = 1;
            else
                ground[i][0] = 0;
        } else {
            if (rand() > RAND_MAX / 10 * 3) ground[i][0] = 1;
            else
                ground[i][0] = 0;
        }
        if (ground[i - 1][1] == 0) {
            if (rand() > RAND_MAX / 10 * 9) ground[i][1] = 1;
            else
                ground[i][1] = 0;
        } else {
            if (rand() > RAND_MAX / 10 * 3) ground[i][1] = 1;
            else
                ground[i][1] = 0;
        }
    }
}

void refreshGnd() {
    for (int i = 0; i < 180; ++i) {
        ground[i][0] = ground[i + 5][0];
        ground[i][1] = ground[i + 5][1];
    }
    for (int i = 175; i < 180; ++i) {
        if (ground[i - 1][0] == 0) {
            if (rand() > RAND_MAX / 10 * 9) ground[i][0] = 1;
            else
                ground[i][0] = 0;
        } else {
            if (rand() > RAND_MAX / 10 * 3) ground[i][0] = 1;
            else
                ground[i][0] = 0;
        }
        if (ground[i - 1][1] == 0) {
            if (rand() > RAND_MAX / 10 * 9) ground[i][1] = 1;
            else
                ground[i][1] = 0;
        } else {
            if (rand() > RAND_MAX / 10 * 3) ground[i][1] = 1;
            else
                ground[i][1] = 0;
        }
    }
}

void drawGnd() {
    LCD_Fill(0, 65, 159, 65, BLACK);
    LCD_Fill(0, 70, 159, 70, BLACK);
    for (int i = 0; i < 160; ++i) {
        if (ground[i][1]) LCD_DrawPoint(i, 65, WHITE60);
        if (ground[i][0]) LCD_DrawPoint(i, 70, WHITE40);
    }
}

int initPage() {
    LCD_Clear(BLACK);
    LCD_ShowString(50, 20, (u8 *) "Dino!", BLUE);
    LCD_ShowString(20, 50, (u8 *) "Play", MAGENTA);
    LCD_ShowString(78, 50, (u8 *) "Settings", MAGENTA);
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
    } else if (status == 1) {
        status = 3;
        speedH = 0;
        gravity *= 4;
    } else if (status == 2) {
        status = 3;
        gravity *= 4;
    }
}

static void uncrawl() {
    if (status == 3) {
        gravity /= 4;
        status = 2;
    } else if (status == 4) {
        status = 0;
        gravity /= 4;
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
    initGnd();
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
        refreshGnd();

        // Draw
        drawGnd();
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
    LCD_ShowString(10, 45, (u8 *) "Back to main menu", WHITE40);
    delay_1ms(500);
    while (1) {
        if (Get_Button(0)) return;
        if (Get_Button(1)) return;
    }
}

char* l_c_s(char *str1,char *str2)
{
	int str1len = strlen(str1);
	int str2len = strlen(str2);
	int i,j,index,max=0,num=0; 
	int start;
    
	//将两个字符串看做两个直尺，固定一个直尺，另外一个从头到尾开始移动，逐一与固定的直尺比较值。
	for(i = 0; i < str1len; i++) 
	{
		for(j = 0; j < str2len; j++)
		{
			//这里的start1、start2是比较关键的
			int start1=i;
			int start2=j;
			while((start1 <= str1len-1) && (start2 <= str2len-1) && (str1[start1++] == str2[start2++]))
				num++;
			if(num > max)//如果num是当前最大匹配的个数，则赋给max，并且在start记下str1最长匹配开始的位置
			{
				max=num;
				start=i; 
			} 
			num=0;//如果num不是当前最大的，则赋为0值继续循环
		}
	}
	char *str=(char *)malloc(max + 1);
	strncpy(str,str1 + start,max);//从字符串str1的start位置开始，拷贝max个字符到str中，这就是我们找出的最大子串
	str[max] = '\0';
	printf("最长公共连续子串的长度为：%d\n",max);
	return str;
}