//程序已基本完成，你们把它看懂，调试下，有错误跟我说下，你们自己改吧
//对子和分牌的功能还没写
//最好把它切成几部分，做成工程
//在7.7号把课程设计全部搞定，我接下来要玩arm了，没时间弄这个了

#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include"card.h"
#include"player.h"
#define N 5
#define ClearScreen()  system( "cls" )		//清屏操作

//int blackjack(int *p);



int main()
{

	player p[N];
	int people_num,poker_num,i,j;
	char pd,playgame,db,safejudge;
	while(1){
		help();
		printf("\n");
		printf("参与游戏人数(2-5):	");
		scanf("%d",&people_num);
		if(people_num >= 2 && people_num <= 5)
			break;
		else{
			printf("人数有误，请重新输入!\n");
			continue;
		}
	}
	getchar();
	p[0].poker=1;
	for(i=0;i<people_num;i++)
	{
		if(i == 0)
			p[i].poker=1;
		else
			p[i].poker=0;
		p[i].player_id=i;
		p[i].lost_num=p[i].win_num=0;
		p[i].money=10000;
	}
	poker_num=0;
	printf("*********************************************************\n");
	printf("*                     Y.开始游戏                        *\n");
	printf("*                     N.退出游戏                        *\n");
	printf("*********************************************************\n");
	printf("选	择:	");
	while(scanf("%c",&playgame))
	{	
		printf("---------------------------------------------------------\n");
		getchar();
		print_money(p,people_num,poker_num);
		if(playgame == 'Y' || playgame == 'y')
		{
			shuffle_player(p,people_num);
			shuffle_card();
			give_bet(p,people_num,poker_num);
			sent_card(p,poker_num);
			sent_card(p,poker_num);
			if(p[poker_num].card[6] == 10)
				printf("庄家 ID %d card is [*] %c%-3d\n",poker_num,p[poker_num].card[1],p[poker_num].card[6]);
			else
				printf("庄家 ID %d card is [*] %c%-3c\n",poker_num,p[poker_num].card[1],p[poker_num].card[6]);
			for(i=0;i<people_num;i++)
			{
			
				if(i == poker_num)
					continue;
				pd=0;
				if(p[poker_num].card[6] == 65)
				{
					printf("保险?(Y/N) \n");
					scanf("%c",&safejudge);
					getchar();
					if(safejudge == 'Y' || safejudge == 'y'){
						p[i].safe = 1;
					}
				}
	
				printf("玩家 %d 开始要牌\n",p[i].player_id);
				printf("起始手牌----->");
				for(j=0;j<2;j++)
					sent_card(p,i);
				printf("\n加倍?(y/n) -----> ");
				scanf("%c",&db);
				getchar();
				if((db == 'Y' || db == 'y') && blackjack(p[i].card))
					printf("Can't double!!!!!\n");
				else if((db == 'Y' || db == 'y') && !blackjack(p[i].card))
				{
					double_bet(p,i);
					sent_card(p,i);
					printf("\n");
					count_bumb(p,i);
					continue;
				}
				printf("\n要牌?(y/n)----->");
				while(scanf("%c",&pd))
				{
					getchar();
					if(p[i].card_num>=5)
					{
						printf("你的手牌超出5张了!\n");
						break;
					}
					if(count_bumb(p,i))
					{
						printf("\nbumb!!!!!!!!!\n");
						break;
					}
					if(pd == 'Y' || pd == 'y')
					{
						printf("抓牌----->");
						sent_card(p,i);
						printf("\n");
						printf("继续要牌?(y/n)----->");
					}
					else if(pd == 'N' || pd == 'n')
						break;
					else
					{
						printf("input error\n");		
						printf("\n要牌?(y/n)----->");
						continue;
					}

				}

				printf("\n");

			}
			
			sent_card_poker(p,poker_num);
			count_bumb(p,poker_num);
			print(p,people_num,poker_num);
			printf("\n\n\n");
			poker_num = compare(p,people_num,poker_num);
		}
		else if(playgame == 'N' || playgame == 'n')
			break;
		else if(playgame == 'C' || playgame == 'c')
			ClearScreen();
		else if(playgame == 'H' || playgame == 'h')
			help();
		else
			printf("操作不正确!\n");
		printf("************************************************\n");
		printf("*                Y.下一局                      *\n");
		printf("*                C.清屏                        *\n");
		printf("*                H.帮助                        *\n");
		printf("*                N.退出游戏                    *\n");
		printf("************************************************\n");

	}


	return 0;
}

