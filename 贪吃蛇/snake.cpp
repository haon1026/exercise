//ʱ�䣺2019��7��13��15:52:49
//̰������Ϸ

#include <stdio.h>
#include <stdlib.h>          //system("pause")ͷ�ļ�

////����������Ҫ���������ļ�
#include <windows.h>         
#include <mmsystem.h>      //PlaySound����ͷ�ļ�
#pragma comment(lib, "winmm.lib")   //PlaySound�ļ���
//#include "resource.h"    //�����ļ���ӳ���Դ�ļ������ɵ�ͷ�ļ�

#include <conio.h>   // _getch()ͷ�ļ�
#include "head.h"    //��Ϸ������ͷ�ļ�

#include <time.h>   //���������������Ҫ��ʱ��ͷ�ļ�

//��ʾ��ҳ
void FirstPage();
//��������
void MyPlaySound();
//���ո��
void TestSpace();
//ֹͣ����
void MyStopMusic();
//������
void ShowBackground();
//Ϊ�߲���һ�������λ��
void SetSnakeRandPos();
//����
void DrawSnake();
//�߶�
void SnakeMove();
//������
void DropSnake();
//���淽������
void ChangeDir();
//�������ж�
bool IsSnakeAlive();
//�����µ�ʳ��
void ProduceFood();
//�߳���
void SnakeGrowUp();
//�Ʒ� 
void Score();

int main()
{
	//��ʾ��ҳ
	FirstPage();

	//��������
	MyPlaySound();

	//���ո��
	TestSpace();

	//ֹͣ����
	MyStopMusic();

	//�������̨
	system("cls");  

	//Ϊ�߲���һ�������λ��
	SetSnakeRandPos();
	ShowBackground();

	//��Ϸ����
	while (1)
	{
		system("cls");

		//����ʳ��
		ProduceFood();

		//�߱䳤
		SnakeGrowUp();

		//���淽������
		ChangeDir();

		//�ж�����
		if (false == IsSnakeAlive())
		{
			printf("snake die");
			break;
		}

		//�߶�
		SnakeMove();

		//��ʾ����
		ShowBackground();

		//��ʾ����
		Score();

		Sleep(500);
	}

	system("pause");
	return 0;
}






//��ʾ��ҳ
void FirstPage()
{
	printf("\n\n\n\n\n");
	printf("\t\t\t <<��ӭ����̰��������>>\n");
	printf("\t\t\t  <<���ո�ʼ��Ϸ>>\n");
	printf("\t\t\t<<w a s d �����ߵķ���>>\n");
}

//��������
void MyPlaySound()
{
	//1.��һ������Ϊ·�������       //��Դ����Ըߣ����滻
	//PlaySound(L"C:\\Windows\\Media\\Ring02.wav", NULL, SND_FILENAME | SND_ASYNC);   //����·��                                        //debug�ǵ��԰汾������Ա���Գ���    //release�Ƿ����汾��Ϊ�û�ʹ�ã������ɿ�ִ���ļ�
	PlaySound(L"Ring02.wav", NULL, SND_FILENAME | SND_ASYNC);        //���·��

	//�˴������е������ļ������������޸ģ�����������ļ����ĳ�1����ͨ�õ����֣��Ժ�Ϳ��԰ѱ���������ָĳ�1���ڸ�Ŀ¼��ʵ�����ָ���
	//����·��������·���� �������Ϸ�������ˣ�·����һ�»��������ļ����޷���������
	//���·�����ڵ�ǰ�ļ����²��ң���������ļ����ڵ�ǰ�����ļ����¡�     Release�ļ�����Ҳ��Ҫ�������ļ�����ִ���ļ����ܲ���

	//2/��һ������Ϊ��Դ�����      ��ʽ�����������ӵ�����Դ���������ļ���������ͷ�ļ�����Դ�ļ��������ļ���ȫ������Ŀ��һ����      ȱ�㣺�޷��滻������Բ��ִ���ļ���
	//PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_RESOURCE | SND_ASYNC);
}

//���ո��
void TestSpace()
{
	char chInput;
	while (1)
	{
		chInput = _getch();    //�ӿ���̨��ȡһ���ַ�������ʾ����Ļ�ϣ������ַ����ð��س��Զ�����       getchar()�����ַ����س�����
		if (' ' == chInput)
		{
			break;
		}
	}
}

//ֹͣ����
void MyStopMusic()
{
	PlaySound(NULL, 0, 0);   // PlaySound(NULL, NULL, NULL)
}

//������
void ShowBackground()              
{
	int i = 0;
	for (i = 0; i < 20; i++)
	{
		printf(g_strGameBack[i]);
	}
}

