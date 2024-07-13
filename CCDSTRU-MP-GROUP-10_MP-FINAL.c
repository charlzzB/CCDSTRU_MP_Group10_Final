/*
	CCDSTRU Machine Project
	Made by: 
	Keira Gabrielle Alcantra; S24A 
	Charlize Kirsten Brodeth; S22A 
	Candice Aura Fernandez; S22A
*/

#include <stdio.h>
#include <string.h>
#define NUMP 9 
typedef int nPegs[NUMP];
typedef int nRow[3];
typedef int nColumn[3];

/*[Functions Used]**********************************************************************************************************************/
void
displayTitle ()
{
    printf("\t\t\t\t\t================================\n");
    printf("\t\t\t\t\t||      Number Scrabble       ||\n");
    printf("\t\t\t\t\t================================\n");
}

//These functions validates the inputs of the player
int 
inputDigits(int a)
{
    if (a <10 && a >0)
        return 1;
    else
        return 0;  
}

int 
inputCoord (int a)
{
    if(a>=1 && a<=3)
        return 1;
    else 
        return 0; 
}


//This function is to print the contents of the box 
void 
displaybox(int Box[][3])
{
	int i, j;
	printf("-------------\n");
	for(i=0; i<3; i++) //row
	{
		j=0; //column
		
		
		if(Box[i][j] == 0 && Box[i][j+1] == 0 && Box[i][j+2] == 0)
		{
			printf("|   |   |   |\n");
		}
		
		if(Box[i][j] > 0 && Box[i][j+1] == 0 && Box[i][j+2] == 0)
		{
			printf("| %d |   |   |\n", Box[i][j]);
		}
		
		if(Box[i][j] == 0 && Box[i][j+1] > 0 && Box[i][j+2] == 0 )
		{
			printf("|   | %d |   |\n", Box[i][j+1]);
		}
		
		if(Box[i][j] == 0 && Box[i][j+1] == 0 && Box[i][j+2] > 0)
		{
			printf("|   |   | %d |\n", Box[i][j+2]);
		}
		
		if(Box[i][j] > 0 && Box[i][j+1] > 0 && Box[i][j+2] == 0)
		{
			printf("| %d | %d |   |\n", Box[i][j], Box[i][j+1]);
		}
		
		if(Box[i][j] == 0 && Box[i][j+1] > 0 && Box[i][j+2] > 0)
		{
			printf("|   | %d | %d |\n", Box[i][j+1], Box[i][j+2]);
		}
		
		if(Box[i][j] > 0 && Box[i][j+1] == 0 && Box[i][j+2] > 0)
		{
			printf("| %d |   | %d |\n", Box[i][j], Box[i][j+2]);
		}
		
		if(Box[i][j] > 0 && Box[i][j+1] > 0 && Box[i][j+2] > 0)
		{
			printf("| %d | %d | %d |\n", Box[i][j], Box[i][j+1], Box[i][j+2]);
		}
	
		printf("-------------\n");
	}
	
}

//This function is to store the peg inputs in their respective arrays [Row Wise]
void                      
sortRow(int peg, int row, int *One, int *Two, int *Three, int sT, int sM, int sB)
{
	switch (row)
	{
		case 1:
			One[sT] = peg;
			break;
		case 2:
			Two[sM] = peg;
			break;
		case 3: 
			Three[sB] = peg;
			break;
	}
}

//This function is to store the peg inputs in their respective arrays [Column Wise]
void
sortCol(int peg, int col, int *Four, int *Five, int *Six, int sL, int sC, int sR)
{
	switch (col)
	{
		case 1:
			Four[sL] = peg;
			break;
		case 2:
			Five[sC] = peg;
			break;
		case 3: 
			Six[sR] = peg;
			break;
	}
}

//This function collects all used up pegs and stor them in an array
void
sortUsedPeg(int peg, int *UsedP, int Ucount, int round)
{
	int i;
	if (round == 0)
	{
		for(i=0; i<NUMP; i++)
		{
			UsedP[i] = 0; //initialize at the start
		}
	}
	else
	{
		UsedP[Ucount] = peg;
	}
}

//This function is to sort the coordinates and mark the values in the coordinate as well as mark if the taken coordinates
void
SortCoord(int Free[][3], int Occ[][3], int row, int col, int peg, int round)
{
	int i, j;
	if(round == 0)
	{
		for(i=0; i< 3; i++)
		{
			for(j=0; j<3; j++)
			{
				Free[i][j]= 0;
				Occ[i][j]= 0;
			}
		}
	}
	else
	{
		Free[row-1][col-1] = 1; //signifies that the spot is taken
		Occ[row-1][col-1] = peg; //places the peg in the box
	}
}

//Linear Search searches if the peg inputed has been used already
int
SearchPeg(int *WPegs, int PInput, int n)
{
	int i;
	for(i=0; i<n; i++)
	{
		if(WPegs[i] == PInput)
		{
			return 1;
		}
	}
	return 0;
	
}

