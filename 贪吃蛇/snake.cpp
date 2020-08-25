//时间：2019年7月13日15:52:49
//贪吃蛇游戏

#include <stdio.h>
#include <stdlib.h>          //system("pause")头文件

////播放声音需要以下三个文件
#include <windows.h>         
#include <mmsystem.h>      //PlaySound函数头文件
#pragma comment(lib, "winmm.lib")   //PlaySound文件库
//#include "resource.h"    //音乐文件添加成资源文件后生成的头文件

#include <conio.h>   // _getch()头文件
#include "head.h"    //游戏背景的头文件

#include <time.h>   //生成随机数种子需要的时间头文件

//显示首页
void FirstPage();
//播放音乐
void MyPlaySound();
//按空格键
void TestSpace();
//停止播放
void MyStopMusic();
//画背景
void ShowBackground();
//为蛇产生一个随机的位置
void SetSnakeRandPos();
//画蛇
void DrawSnake();
//蛇动
void SnakeMove();
//销毁蛇
void DropSnake();
//蛇随方向动起来
void ChangeDir();
//蛇死亡判断
bool IsSnakeAlive();
//产生新的食物
void ProduceFood();
//蛇长大
void SnakeGrowUp();
//计分 
void Score();

int main()
{
	//显示首页
	FirstPage();

	//播放音乐
	MyPlaySound();

	//按空格键
	TestSpace();

	//停止播放
	MyStopMusic();

	//清除控制台
	system("cls");  

	//为蛇产生一个随机的位置
	SetSnakeRandPos();
	ShowBackground();

	//游戏界面
	while (1)
	{
		system("cls");

		//产生食物
		ProduceFood();

		//蛇变长
		SnakeGrowUp();

		//蛇随方向动起来
		ChangeDir();

		//判断死亡
		if (false == IsSnakeAlive())
		{
			printf("snake die");
			break;
		}

		//蛇动
		SnakeMove();

		//显示背景
		ShowBackground();

		//显示分数
		Score();

		Sleep(500);
	}

	system("pause");
	return 0;
}






//显示首页
void FirstPage()
{
	printf("\n\n\n\n\n");
	printf("\t\t\t <<欢迎进入贪吃蛇世界>>\n");
	printf("\t\t\t  <<按空格开始游戏>>\n");
	printf("\t\t\t<<w a s d 控制蛇的方向>>\n");
}

//播放音乐
void MyPlaySound()
{
	//1.第一个参数为路径的情况       //资源灵活性高，可替换
	//PlaySound(L"C:\\Windows\\Media\\Ring02.wav", NULL, SND_FILENAME | SND_ASYNC);   //绝对路径                                        //debug是调试版本，程序员调试程序    //release是发布版本，为用户使用，会生成可执行文件
	PlaySound(L"Ring02.wav", NULL, SND_FILENAME | SND_ASYNC);        //相对路径

	//此处代码中的音乐文件名可以自主修改，比如把音乐文件名改成1或者通用的名字，以后就可以把别的音乐名字改成1放在该目录下实现音乐更改
	//绝对路径：完整路径， 如果把游戏传给别人，路径不一致或无音乐文件则无法播放音乐
	//相对路径：在当前文件夹下查找，需把音乐文件放在当前工程文件夹下。     Release文件夹下也需要该音乐文件，可执行文件才能播放

	//2/第一个参数为资源的情况      方式：解决方案添加导入资源导入音乐文件，会生成头文件和资源文件，音乐文件完全成了项目的一部分      缺点：无法替换，灵活性差，可执行文件大
	//PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_RESOURCE | SND_ASYNC);
}

//按空格键
void TestSpace()
{
	char chInput;
	while (1)
	{
		chInput = _getch();    //从控制台读取一个字符，不显示在屏幕上，输入字符不用按回车自动读入       getchar()输入字符按回车读入
		if (' ' == chInput)
		{
			break;
		}
	}
}

//停止播放
void MyStopMusic()
{
	PlaySound(NULL, 0, 0);   // PlaySound(NULL, NULL, NULL)
}

