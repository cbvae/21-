#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include"card.h"
#define N 5

//��
int cards[4][14]={0};
//����Ŀ������,��ʼ���ƵĴ�С
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
	//��ʼ����AȡֵΪ11��ʱ�� 
	flagA0=0;
	flagA1=0;
	//��ʼ����
	for(i=0;i<4;i++)
	{
		cards[i][0]=i+3;//��ֵ��ʽ
		cards[i][1]=65;//��ֵA
		cards[i][10]=10;//��ֵ10,��ʮ�������
		cards[i][11]=74;//��ֵJ
		cards[i][12]=81;//��ֵQ
		cards[i][13]=75;//��ֵK
	}
	for(i=0;i<4;i++)
		for(j=2;j<=9;j++)
			cards[i][j]=j+48;//��ֵ2-9

	//��ʼ������
	for(i=1;i<=9;i++)
	   card_num[i][1]=4;//1-9�Ƶ���Ŀ(����AΪ1)
	card_num[10][1]=4*4;//10.J.Q.K����Ŀ
	card_num[11][1]=4;//AΪ11ʱ�Ƶ���Ŀ
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
		//�ų������ϵ���
		if(cards[row][line]==0)
		{
			continue;
		}
		//����ַ���ʽ
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
		printf("ׯ�� ID %d card is %c%-3d  ",poker_num,p[poker_num].card[0],p[poker_num].card[5]);
	else
		printf("ׯ�� ID %d card is %c%-3c  ",poker_num,p[poker_num].card[0],p[poker_num].card[5]);
	if(p[poker_num].card[6] == 10)
		printf("%c%-3d\n",p[poker_num].card[1],p[poker_num].card[6]);
	else
		printf("%c%-3c\n",p[poker_num].card[1],p[poker_num].card[6]);
		
	printf("ׯ�� ,Ҫ�� ?(Y/N) \n");
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
			printf("����Ҫ��!\n");
			return;
		}
		if(p[poker_num].card_num>=5)
		{
			printf("������Ƴ���5��?\n");
			return;
		}

		if(c == 'Y' || c == 'y')
		{
			do
			{ 
				row=rand()%4;
				line=rand()%13+1;
				//�ų������ϵ���
				if(cards[row][line]==0)
				{
					continue;
				}
				//����ַ���ʽ
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
		printf("ׯ��,����Ҫ��?(Y/N) :\n");

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