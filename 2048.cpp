e <ctime>
#include <windows.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <conio.h>
using namespace std;

int map[4][4] = {0}; 
int g = 1;  
int score = 0;
int move = 0;  
int check = 1;

void gotoxy(short x, short y)  //定位
{
    COORD position = { x, y };
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, position);
}


void start()  //初始化界面
{
    gotoxy(1,9);
    cout <<"按'w''a''s''d'控制数字"<<endl<<"得分: " << score<<endl<<"打出2048有惊喜哟"<<endl<<"dont_fishing";
    for(int k=1;k<=7;)
    {
        for(int l=0;l<=16;)
        {
            gotoxy(l,k);
            cout << "|";
            l += 4;
        }
        k += 2;
    }
    for(int i=0;i<9;)
    {
        gotoxy(0,i);
        cout << "----------------";
        i += 2;
    }
}

void win()	//游戏胜利  
{	
	for(int i=0;i<4;i++)
		{	for(int j=0;j<4;j++)
			{	if(map[i][j]==2048)
					{	system("cls");
						gotoxy(1,1); 
						cout<<"你赢了这个弱智的游戏好吧"<<endl<< "得分: " << score;
						check=0;
					}
			}
		}
 } 


void print()   //控制界面 
{
    system("cls");
    start();
    for(int i=0;i<4;i++)
    {
        for(int l=0;l<4;l++)
        {
            gotoxy(4*i+2,2*l+1);
            if(map[i][l] != 0)
                cout << map[i][l];
            else
                cout << " ";
        }
    }
    win();
    gotoxy(1,9);
    cout <<"按'w''a''s''d'控制数字"<<endl<<"得分: " << score<<endl<<"打出2048有惊喜哟"<<endl<<"dont_fishing";
}

void newNumber()  //生成新数字
{
    Sleep(500);
    move = 0;
    int f = 1;
	while(f)
	{
	    int h = 1;
        srand((int)time(0));
        int x = rand() % 4;
        int y = rand() % 4;
        int y2 = y;
        if(map[x][y] != 0)  
        {
            while(h)
            {
                x += 1;
                y = y2;
                if(x == 4)
                    x = 0;
                for(int l=0;l<4;l++)
                {
                    if(map[x][y] == 0)
                    {
                        h = 0;
                        break;
                    }
                    else
                    {
                        y += 1;
                        if(y == 4)
                            y = 0;
                    }
                }
            }

        }
        map[x][y] = 2;
        f = 0;
        gotoxy(4*x+2,2*y+1);
        cout << map[x][y];

	}
}

void toTop()  //向上移动
{               //填补空位
    for(int i=0;i<4;i++)
    {
        for(int l=1;l<=3;l++)
        {
            while(map[i][l] != 0 && map[i][l-1] == 0)
            {
                map[i][l-1] = map[i][l];
                map[i][l] = 0;
                if(l>1)
                    l--;
                move = 1;
            }
        }
    }
    for(int m=0;m<4;m++)  //合并相同
    {
        for(int n=0;n<3;n++)
        {
            if(map[m][n] != 0 && map[m][n+1] == map[m][n])
            {
                map[m][n] += map[m][n+1];
                score += map[m][n+1];
                map[m][n+1] = 0;
                move = 1;
            }
        }
    }
    for(int j=0;j<4;j++)  //填补空位
    {
        for(int k=1;k<=3;k++)
        {
            while(map[j][k] != 0 && map[j][k-1] == 0)
            {
                map[j][k-1] = map[j][k];
                map[j][k] = 0;
                if(k>1)
                    k--;
            }
        }
    }
}

