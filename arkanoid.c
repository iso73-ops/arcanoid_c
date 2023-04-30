#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <math.h>

#define width 65
#define height 25
#define M_PI 3.14159265358979

typedef struct {
    int x, y;
    int w;
} TRacket;

typedef struct {
    float x, y;
    int ix, iy;
    float alfa;
    float speed;
} TBall;

char mas[height][width+1];
TRacket racket;
TBall ball;
int hitCnt = 0;
int maxHitCnt = 0;
int io;
int goal = 10;

void initRacket()
{
    racket.w = 7;
    racket.x = (width - racket.w) / 2;
    racket.y = height - 1;
}

void putRacket()
{
    for (int i = racket.x; i < racket.x + racket.w; i++)
        mas[racket.y][i] = 'X';
}

void moveRacket(int x)
{
    racket.x = x;
    if (racket.x < 1)
        racket.x = 1;
    if (racket.x + racket.w >= width)
        racket.x = width - 1 - racket.w;
}



void initBall()
{
    ball.x = 2;
    ball.y = 2;
    ball.alfa = -1;
    ball.speed = 0.5;

}

void putBall()
{
    mas[ball.iy][ball.ix] = '@';
}


void moveBall(float x, float y)
{
    ball.x = x;
    ball.y = y;
    ball.ix = (int)round(ball.x);
    ball.iy = (int)round(ball.y);
}

void autoMoveBall()
{
    if (ball.alfa < 0) ball.alfa += M_PI*2;
    if (ball.alfa > M_PI*2) ball.alfa -= M_PI*2;

    TBall bl = ball;

    moveBall(ball.x + cos(ball.alfa) * ball.speed
            , ball.y + sin(ball.alfa) * ball.speed);

    if ((mas[ball.iy][ball.ix] == '#') || (mas[ball.iy][ball.ix] == 'X'))
    {
        if (mas[ball.iy][ball.ix] == 'X')
            hitCnt++;

        if ((ball.ix != bl.ix) && (ball.iy != bl.iy))
        {
            if (mas[bl.iy][ball.ix] == mas[ball.iy][bl.ix])
                bl.alfa = bl.alfa + M_PI;
            else
            {
                if (mas[bl.iy][ball.ix] == '#')
                    bl.alfa = (2*M_PI - bl.alfa) + M_PI;
                else
                    bl.alfa = (2*M_PI - bl.alfa);
            }
        }
        else if (ball.iy == bl.iy)
            bl.alfa = (2*M_PI - bl.alfa) + M_PI;
        else
            bl.alfa = (2*M_PI - bl.alfa);

        ball = bl;
        autoMoveBall();
    }

}

void init(io)
{
    if (io == 1){
        for (int i = 0; i < width; i++)
            mas[0][i] = '#';

        mas[0][width] = '\0';

        strncpy(mas[1], mas[0], width+1);

        for (int i = 1; i < width-1; i++)
            mas[1][i] = ' ';

        for (int i = 1; i < height; i++)
            strncpy(mas[i], mas[1], width+1);

        //new levels below this line

        for (int i = 25; i < 40; i++)
            mas[8][i] = '#';
    }

    if (io == 2){
        for (int i = 0; i < width; i++)
            mas[0][i] = '#';

        mas[0][width] = '\0';

        strncpy(mas[1], mas[0], width+1);

        for (int i = 1; i < width-1; i++)
            mas[1][i] = ' ';

        for (int i = 1; i < height; i++)
            strncpy(mas[i], mas[1], width+1);

        //new levels below this line

        for (int i = 25; i < 40; i++)
            mas[8][i] = '#';
        for (int i = 25; i < 27; i++)
            mas[7][i] = '#';
        for (int i = 38; i < 40; i++)
            mas[7][i] = '#';

        for (int i = 1; i < 5; i++)
            mas[10][i] = '#';
        for (int i = (width - 5); i < width; i++)
            mas[10][i] = '#';

    }

    if (io == 3){
        for (int i = 0; i < width; i++)
            mas[0][i] = '#';

        mas[0][width] = '\0';

        strncpy(mas[1], mas[0], width+1);

        for (int i = 1; i < width-1; i++)
            mas[1][i] = ' ';

        for (int i = 1; i < height; i++)
            strncpy(mas[i], mas[1], width+1);

        //new levels below this line


        for (int i = 1; i < 5; i++)
            mas[10][i] = '#';
        for (int i = (width - 5); i < width; i++)
            mas[10][i] = '#';
        for (int i = 1; i < 5; i++)
            mas[6][i] = '#';
        for (int i = (width - 5); i < width; i++)
            mas[6][i] = '#';

    }

    if (io > 3){
        for (int i = 0; i < width; i++)
            mas[0][i] = '#';

        mas[0][width] = '\0';

        strncpy(mas[1], mas[0], width+1);

for (int i = 1; i < width-1; i++)
            mas[1][i] = ' ';

        for (int i = 1; i < height; i++)
            strncpy(mas[i], mas[1], width+1);
    }




}

void show()
{
    int i;
    for (i = 0; i < height; i++)
    {
        printf("%s", mas[i]);
        if (i == 3)
            printf("   SCORE: %d", hitCnt);
        if (i == 5)
            printf("   RECORD: %d", maxHitCnt);
        if (i == 7)
            printf("   GOAL: %d", goal);
        if (i < height - 1)
            printf("\n");
    }
}



void setcur(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , coord);
}

int main()
{
    BOOL run = FALSE;
    initRacket();
    initBall();



    do{
        printf("hello, stranger. let's play. choose difficulty(5-20):\n");
        scanf("%d", &goal);
    } while ((goal < 5) || (goal > 20));
    do{
        printf("hello, stranger. let's play. chose level(1-3):\n");
        scanf("%d", &io);
    } while (io < 1 || io > 3);

    do
    {

        setcur(0, 0);

        if (run)
            autoMoveBall();
        if (ball.iy > height)
        {
            run = FALSE;
            if (hitCnt > maxHitCnt)
                maxHitCnt = hitCnt;
            hitCnt = 0;
        }

        if (maxHitCnt >= goal)
        {
            maxHitCnt = 0;
            hitCnt = 0;
            io++;
        }


        init(io);
        putRacket();
        putBall();

        show();

        if (GetKeyState(VK_LEFT) < 0) moveRacket(racket.x - 1);
        if (GetKeyState(VK_RIGHT) < 0) moveRacket(racket.x + 1);
        if (GetKeyState(VK_UP) < 0) run = TRUE;
        if (!run)
            moveBall(racket.x + racket.w / 2, racket.y - 1);
        Sleep(10);

    }
    while (GetKeyState(VK_ESCAPE) >= 0);



    return 0;
}
