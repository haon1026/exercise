//时间：2019年7月24日12:01:29
//学生管理系统

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//学生结点
typedef struct STU
{
	char arrStuNum[10];
	char arrStuName[10];
	int iStuScore;
	struct STU *pnext;
}STUNODE;

//声明链表的头和尾
STUNODE *g_pHead = NULL;
STUNODE *g_pEnd = NULL;

//显示指令
void ShowOrder();

//增加一个学生信息（尾添加）
void AddStuMsgToLinkHead(char *arrStuNum, char arrStuName[10], int iStuScore);

//增加一个学生信息（头添加）
void AddStuMsgToLinkEnd(char *arrStuNum, char arrStuName[10], int iStuScore);

//清空链表
void FreeLinkData();

//显示所有学生的信息
void ShowStudata();

//查找指定学生
STUNODE *FindStuByNum(char *arrStuNum);

//指定位置插入结点
void InsertNode(STUNODE *pTemp, char *arrStuNum, char arrStuName[10], int iStuScore);

//删除指定学生
void DeleteStuNode(STUNODE *pNode);

//保存信息进文件
void SaveStuToFile();

//读取文件中学生信息
void ReadStuFromFile();

int main()
{
	int nOrder = -1;     //初始化
	char arrStuNum[10] = {'\0'};
	char arrStuName[10] = {'\0'};
	int iStuScore = -1;
	int nflag = 1;   //退出循环标记
	STUNODE *pTemp = NULL;

	ShowOrder();

	//读取文件中学生信息,一启动就应该读取上次的文件
	ReadStuFromFile();

	while (nflag)
	{
		printf("请选择需要执行的操作(10,查看指令):");
		scanf("%d", &nOrder);

		switch (nOrder)
		{
		case 1:  //尾添加
			//输入一个学生信息
			printf("输入添加的学生学号：");
			scanf("%s", arrStuNum);   //数组名就是数组首地址
			printf("输入添加的学生名字：");
			scanf("%s", arrStuName);
			printf("输入添加的学生成绩：");
			scanf("%d", &iStuScore);
			//添加一个学生信息
			AddStuMsgToLinkHead(arrStuNum, arrStuName, iStuScore);
			break;

		case 11:  //头添加
			//输入一个学生信息
			printf("输入添加的学生学号：");
			scanf("%s", arrStuNum);   
			printf("输入添加的学生名字：");
			scanf("%s", arrStuName);
			printf("输入添加的学生成绩：");
			scanf("%d", &iStuScore);
			//添加一个学生信息
			AddStuMsgToLinkEnd(arrStuNum, arrStuName, iStuScore);
			break;
		case 111:  //中间添加
			printf("输入指定位置的学号：");
			scanf("%s", arrStuNum);
			pTemp = FindStuByNum(arrStuNum);
			if (NULL != pTemp)
			{
				printf("输入添加的学生学号：");
				scanf("%s", arrStuNum);
				printf("输入添加的学生名字：");
				scanf("%s", arrStuName);
				printf("输入添加的学生成绩：");
				scanf("%d", &iStuScore);
				InsertNode(pTemp, arrStuNum, arrStuName, iStuScore);
			}
			break;
		case 2: //打印制定学生的信息
			//输入一个学号
			printf("输入要输出的学生的学号：");
			scanf("%s", arrStuNum);
			//查找
			pTemp = FindStuByNum(arrStuNum);
			//打印学生信息
			if (NULL != pTemp)
			{
				printf("学号：%s,姓名：%s,分数：%d\n", pTemp->arrStuNum, pTemp->arrStuName, pTemp->iStuScore);
			}
			break;
		case 3: //修改指定学生的信息
			//输入一个学号
			printf("输入要修改的学生的学号：");
			scanf("%s", arrStuNum);
			//查找
			pTemp = FindStuByNum(arrStuNum);
			//修改信息
			if (NULL != pTemp)
			{
				//修改学号
				printf("输入修改后的学号：");
				scanf("%s", arrStuNum);
				strcpy(pTemp->arrStuNum, arrStuNum);

				//修改名字
				printf("输入修改后的姓名：");
				scanf("%s", arrStuName);
				strcpy(pTemp->arrStuName, arrStuName);

				//修改分数
				printf("输入修改后的分数：");
				scanf("%d", &iStuScore);
				pTemp->iStuScore = iStuScore;
			}
			break;
		case 4:
			//保存学生信息
			SaveStuToFile();
			break;
		case 5:
			break;
		case 6:
			//输入一个学号
			printf("输入要删除的学生的学号：");
			scanf("%s", arrStuNum);
			//查找
			pTemp = FindStuByNum(arrStuNum);
			//删除这个节点
			if (NULL != pTemp)
			{
				//调用删除学生信息的函数
				DeleteStuNode(pTemp);
			}
			break;
		case 7:
			//恢复删除的学生的信息
			FreeLinkData();
			g_pHead = NULL;
			g_pEnd = NULL;
			//恢复到启动前最原始文件
			ReadStuFromFile();
			break;
		case 8:
			//显示所有学生的信息 
			ShowStudata();
			break;
		case 9 :
			//显示指令
			ShowOrder();
			break;
		case 0:
			nflag = 0;
			break;
		default:
			printf("输入的指令不对!\n");
		}
	}
	//保存信息
	SaveStuToFile();
	//释放链表
	FreeLinkData();
	system("pause");
	return 0;
}

