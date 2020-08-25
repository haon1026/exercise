//ʱ�䣺2019��7��24��12:01:29
//ѧ������ϵͳ

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//ѧ�����
typedef struct STU
{
	char arrStuNum[10];
	char arrStuName[10];
	int iStuScore;
	struct STU *pnext;
}STUNODE;

//���������ͷ��β
STUNODE *g_pHead = NULL;
STUNODE *g_pEnd = NULL;

//��ʾָ��
void ShowOrder();

//����һ��ѧ����Ϣ��β��ӣ�
void AddStuMsgToLinkHead(char *arrStuNum, char arrStuName[10], int iStuScore);

//����һ��ѧ����Ϣ��ͷ��ӣ�
void AddStuMsgToLinkEnd(char *arrStuNum, char arrStuName[10], int iStuScore);

//�������
void FreeLinkData();

//��ʾ����ѧ������Ϣ
void ShowStudata();

//����ָ��ѧ��
STUNODE *FindStuByNum(char *arrStuNum);

//ָ��λ�ò�����
void InsertNode(STUNODE *pTemp, char *arrStuNum, char arrStuName[10], int iStuScore);

//ɾ��ָ��ѧ��
void DeleteStuNode(STUNODE *pNode);

//������Ϣ���ļ�
void SaveStuToFile();

//��ȡ�ļ���ѧ����Ϣ
void ReadStuFromFile();

int main()
{
	int nOrder = -1;     //��ʼ��
	char arrStuNum[10] = {'\0'};
	char arrStuName[10] = {'\0'};
	int iStuScore = -1;
	int nflag = 1;   //�˳�ѭ�����
	STUNODE *pTemp = NULL;

	ShowOrder();

	//��ȡ�ļ���ѧ����Ϣ,һ������Ӧ�ö�ȡ�ϴε��ļ�
	ReadStuFromFile();

	while (nflag)
	{
		printf("��ѡ����Ҫִ�еĲ���(10,�鿴ָ��):");
		scanf("%d", &nOrder);

		switch (nOrder)
		{
		case 1:  //β���
			//����һ��ѧ����Ϣ
			printf("������ӵ�ѧ��ѧ�ţ�");
			scanf("%s", arrStuNum);   //���������������׵�ַ
			printf("������ӵ�ѧ�����֣�");
			scanf("%s", arrStuName);
			printf("������ӵ�ѧ���ɼ���");
			scanf("%d", &iStuScore);
			//���һ��ѧ����Ϣ
			AddStuMsgToLinkHead(arrStuNum, arrStuName, iStuScore);
			break;

		case 11:  //ͷ���
			//����һ��ѧ����Ϣ
			printf("������ӵ�ѧ��ѧ�ţ�");
			scanf("%s", arrStuNum);   
			printf("������ӵ�ѧ�����֣�");
			scanf("%s", arrStuName);
			printf("������ӵ�ѧ���ɼ���");
			scanf("%d", &iStuScore);
			//���һ��ѧ����Ϣ
			AddStuMsgToLinkEnd(arrStuNum, arrStuName, iStuScore);
			break;
		case 111:  //�м����
			printf("����ָ��λ�õ�ѧ�ţ�");
			scanf("%s", arrStuNum);
			pTemp = FindStuByNum(arrStuNum);
			if (NULL != pTemp)
			{
				printf("������ӵ�ѧ��ѧ�ţ�");
				scanf("%s", arrStuNum);
				printf("������ӵ�ѧ�����֣�");
				scanf("%s", arrStuName);
				printf("������ӵ�ѧ���ɼ���");
				scanf("%d", &iStuScore);
				InsertNode(pTemp, arrStuNum, arrStuName, iStuScore);
			}
			break;
		case 2: //��ӡ�ƶ�ѧ������Ϣ
			//����һ��ѧ��
			printf("����Ҫ�����ѧ����ѧ�ţ�");
			scanf("%s", arrStuNum);
			//����
			pTemp = FindStuByNum(arrStuNum);
			//��ӡѧ����Ϣ
			if (NULL != pTemp)
			{
				printf("ѧ�ţ�%s,������%s,������%d\n", pTemp->arrStuNum, pTemp->arrStuName, pTemp->iStuScore);
			}
			break;
		case 3: //�޸�ָ��ѧ������Ϣ
			//����һ��ѧ��
			printf("����Ҫ�޸ĵ�ѧ����ѧ�ţ�");
			scanf("%s", arrStuNum);
			//����
			pTemp = FindStuByNum(arrStuNum);
			//�޸���Ϣ
			if (NULL != pTemp)
			{
				//�޸�ѧ��
				printf("�����޸ĺ��ѧ�ţ�");
				scanf("%s", arrStuNum);
				strcpy(pTemp->arrStuNum, arrStuNum);

				//�޸�����
				printf("�����޸ĺ��������");
				scanf("%s", arrStuName);
				strcpy(pTemp->arrStuName, arrStuName);

				//�޸ķ���
				printf("�����޸ĺ�ķ�����");
				scanf("%d", &iStuScore);
				pTemp->iStuScore = iStuScore;
			}
			break;
		case 4:
			//����ѧ����Ϣ
			SaveStuToFile();
			break;
		case 5:
			break;
		case 6:
			//����һ��ѧ��
			printf("����Ҫɾ����ѧ����ѧ�ţ�");
			scanf("%s", arrStuNum);
			//����
			pTemp = FindStuByNum(arrStuNum);
			//ɾ������ڵ�
			if (NULL != pTemp)
			{
				//����ɾ��ѧ����Ϣ�ĺ���
				DeleteStuNode(pTemp);
			}
			break;
		case 7:
			//�ָ�ɾ����ѧ������Ϣ
			FreeLinkData();
			g_pHead = NULL;
			g_pEnd = NULL;
			//�ָ�������ǰ��ԭʼ�ļ�
			ReadStuFromFile();
			break;
		case 8:
			//��ʾ����ѧ������Ϣ 
			ShowStudata();
			break;
		case 9 :
			//��ʾָ��
			ShowOrder();
			break;
		case 0:
			nflag = 0;
			break;
		default:
			printf("�����ָ���!\n");
		}
	}
	//������Ϣ
	SaveStuToFile();
	//�ͷ�����
	FreeLinkData();
	system("pause");
	return 0;
}