//Ϊ�߲���һ�������λ��
void SetSnakeRandPos()
{
	int nX = -1;
	int nY = -1;

	//���������
	srand((unsigned int)time(NULL));    //������
	nX = rand() % 19 + 1;    //С���������㣬ͷ������ߣ����������£�����nX��Χ��1-19
	nY = rand() % 18 + 1;    //nY��Χ��1-18

	//��ʼ���ߵ������ڵ�
	g_arrSnake[0][0] = nY;   //��
	g_arrSnake[0][1] = nX * 2;   //��
	g_arrSnake[0][2] = to_west;

	g_arrSnake[1][0] = nY;   //��
	g_arrSnake[1][1] = nX * 2 + 2;   //��
	g_arrSnake[1][2] = to_west;

	g_arrSnake[2][0] = nY;   //��
	g_arrSnake[2][1] = nX * 2 + 4;   //��
	g_arrSnake[2][2] = to_west;

	//����������
	DrawSnake();
}

//����
void DrawSnake()
{
	int i = 0;
	for (i = 0; g_arrSnake[i][0] != 0; i++)
	{
		strncpy(&g_strGameBack[g_arrSnake[i][0]][g_arrSnake[i][1]], "��", 2);    //�ַ���ĩβ����\0���÷����ַ���3���ַ�������һ��\0,����������\0��ͣ����������Ҫָ�������ַ������ȵ�strncpy����c
	}
}

//�߶�
void SnakeMove()
{
	int i = DEF_SNAKE_LONG - 1;

	//������
	DropSnake();

	for (i; i >= 1; i--)
	{
		//���˵��Ƿ�����
		if (0 == g_arrSnake[i][0])
		{
			continue;
		}

		//��ǰһ���ڵ��ֵ����ֵ����ǰ�ڵ�
		g_arrSnake[i][0] = g_arrSnake[i-1][0];
		g_arrSnake[i][1] = g_arrSnake[i-1][1];
		g_arrSnake[i][2] = g_arrSnake[i-1][2];
	}

	//������ͷ
	g_arrSnake[0][2] = g_nSnakeDir;

	if (to_west == g_arrSnake[0][2] || to_east == g_arrSnake[0][2])
	{
		g_arrSnake[0][1] += g_arrSnake[0][2];
	}
	else
	{
		g_arrSnake[0][0] += g_arrSnake[0][2];
	}

	//����
	DrawSnake();
}

//������
void DropSnake()
{
	int i = 0;
	for (i = 0; g_arrSnake[i][0] != 0; i++)
	{
		strncpy(&g_strGameBack[g_arrSnake[i][0]][g_arrSnake[i][1]], "  ", 2);    //��ԭ�Ȼ��ߵķ����ɿո�
	}
}

//���淽������
void ChangeDir()
{
	//getchar();   //�����ã����ڿ���̨��ʾ����Ҫ���س�
	//_getch();    //�����ã��ȴ�����Ῠס��ͬ�����

	//����short���ͣ� �����ֽ�  ���ֽ� ���ֽ�   0000 0000 0000 0000  //���ֽڣ��ߵ�������ʱ��ͬʱw�����ڰ��ţ����ֽ�װһ����0����0��ֵ�������ֽڣ�������ִ��֮ǰ������һ��W�������֮ǰ���������ֽڷ���1
	if (GetAsyncKeyState('W'))    //û����W������0���а���W�����ط�0��ֵ         GetAsyncKeyState('W') & 1��д��   ֻ�ж��Ƿ񰴹�W   �������򲻹ܰ�������һֱ���Ŷ�Ҫִ�з�����
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
		//��ͷ����һ���Ƿ����������
		if (0 == strncmp(&g_strGameBack[g_arrSnake[0][0]][g_arrSnake[0][1] + g_arrSnake[0][2]], "��", 2))
		{
			return false;
		}

	}
	else
	{
		if (0 == strncmp(&g_strGameBack[g_arrSnake[0][0] + g_arrSnake[0][2]][g_arrSnake[0][1]], "��", 2))
		{
			return false;
		}
	}

	return true;
}

//�����µ�ʳ��
void ProduceFood()
{
	
	//�ж��Ƿ�����µ�ʳ��
	if (false == g_blProFood)
	{
		return;
	}

	//�����������
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
	//���껭ʳ��
	strncpy(&g_strGameBack[g_nRow][g_nCol * 2], "��", 2);

	g_blProFood = false;
}

//�߳���
void SnakeGrowUp()
{
	//��ͷ�����ʳ���������
	if (g_nRow == g_arrSnake[0][0] && g_nCol*2 == g_arrSnake[0][1])
	{
		//�߳���
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

//�Ʒ�
void Score()
{
	COORD rd;
	rd.X = 55;
	rd.Y = 8;
	//���ù��λ��
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	//��ӡ
	printf("����");

	rd.X = 56;
	rd.Y = 9;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
    printf("%d", g_nScore);


}