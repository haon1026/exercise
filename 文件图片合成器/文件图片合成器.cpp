# include <stdio.h>
# include <stdlib.h>

int main(void)
{
	FILE * fp_file, * fp_pic, * fp_finish;
	char ch;
	char file_name[20], pic_name[20], finish_name[20];

	printf("请输入文件名，照片名，合成名\n");
	printf("文件名:");
	scanf("%s", file_name);
	printf("照片名:");
	scanf("%s", pic_name);
	printf("合成名:");
	scanf("%s", finish_name);

	if( !(fp_file = fopen(file_name, "rb")) )
	{
		printf("文件%s打开失败",file_name);
		exit(0);
	}
	if( !(fp_pic = fopen(pic_name, "rb")) )
	{
		printf("照片%s打开失败",pic_name);
		exit(0);
	}
	if( !(fp_finish = fopen(finish_name, "wb")) )
	{
		printf("文件%s打开失败",finish_name);
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