//显示指令
void ShowOrder()
{
	printf("********************学生信息管理系统**********************\n");
	printf("********************本系统操作指令如下********************\n");
	printf("***              1. 增加一个学生信息（尾添加）         ***\n");
	printf("***              11. 增加一个学生信息（头添加）        ***\n");
	printf("***              111. 增加一个学生信息（指定位置添加） ***\n");
	printf("***              2. 查找指定学生的信息（姓名/学号）    ***\n");
	printf("***              3. 修改指定学生的信息                 ***\n");
	printf("***              4. 保存业主的信息到文件               ***\n");
	printf("***              5. 读取文件中的业主信息               ***\n");     //不需要读取文件指令，每次进系统直接运行上次的文件
	printf("***              6. 删除指定学生的信息                 ***\n");
	printf("***              7. 恢复删除的学生的信息               ***\n");
	printf("***              8. 显示所有学生的信息                 ***\n");
	printf("***              0. 退出系统                           ***\n");
	printf("**********************************************************\n");
}

//增加一个学生信息（尾添加）
void AddStuMsgToLinkHead(char *arrStuNum, char arrStuName[10], int iStuScore)   //字符数组名作为形参是传的是地址，可以写成指针类型，也可以写成数组类型  
{
	//第一步，检验参数的合法性
	if (NULL == arrStuNum || NULL == arrStuName || iStuScore < 0)
	{
		printf("学生信息输入有误！\n");
		return;
	}

	//逻辑
	//创建一个结点
	STUNODE *pTemp = (STUNODE *)malloc(sizeof(STUNODE));
	//结点成员初始值
	strcpy(pTemp->arrStuNum, arrStuNum);
	strcpy(pTemp->arrStuName, arrStuName);
	pTemp->iStuScore = iStuScore;
	pTemp->pnext = NULL;

	//接在链表上
	if (NULL == g_pHead || NULL == g_pEnd)
	{
		g_pHead = pTemp;
		//g_pEnd = pTemp;
	}
	else
	{
		g_pEnd->pnext = pTemp;   //链接
		//g_pEnd = pTemp;      //向后移动
	}
	g_pEnd = pTemp;
}

//增加一个学生信息（头添加）
void AddStuMsgToLinkEnd(char *arrStuNum, char arrStuName[10], int iStuScore)  
{
	//第一步，检验参数的合法性
	if (NULL == arrStuNum || NULL == arrStuName || iStuScore < 0)
	{
		printf("学生信息输入有误！\n");
		return;
	}

	//逻辑
	//创建一个结点
	STUNODE *pTemp = (STUNODE *)malloc(sizeof(STUNODE));
	//结点成员初始值
	strcpy(pTemp->arrStuNum, arrStuNum);
	strcpy(pTemp->arrStuName, arrStuName);
	pTemp->iStuScore = iStuScore;
	pTemp->pnext = NULL;

	//接在链表上
	if (NULL == g_pHead || NULL == g_pEnd)
	{
		g_pEnd = pTemp;
		//g_pHead = pTemp;
	}
	else
	{
		pTemp->pnext = g_pHead;   //链接
		//g_pHead = pTemp;      //向前移动
	}
	g_pHead = pTemp;
}

//清空链表
void FreeLinkData()
{
	STUNODE *pTemp = g_pHead;
	while (g_pHead != NULL)
	{
		//记录结点
		pTemp = g_pHead;

		//向后移动一个
		g_pHead = g_pEnd->pnext;

		//删除结点
		free(pTemp);
	}
}

//显示所有学生的信息 
void ShowStudata()
{
	STUNODE *pTemp = g_pHead;
	while (pTemp != NULL)
	{
		//输出学生信息
		printf("学号：%s, 姓名：%s, 分数：%d\n", pTemp->arrStuNum, pTemp->arrStuName, pTemp->iStuScore);

		//向下走一步
		pTemp = pTemp->pnext;
	}
}

//查找指定学生
STUNODE *FindStuByNum(char *arrStuNum)
{
	//检测参数的合法性
	if (NULL == arrStuNum)
	{
		printf("学号输入错误！\n");
		return NULL;
	}

	//判断链表是否为空
	if (NULL == g_pHead || NULL == g_pEnd)
	{
		printf("链表为NULL！\n");
		return NULL;
	}

	//遍历链表
	STUNODE *pTemp = g_pHead;
	while (pTemp != NULL)
	{
		if (0 == strcmp(pTemp->arrStuNum, arrStuNum))    //字符串比较不能直接用==判断
		{
			return pTemp;
		}
		pTemp = pTemp->pnext;
	}
	printf("查无此结点！\n");
	return NULL;
}

