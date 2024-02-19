#include <stdio.h>
#include<stdlib.h>
#include<time.h>

void menu()
{
    printf("*********************************\n");
    printf("*********   1.play   ************\n");
    printf("*********   0.exit   ************\n");
    printf("*********************************\n");
}

void game()
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

}
int main()
{
    int input = 0;
    do
    {
        menu();
        printf("请输入你的选择：");
        scanf("%d", &input);

        switch (input)
        {
        case 1:
            game();
            break;
        case 0:
            printf("退出游戏\n");
            break;
        
        default:
            printf("选择错误，重新选择：");
            break;
        }
    } while (input);
    
    return 0;
}
