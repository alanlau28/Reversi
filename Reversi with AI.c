#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


bool positionInBounds(int n, int row, int col){
	if(row < 0 || row > n - 1 || col < 0 || col > n - 1){
		return false;
	}
	return true;
}

bool checkLegalInDirection(char board[][26], int n, int row, int col,char colour, int deltaRow, int deltaCol){
	int count = 0;
	row+= deltaRow;
	col+= deltaCol;
	
	while (positionInBounds(n,row,col)){
		if(board[row][col] != colour && board[row][col]!= 'U'){
			row+= deltaRow;
			col+= deltaCol;
			count++;
		}
		else if(board[row][col] == colour && count > 0){
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
void flipTile(char board[][26],int n, int row, int col, char colour, int deltaRow, int deltaCol){
	board[row][col] = colour;
	row+= deltaRow;
	col+= deltaCol;
	while (positionInBounds(n,row,col)){
		if(board[row][col] != colour && board[row][col]!= 'U'){
			board[row][col] = colour;
			row+= deltaRow;
			col+= deltaCol;
		}
		else if(board[row][col] == colour){
			return;
		}
	}
	return;
}

int checkAvailable(int directions[][2],char colour, int n,char board[][26]){
	int i,j,k;
	int count = 0;
	for(i = 0;i < n;i++){
			for(j = 0;j < n;j++){
				if(board[i][j] == 'U'){
					for(k = 0;k < 8;k++){
							if(checkLegalInDirection(board,n,i,j,colour,directions[k][0],directions[k][1])){
								count++;
								break;
							}
					}
				}
			}
		}
	return count;
}

bool checkCorner(char board[][26],char colour,int directions[][2],int n,int row,int col){
	int i;
	for(i = 0;i < 8;i++){
		if(checkLegalInDirection(board,n,row,col,colour,directions[i][0],directions[i][1])){
			return true;
		}
	}
	return false;
}

int countBoard(char board[][26],int n){
	int count = 0,i,j;
	for(i = 0;i<n;i++){
		for(j = 0;j < n; j++){
			if(board[i][j] != 'U'){
				count++;
			}
		}
	}
	return count;
}
void compPlay(char move[3],char board[][26],char colour,int directions[][2],int n,char player){
	
	int i,j,k,l,m;
	int greatest = n*-n, counter = 0, least = n*n;
	char copyBoard[26][26];
	for(i = 0;i < n; i++){
		for(j = 0;j < n; j++){
			if(board[i][j] == 'U'){
				counter = 0;
				int row = i;
				int col = j;
				for(l = 0;l<n;l++){
					for(m = 0;m<n;m++){
						copyBoard[l][m] = board[l][m];
					}
				}
				if((i == 0 && j == 0)||(i == 0 && j == n-1)||(i == n-1 && j == 0)||(i == n-1 && j == n-1)){
					if(checkCorner(board,colour,directions,n,i,j)){
						move[0] = i;
						move[1] = j;
						return;
					}
				}
				else if(countBoard(board,n) < n*n/2){
					for(k = 0;k < 8;k++){
							int count = 0;
								row+= directions[k][0];
								col+= directions[k][1];
								if(!positionInBounds(n,row,col)){
									row = i;
									col = j;
								}	
								while (positionInBounds(n,row,col)){
									if(board[row][col] != colour && board[row][col]!= 'U'){
										row+= directions[k][0];
										col+= directions[k][1];
										count++;
									}
									else if(board[row][col] == colour && count > 0){
										counter += count;
										flipTile(copyBoard,n,i,j,colour,directions[k][0],directions[k][1]);
										row = i;
										col = j;
										break;
									}
									else{
										row = i;
										col = j;
										break;
									}
								}
					}
					if(least > (counter + checkAvailable(directions,player,n,copyBoard)) && counter > 0){
						move[0] = i;
						move[1] = j;
						least = counter + checkAvailable(directions,player,n,copyBoard);
					}
				}
				else{
					for(k = 0;k < 8;k++){
							int count = 0;
								row+= directions[k][0];
								col+= directions[k][1];
								if(!positionInBounds(n,row,col)){
									row = i;
									col = j;
								}	
								while (positionInBounds(n,row,col)){
									if(board[row][col] != colour && board[row][col]!= 'U'){
										row+= directions[k][0];
										col+= directions[k][1];
										count++;
									}
									else if(board[row][col] == colour && count > 0){
										counter += count;
										flipTile(copyBoard,n,i,j,colour,directions[k][0],directions[k][1]);
										row = i;
										col = j;
										break;
									}
									else{
										row = i;
										col = j;
										break;
									}
								}
					}
					if(greatest < (counter - checkAvailable(directions,player,n,copyBoard)) && counter > 0){
						move[0] = i;
						move[1] = j;
						greatest = counter - checkAvailable(directions,player,n,copyBoard);
					}
				}
			}
		}
	}

}
bool boardFull(char board[][26],int n){
	int i,j;
	for(i = 0;i < n;i++){
		for(j = 0;j < n;j++){
			if(board[i][j] == 'U'){
				return false;
			}
		}
	}
	return true;
}
void checkScore(char board[][26],int n,int* pScore,int* cScore,char player, char comp){
	int i,j;
	for (i = 0;i < n;i++){
		for(j = 0;j < n; j++){
			if(board[i][j] == player){
				*pScore += 1;
			}
			else if (board[i][j] == comp){
				*cScore += 1;
			}
		}
	}
	return;
}
void printBoard(char board[][26], int n){
	int i,j;
	printf("  ");
	for(i = 0;i < n;i ++){
		printf("%c",'a' + i);
	}
	printf("\n");
	for (i = 0; i < n; i ++){
		printf("%c ",'a' + i);
		for(j = 0; j < n; j ++){
			printf("%c",board[i][j]);
		}
		printf("\n");
	}
}



int main(void) {	
	int n;
	int i,j,k;
	int pScore = 0, cScore = 0;
	int directions [8][2] = {{-1,0},{0,-1},{0,1},{1,0},{-1,-1},{-1,1},{1,-1},{1,1}};
	char move[3], comp, player;
	bool white = true, valid = false;
	printf("Enter the board dimension: ");
	scanf("%d",&n);
	
	char board [26][26];
	
	for (i = 0; i < n; i ++){
		for(j = 0; j < n; j ++){
			board[i][j] = 'U';
		}
	}
	
	board[n/2 - 1][n/2 -1] = 'W';
	board[n/2 - 1][n/2] = 'B';
	board[n/2 ][n/2 -1] = 'B';
	board[n/2][n/2] = 'W';
	
	printf("Computer plays (B/W): ");
	scanf(" %c",&comp);
	
	if(comp == 'W'){
		white = false;
		player = 'B';
	}
	else if(comp == 'B'){
		player = 'W';
	}
	
	printBoard(board,n);
	
	while(checkAvailable(directions,player,n,board) > 0 || checkAvailable(directions,comp,n,board) > 0){		
		if (!white){
			if(checkAvailable(directions,player,n,board) > 0){
				printf("Enter move for colour B (RowCol): ");
				scanf("%s",move);
				int xCoord = move[0] - 'a';
				int yCoord = move[1] - 'a';
				for(i = 0;i < 8;i++){
					if(checkLegalInDirection(board,n,xCoord,yCoord,player,directions[i][0],directions[i][1])){
						flipTile(board,n,xCoord,yCoord,player,directions[i][0],directions[i][1]);
						printBoard(board,n);
						valid = true;
						break;
					}
				}
				if (!valid){
					printf("Invalid move.\n%c player wins.",comp);
					return 0;
					}
				valid = false;
			}
			else if (!boardFull(board,n)){
				printf("B player has no valid move.\n");
			}
			if(checkAvailable(directions,comp,n,board) > 0){
				compPlay(move,board,comp,directions,n,player); 
				int xCoord = move[0];
				int yCoord = move[1];
				for(i = 0;i < 8;i++){
					if(checkLegalInDirection(board,n,xCoord,yCoord,comp,directions[i][0],directions[i][1])){
						flipTile(board,n,xCoord,yCoord,comp,directions[i][0],directions[i][1]);
					}
				}
				printf("Computer places W at %c%c.\n",move[0]+'a',move[1]+'a'); 
				printBoard(board,n);
			}
			else if(!boardFull(board,n)){
				printf("W player has no valid move.\n");
			}
		}
		else if(white){
			if(checkAvailable(directions,comp,n,board) > 0){
				compPlay(move,board,comp,directions,n,player); 
				int xCoord = move[0];
				int yCoord = move[1];
				for(i = 0;i < 8;i++){
					if(checkLegalInDirection(board,n,xCoord,yCoord,comp,directions[i][0],directions[i][1])){
						flipTile(board,n,xCoord,yCoord,comp,directions[i][0],directions[i][1]);
					}
				}
				printf("Computer places B at %c%c.\n",move[0]+'a',move[1]+'a'); 
				printBoard(board,n);
			}
			else if(!boardFull(board,n)){
				printf("B player has no valid move.\n");
			}
			if(checkAvailable(directions,player,n,board) > 0){
				printf("Enter move for colour W (RowCol): ");
				scanf("%s",move);
				int xCoord = move[0] - 'a';
				int yCoord = move[1] - 'a';
				for(i = 0;i < 8;i++){
					if(checkLegalInDirection(board,n,xCoord,yCoord,player,directions[i][0],directions[i][1])){
						flipTile(board,n,xCoord,yCoord,player,directions[i][0],directions[i][1]);
						printBoard(board,n);
						valid = true;
						break;
					}
				}
				if (!valid){
					printf("Invalid move.\n%c player wins.",comp);
					return 0;
					}
				valid = false;
			}
			else if (!boardFull(board,n)){
				printf("W player has no valid move.\n");
			}
			
		}
		
	} 
	checkScore(board,n,&pScore,&cScore,player,comp);
	if(pScore > cScore){
		printf("%c player wins",player);
	}
	else{
		printf("%c player wins",comp);
	}
	return 0;
}
