 /* 
 *Copyright(c) 李文龙
 *All rights reserved.
 *
 * 文件名称：guess.c
 * 文件标识：
 * 摘    要：100以内猜数字游戏
 * 
 * 当前版本：1.0
 * 作    者：李文龙
 * 完成日期：2024年2月6日
 * 
 * 取代版本：
 * 原作者  ：
 * 完成日期： 
 */
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main()
{
	//1.set the limit 1-100, and the number of tries to be 7
	int limit = 100;
	int number_of_tries = 7;
	int is_win = 0;
	printf("Please input number 0-100\n");

	//2.set a reward number
	srand(time(NULL));//user current time as seed for random genertaor
	int reward = rand() % 100 + 1;//%100取余（0-99 +1=1-100）
	//5.repeat 3 and 4 until??

	while (number_of_tries > 0 & is_win == 0)
	{
		//3.take an input from the kyboard
		int guess;
		printf("[%d] Please enter your guess:", number_of_tries);
		scanf("%d", &guess);//取地址
		printf("Your guess:%d.\n", guess);
		//4.compare
		if (guess == reward)
		{
			printf("Guess == reward! You win!\n");//beark
			printf("reward:%d\n", reward);
			is_win = 1;
		}
		else if (guess > reward)
		{
			printf("Guess>reward!\n");

		}
		else if (guess < reward)
		{
			printf("Guess<reward!\n");
		}
		number_of_tries--;

	}
	if (is_win != 1)
		printf("You Lose!!!\n");

	printf("reward:%d\n", reward);
	return 0;
}