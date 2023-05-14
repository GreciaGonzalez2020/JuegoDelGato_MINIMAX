/*Juego del Gato
    Trabajo realizado para la materia de Inteligencia Artificial I.
    En este juego se ultiliza algoritmo minimax por parte de la máquina*/


#include<stdio.h>
#include<stdbool.h>

#define COMPUTER 1
#define HUMAN 2

#define SIDE 3

#define COMPUTERMOVE 'O'
#define HUMANMOVE 'X'

void showBoard(char board[][SIDE])
{
	printf("\t\t\t %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
	printf("\t\t\t-----------\n");
	printf("\t\t\t %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
	printf("\t\t\t-----------\n");
	printf("\t\t\t %c | %c | %c \n\n", board[2][0], board[2][1], board[2][2]);
}

void showInstructions()//Función para indicarle al usuario cómo deberá jugar
{
	printf("\t\nElige una casilla de acuerdo a lo siguiente:\n\n");

	printf("\t\t\t 1 | 2 | 3 \n");
	printf("\t\t\t-----------\n");
	printf("\t\t\t 4 | 5 | 6 \n");
	printf("\t\t\t-----------\n");
	printf("\t\t\t 7 | 8 | 9 \n\n");
}

void initialise(char board[][SIDE])
{
	for (int i=0; i<SIDE; i++)
	{
		for (int j=0; j<SIDE; j++)
			board[i][j] = ' ';
	}
}

void declareWinner(int whoseTurn)
{
	if (whoseTurn == COMPUTER)
		printf("\t\tHa ganado la IA\n");
	else
		printf("\t\tLo lograste! Ganaste!\n");
}

bool rowCrossed(char board[][SIDE])
{
	for (int i=0; i<SIDE; i++)
	{
		if (board[i][0] == board[i][1] &&
			board[i][1] == board[i][2] &&
			board[i][0] != ' ')
			return (true);
	}
	return(false);
}

//Funciones que buscan si se ha ganado de forma lineal o cruzada
bool columnCrossed(char board[][SIDE])
{
	for (int i=0; i<SIDE; i++)
	{
		if (board[0][i] == board[1][i] &&
			board[1][i] == board[2][i] &&
			board[0][i] != ' ')
			return (true);
	}
	return(false);
}

bool diagonalCrossed(char board[][SIDE])
{
	if (board[0][0] == board[1][1] &&
		board[1][1] == board[2][2] &&
		board[0][0] != ' ')
		return(true);

	if (board[0][2] == board[1][1] &&
		board[1][1] == board[2][0] &&
		board[0][2] != ' ')
		return(true);

	return(false);
}

//Si se encuentra un ganador se termina el juego.
bool gameOver(char board[][SIDE])
{
	return(rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board) );
}

//Función minimax
int minimax(char board[][SIDE], int depth, bool isAI)
{
	int score = 0;
	int bestScore = 0;
	if (gameOver(board) == true)
	{
		if (isAI == true)
			return -1;
		if (isAI == false)
			return +1;
	}
	else
	{
		if(depth < 9)//Aqui se define la profundidad que se tendrá, con una profundidad de 9 es poco probable o imposible ganar, con una profundidad de 5 es más probable poder ganar.
		{
			if(isAI == true)
			{
				bestScore = -999;
				for(int i=0; i<SIDE; i++)
				{
					for(int j=0; j<SIDE; j++)
					{
						if (board[i][j] == ' ')
						{
							board[i][j] = COMPUTERMOVE;
							score = minimax(board, depth + 1, false);
							board[i][j] = ' ';
							if(score > bestScore)
							{
								bestScore = score;
							}
						}
					}
				}
				return bestScore;
			}
			else
			{
				bestScore = 999;
				for (int i = 0; i < SIDE; i++)
				{
					for (int j = 0; j < SIDE; j++)
					{
						if (board[i][j] == ' ')
						{
							board[i][j] = HUMANMOVE;
							score = minimax(board, depth + 1, true);
							board[i][j] = ' ';
							if (score < bestScore)
							{
								bestScore = score;
							}
						}
					}
				}
				return bestScore;
			}
		}
		else
		{
			return 0;
		}
	}
}

int bestMove(char board[][SIDE], int moveIndex)
{
	int x = -1, y = -1;
	int score = 0, bestScore = -999;
	for (int i = 0; i < SIDE; i++)
	{
		for (int j = 0; j < SIDE; j++)
		{
			if (board[i][j] == ' ')
			{
				board[i][j] = COMPUTERMOVE;
				score = minimax(board, moveIndex+1, false);
				board[i][j] = ' ';
				if(score > bestScore)
					{
						bestScore = score;
						x = i;
						y = j;
					}
				}
			}
		}
	return x*3+y;
}

void playGato(int whoseTurn)
{
	char board[SIDE][SIDE];
	int moveIndex = 0, x = 0, y = 0;

	initialise(board);

	while (gameOver(board) == false && moveIndex != SIDE*SIDE)
	{
		int n;
		if (whoseTurn == COMPUTER)
		{
			n = bestMove(board, moveIndex);
			x = n / SIDE;
			y = n % SIDE;
			board[x][y] = COMPUTERMOVE;
			printf("\tLa IA ha colocado %c en la casilla %d\n\n", COMPUTERMOVE, n+1);
			showBoard(board);
			moveIndex ++;
			whoseTurn = HUMAN;
		}

		else if (whoseTurn == HUMAN)
		{
			printf("\tPuedes elegir las siguientes casillas : ");
			for(int i=0; i<SIDE; i++)
				for (int j = 0; j < SIDE; j++)
					if (board[i][j] == ' ')
						printf("%d ", (i * 3 + j) + 1);
			printf("\t\n\nElige una casilla = ");
			scanf("%d",&n);
			n--;
			x = n / SIDE;
			y = n % SIDE;
			if(board[x][y] == ' ' && n<9 && n>=0)
			{
				board[x][y] = HUMANMOVE;
				printf ("\t\nHaz puesto %c en la casilla %d\n\n", HUMANMOVE, n+1);
				showBoard(board);
				moveIndex ++;
				whoseTurn = COMPUTER;
			}
            			else if(board[x][y] != ' ' && n<9 && n>=0)
			{
				printf("\t\nLa casilla esta ocupada, selecciona una casilla disponible\n\n");
			}
			else if(n<0 || n>8)
			{
				printf("\tPosicion invalida\n");
			}
		}
	}

	if (gameOver(board) == false && moveIndex == SIDE * SIDE)
		printf("\t\tEs un empate\n");
	else
	{
		if (whoseTurn == COMPUTER)
			whoseTurn = HUMAN;
		else if (whoseTurn == HUMAN)
			whoseTurn = COMPUTER;

		declareWinner(whoseTurn);
	}
}

int main()
{
	printf("\n-----------------------------------------------------------------\n\n");
	printf("|\t\t\t Jugo del Gato\t\t\t\t|\n");
	printf("\n-----------------------------------------------------------------\n\n");
	char cont='y';
	do {
		char choice;
	 	printf("\t¿Quieres empezar primero? (y/n): ");
	 	scanf(" %c", &choice);
        showInstructions();
		if(choice=='n')
			playGato(COMPUTER);
		else if(choice=='y')
			playGato(HUMAN);
		else
			printf("\tElección inválida\n");

		printf("\t\n¿Quieres salir? (y/n): ");
       		scanf(" %c", &cont);
	} while(cont=='n');
	return (0);
}


