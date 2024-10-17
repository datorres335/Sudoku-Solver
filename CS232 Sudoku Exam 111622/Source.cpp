#include<iostream>
using namespace std;

const int ROW = 9;
const int COL = 9;
static int displayCounter = 0; //for STEPS 6 & 7

void displayPuzzle(int arrayPar[ROW][COL]);
void solvePuzzle(int arrayPar[ROW][COL]);

int main()
{
	char userInput = 'y';

	int firstPuzzle[ROW][COL] = {
		{5,0,4,6,0,7,9,0,2},
		{0,7,0,1,0,5,0,4,0},
		{1,0,8,0,4,0,5,0,7},
		{0,5,0,7,0,1,0,2,0},
		{4,0,6,0,5,0,7,0,1},
		{0,1,0,9,0,4,0,5,0},
		{9,0,1,0,3,0,2,0,4},
		{0,8,0,4,0,9,0,3,0},
		{3,0,5,0,8,0,1,0,9} };

	int secondPuzzle[ROW][COL] = {
		{0,3,0,2,6,0,7,8,0},
		{6,0,0,5,7,0,4,9,0},
		{1,9,0,8,3,0,0,6,0},
		{8,2,0,0,9,0,3,4,0},
		{3,7,0,6,0,0,9,1,0},
		{9,5,0,0,4,0,6,2,0},
		{5,1,0,3,2,0,0,7,0},
		{2,4,0,9,5,0,1,0,0},
		{0,6,0,4,1,0,2,5,0} };

	//display unsolved puzzle
	displayPuzzle(firstPuzzle);

	cout << "Are you ready to see the answers to the puzzle? (y/n): ";
	cin >> userInput;

	if (userInput == 'Y' || userInput == 'y')
	{
		solvePuzzle(firstPuzzle);
	}

	displayPuzzle(secondPuzzle);

	cout << "Are you ready to see the answers to the puzzle? (y/n): ";
	cin >> userInput;

	if (userInput == 'Y' || userInput == 'y')
	{
		solvePuzzle(secondPuzzle);
	}

	return 0;
}