//指定位置插入结点
void InsertNode(STUNODE *pTemp, char *arrStuNum, char arrStuName[10], int iStuScore)
{
	//创建结点
	STUNODE *pNew = (STUNODE*)malloc(sizeof(STUNODE));
	strcpy(pNew->arrStuNum, arrStuNum);
	strcpy(pNew->arrStuName, arrStuName);
	pNew->iStuScore = iStuScore;
	pNew->pnext = NULL;

	//插入结点
	if (pTemp == g_pEnd)   //尾结点
	{
		g_pEnd->pnext = pNew;
		g_pEnd = pNew;
	}
	else
	{
		pNew->pnext = pTemp->pnext;
		pTemp->pnext = pNew;
	}

}

//删除指定学生
void DeleteStuNode(STUNODE *pNode)
{
	//只有一个结点
	if (g_pHead == g_pEnd)
	{
		free(g_pHead);
		g_pHead = NULL;
		g_pEnd = NULL;
	}
	//两个结点
	else if (g_pHead->pnext == g_pEnd)
	{
		if (g_pHead == pNode)     //删除两个结点中的第一个
		{
			free(g_pHead);
			g_pHead == g_pEnd;
		}
		else                        //删除两个结点中的第二个
		{
			free(g_pEnd);
			g_pEnd = g_pHead;
			g_pHead->pnext = NULL;
		}
	}
	//结点大于两个
	else
	{
		STUNODE *pTemp = g_pHead;
		//判断要删除的结点是头结点
		if (g_pHead == pNode)
		{
			pTemp = g_pHead;
			g_pHead = g_pHead->pnext;
			free(pTemp);
			pTemp = NULL;
			return;
		}
		while (pTemp)    //要删除的不是头结点
		{
			if (pTemp->pnext == pNode)   //直接从第二个结点开始判断
			{
				//如果要删除的结点是尾结点
				if (pNode == g_pEnd)
				{
					free(g_pEnd);
					g_pEnd = pTemp;
					g_pEnd->pnext = NULL;
					return;
				}
				//不是尾结点
				else
				{
					pTemp->pnext = pNode->pnext;
					free(pNode);
					pNode = NULL;
					return;
				}
			}
			pTemp = pTemp->pnext;
		}
	}

}

//保存信息进文件
void SaveStuToFile()
{
	//判断链表是否为空
	if (NULL == g_pHead)
	{
		printf("没有学生\n");
		return;
	}

	FILE *pFile = NULL;

	//打开文件
	pFile = fopen("dat.dat", "wb+");
	if (NULL == pFile)
	{
		printf("文件打开失败\n");
		return;
	}

	//操作文件指针
	STUNODE *pTemp = g_pHead;
	char strBuf[30] = { 0 };
	char strScore[10] = { 0 };
	while (pTemp)
	{
		//学号赋值给BUF
		strcpy(strBuf, pTemp->arrStuNum);
		//加入"."分割
		strcat(strBuf, ".");
		//姓名追加到BUF后
		strcat(strBuf, pTemp->arrStuName);
		strcat(strBuf, ".");
		//分数转换为字符型
		itoa(pTemp->iStuScore, strScore, 10);
		//转换后的分数追加到BUF
		strcat(strBuf, strScore);

		//信息写入文件
		fwrite(strBuf, 1, strlen(strBuf), pFile);    //1 * strlen(strBuf)表示写入的字节数
		//加入换行符
		fwrite("\r\n", 1, strlen("\r\n"), pFile);
		pTemp = pTemp->pnext;
	}

	//关闭文件
	fclose(pFile);
}

//读取文件中学生信息
void ReadStuFromFile()
{
	FILE *pFile = fopen("dat.dat", "rb+");
	if (NULL == pFile)
	{
		printf("文件打开失败！\n");
		return;
	}

	//操作指针，读取文件
	char strBuf[30] = { 0 };
	char strStuNum[10] = { 0 };
	char strStuName[10] = { 0 };
	char strStuScore[10] = { 0 };
	
	   
	while (NULL != fgets(strBuf, 30, pFile))   //最大读取量30，不能超过strBuf的长度      
	{
		int i = 0;
		int j = 0;
		int nCount = 0;   //记住读取时.的次数
		//读取一个学生信息
		for (i = 0; strBuf[i] != '\r'; i++)    //fgets读取一行，包括行结尾"\r\n"
		{
			if (0 == nCount)    //没到'.'
			{
				strStuNum[i] = strBuf[i];
				if ('.' == strBuf[i])
				{
					strStuNum[i] = '\0';
					nCount++;
				}
			}
			else if (1 == nCount)   //第一个'.'
			{
				strStuName[j] = strBuf[i];
				j++;
				if ('.' == strBuf[i])
				{
					strStuName[i] = '\0';
					nCount++;
					j = 0;
				}	
			}
			else              // 第二个'.'
			{
				strStuScore[j] = strBuf[i];
				j++;
			}
		}
		
		//插入到链表
		AddStuMsgToLinkHead(strStuNum, strStuName, atoi(strStuScore));
	}

	fclose(pFile);
}