//��ʾָ��
void ShowOrder()
{
	printf("********************ѧ����Ϣ����ϵͳ**********************\n");
	printf("********************��ϵͳ����ָ������********************\n");
	printf("***              1. ����һ��ѧ����Ϣ��β��ӣ�         ***\n");
	printf("***              11. ����һ��ѧ����Ϣ��ͷ��ӣ�        ***\n");
	printf("***              111. ����һ��ѧ����Ϣ��ָ��λ����ӣ� ***\n");
	printf("***              2. ����ָ��ѧ������Ϣ������/ѧ�ţ�    ***\n");
	printf("***              3. �޸�ָ��ѧ������Ϣ                 ***\n");
	printf("***              4. ����ҵ������Ϣ���ļ�               ***\n");
	printf("***              5. ��ȡ�ļ��е�ҵ����Ϣ               ***\n");     //����Ҫ��ȡ�ļ�ָ�ÿ�ν�ϵͳֱ�������ϴε��ļ�
	printf("***              6. ɾ��ָ��ѧ������Ϣ                 ***\n");
	printf("***              7. �ָ�ɾ����ѧ������Ϣ               ***\n");
	printf("***              8. ��ʾ����ѧ������Ϣ                 ***\n");
	printf("***              0. �˳�ϵͳ                           ***\n");
	printf("**********************************************************\n");
}

