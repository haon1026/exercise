//时间：2019年6月14日13:42:53
//推箱子

#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

#define ROW 9     //行
#define COL 11    //列

//地图
int map[ROW][COL] = {               //空地 0；墙 1；箱子 4; 人 5； 目的地 3
		{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0 },
		{ 0, 1, 0, 4, 4, 4, 4, 4, 0, 1, 0 },
		{ 0, 1, 0, 4, 0, 4, 0, 4, 0, 1, 1 },
		{ 0, 1, 0, 0, 0, 5, 0, 0, 4, 0, 1 },
		{ 1, 1, 0, 1, 1, 1, 1, 0, 4, 0, 1 },
		{ 1, 0, 3, 3, 3, 3, 3, 1, 0, 0, 1 },
		{ 1, 0, 3, 3, 3, 3, 3, 0, 0, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 }
};

void Drawmap(); //画地图
void BeginGame();//开始游戏

int main()
{
	//设置窗口标题
	SetConsoleTitle("推箱子");
	//设置窗口大小
	//system("mode con cols=40 lines=20");
	while (1)
	{
		system("cls");    //清屏
		Drawmap();        
		BeginGame();
		if (map[6][2] + map[6][3] + map[6][4] + map[6][5] + map[6][6] + map[7][2] + map[7][3] + map[7][4] + map[7][5] + map[7][6] == 70)
			break;
	}
	std::cout << "恭喜过关" << std::endl;


	return 0;
}

void Drawmap()
{
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COL; ++j)
		{
			switch (map[i][j])
			{
			case 0:   //空地
				std::cout << "  ";
				break;
			case 1:   //墙
				std::cout << "■";
				break;
			case 3:   //目的地
				std::cout << "☆";
				break;
			case 4:    //箱子
				std::cout << "□";
				break;
			case 5:    //人
				std::cout << "♀";
				break;
			case 7:    //4+3箱子在目的地
				std::cout << "★";
				break;
			case 8:    //5+3人在目的地
				std::cout << "♀";
				break;
			}
		}
		std::cout << std::endl;
	}
}