//画背景
void ShowBackground()              
{
	int i = 0;
	for (i = 0; i < 20; i++)
	{
		printf(g_strGameBack[i]);
	}
}

//为蛇产生一个随机的位置
void SetSnakeRandPos()
{
	int nX = -1;
	int nY = -1;

	//产生随机数
	srand((unsigned int)time(NULL));    //种种子
	nX = rand() % 19 + 1;    //小蛇有三个点，头在最左边，不考虑上下，所以nX范围是1-19
	nY = rand() % 18 + 1;    //nY范围是1-18

	//初始化蛇的三个节点
	g_arrSnake[0][0] = nY;   //行
	g_arrSnake[0][1] = nX * 2;   //列
	g_arrSnake[0][2] = to_west;

	g_arrSnake[1][0] = nY;   //行
	g_arrSnake[1][1] = nX * 2 + 2;   //列
	g_arrSnake[1][2] = to_west;

	g_arrSnake[2][0] = nY;   //行
	g_arrSnake[2][1] = nX * 2 + 4;   //列
	g_arrSnake[2][2] = to_west;

	//画到背景上
	DrawSnake();
}

//画蛇
void DrawSnake()
{
	int i = 0;
	for (i = 0; g_arrSnake[i][0] != 0; i++)
	{
		strncpy(&g_strGameBack[g_arrSnake[i][0]][g_arrSnake[i][1]], "■", 2);    //字符串末尾含有\0，该方块字符是3个字符，包括一个\0,画背景遇到\0会停下来，所以要指定复制字符串长度的strncpy函数c
	}
}

//蛇动
void SnakeMove()
{
	int i = DEF_SNAKE_LONG - 1;

	//销毁蛇
	DropSnake();

	for (i; i >= 1; i--)
	{
		//过滤掉非法蛇身
		if (0 == g_arrSnake[i][0])
		{
			continue;
		}

		//把前一个节点的值，赋值给当前节点
		g_arrSnake[i][0] = g_arrSnake[i-1][0];
		g_arrSnake[i][1] = g_arrSnake[i-1][1];
		g_arrSnake[i][2] = g_arrSnake[i-1][2];
	}

	//处理蛇头
	g_arrSnake[0][2] = g_nSnakeDir;

	if (to_west == g_arrSnake[0][2] || to_east == g_arrSnake[0][2])
	{
		g_arrSnake[0][1] += g_arrSnake[0][2];
	}
	else
	{
		g_arrSnake[0][0] += g_arrSnake[0][2];
	}

	//画蛇
	DrawSnake();
}

//销毁蛇
void DropSnake()
{
	int i = 0;
	for (i = 0; g_arrSnake[i][0] != 0; i++)
	{
		strncpy(&g_strGameBack[g_arrSnake[i][0]][g_arrSnake[i][1]], "  ", 2);    //把原先画蛇的方块变成空格
	}
}

//蛇随方向动起来
void ChangeDir()
{
	//getchar();   //不可用，会在控制台显示且需要按回车
	//_getch();    //不可用，等待输入会卡住，同步检测

	//返回short类型， 两个字节  高字节 低字节   0000 0000 0000 0000  //高字节，走到检测语句时，同时w键正在按着，高字节装一个！0（非0的值），低字节，检测语句执行之前，按了一下W键，检测之前按过，低字节返回1
	if (GetAsyncKeyState('W'))    //没按过W键返回0，有按过W，返回非0的值         GetAsyncKeyState('W') & 1的写法   只判断是否按过W   ，本程序不管按过还是一直按着都要执行方向动作
	{
		if (to_south != g_arrSnake[0][2])
		{
			g_nSnakeDir = to_north;
		}
	}
	else if (GetAsyncKeyState('S'))
	{
		if (to_north != g_arrSnake[0][2])
		{
			g_nSnakeDir = to_south;
		}
	}
	else if (GetAsyncKeyState('A'))
	{
		if (to_east != g_arrSnake[0][2])
		{
			g_nSnakeDir = to_west;
		}
	}
	else if (GetAsyncKeyState('D'))
	{
		if (to_west != g_arrSnake[0][2])
		{
			g_nSnakeDir = to_east;
		}
	}
}