void toBottom()  //向下移动
{
    for(int i=0;i<4;i++)
    {
        for(int l=2;l>=0;l--)
        {
            while(map[i][l] != 0 && map[i][l+1] == 0)
            {
                map[i][l+1] = map[i][l];
                map[i][l] = 0;
                if(l<2)
                    l++;
                move = 1;
            }
        }
    }
    for(int m=0;m<4;m++)
    {
        for(int n=3;n>=0;n--)
        {
            if(map[m][n] != 0 && map[m][n-1] == map[m][n])
            {
                map[m][n] += map[m][n-1];
                score += map[m][n-1];
                map[m][n-1] = 0;
                move = 1;
            }
        }
    }
    for(int j=0;j<4;j++)
    {
        for(int k=2;k>=0;k--)
        {
            while(map[j][k] != 0 && map[j][k+1] == 0)
            {
                map[j][k+1] = map[j][k];
                map[j][k] = 0;
                if(k<2)
                    k++;
            }
        }
    }
}

void toLeft()   //向左移动
{
    for(int i=1;i<4;i++)
    {
        for(int l=0;l<4;l++)
        {
            while(map[i][l] != 0 && map[i-1][l] == 0)
            {
                map[i-1][l] = map[i][l];
                map[i][l] = 0;
                if(i>1)
                    i--;
                move = 1;
            }
        }
    }
    for(int m=0;m<3;m++)
    {
        for(int n=0;n<4;n++)
        {
            if(map[m][n] != 0 && map[m+1][n] == map[m][n])
            {
                map[m][n] += map[m+1][n];
                score += map[m+1][n];
                map[m+1][n] = 0;
                move = 1;
            }
        }
    }
    for(int j=1;j<4;j++)
    {
        for(int k=0;k<4;k++)
        {
            while(map[j][k] != 0 && map[j-1][k] == 0)
            {
                map[j-1][k] = map[j][k];
                map[j][k] = 0;
                if(j>1)
                    j--;
            }
        }
    }
}

void toRight()   //向右移动
{
    for(int i=2;i>=0;i--)
    {
        for(int l=0;l<4;l++)
        {
            while(map[i][l] != 0 && map[i+1][l] == 0)
            {
                map[i+1][l] = map[i][l];
                map[i][l] = 0;
                if(i<2)
                    i++;
                move = 1;
            }
        }
    }
    for(int m=3;m>=0;m--)
    {
        for(int n=0;n<4;n++)
        {
            if(map[m][n] != 0 && map[m-1][n] == map[m][n])
            {
                map[m][n] += map[m-1][n];
                score += map[m-1][n];
                map[m-1][n] = 0;
                move = 1;
            }
        }
    }
    for(int j=2;j>=0;j--)
    {
        for(int k=0;k<4;k++)
        {
            while(map[j][k] != 0 && map[j+1][k] == 0)
            {
                map[j+1][k] = map[j][k];
                map[j][k] = 0;
                if(j<2)
                    j++;
            }
        }
    }
}


void gameOver() //结束游戏
{
    g = 0;
    for(int i=0;i<4;i++)
    	{
        	for(int l=0;l<4;l++)
        	{	
            	if(map[i][l] == 0)
            	{
        	        g = 1;
                	break;
            	}
        	}
    	}
	
}

void changeMap()  //获取操作 
{
    char in = getch();
    switch (in)
    {
        case 'w':
            toTop();
            break;
        case 's':
            toBottom();
            break;
        case 'a':
            toLeft();
            break;
        case 'd':
			toRight();
            break;
        default:
            break;
    }
    print();
    gameOver();
    if(move)  //方向可移动进行下一步
        newNumber();
}

void hide()  //隐藏光标
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = false; //隐藏控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
}


int main()
{
    hide();
    start();
    newNumber();
    while(g)
    {
        if (kbhit()!=0)
            changeMap();

    }
    if(check=1) 
	{
	system("cls");  //清屏 
    gotoxy(1,1);	//打印分数 
    cout <<"你就这点能耐吗菜狗？"<<endl<<"x x"<<endl<<" o "<<endl<< "得分: " << score;
	} 
	else
	win();
    return 0;
    
}
