#ifndef _CARD_H
#define _CARD_H


struct player
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

//void shuffle_player(player *p,int);
void shuffle_card(); 
 
void sent_card(player *p,int id);

void sent_card_poker(player *p,int poker_num);

int count_bumb(player *p,int id);

int count_bumb(player *p,int id);

int blackjack(int *card);

#endif