//�����ѻ�����ɣ����ǰ��������������£��д������˵�£������Լ��İ�
//���Ӻͷ��ƵĹ��ܻ�ûд
//��ð����гɼ����֣����ɹ���
//��7.7�Űѿγ����ȫ���㶨���ҽ�����Ҫ��arm�ˣ�ûʱ��Ū�����

#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include"card.h"
#include"player.h"
#define N 5
#define ClearScreen()  system( "cls" )		//��������

//int blackjack(int *p);



int main()
{

	player p[N];
	int people_num,poker_num,i,j;
	char pd,playgame,db,safejudge;
	while(1){
		help();
		printf("\n");
		printf("������Ϸ����(2-5):	");
		scanf("%d",&people_num);
		if(people_num >= 2 && people_num <= 5)
			break;
		else{
			printf("������������������!\n");
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
	printf("*                     Y.��ʼ��Ϸ                        *\n");
	printf("*                     N.�˳���Ϸ                        *\n");
	printf("*********************************************************\n");
	printf("ѡ	��:	");
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
				printf("ׯ�� ID %d card is [*] %c%-3d\n",poker_num,p[poker_num].card[1],p[poker_num].card[6]);
			else
				printf("ׯ�� ID %d card is [*] %c%-3c\n",poker_num,p[poker_num].card[1],p[poker_num].card[6]);
			for(i=0;i<people_num;i++)
			{
			
				if(i == poker_num)
					continue;
				pd=0;
				if(p[poker_num].card[6] == 65)
				{
					printf("����?(Y/N) \n");
					scanf("%c",&safejudge);
					getchar();
					if(safejudge == 'Y' || safejudge == 'y'){
						p[i].safe = 1;
					}
				}
	
				printf("��� %d ��ʼҪ��\n",p[i].player_id);
				printf("��ʼ����----->");
				for(j=0;j<2;j++)
					sent_card(p,i);
				printf("\n�ӱ�?(y/n) -----> ");
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
				printf("\nҪ��?(y/n)----->");
				while(scanf("%c",&pd))
				{
					getchar();
					if(p[i].card_num>=5)
					{
						printf("������Ƴ���5����!\n");
						break;
					}
					if(count_bumb(p,i))
					{
						printf("\nbumb!!!!!!!!!\n");
						break;
					}
					if(pd == 'Y' || pd == 'y')
					{
						printf("ץ��----->");
						sent_card(p,i);
						printf("\n");
						printf("����Ҫ��?(y/n)----->");
					}
					else if(pd == 'N' || pd == 'n')
						break;
					else
					{
						printf("input error\n");		
						printf("\nҪ��?(y/n)----->");
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
			printf("��������ȷ!\n");
		printf("************************************************\n");
		printf("*                Y.��һ��                      *\n");
		printf("*                C.����                        *\n");
		printf("*                H.����                        *\n");
		printf("*                N.�˳���Ϸ                    *\n");
		printf("************************************************\n");

	}


	return 0;
}

