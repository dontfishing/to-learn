#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <string.h>
#include <time.h>
void food();
void show();
void move();
void turn();
void check();
void ini();
int  dy[4] = { 0, 1, 0, -1 };
int  dx[4] = { -1, 0, 1, 0 };
int sum = 5;  //蛇总长度
int over = 0;
int speed = 50;	//越小越快    
char map[20][80];

void hide(){	//隐藏光标 
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_CURSOR_INFO CursorInfo;
GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
CursorInfo.bVisible = false; //隐藏控制台光标
SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态

}

struct snake {
    int x, y;  //身体坐标 
    int dir;  //方向
} A[100];

void ini() {  //初始化界面
    over = 0;
    sum = 5;
    int i, j;
    for (i = 0; i < 80; i++) {  //初始化蛇头和蛇身的数据
        A[i].dir = 0;
        A[i].x = 0;
        A[i].y = 0;
    }
    A[0].x = 1; A[0].y = 1;  
    A[1].x = 1; A[1].y = 2;
    A[2].x = 1; A[2].y = 3;
    A[3].x = 1; A[3].y = 4;
    A[4].x = 1; A[4].y = 5; A[4].dir = 1;
    srand(time(0));
    for (i = 0; i < 20; i++) {  //设置地图
        for (j = 0; j < 80; j++) {
            map[i][j] = '*';
        }
    }
    for (i = 1; i < 19; i++) {
        for (j = 1; j <79; j++) {
            map[i][j] = ' ';
        }
    }
map[6][14]='*';map[6][22]='*';
map[7][13]='*';map[7][15]='*';map[7][21]='*';map[7][23]='*';
map[8][12]='*';map[8][16]='*';map[8][20]='*';map[8][24]='*';
map[9][11]='*';map[9][17]='*';map[9][19]='*';map[9][25]='*';
map[10][10]='*';map[10][18]='*';map[10][26]='*';//M 

map[6][33]='*';map[6][34]='*';map[6][35]='*';
map[7][30]='*';map[7][31]='*';map[7][32]='*';map[7][36]='*';map[7][37]='*';map[7][38]='*';
map[8][33]='*';map[8][34]='*';map[8][35]='*';
map[9][30]='*';map[9][31]='*';map[9][32]='*';map[9][36];map[9][37]='*';map[9][38]='*';
map[10][33]='*';map[10][34]='*';map[10][35]='*';//S

map[6][45]='*';map[6][46]='*';map[6][47]='*';map[6][48]='*';
map[7][43]='*';map[7][44]='*';map[7][49]='*';map[7][50]='*';
map[8][43]='*';map[8][44]='*';
map[9][43]='*';map[9][44]='*';map[9][49]='*';map[9][50]='*';
map[10][45]='*';map[10][46]='*';map[10][47]='*';map[10][48]='*';//C



    map[A[4].x][A[4].y] = 'M';  //设置蛇头
    for (i = 0; i < sum - 1; i++) {  //设置蛇身
        map[A[i].x][A[i].y] = 'S';
    }
    food();
}