//����һ��ѧ����Ϣ��β��ӣ�
void AddStuMsgToLinkHead(char *arrStuNum, char arrStuName[10], int iStuScore)   //�ַ���������Ϊ�β��Ǵ����ǵ�ַ������д��ָ�����ͣ�Ҳ����д����������  
{
	//��һ������������ĺϷ���
	if (NULL == arrStuNum || NULL == arrStuName || iStuScore < 0)
	{
		printf("ѧ����Ϣ��������\n");
		return;
	}

	//�߼�
	//����һ�����
	STUNODE *pTemp = (STUNODE *)malloc(sizeof(STUNODE));
	//����Ա��ʼֵ
	strcpy(pTemp->arrStuNum, arrStuNum);
	strcpy(pTemp->arrStuName, arrStuName);
	pTemp->iStuScore = iStuScore;
	pTemp->pnext = NULL;

	//����������
	if (NULL == g_pHead || NULL == g_pEnd)
	{
		g_pHead = pTemp;
		//g_pEnd = pTemp;
	}
	else
	{
		g_pEnd->pnext = pTemp;   //����
		//g_pEnd = pTemp;      //����ƶ�
	}
	g_pEnd = pTemp;
}

//����һ��ѧ����Ϣ��ͷ��ӣ�
void AddStuMsgToLinkEnd(char *arrStuNum, char arrStuName[10], int iStuScore)  
{
	//��һ������������ĺϷ���
	if (NULL == arrStuNum || NULL == arrStuName || iStuScore < 0)
	{
		printf("ѧ����Ϣ��������\n");
		return;
	}

	//�߼�
	//����һ�����
	STUNODE *pTemp = (STUNODE *)malloc(sizeof(STUNODE));
	//����Ա��ʼֵ
	strcpy(pTemp->arrStuNum, arrStuNum);
	strcpy(pTemp->arrStuName, arrStuName);
	pTemp->iStuScore = iStuScore;
	pTemp->pnext = NULL;

	//����������
	if (NULL == g_pHead || NULL == g_pEnd)
	{
		g_pEnd = pTemp;
		//g_pHead = pTemp;
	}
	else
	{
		pTemp->pnext = g_pHead;   //����
		//g_pHead = pTemp;      //��ǰ�ƶ�
	}
	g_pHead = pTemp;
}

//�������
void FreeLinkData()
{
	STUNODE *pTemp = g_pHead;
	while (g_pHead != NULL)
	{
		//��¼���
		pTemp = g_pHead;

		//����ƶ�һ��
		g_pHead = g_pEnd->pnext;

		//ɾ�����
		free(pTemp);
	}
}

//��ʾ����ѧ������Ϣ 
void ShowStudata()
{
	STUNODE *pTemp = g_pHead;
	while (pTemp != NULL)
	{
		//���ѧ����Ϣ
		printf("ѧ�ţ�%s, ������%s, ������%d\n", pTemp->arrStuNum, pTemp->arrStuName, pTemp->iStuScore);

		//������һ��
		pTemp = pTemp->pnext;
	}
}

//����ָ��ѧ��
STUNODE *FindStuByNum(char *arrStuNum)
{
	//�������ĺϷ���
	if (NULL == arrStuNum)
	{
		printf("ѧ���������\n");
		return NULL;
	}

	//�ж������Ƿ�Ϊ��
	if (NULL == g_pHead || NULL == g_pEnd)
	{
		printf("����ΪNULL��\n");
		return NULL;
	}

	//��������
	STUNODE *pTemp = g_pHead;
	while (pTemp != NULL)
	{
		if (0 == strcmp(pTemp->arrStuNum, arrStuNum))    //�ַ����Ƚϲ���ֱ����==�ж�
		{
			return pTemp;
		}
		pTemp = pTemp->pnext;
	}
	printf("���޴˽�㣡\n");
	return NULL;
}

