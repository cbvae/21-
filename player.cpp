#include<stdio.h>
#include"card.h"



void double_bet(player *p,int id)
{
	p[id].bet*=2;
}


void print(player *p,int people_num,int poker_num)
{
	int i;
	printf("\nID %d 点数----%d\n",p[poker_num].player_id,p[poker_num].card_sum);
	for(i=0;i<people_num;i++)
	{
		if(i == poker_num)
			continue;
		printf("ID %d 点数----%d\n",p[i].player_id,p[i].card_sum);
	}
}



void print_money(player *p,int people_num,int poker_num)
{
	int i;
	printf("庄家 ID %d has money %d\n",p[poker_num].player_id,p[poker_num].money);
	for(i = 0;i<people_num;i++)
	{
		if(i == poker_num)
			continue;
		printf("闲家 ID %d has money %d\n",p[i].player_id,p[i].money);
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
	printf("点数 --- %d\n",p[poker_n].card_sum);
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
		printf("点数 ----%d\n",p[i].card_sum);
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
		printf("ID %d 请下注(%d-%d)  :",p[i].player_id, (p[poker_num].money/300), (p[poker_num].money/300*50));
		while(scanf("%d",&sum) !=EOF)
		{
			if((sum < p[poker_num].money / 300) || (sum > (p[poker_num].money / 300 * 50))){
				printf("筹码不在要求范围!!!\n");
				printf("ID %d 请下注(%d-%d)  :",p[i].player_id, (p[poker_num].money/300), (p[poker_num].money/300*50));
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
			printf("winner is 庄家!!\n");
			continue;
		}
		else if(p[i].card_sum <= 21 && p[poker_num].card_sum >21)
		{
			p[i].money+=p[i].bet;
			p[poker_num].money-=p[i].bet;
			p[poker_num].bet-=p[i].bet;
			printf("winner is 玩家%d!!\n", p[i].player_id);
		}
		else if(p[i].card_sum > p[poker_num].card_sum)
		{
			printf("winner is 玩家%d\n",p[i].player_id);
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
				printf("winner is 庄家!!\n");
			}
			else if(!blackjack_poker && blackjack_player)
			{
				printf("winner is 玩家%d\n",p[i].player_id);
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
			printf("winner is 庄家!!\n");
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
	printf("☆☆☆☆☆☆☆☆☆☆☆☆☆   欢迎来到21点游戏世界!   ☆☆☆☆☆☆☆☆☆☆☆☆☆\n");
	printf("☆☆    游戏规则：                                                         ☆☆\n");
	printf("☆☆    1.玩家最多可以要五张牌!                                            ☆☆\n");
	printf("☆☆    2.在您已经抽取了两张不是 黑杰克 的牌前提下，如果认为第三张牌可以   ☆☆\n");
	printf("☆☆      让您赢过庄家的手牌，您可以要求双倍押注。                         ☆☆\n");
	printf("☆☆    3.保险：发过牌后如果庄家手中拿到明牌A，玩家就有机会买保险，保险金  ☆☆\n");
	printf("☆☆      是玩家当初下注的一半。如果押过保险后，庄家是黑杰克 即庄家的另一  ☆☆\n");
	printf("☆☆      张牌为10、J、Q、K，那么需要陪给玩家2倍的保险金。                 ☆☆\n");
	printf("☆☆    4.庄家输钱后下庄，各玩家逆时针轮流做庄。                           ☆☆\n");
	printf("☆☆    5.庄家在大于16点时不能再要牌                                       ☆☆\n");
	printf("☆☆    6.如果庄家和闲家同时爆牌，则判闲家输                               ☆☆\n");
	printf("☆☆☆☆☆☆☆☆☆☆☆☆☆☆     GOOD LUCK !!!   ☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n");

}