bool IsSnakeAlive()
{
	if (to_west == g_arrSnake[0][2] || to_east == g_arrSnake[0][2])
	{
		//蛇头的下一个是方块就是死亡
		if (0 == strncmp(&g_strGameBack[g_arrSnake[0][0]][g_arrSnake[0][1] + g_arrSnake[0][2]], "■", 2))
		{
			return false;
		}

	}
	else
	{
		if (0 == strncmp(&g_strGameBack[g_arrSnake[0][0] + g_arrSnake[0][2]][g_arrSnake[0][1]], "■", 2))
		{
			return false;
		}
	}

	return true;
}

//产生新的食物
void ProduceFood()
{
	
	//判断是否产生新的食物
	if (false == g_blProFood)
	{
		return;
	}

	//产生随机坐标
	srand((unsigned)time (NULL));
	while (1)
	{
		bool bFlag = true;
		g_nRow = rand() % 18 + 1;
		g_nCol = rand() % 20 + 1;

		for (int i = 0; g_arrSnake[i][0] != 0; i++)
		{
			if (g_nRow == g_arrSnake[i][0] && g_nCol == g_arrSnake[i][1])
			{
				bFlag = false;
				break;
			}
		}

		if (true == bFlag)
		{
			break;
		}
	}
	//坐标画食物
	strncpy(&g_strGameBack[g_nRow][g_nCol * 2], "★", 2);

	g_blProFood = false;
}

//蛇长大
void SnakeGrowUp()
{
	//蛇头坐标跟食物坐标相等
	if (g_nRow == g_arrSnake[0][0] && g_nCol*2 == g_arrSnake[0][1])
	{
		//蛇长大
		if (to_east == g_arrSnake[g_nSnakelen][2])
		{
			g_arrSnake[g_nSnakelen + 1][0] = g_arrSnake[g_nSnakelen][0];
			g_arrSnake[g_nSnakelen + 1][1] = g_arrSnake[g_nSnakelen][1] - 2;
			g_arrSnake[g_nSnakelen + 1][2] = g_arrSnake[g_nSnakelen][2];
		}
		else if (to_west == g_arrSnake[g_nSnakelen][2])
		{
			g_arrSnake[g_nSnakelen + 1][0] = g_arrSnake[g_nSnakelen][0];
			g_arrSnake[g_nSnakelen + 1][1] = g_arrSnake[g_nSnakelen][1] + 2;
			g_arrSnake[g_nSnakelen + 1][2] = g_arrSnake[g_nSnakelen][2];
		}
		else if (to_north == g_arrSnake[g_nSnakelen][2])
		{
			g_arrSnake[g_nSnakelen + 1][0] = g_arrSnake[g_nSnakelen][0] + 1;
			g_arrSnake[g_nSnakelen + 1][1] = g_arrSnake[g_nSnakelen][1];
			g_arrSnake[g_nSnakelen + 1][2] = g_arrSnake[g_nSnakelen][2];
		}
		else if (to_south == g_arrSnake[g_nSnakelen][2])
		{
			g_arrSnake[g_nSnakelen + 1][0] = g_arrSnake[g_nSnakelen][0] - 1;
			g_arrSnake[g_nSnakelen + 1][1] = g_arrSnake[g_nSnakelen][1];
			g_arrSnake[g_nSnakelen + 1][2] = g_arrSnake[g_nSnakelen][2];
		}

		g_nSnakelen++;
		g_blProFood = true;
		g_nScore++;
	}
}

//计分
void Score()
{
	COORD rd;
	rd.X = 55;
	rd.Y = 8;
	//设置光标位置
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	//打印
	printf("分数");

	rd.X = 56;
	rd.Y = 9;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
    printf("%d", g_nScore);


}