void BeginGame()
{
	//1.需要接受键盘
	//2.在接受键盘的时候，改变二维数组的元素
	//3.要改变哪些元素 人前面的值
	//确定人的位置 5 只有一个5

	//==============找到人的位置=====================
	int r, c;
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COL; ++j)
		{
			if (map[i][j] == 5 || map[i][j] == 8)
			{
				r = i;
				c = j;
			}
		}
	}
	std::cout << r << " " << c << std::endl;

	//==============接受键盘的输入=====================
	int ch;
	ch = getch();
	switch (ch)
	{
	case 'W':     //上
	case 'w':
	case 72:    //键盘键值
		//人本身的位置不在目的地
		if (map[r][c] == 5)
		{
			//1.人的上面是空地
			if (map[r - 1][c] == 0)
			{
				map[r][c] = 0;
				map[r - 1][c] = 5;
			}
			//2.人的上面是目的地
			else if (map[r - 1][c] == 3)
			{
				map[r][c] = 0;
				map[r - 1][c] = 8;
			}
			//3.人的上面是箱子
			else if (map[r - 1][c] == 4 || map[r - 1][c] == 7)
			{
				//3.1箱子在空地上
				if (map[r - 1][c] == 4)
				{
					//3.1.1箱子的上面是空地
					if (map[r - 2][c] == 0)
					{
						map[r - 2][c] = 4;
						map[r - 1][c] = 5;
						map[r][c] = 0;
					}
					//3.1.2箱子的上面是目的地
					else if (map[r - 2][c] == 3)
					{
						map[r - 2][c] = 7;
						map[r - 1][c] = 5;
						map[r][c] = 0;
					}
				}
				//3.2箱子在目的地上
				else if (map[r - 1][c] == 7)
				{
					//3.2.1箱子的上面是空地
					if (map[r - 2][c] == 0)
					{
						map[r - 2][c] = 4;
						map[r - 1][c] = 8;
						map[r][c] = 0;
					}
					//3.2.2箱子的上面是目的地
					else if (map[r - 2][c] == 3)
					{
						map[r - 2][c] = 7;
						map[r - 1][c] = 8;
						map[r][c] = 0;
					}

				}
			}

		}
		//人在目的地
		else if (map[r][c] == 8)
		{
			//1.人的上面是空地
			if (map[r - 1][c] == 0)
			{
				map[r][c] = 3;
				map[r - 1][c] = 5;
			}
			//2.人的上面是目的地
			else if (map[r - 1][c] == 3)
			{
				map[r][c] = 3;
				map[r - 1][c] = 8;
			}
			//3.人的上面是箱子
			else if (map[r - 1][c] == 4 || map[r - 1][c] == 7)
			{
				//3.1箱子在空地上
				if (map[r - 1][c] == 4)
				{
					//3.1.1箱子的上面是空地
					if (map[r - 2][c] == 0)
					{
						map[r - 2][c] = 4;
						map[r - 1][c] = 5;
						map[r][c] = 3;
					}
					//3.1.2箱子的上面是目的地
					else if (map[r - 2][c] == 3)
					{
						map[r - 2][c] = 7;
						map[r - 1][c] = 5;
						map[r][c] = 3;
					}
				}
				//3.2箱子在目的地上
				else if (map[r - 1][c] == 7)
				{
					//3.2.1箱子的上面是空地
					if (map[r - 2][c] == 0)
					{
						map[r - 2][c] = 4;
						map[r - 1][c] = 8;
						map[r][c] = 3;
					}
					//3.2.2箱子的上面是目的地
					else if (map[r - 2][c] == 3)
					{
						map[r - 2][c] = 7;
						map[r - 1][c] = 8;
						map[r][c] = 3;
					}
				}
			}
		}
		break;

	case 'S':     //下
	case 's':
	case 80:
		//人本身的位置不在目的地
		if (map[r][c] == 5)
		{
			//1.人的下面是空地
			if (map[r + 1][c] == 0)
			{
				map[r][c] = 0;
				map[r + 1][c] = 5;
			}
			//2.人的下面是目的地
			else if (map[r + 1][c] == 3)
			{
				map[r][c] = 0;
				map[r + 1][c] = 8;
			}
			//3.人的下面是箱子
			else if (map[r + 1][c] == 4 || map[r + 1][c] == 7)
			{
				//3.1箱子在空地上
				if (map[r + 1][c] == 4)
				{
					//3.1.1箱子的下面是空地
					if (map[r + 2][c] == 0)
					{
						map[r + 2][c] = 4;
						map[r + 1][c] = 5;
						map[r][c] = 0;
					}
					//3.1.2箱子的下面是目的地
					else if (map[r + 2][c] == 3)
					{
						map[r + 2][c] = 7;
						map[r + 1][c] = 5;
						map[r][c] = 0;
					}
				}
				//3.2箱子在目的地上
				else if (map[r + 1][c] == 7)
				{
					//3.2.1箱子的下面是空地
					if (map[r + 2][c] == 0)
					{
						map[r + 2][c] = 4;
						map[r + 1][c] = 8;
						map[r][c] = 0;
					}
					//3.2.2箱子的下面是目的地
					else if (map[r + 2][c] == 3)
					{
						map[r + 2][c] = 7;
						map[r + 1][c] = 8;
						map[r][c] = 0;
					}

				}
			}

		}
		//人在目的地
		else if (map[r][c] == 8)
		{
			//1.人的下面是空地
			if (map[r + 1][c] == 0)
			{
				map[r][c] = 3;
				map[r + 1][c] = 5;
			}
			//2.人的下面是目的地
			else if (map[r + 1][c] == 3)
			{
				map[r][c] = 3;
				map[r + 1][c] = 8;
			}
			//3.人的下面是箱子
			else if (map[r + 1][c] == 4 || map[r + 1][c] == 7)
			{
				//3.1箱子在空地上
				if (map[r + 1][c] == 4)
				{
					//3.1.1箱子的下面是空地
					if (map[r + 2][c] == 0)
					{
						map[r + 2][c] = 4;
						map[r + 1][c] = 5;
						map[r][c] = 3;
					}
					//3.1.2箱子的下面是目的地
					else if (map[r + 2][c] == 3)
					{
						map[r + 2][c] = 7;
						map[r + 1][c] = 5;
						map[r][c] = 3;
					}
				}
				//3.2箱子在目的地上
				else if (map[r + 1][c] == 7)
				{
					//3.2.1箱子的下面是空地
					if (map[r + 2][c] == 0)
					{
						map[r + 2][c] = 4;
						map[r + 1][c] = 8;
						map[r][c] = 3;
					}
					//3.2.2箱子的下面是目的地
					else if (map[r + 2][c] == 3)
					{
						map[r + 2][c] = 7;
						map[r + 1][c] = 8;
						map[r][c] = 3;
					}
				}
			}
		}
		break;

	case 'A':     //左
	case 'a':
	case 75:
		//人本身的位置不在目的地
		if (map[r][c] == 5)
		{
			//1.人的左面是空地
			if (map[r][c - 1] == 0)
			{
				map[r][c] = 0;
				map[r][c - 1] = 5;
			}
			//2.人的左面是目的地
			else if (map[r][c - 1] == 3)
			{
				map[r][c] = 0;
				map[r][c - 1] = 8;
			}
			//3.人的左面是箱子
			else if (map[r][c - 1] == 4 || map[r][c - 1] == 7)
			{
				//3.1箱子在空地上
				if (map[r][c - 1] == 4)
				{
					//3.1.1箱子的左面是空地
					if (map[r][c - 2] == 0)
					{
						map[r][c - 2] = 4;
						map[r][c - 1] = 5;
						map[r][c] = 0;
					}
					//3.1.2箱子的左面是目的地
					else if (map[r][c - 2] == 3)
					{
						map[r][c - 2] = 7;
						map[r][c - 1] = 5;
						map[r][c] = 0;
					}
				}
				//3.2箱子在目的地上
				else if (map[r][c - 1] == 7)
				{
					//3.2.1箱子的左面是空地
					if (map[r][c - 2] == 0)
					{
						map[r][c - 2] = 4;
						map[r][c - 1] = 8;
						map[r][c] = 0;
					}
					//3.2.2箱子的左面是目的地
					else if (map[r][c - 2] == 3)
					{
						map[r][c - 2] = 7;
						map[r][c - 1] = 8;
						map[r][c] = 0;
					}

				}
			}

		}
		//人在目的地
		else if (map[r][c] == 8)
		{
			//1.人的左面是空地
			if (map[r][c - 1] == 0)
			{
				map[r][c] = 3;
				map[r][c - 1] = 5;
			}
			//2.人的左面是目的地
			else if (map[r][c - 1] == 3)
			{
				map[r][c] = 3;
				map[r][c - 1] = 8;
			}
			//3.人的左面是箱子
			else if (map[r][c - 1] == 4 || map[r][c - 1] == 7)
			{
				//3.1箱子在空地上
				if (map[r][c - 1] == 4)
				{
					//3.1.1箱子的左面是空地
					if (map[r][c - 2] == 0)
					{
						map[r][c - 2] = 4;
						map[r][c - 1] = 5;
						map[r][c] = 3;
					}
					//3.1.2箱子的左面是目的地
					else if (map[r][c - 2] == 3)
					{
						map[r][c - 2] = 7;
						map[r][c - 1] = 5;
						map[r][c] = 3;
					}
				}
				//3.2箱子在目的地上
				else if (map[r][c - 1] == 7)
				{
					//3.2.1箱子的左面是空地
					if (map[r][c - 2] == 0)
					{
						map[r][c - 2] = 4;
						map[r][c - 1] = 8;
						map[r][c] = 3;
					}
					//3.2.2箱子的左面是目的地
					else if (map[r][c - 2] == 3)
					{
						map[r][c - 2] = 7;
						map[r][c - 1] = 8;
						map[r][c] = 3;
					}
				}
			}
		}
		break;

	case 'D':     //右
	case 'd':
	case 77:
		//人本身的位置不在目的地
		if (map[r][c] == 5)
		{
			//1.人的右面是空地
			if (map[r][c + 1] == 0)
			{
				map[r][c] = 0;
				map[r][c + 1] = 5;
			}
			//2.人的右面是目的地
			else if (map[r][c + 1] == 3)
			{
				map[r][c] = 0;
				map[r][c + 1] = 8;
			}
			//3.人的右面是箱子
			else if (map[r][c + 1] == 4 || map[r][c + 1] == 7)
			{
				//3.1箱子在空地上
				if (map[r][c + 1] == 4)
				{
					//3.1.1箱子的右面是空地
					if (map[r][c + 2] == 0)
					{
						map[r][c + 2] = 4;
						map[r][c + 1] = 5;
						map[r][c] = 0;
					}
					//3.1.2箱子的右面是目的地
					else if (map[r][c + 2] == 3)
					{
						map[r][c + 2] = 7;
						map[r][c + 1] = 5;
						map[r][c] = 0;
					}
				}
				//3.2箱子在目的地上
				else if (map[r][c + 1] == 7)
				{
					//3.2.1箱子的右面是空地
					if (map[r][c + 2] == 0)
					{
						map[r][c + 2] = 4;
						map[r][c + 1] = 8;
						map[r][c] = 0;
					}
					//3.2.2箱子的右面是目的地
					else if (map[r][c + 2] == 3)
					{
						map[r][c + 2] = 7;
						map[r][c + 1] = 8;
						map[r][c] = 0;
					}

				}
			}

		}
		//人在目的地
		else if (map[r][c] == 8)
		{
			//1.人的右面是空地
			if (map[r][c + 1] == 0)
			{
				map[r][c] = 3;
				map[r][c + 1] = 5;
			}
			//2.人的右面是目的地
			else if (map[r][c + 1] == 3)
			{
				map[r][c] = 3;
				map[r][c + 1] = 8;
			}
			//3.人的右面是箱子
			else if (map[r][c + 1] == 4 || map[r][c + 1] == 7)
			{
				//3.1箱子在空地上
				if (map[r][c + 1] == 4)
				{
					//3.1.1箱子的右面是空地
					if (map[r][c + 2] == 0)
					{
						map[r][c + 2] = 4;
						map[r][c + 1] = 5;
						map[r][c] = 3;
					}
					//3.1.2箱子的右面是目的地
					else if (map[r][c + 2] == 3)
					{
						map[r][c + 2] = 7;
						map[r][c + 1] = 5;
						map[r][c] = 3;
					}
				}
				//3.2箱子在目的地上
				else if (map[r][c + 1] == 7)
				{
					//3.2.1箱子的右面是空地
					if (map[r][c + 2] == 0)
					{
						map[r][c + 2] = 4;
						map[r][c + 1] = 8;
						map[r][c] = 3;
					}
					//3.2.2箱子的右面是目的地
					else if (map[r][c + 2] == 3)
					{
						map[r][c + 2] = 7;
						map[r][c + 1] = 8;
						map[r][c] = 3;
					}
				}
			}
		}
		break;

	}


}


/*
游戏规则：

可以动的：  (改变坐标。写代码)
1.人的前面是空地
2.人的前面是目的地
3.人的前面是箱子（不一定）
3.1箱子的前面是空地
3.2箱子的前面是目的地

不可以动的情况：(啥都不干，啥都不写)
*/