void show() {  //显示界面 
    int i, j, x, y;
    for (i = 0; i < 20; i++) {  //显示界面
        for (j = 0; j < 80; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
    while (1) {
        Sleep(speed);  //界面刷新速度
        turn();
        move();
        if (over) {  //设置蛇死掉后可以进行的操作 
            while (1) {
                char ch = _getch();
                if (ch == 113) {  //输入‘q’结束 
                    return;
                }
                else if (ch == 114) {  //输入‘r’重新开始 
                    ini();
                    break;
                }
            }
        }
        system("cls");  //清屏 
        for (i = 0; i <20; i++) {  //重新显示界面
            for (j = 0; j < 80; j++) {
                printf("%c", map[i][j]);
            }
            printf("\n");
        }
    }
}

void food() {  //生成食物
    int x, y;
    while (1) {
        x = (int)(15 * rand() / (RAND_MAX + 1.0));  //随机产生一组食物坐标
        y = (int)(78 * rand() / (RAND_MAX + 1.0));
        if (map[x][y] == ' ') {  //如果是空格则在该处生成食物
            map[x][y] = 'C';
            break;
        }
    }
}


void move() {  //蛇移动 
    int i, x, y;
    int t = sum;  //记录当前蛇总长度 
    check();  //移动前检查按当前方向移动一步后的情况
    if (t == sum) {  //没有吃到苹果
        for (i = 0; i < sum - 1; i++) {
            if (i == 0) {  //蛇尾坐标处变成空格，把蛇尾坐标变成前一个蛇身的坐标 
                map[A[i].x][A[i].y] = ' ';
                A[i].x = A[i + 1].x;
                A[i].y = A[i + 1].y;
            }
            else {  //每个蛇身坐标都变为它前一个蛇身的坐标
                A[i].x = A[i + 1].x;
                A[i].y = A[i + 1].y;
            }
            map[A[i].x][A[i].y] = 'S';  //把地图上蛇身坐标处的字符设置成‘S’
        }
        A[sum - 1].x = A[sum - 1].x + dx[A[sum - 1].dir];  //蛇头按当前方向移动一格 
        A[sum - 1].y = A[sum - 1].y + dy[A[sum - 1].dir];
        map[A[sum - 1].x][A[sum - 1].y] = 'M';  //把地图上蛇头坐标处的字符设置成‘M’
    }
    else {  //吃到苹果
        map[A[sum - 2].x][A[sum - 2].y] = 'S';  //把地图上原蛇头坐标处的字符设置成‘S’
        A[sum - 1].x = A[sum - 2].x + dx[A[sum - 2].dir];  //新蛇头的坐标是原蛇头沿当前方向移动一格后的坐标 
        A[sum - 1].y = A[sum - 2].y + dy[A[sum - 2].dir];
        A[sum - 1].dir = A[sum - 2].dir;  //新蛇头方向为原蛇头的方向
        map[A[sum - 1].x][A[sum - 1].y] = 'M';  //把地图上蛇头坐标处的字符设置成‘M’
        food();
    }
}

void check() {  //检查是否死亡或者吃到食物
    int x, y, i, j;
    x = A[sum - 1].x + dx[A[sum - 1].dir];  //记录按当前方向移动一格后蛇头的坐标 
    y = A[sum - 1].y + dy[A[sum - 1].dir];
    if (map[x][y] == '*' || map[x][y] == 'S') {  //如果地图上该坐标处字符为‘*’或‘S’就死亡 
        if (x != A[0].x || y != A[0].y) {  //蛇尾除外 
            system("cls");
            map[8][4] = 'G'; map[8][5] = 'A'; map[8][6] = 'M'; map[8][7] = 'E';  //输出“GAME OVER” 
            map[8][9] = 'O'; map[8][10] = 'V'; map[8][11] = 'E'; map[8][12] = 'R';
            map[8][8] = ' ';
            for (i = 0; i < 20; i++) {
                for (j = 0; j < 80; j++) {
                    printf("%c", map[i][j]);
                }
                printf("\n");
            }
            printf("按‘r’重新开始\n按‘q’退出游戏\n");
            printf("你们这个题真不当人！");
            over = 1;
        }   
    }
    else if(map[x][y]=='C')
	sum++;
}

void turn() {  //转弯
    if (_kbhit()) {
        char dir = _getch();  //读取输入的键 
        switch (dir) {  //改变方向 
        case 119: A[sum - 1].dir = (A[sum - 1].dir == 2)?2:0; break;
        case 100: A[sum - 1].dir = (A[sum - 1].dir == 3)?3:1; break;
        case 115: A[sum - 1].dir = (A[sum - 1].dir == 0)?0:2; break;
        case 97: A[sum - 1].dir = (A[sum - 1].dir == 1)?1:3; break;
        }
    }
}


int main() {
    printf("'w''s''a''d'控制上下左右\n按任意键开始\n别动鼠标\nDont_fishing\n");
    hide(); 
	char ch = _getch();
    system("cls");
    ini();
    show(); 
    return 0;
}
