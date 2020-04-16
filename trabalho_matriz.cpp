// C++ implementation of the above approach
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <algorithm> //para uso do fill
using namespace std;

//http://mathworld.wolfram.com/KnightsProblem.html

/* m*n is the board dimension
k is the number of knights to be placed on board
count is the number of possible solutions */
int m, n, k;
//int count = 0;
clock_t tempo_inicial, tempo_final;

/* Essa função preenche as casas do tabuleiro com "_" */
void makeBoard(char** board){
    //Aqui inicializo as posições com '_' com o uso do fill. O tempo de código não alterou muito.
    //fill(*board, *board + m*n, '_');
	
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			board[i][j] = '_';
		}
	}
}

/* Imprimir tabuleiro */
/*
void displayBoard(char** board){
	cout << endl;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cout << "\t" << board[i][j] << " ";
		}
		cout << endl;
	}
}
*/

/* Imprimir tabuleiro com coordenadas*/
void displayBoardCoordenatesMatrix(char** board){
	cout << endl;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if ((board[i][j] != 'K') && (board[i][j] != 'Q')) {
				cout << "\t" << (i*m)+(j+1) << ";" ;
			} else {
				cout << "\t" << board[i][j] << ";" ;
			}
		}
		cout << endl;
	}
	cout << endl;
}

/* Imprimir resultado final */
void displayResult(char** board){
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (board[i][j] == 'K' || board[i][j] == 'Q') {
				cout << board[i][j] << (i*m)+(j+1) << ";" ;
			}			
		}
	}
	cout << endl;
}


/* Imprimir coordenadas do tabuleiro */
/*void displayBoardCoordenates(char** board){
	cout << endl;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if ((board[i][j] == 'K') || (board[i][j] == 'Q')) {
				//cout << m << board[i][j] << i << j << (i*m)+(j+1) << ";" ;
				cout << (i*m)+(j+1) << ";" ;
			}
		}
	}
	cout << endl;
}
*/


/* Marca todas as posições de ataque de um cavaleiro colocado na posição [i][j]*/
void attack(int i, int j, char a, char** board){

	/* Condições para garantir que o bloco a ser verificado esteja dentro do tabuleiro
    void displayBoardCoordenatesMatrix(char** board, char a) */
	
    if ((i + 2) < m && (j - 1) >= 0) { /*baixo 2 esquerda 1*/
		board[i + 2][j - 1] = a;
	}
	if ((i - 2) >= 0 && (j - 1) >= 0) { /*cima 2 esquerda 1*/
		board[i - 2][j - 1] = a;
	}
	if ((i + 2) < m && (j + 1) < n) { /* baixo 2 direita 1*/
		board[i + 2][j + 1] = a;
	}
	if ((i - 2) >= 0 && (j + 1) < n) { /* cima 2 direita 1*/
		board[i - 2][j + 1] = a;
	}
	if ((i + 1) < m && (j + 2) < n) { /* baixo 1 direita 2 */
		board[i + 1][j + 2] = a;
	}
	if ((i - 1) >= 0 && (j + 2) < n) { /* cima 1 direita 2 */
		board[i - 1][j + 2] = a;
	}
	if ((i + 1) < m && (j - 2) >= 0) { /* baixo 1 esquerda 2 */
		board[i + 1][j - 2] = a;
	}
	if ((i - 1) >= 0 && (j - 2) >= 0) { /*cima 1 esquerda 2*/
		board[i - 1][j - 2] = a;
	}
}

/*Marca todas as posições de ataque de uma rainha colocada na posição [i][j] */
int attackqueens(int oi, int oj, char a, char** board){
	int i,j;

    /*vertical esquerda cima*/
	i = oi;
	j = oj;
	while ((i > 0) && (j > 0)) {
        //Não faz mto sentido um "||" nesse caso, será que não seria "&&"?
		//if ((board[i-1][j-1] != 'K') || (board[i-1][j-1] != 'A') || (board[i-1][j-1] != 'Q') || (board[i-1][j-1] != 'q')){
		if ((board[i-1][j-1] != 'K') || (board[i-1][j-1] != 'A') || (board[i-1][j-1] != 'Q')){
			if ((board[i-1][j-1] != 'K')) {
                board[i-1][j-1] = a;
			} else {
				return(1);				
			}
		}
		i--;
		j--;
	}

    /*cima*/
	i = oi;
	j = oj;
	while (i > 0) {
		if (board[i-1][j] != 'Q' && board[i-1][j] != 'K') {
            board[i-1][j] = a;
		} else {
			return(1);
		}
		i--;
	}

    /*vertical cima direita*/
	i = oi;
	j = oj;
	while ((i > 0) && (j < n)) {
		if (board[i-1][j+1] != 'Q' && board[i-1][j+1] != 'K') {
			
            board[i-1][j+1] = a;
		}else {
			return(1);
		}
		i--;
		j++;
	}

    /*lado esquerdo*/
	i = oi;
	j = oj;
	while (j > 0) {
		if (board[i][j-1] != 'Q' && board[i][j-1] != 'K') {
			board[i][j-1] = a;   
		}else {
			return(1);	
		}
		j--;
	}

    /*lado direito*/
	i = oi;
	j = oj;
	while (j+1 < n) {
		if (board[i][j+1] != 'Q' && board[i][j+1] != 'K') {
			board[i][j+1] = a;
           
		}else {
		    return(1);
        }
		j++;
	}

    /*vertical esquerda baixo*/
	i = oi;
	j = oj;
	while ((i+1 < m) && (j > 0)) {
		if (board[i+1][j-1] != 'Q' && board[i+1][j-1] != 'K') {
			board[i+1][j-1] = a;
		}else {
		   
            return(1);
        }
		i++;
		j--;
	}

    /*baixo*/
	i = oi;
	j = oj;
	while (i+1 < m) {
		if (board[i+1][j] != 'Q' && board[i+1][j] != 'K') {
			board[i+1][j] = a;
		}else {
		    return(1);
        }
		i++;
	}

    /*vertical direita baixo*/
	i = oi;
	j = oj;
	while ((i+1 < m) && (j+1 < n)) {
		/* antes da inversão para o if possuir a maior ocorrência
        if (board[i+1][j+1] != 'Q' && board[i+1][j+1] != 'K') {
			return(1);
		}else {
			board[i+1][j+1] = a;
		}
        */
        if (board[i+1][j+1] != 'Q' && board[i+1][j+1] != 'K') {
			board[i+1][j+1] = a;
		}else {
            return(1);
        }
		i++;
		j++;
	}
	return(0);
}