void displayPuzzle(int arrayPar[ROW][COL])
{
	if (displayCounter == 0) cout << "Here is an unsolved sudoku puzzle: " << endl;
	else cout << "Here is another unsolved sudoku puzzle: " << endl;

	cout << "-------------------------" << endl;
	for (int i = 0; i <= 8; i++)
	{
		cout << "| ";
		for (int j = 0; j <= 8; j++)
		{
			if (arrayPar[i][j] == 0) cout << "  ";
			if (arrayPar[i][j] != 0) cout << arrayPar[i][j] << " ";
			if (j == 2 || j == 5) cout << "| ";
			if (j == 8) cout << "| ";
		}
		cout << endl;
		if (i == 2 || i == 5) cout << "-------------------------" << endl;
	}
	cout << "-------------------------" << endl << endl;
	displayCounter++;
}
void solvePuzzle(int arrayPar[ROW][COL])
{
	bool hasNum = false;

	int blockCounter = 0;
	//(*STEP 7*)
	while (blockCounter < 9) //need to continously loop thru this until block counter hits 9, block counter will only increment after each block is full with numbers 
	{	
		//(*STEP 7*)
		for (int numInQuestion = 1; numInQuestion <= 9; numInQuestion++) //transverse through the 2D array one number at a time 
		{
			//(*FOR STEPS 1 THRU 6*)
			for (int blockRow = 0; blockRow <= 6; blockRow = blockRow + 3) //transverse thru each block 
			{
				//(*FOR STEPS 1 THRU 6*)
				for (int blockCol = 0; blockCol <= 6; blockCol = blockCol + 3) //transverse thru each block 
				{
					hasNum = false;

					// (*STEP 1*)
					// checks block for number in question, if it does have it, move on to next block 
					for (int i = blockRow; i <= blockRow + 2; i++)
					{
						for (int j = blockCol; j <= blockCol + 2; j++)
						{
							if (arrayPar[i][j] == numInQuestion) hasNum = true;
							if (hasNum == true) break;
						}
						if (hasNum == true) break;
					} // checks block for number in question, if it does have it, move on to next block

					//(*STEP 2*)
					//checks rows and cols corresponding to block for number in question 
					if (hasNum == false)
					{
						int tempArr[ROW][COL]; //parallel temporary array to hold temporary place holder numbers
						for (int i = 0; i <= 8; i++)
						{
							for (int j = 0; j <= 8; j++)
							{
								tempArr[i][j] = arrayPar[i][j];
							}
						}

						//(*STEP 3*)
						//this section is fill block with temporary values 
						for (int i = blockRow; i <= blockRow + 2; i++) //block scan, rows
						{
							for (int j = 0; j <= 8; j++) //scan entire row for num in question
							{
								if (arrayPar[i][j] == numInQuestion) //if row has numInQuestion, fill empty spaces with temp values
								{
									for (int k = blockCol; k <= blockCol + 2; k++) //look for empty spaces in block to fill with temp values
									{
										if (tempArr[i][k] == 0)
										{
											tempArr[i][k] = numInQuestion;
										}
									}
								}
							}
						}
						for (int i = blockCol; i <= blockCol + 2; i++) //block scan, columns
						{
							for (int j = 0; j <= 8; j++) //scan entire col for num in question
							{
								if (arrayPar[j][i] == numInQuestion) //if col has numInQuestion, fill empty spaces with temp values
								{
									for (int k = blockRow; k <= blockRow + 2; k++) //look for empty spaces in block to fill with temp values
									{
										if (tempArr[k][i] == 0)
										{
											tempArr[k][i] = numInQuestion;
										}
									}
								}
							}
						} //this section is fill block with temporary values

						//(*STEP 4*)
						//after filling block with temp values, check to see if block has only one remaining empty space, if it does, fill that empty space with numInQuestion 
						int emptySpaceCounter = 0;
						int zeroRow;
						int zeroCol;
						for (int i = blockRow; i <= blockRow + 2; i++)
						{
							for (int j = blockCol; j <= blockCol + 2; j++)
							{
								if (tempArr[i][j] == 0)
								{
									emptySpaceCounter++;
									zeroRow = i;
									zeroCol = j;
								}
							}
						}
						if (emptySpaceCounter == 1)
						{
							arrayPar[zeroRow][zeroCol] = numInQuestion;
						}

						//*STEP 5 occurs automatically after tempArr goes out of scope

						//(*STEP 6*)
						//check to too see if there is only one empty space remaining in the block, if so fill that number with the missing number
						//need to subtract all the numbers from the block from 45 and assign it to the empty space 
						emptySpaceCounter = 0;
						for (int i = blockRow; i <= blockRow + 2; i++)
						{
							for (int j = blockCol; j <= blockCol + 2; j++)
							{
								if (arrayPar[i][j] == 0)
								{
									emptySpaceCounter++;
									zeroRow = i;
									zeroCol = j;
								}
							}
						}
						if (emptySpaceCounter == 1)
						{
							int remainingNum = 0;
							for (int i = blockRow; i <= blockRow + 2; i++)
							{
								for (int j = blockCol; j <= blockCol + 2; j++)
								{
									remainingNum += arrayPar[i][j];
								}
							}
							remainingNum = 45 - remainingNum;

							arrayPar[zeroRow][zeroCol] = remainingNum;

							blockCounter++;
						}
					} // checks rows and cols corresponding to block for number in question
				} //transverse thru each block
			} //transverse thru each block
		} //for (int numInQuestion = 1; numInQuestion <= 9; numInQuestion++)
	} //while (blockCounter <= 9)

	//display solved puzzle
	cout << "-------------------------" << endl;
	for (int i = 0; i <= 8; i++)
	{
		cout << "| ";
		for (int j = 0; j <= 8; j++)
		{
			cout << arrayPar[i][j] << " ";
			if (j == 2 || j == 5) cout << "| ";
			if (j == 8) cout << "| ";
		}
		cout << endl;
		if (i == 2 || i == 5) cout << "-------------------------" << endl;
	}
	cout << "-------------------------" << endl << endl;
}