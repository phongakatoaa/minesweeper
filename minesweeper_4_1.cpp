#include <iostream> 
#include <stdlib.h>
#include <time.h>
#include <string.h>
using namespace std;

char mines_board[10][10]; //board de xem min
char play_board[10][10]; //board de choi cmm di
int expand_board[10][10]; //board de expand ok ? logic nhu lozz
int m, n; //coordinate
int mines_number;
char flag; //place flag keyword
char unflag;//remove flag keyword
int block_count = 0; // bo dem o trong da dc mo
int mines_count = 0; //bo dem so min da dc cam co
char status[10]; //kiem tra neu nguoi choi muon choi lai hoac ket thuc
int temp = 0;//kiem tra so lan ham expand chay
//==========================================================================================================================
//Muon cua thay Long
void clearScreen()
{
#ifdef __WIN32__
	system("cls");
#else
	for (int i = 0; i < 30; i++) cout << endl;
#endif
}
//==========================================================================================================================
//Ham kiem tra vuot bien
int in_range(int a, int b){
    if (a >= 0 && a <= 9 && b >= 0 && b<= 9) return 1;
    else return 0;
}
//==========================================================================================================================
//Ham tao so luong min ngau nhien, vi tri min ngau nhien, bang min, bang choi
int mines_check(int m, int n);
//==========================================================================================================================
int generate_mines_number(int mines_number) {
	mines_number=rand()%20+10;
	return mines_number;	
} 

void generate_random_mines(int mines_number) {
	int m,n; //coordinate for generating mines
	int temp=0; 
	do {
		m=rand()%10; n=rand()%10;
		if (mines_check(m, n) == 0)
		{
			mines_board[m][n] = 42;
			temp++;
		}
	} while (temp<mines_number);
}
void generate_play_board() {
	for (int i=0; i<10; i++) {
		for (int j=0; j<10; j++) {
			play_board[i][j]='-';
		}
	}
}
void generate_mines_board() {
	for (int i=0; i<10; i++) {
		for (int j=0; j<10; j++) {
			mines_board[i][j]='-';
		}
	}
}
//==========================================================================================================================
//Ham kiem soat ham expand
void generate_expand_board() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			expand_board[m][n] = 0;
		}
	}
}
void display_play_board() {
	int i=0;
	cout << "  ";
	while (i < 10) {
		cout << " " << i ;
		i++;
	}
	cout << endl << endl;
	i = 0;
	while (i<10) {
		cout << i << "  ";
		for (int j=	0; j<10; j++) {
			cout << play_board[i][j] << " ";
		}	
		cout << endl;
		i++;
	}
}
//==========================================================================================================================
//Cheat ok?
void display_mines_board() {
	int i = 0;
	cout << "  ";
	while (i < 10) {
		cout << " " << i;
		i++;
	}
	cout << endl << endl;
	i = 0;
	while (i<10) {
		cout << i << "  ";
		for (int j = 0; j<10; j++) {
			cout << mines_board[i][j] << " ";
		}
		cout << endl;
		i++;
	}
}
//==========================================================================================================================
//Ham kiem tra so luong min xung quanh 1 o vuong
int surround_mines(int m, int n) {
	int surround_mines_count=0;
	if (mines_board[m+1][n]=='*'&&in_range(m+1,n)) surround_mines_count++;
	if (mines_board[m+1][n+1]=='*'&&in_range(m+1,n+1)) surround_mines_count++;
	if (mines_board[m+1][n-1]=='*'&&in_range(m+1,n-1)) surround_mines_count++;
	if (mines_board[m][n+1]=='*'&&in_range(m,n+1)) surround_mines_count++;
	if (mines_board[m][n-1]=='*'&&in_range(m,n-1)) surround_mines_count++;
	if (mines_board[m-1][n]=='*'&&in_range(m-1,n)) surround_mines_count++;
	if (mines_board[m-1][n+1]=='*'&&in_range(m-1,n+1)) surround_mines_count++;
	if (mines_board[m-1][n-1]=='*'&&in_range(m-1,n-1)) surround_mines_count++;
	return surround_mines_count;
}
//==========================================================================================================================
//Kiem tra neu dam phai min
int mines_check(int m, int n) {
	if (mines_board[m][n]==42) return 1;
	else return 0; 
}
//==========================================================================================================================
//tra ve so luong min xung quanh neu vao o ko phai min
void player_dont_hit_mines(int m, int n) {
	int a=surround_mines(m, n);
	play_board[m][n]=a+48;
}
//==========================================================================================================================
void mines_position_check() { // for debugging only
	int count=0;
	for (int i=0; i<10; i++) {
		for (int j=0; j<10; j++) {
			if (mines_board[i][j]=='*') {cout << "mine[" << count << "]: (" << i << ";" << j << ")" << endl;
			count++;}
		}
	}
}
//==========================================================================================================================
//Cam co
void flag_placing(int m, int n) {
	play_board[m][n]='F';
}
// toan bo doan nay dung de expand, se co giai thich sau
//==========================================================================================================================
void expand(int m, int n);

void expand_up(int m, int n) {
	if (in_range(m - 1 , n) && expand_board[m - 1][n] == 0) {
		if (surround_mines(m - 1, n) == 0) expand(m - 1, n);
		else
		{ player_dont_hit_mines(m - 1, n); block_count++; expand_board[m - 1][n] = -1; }
		temp++; 
	}
	else return;
}

