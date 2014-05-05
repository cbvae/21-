#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include"card.h"
#define N 5

//牌
int cards[4][14]={0};
//牌数目的数组,初始化牌的大小
int card_num[12][2]={{0,0},{1},{2},{3},{4},{5},{6},{7},{8},{9},{10},{11}};

int flag_choice,flagA0,flagA1;

/*struct player
{
	int player_id;
	int card[10];
	int card_num;
	int card_sum;
	int bet;
	int money;
	int win_num;
	int lost_num;
	bool safe;
	bool poker;
};
*/
void shuffle_card()
{
	int i,j;
	//初始化牌A取值为11的时候 
	flagA0=0;
	flagA1=0;
	//初始化牌
	for(i=0;i<4;i++)
	{
		cards[i][0]=i+3;//赋值样式
		cards[i][1]=65;//赋值A
		cards[i][10]=10;//赋值10,以十进制输出
		cards[i][11]=74;//赋值J
		cards[i][12]=81;//赋值Q
		cards[i][13]=75;//赋值K
	}
	for(i=0;i<4;i++)
		for(j=2;j<=9;j++)
			cards[i][j]=j+48;//赋值2-9

	//初始化牌数
	for(i=1;i<=9;i++)
	   card_num[i][1]=4;//1-9牌的数目(包括A为1)
	card_num[10][1]=4*4;//10.J.Q.K的数目
	card_num[11][1]=4;//A为11时牌的数目
}


void sent_card(player *p,int id)
{
	int row,line;
	int card_n=p[id].card_num;
	srand(time(NULL));
	do
	{ 
		row=rand()%4;
		line=rand()%13+1;
		//排除桌面上的牌
		if(cards[row][line]==0)
		{
			continue;
		}
		//输出字符形式
		if(line==10)
		{
			if(!p[id].poker)
			{
				printf("%c",cards[row][0]);
				printf("%-3d",cards[row][line]);
			}
		}
		else
		{
			if(!p[id].poker)
			{
				printf("%c",cards[row][0]);
				printf("%-3c",cards[row][line]);
			}
		}

	}while(cards[row][line]==0);
	p[id].card[card_n]=cards[row][0];
	p[id].card[card_n+5]=cards[row][line];
	cards[row][line]=0;
	p[id].card_num++;
}



void sent_card_poker(player *p,int poker_num)
{
	int row,line;
	int sum1=0,sum2=0,i;
	char c;
	int card_n=p[poker_num].card_num;
	srand(time(NULL));
	if(p[poker_num].card[5] == 10)
		printf("庄家 ID %d card is %c%-3d  ",poker_num,p[poker_num].card[0],p[poker_num].card[5]);
	else
		printf("庄家 ID %d card is %c%-3c  ",poker_num,p[poker_num].card[0],p[poker_num].card[5]);
	if(p[poker_num].card[6] == 10)
		printf("%c%-3d\n",p[poker_num].card[1],p[poker_num].card[6]);
	else
		printf("%c%-3c\n",p[poker_num].card[1],p[poker_num].card[6]);
		
	printf("庄家 ,要牌 ?(Y/N) \n");
	while(scanf("%c",&c))
	{
		getchar();
		sum1=sum2=0;
		if(c == 'n' || c == 'N')
			return;
		for(i=0;i<p[poker_num].card_num;i++)
		{
			if(p[poker_num].card[i+5] == 65)
			{
				sum1+=11;
				sum2+=1;
			}
			if(p[poker_num].card[i+5]>=74)
			{
				sum1+=10;
				sum2+=10;
			}
			if(p[poker_num].card[i+5] == 10)
			{
				sum1+=10;
				sum2+=10;
			}
			if(p[poker_num].card[i+5] >= 50 && p[poker_num].card[i+5]<=57)
			{
				sum1=sum1+p[poker_num].card[i+5]-48;
				sum2=sum2+p[poker_num].card[i+5]-48;
			}
			if(sum2>21)
			{
				printf("bumb!!!\n");
				return;
			}
		}

		if(sum2>16)
		{
			printf("不能要牌!\n");
			return;
		}
		if(p[poker_num].card_num>=5)
		{
			printf("你的手牌超出5张?\n");
			return;
		}

		if(c == 'Y' || c == 'y')
		{
			do
			{ 
				row=rand()%4;
				line=rand()%13+1;
				//排除桌面上的牌
				if(cards[row][line]==0)
				{
					continue;
				}
				//输出字符形式
				if(line==10)
				{
						printf("%c",cards[row][0]);
						printf("%-3d\n",cards[row][line]);
				}
				else
				{
						printf("%c",cards[row][0]);
						printf("%-3c\n",cards[row][line]);
				}

			}while(cards[row][line]==0);
			p[poker_num].card[card_n]=cards[row][0];
			p[poker_num].card[card_n+5]=cards[row][line];
			cards[row][line]=0;
			p[poker_num].card_num++;
		}
		else if(c == 'N' || c == 'n')
			return;
		printf("庄家,继续要牌?(Y/N) :\n");

	}
}



int count_bumb(player *p,int id)
{
	int sum=0,i;
	int flag =0;
	for(i=0;i<p[id].card_num;i++)
	{
		if(p[id].card[i+5] == 65)
		{
			sum+=11;
			flag = 1;
		}

		if(p[id].card[i+5]>=74)
			sum+=10;
		if(p[id].card[i+5] == 10)
			sum+=10;
		if(p[id].card[i+5] >= 50 && p[id].card[i+5]<=57)
			sum=sum+p[id].card[i+5]-48;
		if(flag && sum>21)
			sum-=10;
		if(sum>21)
		{
			p[id].card_sum = 10000;
			return 1;
		}
	}
	p[id].card_sum = sum;
	return 0;
	
}




int blackjack(int *card)
{
	if((card[5] == 65 && card[6] == 10) || (card[5] == 10 && card[6] == 65))
		return 1;
	return 0;
}