//This function computes for the sum of the pegs
int
GetSum(int n, int *Triple)
{
	int i, sum=0;
	for(i = 0; i< 3; i++)
		{
			sum = sum + Triple[i];
		}
	return sum;
}

//This function determines the winner when the game is over
void declareWinner (int round, int sum)
{
	if(round % 2 == 0 && sum < 15 )
	{
		printf("Player 1 wins the game!\n");
	}
	 //--> A wins
	else if(round % 2 == 0 && sum == 15 ) 
	{
		printf("Player 2 wins the game!\n");
	}
	//--> B wins
	if(round % 2 == 1 && sum < 15)
	{	
		printf("Player 2 wins the game!\n");
	}
	 //--> B wins
	else if(round % 2 == 1 && sum == 15) 
	{
		printf("Player 1 wins the game!\n");
	}
	//--> A wins
}

/*[Main Function]****************************************************************************************************************************/
int
main()
{
	//Variables
	int Free[3][3]; 
	int Occ[3][3];
	nPegs UsedP;
	nRow One;
	nRow Two;
	nRow Three;
	nColumn Four;
	nColumn Five;
	nColumn Six;
	int over=0 , sum=0;
	int peg, row, column, round=0;
	int T=0, M=0, B=0, L=0, C=0, R=0, UP=0; // Signifies how many items are in the arrays
	//---------//
	
	
	displayTitle ();
	
	printf(" Coordinate path: \n"); 
	printf(" ------- ------- -------\n");
  	printf("| (1,1) | (1,2) | (1,3) |\n");
	printf(" ------- ------- -------\n");
	printf("| (2,1) | (2,2) | (2,3) |\n");
	printf(" ------- ------- -------\n");
	printf("| (3,1) | (3,2) | (3,3) |\n");
	printf(" ------- ------- -------\n");
	SortCoord(Free, Occ, row, column, peg, round);//this initiates the values of the coordinates
	printf("Lets Start!! \nPlayer 1 goes first!\n");
	round = 1;
	
	//Start Game
	do
	{
		printf("Round [%d]\n", round);
		printf("VALUE TO BE PLACED\n");
		printf("Enter a number among 1-9: \n");	
		do
		{
			scanf("%d", &peg);
			if(inputDigits(peg) == 0 || SearchPeg(UsedP, peg, 9) == 1 )
			{
				printf("invalid input try again: ");
			}
		}while(inputDigits(peg) == 0 || SearchPeg(UsedP, peg, 9) == 1);
		
		
		printf("COORDINNATES\n");
		printf("Enter coordinate x y wherein x-row and y-column (pls put a space in between ie. 1 2): \n");
		do
		{
			scanf("%d %d",&row, &column);
			if(Free[row-1][column-1] == 1 || inputCoord (row) == 0 || inputCoord (column) == 0)
			{
				printf("There is already a peg placed there, please input another one: \n");
			}
		}while(Free[row-1][column-1] == 1|| inputCoord (row) == 0 || inputCoord (column) == 0);
		
		
		//functions
		sortRow(peg, row, One, Two, Three, T, M, B);
		sortCol(peg, column, Four, Five, Six, L, C, R);
		sortUsedPeg(peg, UsedP, UP, round);
		SortCoord(Free, Occ, row, column, peg, round);
		displaybox(Occ);
		
		//conditions to update every after game
		switch (row)
		{
			case 1:
				T++;
				UP++;
				break;
			case 2:
				M++;
				UP++;
				break;
			case 3: 
				B++;
				UP++;
				break;
		}
		
		switch (column)
		{
			case 1:
				L++;
				break;
			case 2:
				C++;
				break;
			case 3: 
				R++;
				break;
		}
		
		
		if(T == 3)
		{
			sum = GetSum(T, One);
			if(sum == 15 || sum < 15)
			{
				over = 1;
			}
			else 
			{
				round++;
				T = 0;
			}
		}
		else if(M == 3)
		{
			sum = GetSum(M, Two);
			if(sum == 15 || sum < 15)
			{
				over = 1;
			}
			else
			{
				round++;
				M = 0;
			}
		}
		else if(B == 3)
		{
			sum = GetSum(B, Three);
			if(sum == 15 || sum < 15)
			{
				over = 1;
			}
			else
			{
				round++;
				B =0;
			}
		}
		else if(L == 3)
		{
			sum = GetSum(L, Four);
			if(sum == 15 || sum < 15)
			{
				over = 1;
			}
			else
			{
				round++;
				L = 0;
			}
		}
		else if(C == 3)
		{
			sum = GetSum(C, Five);
			if(sum == 15 || sum < 15)
			{
				over = 1;
			}
			else
			{
				round++;
				C = 0;
			}
		}
		else if(R == 3)
		{
			sum = GetSum(R, Six);
			if(sum == 15 || sum < 15)
			{
				over = 1;
			}
			else
			{
				round++;
				R = 0;
			}
		}
		else
		{
			round++;
		}
		
	}while(over == 0);

	//printf("%d\n", sum);
	declareWinner (round, sum);
	
	return 0;
}

