#include<stdio.h>
#include"card.h"



void double_bet(player *p,int id)
{
	p[id].bet*=2;
}


void print(player *p,int people_num,int poker_num)
{
	int i;
	printf("\nID %d ����----%d\n",p[poker_num].player_id,p[poker_num].card_sum);
	for(i=0;i<people_num;i++)
	{
		if(i == poker_num)
			continue;
		printf("ID %d ����----%d\n",p[i].player_id,p[i].card_sum);
	}
}



void print_money(player *p,int people_num,int poker_num)
{
	int i;
	printf("ׯ�� ID %d has money %d\n",p[poker_num].player_id,p[poker_num].money);
	for(i = 0;i<people_num;i++)
	{
		if(i == poker_num)
			continue;
		printf("�м� ID %d has money %d\n",p[i].player_id,p[i].money);
	}
	printf("\n");
}




void count(player *p,int p_n,int poker_n ) //error
{
	int i,j;
	int flag = 0;
	for(j=0;j<p[poker_n].card_num;j++)
	{
		if(p[poker_n].card[j+5] == 65)
		{
			p[poker_n].card_sum+=11;
			if(p[poker_n].card_sum>21)
				p[poker_n].card_sum-=10;
		}
		if(p[poker_n].card[j+5]>=74)
			p[poker_n].card_sum+=10;
		if(p[poker_n].card[j+5] == 10)
			p[poker_n].card_sum+=10;
		if(p[poker_n].card[j+5] >= 50 && p[poker_n].card[j+5]<=57)
			p[poker_n].card_sum=p[poker_n].card_sum+p[poker_n].card[j+5]-48;
	}
	printf("���� --- %d\n",p[poker_n].card_sum);
	for(i=0;i<p_n;i++)
	{
		flag = 0;
		if(i == poker_n)
			continue;
		for(j=0;j<p[i].card_num;j++)
		{
			if(p[i].card[j+5] == 65)
			{
				p[i].card_sum+=11;
				if(p[i].card_sum>21)
					p[i].card_sum-=10;
			}
			if(p[i].card[j+5]>=74)
				p[i].card_sum+=10;
			if(p[i].card[j+5] == 10)
				p[i].card_sum+=10;
			if(p[i].card[j+5] >= 50 && p[i].card[j+5]<=57)
				p[i].card_sum=p[i].card_sum+p[i].card[j+5]-48;
		}
		printf("���� ----%d\n",p[i].card_sum);
	}
}



void shuffle_player(player *p,int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		p[i].card_num = 0;
		p[i].card_sum =0;
		p[i].safe =0;
	}
}



void give_bet(player *p,int people_num,int poker_num)
{
	int i;
	int sum;
	for(i=0;i<people_num;i++)
	{
		if(i == poker_num)
			continue;
		printf("ID %d ����ע(%d-%d)  :",p[i].player_id, (p[poker_num].money/300), (p[poker_num].money/300*50));
		while(scanf("%d",&sum) !=EOF)
		{
			if((sum < p[poker_num].money / 300) || (sum > (p[poker_num].money / 300 * 50))){
				printf("���벻��Ҫ��Χ!!!\n");
				printf("ID %d ����ע(%d-%d)  :",p[i].player_id, (p[poker_num].money/300), (p[poker_num].money/300*50));
				continue;
			}
			else{
				p[i].bet = sum;
				break;
			}
		}
	}
	getchar();
	printf("\n\n");
}



