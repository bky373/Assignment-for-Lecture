#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
int selectWord(char *string);
int includeMinus(char *str);
int checkCorrect(char *myword, char ch);
int checkAlreadyGuessed(char *alreadyGuessed, char ch);
int enteredCorrect(char *myword, char *currentCorrect, char ch);
int includeCapital(char *ch)
{
	if (*ch >= 'A' && *ch <= 'Z')
	{
		printf("Please enter a lower case\n"); return 1;
	} return 0;
}
int strlen(char *str)
{
	int leng = 0;
	if (str == 0) return 0;
	for (leng = 0; str[leng]; leng++);
	return leng;
}
void strcpy(char *to, char *from)
{
	if (!to || !from)
		fprintf(stderr, "strcpy:input error\n");
	for (; *from; to++, from++) *to = *from;
	*(to) = 0;
}
int main(void)
{
	char myword[200], ch, in[10], alreadyGuessed[20] = { 0 };
	char currentCorrect[100] =
		"*******************************************************************************";
	int chance = 6, fin = 0;
	selectWord(myword);// 단어 고르기 작업

	//printf("selected & retuned words >%s<\n", myword);
	currentCorrect[strlen(myword)] = 0;
	printf("selected word : %s\n", myword);
	printf("You have only %d chances left\nguess a character\n", chance);
	
	while (chance > 0 && fin == 0)
	{
		scanf("%c", &ch);
		if (ch == '\n' || includeCapital(&ch))
			continue;
		else
			printf("you have entered %c\n", ch);

		if (1 != checkAlreadyGuessed(alreadyGuessed, ch))
		{
			if (1 != checkCorrect(myword, ch))
			{
				chance--;
			}
			if (enteredCorrect(myword, currentCorrect, ch))
				fin = 1; // or break; // 정답이므로 루프 종료
		}
		else printf("---------------------- You have already entered %c\n", ch); // 중복입력 알림

		printf("You have only %d chances left\n", chance);
		printf("Current guessed string is %s\nguess a character\n", currentCorrect);
		fflush(stdout);
		
	}
	if (chance > 0)
		printf("!!Great\n");
	else
	{
		printf("TT Sorry, try more words\n");
		printf(">>> correct word was %s\n", myword);
	}
	getchar();
	return 0;
}

int checkCorrect(char *myword, char ch)
{
	for (; *myword; ++myword)
		if (*myword == ch) return 1;
	return 0;
}
int checkAlreadyGuessed(char *alreadyGuessed, char ch)
{	for (; *alreadyGuessed; ++alreadyGuessed)
		if (*alreadyGuessed == ch) 
			return 1;
		*alreadyGuessed = ch; 
		return 0;
}
int enteredCorrect(char *myword, char *currentCorrect, char ch)
{
	int cntAster = strlen(myword); // 처음 '*' 개수 = 단어 글자 개수만큼
	for (; *myword; ++myword, ++currentCorrect)
	{
		if (*myword == ch) 
			*currentCorrect = ch;
		if ('*' != *currentCorrect) cntAster--; // *가 줄어들수록 cnt-1
	}
	if (cntAster == 0) return 1; // *가 하나도 없으면 1로 리턴
	return 0;
}

int includeMinus(char *str)
{
	int cnt = 0; // 마이너스 확인
	char *temp = malloc(strlen(str));
	for (; *str; ++str) // '-' 제거하기
	{
		if ('-' != *str)
		{
			*temp = *str;
			++temp;
		}
		else ++cnt;
	}
	for (; *temp; ++temp) // '-' 제거한 단어로 교체
	{
		*str = *temp;
	} *str = 0;
	if (cnt) return 1; // '-' 포함
	return 0; // 포함 X
}
int AllLower(char *str)
{
	for (; *str; str++)
		if (!islower(str)) return 0;
	return 1;
}
int islower(char *str)
{
	for (; *str; str++)
	{
		if (*str >= 'a' && *str <= 'z') return 1;
		return 0;
	}
}
int selectWord(char *string)
{
	FILE *fp;
	char str[100];
	int i, fi, nthWord;
	fp = fopen("c:\\users\\yonghwan\\desktop\\hangman_words.txt", "r");
	if (fp == 0) {
		fprintf(stderr, "words.txt 없음.\n");
		strcpy(string, "");
		return 0;
	}
	srand(time(NULL)); // 시드값 조절
	printf("%d %d\n", RAND_MAX, rand()); // RAND_MAX, rand() 출력

#define LASTWORD 479623
#define MIN_LENGTH 6

	nthWord = (int)((float)rand() / (float)RAND_MAX * ((float)LASTWORD) + 0.5);
	if (nthWord + 100 > 479623)
		nthWord = nthWord - 100;
	printf("nth word == %d\n", nthWord);
	for (i = 1; i < nthWord; i++)
	{
		fi = fscanf(fp, "%s", str);
		if (fi == EOF)
			break;
	}
	// 조건 : 6자 이상, 소문자로 된 단어
	for (;;)
	{
		if (strlen(str) >= MIN_LENGTH && AllLower(str))
		{
			if((includeMinus(str))) printf("Success for deleting '-'\n"); // 단어 속 '-' 삭제
			printf("My word : %s\n", str);
			strcpy(string, str);
			break;
		}
		fi = fscanf(fp, "%s", str);
		if (fi == EOF)
			break;
	}

	fclose(fp);
	return 0;
}