#include <iostream>
using namespace std;

/**
 * Enunciado:
 *
 * TIC TAC TOE VS MACHINE
 *
 * SE CREARA UN SISTEMA CAPAZ DE JUGAR A TIC TAC TOE CON LA MÁQUINA
 * EN LA QUE EL USUARIO PUEDE JUGAR CON LA MÁQUINA.
 *
 *
 *
 * Participantes:
 * Victor Jimenez - 1106003
 * Jorge Saldivar - 1105996
 *
 * Fecha: 07/02/2022
 *
 * */

//declaring the structure for the movement
struct Move
{
    int row, col,score;
};
//check if the input is a number
bool check_number(char str)
{
    if (isdigit(str) == false)
         return false;
    
    return true;
}
//function to print the board of the game tic tac toe 3x3
void printBoard(char (&board)[3][3])
{
    for (auto &i : board)
    {
        for (char j : i)
        {
            cout << j << " ";
        }
        cout << endl;
    }
}
//function to check if there is a tie
bool isOver(char board[3][3])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return true;
    return false;
}
//funtion to check who wins the game
char checkWinner(char (&board)[3][3])
{
    //checking for the rows
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            if (board[i][0] == 'X')
                return 'X';
            else if (board[i][0] == 'O')
                return 'O';
        }
    }
    //checking for the columns
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            if (board[0][i] == 'X')
                return 'X';
            else if (board[0][i] == 'O')
                return 'O';
        }
    }
    //checking for the diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        if (board[0][0] == 'X')
            return 'X';
        else if (board[0][0] == 'O')
            return 'O';
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        if (board[0][2] == 'X')
            return 'X';
        else if (board[0][2] == 'O')
            return 'O';
    }
    return ' ';
}

//ask for player's move
void askMove(char (&board)[3][3], char player)
{
    int row, col;
    cout << "Player " << player << " enter your move: ";
    cin >> row >> col;
    // while (check_number(row) == false || check_number(col) == false)
    // {
    //     cout << "Invalid move, please try again: ";
    //     cin >> row >> col;
    // }
    // while (board[row - 1][col - 1] != ' ')
    // {
    //     cout << "Invalid move, please try again: ";
    //     cin >> row >> col;
    // }
    board[row - 1][col - 1] = player;
}
//funtion minimax v2 

Move minimax(char (&board)[3][3],bool maximizing_player = true) {
		Move best_move;
		if (checkWinner(board) == 'O') {
			if (maximizing_player) {
				best_move.score = -1;
			} else {
				best_move.score = 1;
			}
			return best_move;
		} else if (isOver(board)) {
			best_move.score = 0;
			return best_move;
		}
		
		best_move.score = maximizing_player ? -2 : 2;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (board[i][j] == ' ') {
					board[i][j] = maximizing_player ? 'O' : 'X';
					Move board_state = minimax(board,!maximizing_player);
					if (maximizing_player) {
						if (board_state.score > best_move.score) {
							best_move.score = board_state.score;
							best_move.row = i;
							best_move.col = j;
						}
					} else {
						if (board_state.score < best_move.score) {
							best_move.score = board_state.score;
							best_move.row = i;
							best_move.col = j;
						}
					}
					board[i][j] = ' ';
				}
			}
		}
		return best_move;
	}

//funtion to machine move
void machineMove(char (&board)[3][3], char player)
{
    Move move = minimax(board, player);
    board[move.row][move.col] = player;
}


//function to play machine vs player
void playMachine(char (&board)[3][3])
{
    char player = 'X';
    while (isOver(board))
    {
        printBoard(board);
        askMove(board, player);
        if (checkWinner(board) == ' ')
        {
            machineMove(board, player == 'X' ? 'O' : 'X');
            player = player == 'X' ? 'O' : 'X';
        }
        else
        {
            printBoard(board);
            cout << "Player " << checkWinner(board) << " wins!" << endl;
            break;
        }
    }
    if (checkWinner(board) == ' ')
        cout << "Tie!" << endl;
}


//call the main function
int main()
{
    char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}};
    char player,computer;

    //call funtion to play machine vs player
    playMachine(board);
   
    return 0;
}