//ָ��λ�ò�����
void InsertNode(STUNODE *pTemp, char *arrStuNum, char arrStuName[10], int iStuScore)
{
	//�������
	STUNODE *pNew = (STUNODE*)malloc(sizeof(STUNODE));
	strcpy(pNew->arrStuNum, arrStuNum);
	strcpy(pNew->arrStuName, arrStuName);
	pNew->iStuScore = iStuScore;
	pNew->pnext = NULL;

	//������
	if (pTemp == g_pEnd)   //β���
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

//ɾ��ָ��ѧ��
void DeleteStuNode(STUNODE *pNode)
{
	//ֻ��һ�����
	if (g_pHead == g_pEnd)
	{
		free(g_pHead);
		g_pHead = NULL;
		g_pEnd = NULL;
	}
	//�������
	else if (g_pHead->pnext == g_pEnd)
	{
		if (g_pHead == pNode)     //ɾ����������еĵ�һ��
		{
			free(g_pHead);
			g_pHead == g_pEnd;
		}
		else                        //ɾ����������еĵڶ���
		{
			free(g_pEnd);
			g_pEnd = g_pHead;
			g_pHead->pnext = NULL;
		}
	}
	//����������
	else
	{
		STUNODE *pTemp = g_pHead;
		//�ж�Ҫɾ���Ľ����ͷ���
		if (g_pHead == pNode)
		{
			pTemp = g_pHead;
			g_pHead = g_pHead->pnext;
			free(pTemp);
			pTemp = NULL;
			return;
		}
		while (pTemp)    //Ҫɾ���Ĳ���ͷ���
		{
			if (pTemp->pnext == pNode)   //ֱ�Ӵӵڶ�����㿪ʼ�ж�
			{
				//���Ҫɾ���Ľ����β���
				if (pNode == g_pEnd)
				{
					free(g_pEnd);
					g_pEnd = pTemp;
					g_pEnd->pnext = NULL;
					return;
				}
				//����β���
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

//������Ϣ���ļ�
void SaveStuToFile()
{
	//�ж������Ƿ�Ϊ��
	if (NULL == g_pHead)
	{
		printf("û��ѧ��\n");
		return;
	}

	FILE *pFile = NULL;

	//���ļ�
	pFile = fopen("dat.dat", "wb+");
	if (NULL == pFile)
	{
		printf("�ļ���ʧ��\n");
		return;
	}

	//�����ļ�ָ��
	STUNODE *pTemp = g_pHead;
	char strBuf[30] = { 0 };
	char strScore[10] = { 0 };
	while (pTemp)
	{
		//ѧ�Ÿ�ֵ��BUF
		strcpy(strBuf, pTemp->arrStuNum);
		//����"."�ָ�
		strcat(strBuf, ".");
		//����׷�ӵ�BUF��
		strcat(strBuf, pTemp->arrStuName);
		strcat(strBuf, ".");
		//����ת��Ϊ�ַ���
		itoa(pTemp->iStuScore, strScore, 10);
		//ת����ķ���׷�ӵ�BUF
		strcat(strBuf, strScore);

		//��Ϣд���ļ�
		fwrite(strBuf, 1, strlen(strBuf), pFile);    //1 * strlen(strBuf)��ʾд����ֽ���
		//���뻻�з�
		fwrite("\r\n", 1, strlen("\r\n"), pFile);
		pTemp = pTemp->pnext;
	}

	//�ر��ļ�
	fclose(pFile);
}

//��ȡ�ļ���ѧ����Ϣ
void ReadStuFromFile()
{
	FILE *pFile = fopen("dat.dat", "rb+");
	if (NULL == pFile)
	{
		printf("�ļ���ʧ�ܣ�\n");
		return;
	}

	//����ָ�룬��ȡ�ļ�
	char strBuf[30] = { 0 };
	char strStuNum[10] = { 0 };
	char strStuName[10] = { 0 };
	char strStuScore[10] = { 0 };
	
	   
	while (NULL != fgets(strBuf, 30, pFile))   //����ȡ��30�����ܳ���strBuf�ĳ���      
	{
		int i = 0;
		int j = 0;
		int nCount = 0;   //��ס��ȡʱ.�Ĵ���
		//��ȡһ��ѧ����Ϣ
		for (i = 0; strBuf[i] != '\r'; i++)    //fgets��ȡһ�У������н�β"\r\n"
		{
			if (0 == nCount)    //û��'.'
			{
				strStuNum[i] = strBuf[i];
				if ('.' == strBuf[i])
				{
					strStuNum[i] = '\0';
					nCount++;
				}
			}
			else if (1 == nCount)   //��һ��'.'
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
			else              // �ڶ���'.'
			{
				strStuScore[j] = strBuf[i];
				j++;
			}
		}
		
		//���뵽����
		AddStuMsgToLinkHead(strStuNum, strStuName, atoi(strStuScore));
	}

	fclose(pFile);
}