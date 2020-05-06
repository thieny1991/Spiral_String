/*********************************************************************************
*Group Project 1: Y Nguyen, Kiet Dinh, and Chris Macias
*Date:02/01/2018
*Course: Data Structure
*Professor: Rizk
**********************************************************************************/

#include<iostream>
#include<string>
#include<cstring>
#include<cmath>
//#include<time.h>
#include<fstream>
#include"ArgumentManager.h"

using namespace std;
int findMatrixSize(string str);
void createMatrix(char **& matrix, int dim);
void fillString(string &str,int dim);
void fillMatrixInSpiral(char **&matrix, string &str,int diagonal, int dim);
void print(char **&matrix,int dim);
bool readInput(const char*, string &);
void writeOutput(const char*, char **&, int dim);
void destroyMatrix(char**&,int );

/******************************************************************************
*							Entry of program
*******************************************************************************/

int main(int argc, char* argv[]) {

	//clock_t t;
	//int f;
	//t = clock();
	
	string str;
	char **matrix;
	int dim;

	if (argc < 2) {
		std::cout << "./Spiral input=input1.txt;output=output1.txt" << std::endl;
		return -1;
	}

	//creating an Argument Manager object named am
	ArgumentManager am(argc, argv);
	string inputFile = am.get("input"), outputFile = am.get("output");
	//cout << "ILOVEDATASTRUCTUREUSINGC++!BYMAKLIST2007EDITON" << endl;

	// open file read file get string
	if (!readInput(inputFile.c_str(), str)) {
			return 1;
	}
		
	//find the size of matrix and create an empty matrix;
	dim = findMatrixSize(str);

	//fill out "." at the end of string if string length<dim^2
	fillString(str, dim);

	//create matrix
	createMatrix(matrix, dim);

	//fill out matrix
	fillMatrixInSpiral(matrix, str, 0, dim);

	//write Out the content of the matrix to the output file
	writeOutput(outputFile.c_str(), matrix, dim);
	//print Out the content
	//print(matrix, dim);
	destroyMatrix(matrix, dim);
	//t = clock() - t;
	//printf("It took me %d clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);
	return 0;
}

/******************************************************************************
*Function : findMatrixSize this function receive a string as a parameter and 
*			return the number that square of it is larger than the string length
*@para: string
*return: int 
*******************************************************************************/
int findMatrixSize(string str)
{
	int size;
	double len = str.size();
	size=static_cast<int>( sqrt(len));// just to avoid warning loss data
	if (size*size < len)
		size++;
	return size;
}

/*****************************************************************************
*Function: createMatrix an two dimension array of type char, with dimension dim 
*@para: const char**& matrix, int 
*return:void
******************************************************************************/
void createMatrix(char **& matrix, int dim)
{
	matrix = new char*[dim];
	for (int row = 0;row < dim;row++)
		matrix[row] = new char[dim];
}



/*****************************************************************************
*Function: fillString add character "." at the end of string until the length
			of string equal to dim^2
*@para: string& , int
*return:void
******************************************************************************/
void fillString(string & str, int dim)
{
	int len = str.size();
	if (len !=dim*dim) {// if string's length less than size^2
		for (int i = 0;i < dim*dim- len;i++) {
			str.append(".");
		}
	}
}


/******************************************************************************
Author: Y Nguyen
Date: 01/02/2019
*Function: fillMatrixInSpiral fill out the matrix in spiral order
*@para: char**&, string&, int, int
*return:void
*******************************************************************************/
void fillMatrixInSpiral(char **& matrix, string & str, int diagonal, int dim)
{
	int row = diagonal;
	int col = diagonal;

	//if length of string is odd, exist a square size 1;
	if (dim == 1 && !str.empty()) {
		matrix[diagonal][diagonal] = str[0];
	}
	if (dim > 1) {
			//readRight: read (dim-1) characters in str to matrix
			while (col < diagonal+dim-1) {
				matrix[row][col] = str[0];
				col++;
				str.erase(0, 1);
			}

			//start from the last position of the square, readDown (dim-1) characters
			while (row <diagonal+ dim-1) {
				matrix[row][col] = str[0];
				row++;
				str.erase(0, 1);
			}
			
				//read left: Start from the last element of the right columm of the square.
							//read to the left dim-1 character
			while (col > diagonal) {
				matrix[row][col] = str[0];
				str.erase(0, 1);
				col--;
			}

			//readUp: start from the last e element of left columm, read up dim-1 characters
			while (row > diagonal) {
				matrix[row][col] = str[0];
				str.erase(0, 1);
				--row;
			}//end while
			
			//update the width of the new square = width of outerSquare -2;
			dim = dim - 2;
			//update diagonal// move diagonal down to (i+1)(j+1)
			diagonal++;	
			//recall function fillMatrixInSpiral 
			fillMatrixInSpiral(matrix, str, diagonal, dim);
	}// end if
}


/*****************************************************************************
*Function: print print out the content of the a given matrix
*@para: char**&, int
*return:void
******************************************************************************/
void print(char **& matrix, int dim)
{
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim;j++)
			cout << matrix[i][j];
		cout << endl;
	}
}


/*****************************************************************************
*Function: readInput open and read a file with a given name.
*			return false if cannot find the file
*@para: const char* file name, string &
*return:bool
******************************************************************************/
bool readInput(const char * fileName, string &str)
{
	ifstream ifs(fileName);
	if (!ifs)
	{
		cout << "Cannot open file" << endl;
		return false;
	}
	else {
		getline(ifs, str);
		ifs.close();
		return true;
	}
}


/*****************************************************************************
*Function: writeOutput open a output file with the given name,
*		   print out all elements in matrix
*@para: const char* fileName, char **&, int
*return:bool
******************************************************************************/
void writeOutput(const char *fileName, char **&matrix, int dim)
{
	ofstream ofs(fileName);
	
		for (int i = 0; i < dim; i++) {
			for (int j = 0; j < dim;j++)
				ofs << matrix[i][j];
			ofs << endl;
		}
		ofs.close();
}

void destroyMatrix(char **& matrix, int dim)
{
	for (int i = 0; i < dim; i++)
		delete[] matrix[i];
	delete[] matrix;
	matrix= 0;
}