int compare(player *p,int people_num,int poker_num)
{
	int i,next_poker=0;
	int blackjack_poker=0;
	int blackjack_player=0;
	p[poker_num].bet = 0;
	if(p[poker_num].card_num == 2 && blackjack(p[poker_num].card))
		blackjack_poker = 1;
	for(i=0;i<people_num;i++)
	{
		blackjack_player = 0;
		if(p[i].safe == 1)
		{
			if(blackjack_poker == 1)
			{
				p[i].money += p[i].bet/2;
				p[poker_num].money -= p[i].bet/2;
				p[poker_num].bet -= p[i].bet/2;
//				continue;
			}
			else
			{
				p[i].money -= p[i].bet/2;
				p[poker_num].money += p[i].bet/2;
				p[poker_num].bet -= p[i].bet/2;
			}
		}
		if(i == poker_num)
			continue;
		if(p[i].card_sum>21)
		{
			p[i].money-=p[i].bet;
			p[poker_num].money+=p[i].bet;
			p[poker_num].bet+=p[i].bet;
			printf("winner is ׯ��!!\n");
			continue;
		}
		else if(p[i].card_sum <= 21 && p[poker_num].card_sum >21)
		{
			p[i].money+=p[i].bet;
			p[poker_num].money-=p[i].bet;
			p[poker_num].bet-=p[i].bet;
			printf("winner is ���%d!!\n", p[i].player_id);
		}
		else if(p[i].card_sum > p[poker_num].card_sum)
		{
			printf("winner is ���%d\n",p[i].player_id);
			p[i].money+=p[i].bet;
			p[poker_num].money-=p[i].bet;
			p[poker_num].bet-=p[i].bet;
//			next_poker = 1;
		}
		else if(p[i].card_sum == p[poker_num].card_sum)
		{
			if(p[i].card_num == 2 && blackjack(p[i].card))
				blackjack_player = 1;
			if(blackjack_poker && blackjack_player)
				printf("ping!!!!\n");
			else if(blackjack_poker && !blackjack_player)
			{
				p[i].money-=p[i].bet;
				p[poker_num].money+=p[i].bet;
				p[poker_num].bet+=p[i].bet;
				printf("winner is ׯ��!!\n");
			}
			else if(!blackjack_poker && blackjack_player)
			{
				printf("winner is ���%d\n",p[i].player_id);
				p[i].money=p[i].money+p[i].bet/2*3;
				p[poker_num].money=p[poker_num].money-p[i].bet/2*3;
				p[poker_num].bet=p[poker_num].bet-p[i].bet/2*3;
//				next_poker = 1;
			}
			printf("ping!!!!\n");
		}
		else if(p[i].card_sum < p[poker_num].card_sum && p[i].card_sum <22)
		{
			p[i].money-=p[i].bet;
			p[poker_num].money+=p[i].bet;
			p[poker_num].bet+=p[i].bet;
			printf("winner is ׯ��!!\n");
		}

	}
	if(p[poker_num].bet < 0)
	{
		p[poker_num].poker=0;
		poker_num = (poker_num + 1) % people_num;
		p[poker_num].poker = 1;
		return(poker_num);
	}
	else
		return(poker_num);
}


void help()
{
	printf("��������������   ��ӭ����21����Ϸ����!   ��������������\n");
	printf("���    ��Ϸ����                                                         ���\n");
	printf("���    1.���������Ҫ������!                                            ���\n");
	printf("���    2.�����Ѿ���ȡ�����Ų��� �ڽܿ� ����ǰ���£������Ϊ�������ƿ���   ���\n");
	printf("���      ����Ӯ��ׯ�ҵ����ƣ�������Ҫ��˫��Ѻע��                         ���\n");
	printf("���    3.���գ������ƺ����ׯ�������õ�����A����Ҿ��л������գ����ս�  ���\n");
	printf("���      ����ҵ�����ע��һ�롣���Ѻ�����պ�ׯ���Ǻڽܿ� ��ׯ�ҵ���һ  ���\n");
	printf("���      ����Ϊ10��J��Q��K����ô��Ҫ������2���ı��ս�                 ���\n");
	printf("���    4.ׯ����Ǯ����ׯ���������ʱ��������ׯ��                           ���\n");
	printf("���    5.ׯ���ڴ���16��ʱ������Ҫ��                                       ���\n");
	printf("���    6.���ׯ�Һ��м�ͬʱ���ƣ������м���                               ���\n");
	printf("���������������     GOOD LUCK !!!   ����������������\n");

}