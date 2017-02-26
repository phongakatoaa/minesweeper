#include <iostream> 
#include <stdlib.h>
#include <time.h>
using namespace std;

char mines_board[10][10]; //board de xem min
char play_board[10][10]; //board de choi cmm di
int m, n; //coordinate
int mines_number; 

int generate_mines_number(int mines_number) {
	mines_number=rand()%20+10;
	return mines_number;	
} 

void generate_random_mines(int mines_number) {
	int m,n; //coordinate for generating mines
	int temp=0; 
	do {
		m=rand()%10; n=rand()%10;
		mines_board[m][n]=42;
		temp++;
	} while (temp<mines_number);
}
void generate_play_board() {
	for (int i=0; i<10; i++) {
		for (int j=0; j<10; j++) {
			play_board[i][j]='-';
		}
	}
}

void display_play_board() {
	int i=0;
	while (i<10) {
		for (int j=	0; j<10; j++) {
			cout << play_board[i][j] << " ";
		}	
		cout << endl;
		i++;
	}
}


int surround_mines(int m, int n) {
	int surround_mines_count=0;
	if (mines_board[m+1][n]=='*'&&mines_board[m+1][n]!=' ') surround_mines_count++;
	if (mines_board[m+1][n+1]=='*'&&mines_board[m+1][n+1]!=' ') surround_mines_count++;
	if (mines_board[m+1][n-1]=='*'&&mines_board[m+1][n-1]!=' ') surround_mines_count++;
	if (mines_board[m][n+1]=='*'&&mines_board[m][n+1]!=' ') surround_mines_count++;
	if (mines_board[m][n-1]=='*'&&mines_board[m][n-1]!=' ') surround_mines_count++;
	if (mines_board[m-1][n]=='*'&&mines_board[m-1][n]!=' ') surround_mines_count++;
	if (mines_board[m-1][n+1]=='*'&&mines_board[m-1][n+1]!=' ') surround_mines_count++;
	if (mines_board[m-1][n-1]=='*'&&mines_board[m-1][n-1]!=' ') surround_mines_count++;
	return surround_mines_count;
}

int mines_check(int m, int n) {
	if (mines_board[m][n]==42) return 1;
	else return 0; 
}

void player_dont_hit_mines(int m, int n) {
	int a=surround_mines(m, n);
	play_board[m][n]=a+48;
}

void mines_position_check() { // for debugging only
	int count=0;
	for (int i=0; i<10; i++) {
		for (int j=0; j<10; j++) {
			if (mines_board[i][j]=='*') {cout << "mine[" << count << "]: (" << i << ";" << j << ")" << endl;
			count++;}
		}
	}
}
int main() {
	srand(time(0));
	generate_play_board();
	int a=generate_mines_number(mines_number);
	generate_random_mines(a);
	display_play_board();	
	//mines_position_check();
	for (;;) {
		cout<< "Nhap toa do: " << endl;
		cin >> m >> n;
		if (mines_check(m,n)==1) {
			cout << "Game Over!!!" << endl;
			return 0;
		}
		else {
			player_dont_hit_mines(m,n);
			display_play_board();
		}
	} 
	return  0;
}