void expand_down(int m, int n) {
	if (in_range(m + 1, n) && expand_board[m + 1][n] == 0) {
		if (surround_mines(m + 1, n) == 0) expand(m + 1, n);
		else { player_dont_hit_mines(m + 1, n); block_count++; expand_board[m + 1][n] = -1; }
		temp++;
	}
	else return;
}

void expand_left(int m, int n) {
	if (in_range(m, n - 1) && expand_board[m][n - 1] == 0) {
		if (surround_mines(m , n - 1) == 0) expand(m , n - 1);
		else { player_dont_hit_mines(m , n - 1); block_count++; expand_board[m][n - 1] = -1; }
		temp++;
	}
	else return;
}
 
void expand_right(int m, int n) {
	if (in_range(m, n + 1) && expand_board[m][n + 1] == 0) {
		if (surround_mines(m , n + 1) == 0) expand(m , n + 1);
		else { player_dont_hit_mines(m , n + 1); block_count++; expand_board[m][n + 1] = -1; }
		temp++;
	}
	else return;
}
 
void expand_up_left(int m, int n) {
	if (in_range(m - 1, n - 1) && expand_board[m - 1][n - 1] == 0) {
		if (surround_mines(m - 1, n - 1) == 0) expand(m - 1, n - 1);
		else { player_dont_hit_mines(m - 1, n - 1); block_count++; expand_board[m - 1][n - 1] = -1; }
		temp++;
	}
	else return;
}
 
void expand_up_right(int m, int n) {
	if (in_range(m - 1, n + 1) && expand_board[m - 1][n + 1] == 0) {
		if (surround_mines(m - 1, n + 1) == 0) expand(m - 1, n + 1);
		else { player_dont_hit_mines(m - 1, n + 1); block_count++; expand_board[m - 1][n + 1] = -1; }
		temp++;
	}
	else return;
}

void expand_down_left(int m, int n) {
		if (in_range(m + 1, n - 1) && expand_board[m + 1][n - 1] == 0) {
			if (surround_mines(m + 1, n - 1) == 0) expand(m + 1, n - 1);
			else { player_dont_hit_mines(m + 1, n - 1); block_count++; expand_board[m + 1][n - 1] = -1; }
			temp++;
		}
		else return;
}

void expand_down_right(int m, int n) {
	if (in_range(m + 1, n + 1) && expand_board[m + 1][n + 1] == 0) {
		if (surround_mines(m + 1, n + 1) == 0) expand(m + 1, n + 1);
		else { player_dont_hit_mines(m + 1, n + 1); block_count++; expand_board[m + 1][n + 1] = -1; }
		temp++;
	}
	else return;
}
//============================================================================================================================
//ham expand chinh duoi day:
void expand(int m, int n) {
		play_board[m][n] = '+';
		expand_board[m][n] = -1; block_count++;
		expand_up(m, n);
		expand_down(m, n);
		expand_left(m, n);
		expand_right(m, n);
		expand_up_left(m, n);
		expand_up_right(m, n);
		expand_down_left(m, n);
		expand_down_right(m, n);
}
//============================================================================================================================
//Hien bang choi sau khi thang hoac thua
void end_condition_play_board() {
	for (int i=0; i<10; i++) {
		for (int j=0; j<10; j++) {
			if (mines_board[i][j]=='*') play_board[i][j]='*';
		}
	}
}
//==========================================================================================================================
//Debug -_-
void display_bugged_play_board() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << "Board[" << m << "][" << n << "]= " << play_board[m][n] << endl;
		}
	}
}
//==========================================================================================================================
//Ham canh bao input sai
void invalid_input_condition() {
	cout << "invalid input. please re-enter." << endl;
	display_play_board(); cout << endl;
}
//==========================================================================================================================
//Ham thuc hien phan choi
void gameplay() {
	block_count = 0; mines_count = 0;
	mines_number = generate_mines_number(mines_number);
	//cout << "number of mines: " << mines_number << endl;
	generate_mines_board();
	generate_random_mines(mines_number);
	generate_play_board();
	generate_expand_board();
	//display_mines_board(); cout << endl;
	display_play_board(); cout << endl;
	//===================================================================================================================== 
	for (;;) {
		if (mines_count == mines_number && block_count == 100 - mines_number) {
			end_condition_play_board();
			display_play_board();
			cout << endl << "Congratulation! You win!" << endl;
			break;
		}
		else {
			cout << "Nhap toa do x, y (f de cam co, n de chon o): " << endl;
			cin >> m >> n >> flag; clearScreen();
			//display_mines_board(); cout << endl;
			if (in_range(m,n)) {
				if (flag == 'f' || flag == 'F') {
					flag_placing(m, n);
					if (mines_check(m, n) == 1) { mines_count++; }
					display_play_board(); cout << endl;
				}
				else if (flag == 'n' || flag == 'N') {
					if (mines_check(m, n) == 1) {
						end_condition_play_board();
						display_play_board();
						cout << endl << "Too bad! You lose!" << endl;
						break;
					}
					else {
						if (surround_mines(m, n) == 0) { expand(m, n); }
						else {
							player_dont_hit_mines(m, n);
							block_count++;
						}
						display_play_board();
					}
				}
				else invalid_input_condition();
				//cout << endl << block_count << " " << mines_count << endl << temp << endl;
			}
			else invalid_input_condition();
		}
	}
}
//==========================================================================================================================
//Ham main
int main() {
	srand(time(0));
	char status;
	do {
		clearScreen();
		gameplay();
		cout << "Again? (Y for Yes/ N for No) :" << endl;
		cin >> status;
		if (status == 'n') break;
	} while (status == 'y');
	return 0;
}
