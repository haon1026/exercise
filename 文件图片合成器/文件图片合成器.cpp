# include <stdio.h>
# include <stdlib.h>

int main(void)
{
	FILE * fp_file, * fp_pic, * fp_finish;
	char ch;
	char file_name[20], pic_name[20], finish_name[20];

	printf("�������ļ�������Ƭ�����ϳ���\n");
	printf("�ļ���:");
	scanf("%s", file_name);
	printf("��Ƭ��:");
	scanf("%s", pic_name);
	printf("�ϳ���:");
	scanf("%s", finish_name);

	if( !(fp_file = fopen(file_name, "rb")) )
	{
		printf("�ļ�%s��ʧ��",file_name);
		exit(0);
	}
	if( !(fp_pic = fopen(pic_name, "rb")) )
	{
		printf("��Ƭ%s��ʧ��",pic_name);
		exit(0);
	}
	if( !(fp_finish = fopen(finish_name, "wb")) )
	{
		printf("�ļ�%s��ʧ��",finish_name);
		exit(0);
	}

	while( !feof(fp_file) )
	{
		ch = fgetc(fp_file);
        fputc(ch, fp_finish);
	}

	while( !feof(fp_pic) )
	{
		ch = fgetc(fp_pic);
        fputc(ch, fp_finish);
	}

	fclose(fp_file);
	fclose(fp_pic);
	fclose(fp_finish);

	return 0;
}