/* Verifica se a posição está vazia para colocar o cavaleiro */
bool canPlace(int i, int j, char** board){
	if (board[i][j] == '_')
	    return true;
	else
	    return false;
}

/* Coloca o cavaleiro na posição [i][j] no tabuleiro */
int place(int i, int j, char k, char a, char** board, char** new_board){
	/* Copia as configurações do antigo tabuleiro para o novo tabuleiro */
	for (int y = 0; y < m; y++) {
		for (int z = 0; z < n; z++) {
			new_board[y][z] = board[y][z];
		}
	}

	/* Coloca o cavaleiro na posição [i][j] no novo tabuleiro */
	new_board[i][j] = k;

	/* Marca todas as opções de ataque do cavaleiro recém-colocado no novo tabuleiro */
	if (k == 'K') {
		attack(i, j, a, new_board);
	} else {
		return(attackqueens(i, j, a, new_board));
	}
	return (0);
}

/*Encontra as rainhas e coloca elas no tabuleiro*/
void queens (int qui, int quj, char ** board) {
    
	if ((qui*m)+(quj+1) >= (m*n)) {
		//displayBoard(board);
		//displayBoardCoordenates(board,'Q');
	} else {
		for (int i = qui; i < m; i++) {
			for (int j = quj; j < n; j++) {
                
				if (canPlace(i,j,board)) {
				    /* Cria um novo tabuleiro e coloca a nova rainha nele */
					char** new_board = new char*[m];
					for (int x = 0; x < m; x++) {
						new_board[x] = new char[n];
					}
                    
					if (place(i, j, 'Q', 'a', board, new_board)) {    
					    /* Função recursiva para encontrar outras rainhas*/
					    
						board[i][j] = '*';
						queens(i, j, board);
					} else {
						/* Função recursiva para encontrar outras rainhas*/
						//printf("Place queen on %d:%d\n", i,j);
                        
						board[i][j] = 'Q';
                       // displayBoard(new_board);
						queens(i, j, new_board);
					}
					//displayBoard(board);

					/* Deleta o novo tabuleiro*/
					for (int x = 0; x < m; x++) {
						delete[] new_board[x];
                    }
					delete[] new_board;

				}
			}
		}
	}
}

/* Coloca os cavaleiros no tabuleiro de modo que eles não se atacam */
void kkn(int k, int sti, int stj, char** board){

    /* Se não tem cavaleiros, aumenta o contador */
	if (k == 0) {
		queens(0,0,board);
		displayBoardCoordenatesMatrix(board);
		tempo_final = clock();
		cout<<"tempo final = "<< (tempo_final - tempo_inicial) / (double)CLOCKS_PER_SEC << endl;
		displayResult(board);
		exit (1);
	//	count++;
	}
	else {
		/* Loop para verificar todas as posições no tabuleiro */
		for (int i = sti; i < m; i++) {
			for (int j = stj; j < n; j++) {

				/* É possível colocar o cavaleiro na posição [i][j]? */
				if (canPlace(i, j, board)) {
				    /* Cria um novo tabuleiro e coloca o cavaleiro na posição */
					char** new_board = new char*[m];
					for (int x = 0; x < m; x++) {
						new_board[x] = new char[n];
					}

					place(i, j, 'K', 'A', board, new_board);

					/* Função recursiva para os outros cavaleiros*/
					kkn(k - 1, i, j, new_board);

					/* Delete the new board	to free up the memory */
					/*for (int x = 0; x < m; x++) {
						delete[] new_board[x];
					}
					delete[] new_board; não estava sendo utilizado*/
				}
			}
			stj = 0;
		}
	}
}


// Main
int main( int argc, char *argv[]){
	
	tempo_inicial = clock();

	if (argc <= 2 ) {
		printf("./knight <linha_tabuleiro> <nro_cavalos>\n");
		return -1;
	}

	m = atoi(argv	[1]);
	n = m;
	k = atoi(argv [2]);

	/* Criando um tabuleiro m*n */
	char** board = new char*[m];
    for (int i = 0; i < m; i++) {
		board[i] = new char[n];
	}
                
	/* Preenche as casas do tabuleiro com "_" */
	makeBoard(board);

	kkn(k, 0, 0, board);
	
	/*cout << endl
	<< "Total number of solutions : "
	<< count << endl;*/
	return 0;
}
