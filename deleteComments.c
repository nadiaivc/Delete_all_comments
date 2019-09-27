#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void deletee(FILE *f1, FILE *f2,  int len) // ������ //
{
	fseek(f1, len, SEEK_SET);
	char c;
	do {
		c = fgetc(f1);
		len++;
		fseek(f1, len, SEEK_SET);
	} while (c != '\n'&& c!=EOF);
	
	if (c == '\n') { //��������� �������
		if ((backslash(f1, len - 2) == 0 || backslash(f1, len - 2) == 1)) {//����������� ���
			len++;
			fseek(f1, len, SEEK_SET);
			c = fgetc(f1);
			if (c != '\n')
			deletee(f1, f2, len);	//���������� �������
			else
				func(f1, f2, len);
		}else
			func(f1, f2, len);
	}
	else
		func(f1, f2, len);
		
}


void stars(FILE *f1, FILE *f2, int len)
{
	char s1; char s2;
	do{
	
	fseek(f1, len, SEEK_SET);
	s1 = fgetc(f1);len++;
		if (s1 == '*')
		{
			
			fseek(f1, len, SEEK_SET);
			s2 = fgetc(f1);
			if (s2 == '/')
			{
				len++;
				func(f1, f2, len);
			}	
		}
	} while (s1 != EOF);
	func(f1, f2, len);
}

void quote2(FILE *f1, FILE *f2, int len)
{
	char c;
	fseek(f1, len, SEEK_SET); 
	c = fgetc(f1); 
	len++;
	while (c != '\n' && c != '\"'&& c!=EOF)
	{
		fputc(c, f2);
		fseek(f1, len, SEEK_SET);
		len++;
		c = fgetc(f1);
	}

	if (c == '\n') { //��������� �������
		if (backslash(f1, len - 2) == 0|| backslash(f1, len - 2) == 2){
			fputc(c, f2);
			len++;
			func(f1, f2, len);
		}
		else {
			fputc(c, f2); len++;
			quote2(f1, f2, len);
		}
	}
	if (c == EOF)
		func(f1, f2, len);
	else {
		if (backslash(f1, len - 2) == 0 || backslash(f1, len - 2) == 2) {//������ �����������
			fputc(c, f2);
			func(f1, f2, len);
		}
		else {
			fputc(c, f2);//����������� ������
			quote2(f1, f2, len);
		}
		
	}
}


void quote1(FILE *f1, FILE *f2, int len)
{
	char c;
	fseek(f1, len, SEEK_SET); 
	c = fgetc(f1); 
	len++;
	while (c != '\n' && c != (char)39 && c!=EOF)
	{
		fputc(c, f2);
		fseek(f1, len, SEEK_SET);
		len++;
		c = fgetc(f1);
	}
	if (c == (char)39)  //��������� �������
	 {
		if (backslash(f1, len - 2) == 0 || backslash(f1, len - 2) == 2) {
			fputc(c, f2);
			func(f1, f2, len);
		}
		else {
			fputc(c, f2);
			quote1(f1, f2, len);
		}

	}
	if (c == EOF)
		func(f1, f2, len);
	else
	func(f1, f2, len);
}

int backslash(FILE *f1, int len)
{
	char c; int k = 0;
	fseek(f1, len, SEEK_SET);
	c = fgetc(f1); 
	while (c == '\\') {
		k++; //������ ���-�� ���� - ������ �� �����������
		len--;
		fseek(f1, len, SEEK_SET);
		c = fgetc(f1);
	} if (k == 0)return(2);
	else if (k % 2 == 0 && k != 0)
		return(0);
	
		
	else return(1);
}





int func(FILE *f1, FILE *f2, int len)
{
	 char s1 = 0; char s2 = 0;
	fseek(f1, len, SEEK_SET);
	s1 = fgetc(f1);//���� ������
	if (s1 != EOF)
	{
		len++;
		fseek(f1, len, SEEK_SET);
		s2 = fgetc(f1);
		if ((s1 == '/') && (s2 == '/'))//1 ��������
		{
			deletee(f1, f2, len);
		}

		if ((s1 == '/') && (s2 == '*'))  //2 ��������
		{
			len++;
			 stars(f1, f2, len);
		}
		if (s1 == '\"') //3 ������
		{
			fputc(s1, f2);
			quote2(f1, f2, len);
		}
		if (s1 == (char)39)// 4 ������
		{
			fputc(s1, f2);
			quote1(f1, f2, len);
		}
		if (s1 == '\n'&&s2 == '\n') {//������� 2 \n
			len++;
			fputc(s1, f2);
			func(f1, f2, len);
		}
		else
		{
			fputc(s1, f2);
			func(f1, f2, len);
		}
	}
	fclose(f1);
	fclose(f2);
	return(0);
}
int main()
{
	FILE  *f1;
	FILE *f2;

	f1 = fopen("testr1.c", "r");
	char name[17] = "";// ����������� ��� ������ �����
	gets(name);
	strcat(name, ".c");
	f2 = fopen(name, "a");
	printf("%d",func(f1, f2, 0)); 
	system("pause");
}
