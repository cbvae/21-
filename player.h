#ifndef _PLAYER_H
#define _PLAYER_H

void double_bet(player *p,int id);

void print(player *p,int people_num,int poker_num);

void help();

void print_money(player *p,int people_num,int poker_num);

void count(player *p,int p_n,int poker_n );

void shuffle_player(player *p,int n);

void give_bet(player *p,int people_num,int poker_num);

int compare(player *p,int people_num,int poker_num);
#endif
