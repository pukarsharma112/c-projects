#include <stdio.h>
#include <stdlib.h>

// global declarations
struct game_data {
	char p1[20], p2[20], winner;
	int p1_score, p2_score, round;
} data;

char board[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

// function definitions
void welcome_users();
void get_players();
void gameplay();
int validate_position(int);
int check_wins();
void print_board();
int print_result_and_ask();
void reset_board();
void print_final_result();

void main() 
{
	int replay = 1;
	data.round = 1;
	data.winner = '?';
	system("clear");

	while(replay)
	{
		if(data.round == 1) 
		{
			welcome_users();
			get_players();
		}

		gameplay();
		replay = print_result_and_ask();
	}
}

void welcome_users() 
{	
	printf("Welcome to Tic Tac Toe - The Game By Pukar Sharma\n");
	printf("------------------------------------------------------\n");
}

void get_players() 
{
	printf("Enter 1st player name:\t");
	scanf(" %s", data.p1);
	printf("Enter 2nd player name:\t");
	scanf(" %s", data.p2);
}

void gameplay() 
{
	int i, pos, err, wins;
	char marker = data.winner != '?' ? data.winner : 'X';

	// welcome user with board
	print_board();

	for(i=0;i<9;i++) 
	{

		// update current user's indicator
		if(marker == 'X') 
		{
			printf("%s's turn as [%c]:\t", data.p1, marker);
		} 
		else 
		{
			printf("%s's turn as [%c]:\t", data.p2, marker);
		}

		// read for the user's position.
		read_position:
			scanf("%d", &pos);

		// validate user provided position.
		err = validate_position(pos);

		if(err) 
		{
			goto read_position;
		} 
		else 
		{
			board[pos-1] = marker;
		}

		// print board with updated position.
		print_board();
		//check if someone has won the match.
		wins = check_wins();

		if(wins)
		{
			if(marker == 'X') 
			{
				data.p1_score +=1;
				data.winner = 'X';
			} 
			else 
			{
				data.p2_score +=1;
				data.winner = '0';
			}
			break;
		}

		// update user's marker if there is not winner yet.
		marker = marker == 'X' ? '0' : 'X';
	}
}

int validate_position(int pos) 
{
	if(pos < 1 || pos > 9)
	{
		printf("Please select the valid position to mark [1-9]:\t");
		return 1;
	}
	else if(board[pos-1] == 'X' || board[pos-1] == '0') 
	{
		printf("This position is already selected. Please select another one:\t");
		return 1;
	} 
	else 
	{
		return 0;
	}
}

int check_wins() 
{
	int j;
	for(j=0;j<8;j++) 
	{
		if( 
			j%3 == 0 && (board[j] == board[j+1] && board[j] == board[j+2]) ||
			board[j] == board[j+3] && board[j] == board[j+6] ||
			board[0] == board[4] && board[0] == board[8] ||
			board[2] == board[4] && board[2] == board[6]
		) 
		{
			return 1;
		}
	}
	return 0;
}

void print_board() 
{
	system("clear");
	printf("------------------------------------------------------\n");
	printf("1st player: %s as [X]\n", data.p1);
	printf("2nd player: %s as [0]\n", data.p2);
	printf("# Round: %d\n", data.round);
	printf("------------------------------------------------------\n");

	printf("Choose any of the available numbers to mark your position.\n\n");
	printf("  %c  |  %c  |  %c  \n", board[0], board[1], board[2]);
	printf("-----|-----|-----\n");
	printf("  %c  |  %c  |  %c  \n", board[3], board[4], board[5]);
	printf("-----|-----|-----\n");
	printf("  %c  |  %c  |  %c  \n\n", board[6], board[7], board[8]);
}

int print_result_and_ask() 
{
	char opt;
	printf("------------------------------------------------------\n");
	printf("Game Over.\n");
	if(data.winner == 'X') 
	{
		printf("%s won the game as [X].\n", data.p1);
	} 
	else if(data.winner == '0') 
	{
		printf("%s won the game as [0].\n", data.p2);
	} 
	else 
	{
		printf("The game was draw!\n");
	}

	printf("Continue playing the game:[Y/n]:\t");
	scanf(" %c", &opt);
	if(opt == 'n' || opt == 'N') 
	{
		print_final_result();
		return 0;
	} 
	else 
	{
		data.round +=1;
		reset_board();
		return 1;
	}
}

void reset_board()
{
	for(int i=0;i<9;i++) 
		board[i] = '0' + i + 1;
}

void print_final_result() 
{
	system("clear");
	printf("---------------------------------------\n");
	printf("| Scoreboard:\n");
	printf("| %s scored %d.\n", data.p1, data.p1_score);
	printf("| %s scored %d.\n", data.p2, data.p2_score);
	printf("----------------------------------------\n");
}
