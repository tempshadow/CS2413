//============================================================================
// Name        : project1.cpp
// Author      : Nigel Mansell 113208927
// Version     : 0.0.1
// Copyright   : Your copyright notice
// Description : Project1 in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

/*
 * This class holds acts like an arrow. Holds a row, column, and a value.
 */
class SparseRow {
protected:
	int row; //Row#
	int col; //Column#
	int value; //We will assume that all our values will be integers
public:
	//default constructor; row = -1,; col = -1; value = 0
	SparseRow() {
		this->row = -1;
		this->col = -1;
		this->value = 0;
	}

	//Prints the row, column, and the value
	void display() {
		cout << row << ", " << col << ", "<< value << endl;
	}
	int getRow() {return row;} //Gets the row
	void setRow(int temp) {row = temp;} // Sets the row
	int getCol() {return col;} //Gets the Col
	void setCol(int temp) {col = temp;} //Sets the Col
	int getValue() {return value;} //Gets the value
	void setValue(int temp) {value = temp;} //Sets the value

};

/*
 * This class holds a SparseRow object and holds rows, columns, common value,
 * noNonSparseValues with getters and setters accordingly.
 */
class SparseMatrix {
protected:
	int noRows; //Number of rows of the original matrix
	int noCols; //Number of columns of the original matrix
	int commonValue; //read from input
	int noNonSparseValues;//read from input
	int currSize;//used for keeping track of size of array
	SparseRow* myMatrix; //array
public:
	//Empty constructor
	SparseMatrix() {
		noCols = 0;
		noRows = 0;
		commonValue = 0;
		noNonSparseValues = 0;
		currSize = 0;
		myMatrix = new SparseRow[noNonSparseValues];
	}
	//constructor for SparseMatrix, initializes all protected variables based off input
	SparseMatrix(int n, int m, int cv, int noNSV) {
		noRows = n;
		noCols = m;
		commonValue = cv;
		noNonSparseValues = noNSV;
		currSize = 0;
		myMatrix = new SparseRow[noNSV];
	}
	//This function multiplies matrices, takes in a SparseMatrix pointer
	SparseMatrix* Multiply(SparseMatrix& M) {
		SparseMatrix* tempMatrix = new SparseMatrix(noRows, noCols, commonValue, noNonSparseValues);
		int counter = 0;
		//loops through and multiplies each current matrix value by each passed over matrix value
		//then adds that to sum to be set to the tempMatrix matrix value
		for(int i = 0; i < noNonSparseValues; i++) {
			int sum = 0;
			for(int j = 0; j < noNonSparseValues; j++) {
				sum = sum + (myMatrix[j].getValue() * M.myMatrix[i].getValue());
				if(counter < noNonSparseValues) {
					(*tempMatrix).myMatrix[counter].setValue(sum);
					counter++;
				}
			}
		}
		int tempCount = 0;
		int tempC = 0;
		//this is used for constructing a sparse matrix form
		for(int i = 0; i < noRows; i++) {
			for(int j = 0; j < noCols; j++) {
				(*tempMatrix).setMatrix(tempCount, i, j, (*tempMatrix).myMatrix[tempC].getValue());
				tempCount++;
				tempC++;
			}
		}
		return tempMatrix;
	}

	//Reworked based off the scratch slide on canvas
	SparseMatrix* Add(SparseMatrix& M) {
		SparseMatrix* temp = new SparseMatrix(noRows,noCols,commonValue, noNonSparseValues);
		int i = 0;
		int j;
		int valueToAdd;
		bool found;
		bool* mArray = new bool[M.currSize];
		for (int k=0; k < M.currSize; k++)
			mArray[k] = false;
		while (i < currSize) {
			j = 0;
			found = false;
			(*temp).myMatrix[(*temp).currSize].setRow(myMatrix[i].getRow());
			(*temp).myMatrix[(*temp).currSize].setCol(myMatrix[i].getCol());
			valueToAdd = 0;
			while ((j < M.currSize) && (!found)) {
				if ((myMatrix[i].getRow() == M.myMatrix[j].getRow()) &&
					(myMatrix[i].getCol() == M.myMatrix[j].getCol()) ) {
					found = true;
					valueToAdd = M.myMatrix[j].getValue();
					mArray[j] = true;
				}
				else {j++;};
			}
			(*temp).myMatrix[(*temp).currSize++].setValue(myMatrix[i].getValue() + valueToAdd);
			i++;
		}
		for (int k=0; k < M.currSize; k++) {
			if (!mArray[k]) {
				(*temp).myMatrix[(*temp).currSize].setRow(myMatrix[k].getRow());
				(*temp).myMatrix[(*temp).currSize].setCol(myMatrix[k].getCol());
				(*temp).myMatrix[(*temp).currSize++].setValue(myMatrix[k].getValue());
			}
		}
		delete [] mArray;
		return temp;
	}

	//Display the sparse matrix
	void display() {
		for(int i = 0; i < noNonSparseValues; i++) {
			if (myMatrix[i].getValue() != commonValue) {
				myMatrix[i].display();
			}
		}
	}
	//Display the matrix in its original format
	void displayMatrix() {
		bool test;
		int point;
		for(int i = 0; i < noRows; i++) {
			for(int j = 0; j < noCols; j++) {
				for(int k = 0; k < noNonSparseValues; k++) {
					if (myMatrix[k].getRow() == i && myMatrix[k].getCol() ==j) {
						test = true;
						point = myMatrix[k].getValue();
					}
				}
				if(test == true) {
					cout << point << "\t";
					test = false;
				}
				else {
					cout << commonValue << "\t";
				}
			}
			cout << endl;
		}
	}

	//Transposes a matrix
	SparseMatrix* Transpose() {
		SparseMatrix* tempMatrix = new SparseMatrix(noRows, noCols, commonValue, noNonSparseValues);
		for(int i = 0; i < noNonSparseValues; i++) {
			(*tempMatrix).myMatrix[i].setRow(this->myMatrix[i].getCol());
			(*tempMatrix).myMatrix[i].setCol(this->myMatrix[i].getRow());
			(*tempMatrix).myMatrix[i].setValue(this->myMatrix[i].getValue());
		}
		return tempMatrix;
	}
	int getNoRows() {return noRows;}//gets #rows
	void setNoRows() {this->noRows = noRows;}//sets #rows
	int getNoCols() {return noCols;}//gets #cols
	void setNoCols() {this->noCols = noCols;}//sets #cols
	int getCommonValue() {return commonValue;}//gets common value
	void setCommonValue() {this->commonValue = commonValue;}//sets common value
	int getNoNonSparseValues() {return noNonSparseValues;}//gets no non sparse values
	void setNoNonSparseValues() {this->noNonSparseValues = noNonSparseValues;}// sets no non sparse values
	//sets the matrix, keeps track of index with point thats passed in
	void setMatrix(int point, int row, int col, int val) {
		myMatrix[point].setRow(row);
		myMatrix[point].setCol(col);
		myMatrix[point].setValue(val);
		currSize++;
	}
};

//main function of the program
int main() {
	int n, m, cv, noNSV;
	cin >> n >> m >> cv >> noNSV;
	SparseMatrix* firstOne = new SparseMatrix(n, m, cv, noNSV);
	int x;
	int count = 0;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			cin >> x;
			if(x != cv) {
				(*firstOne).setMatrix(count, i, j, x);
				count++;
			}
		}
	}
	cin >> n >> m >> cv >> noNSV;
	SparseMatrix* secondOne = new SparseMatrix(n,m, cv, noNSV);
	int y;
	int counter = 0;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			cin >> y;
			if(y != cv) {
				(*secondOne).setMatrix(counter, i, j, y);
				counter++;
			}
		}
	}
	cout << "First one in sparse matrix format" << endl;
	(*firstOne).display();
	cout << "First one in normal matrix format" << endl;
	(*firstOne).displayMatrix();
	cout << "Second one in sparse matrix format" << endl;
	(*secondOne).display();
	cout << "Second one in normal matrix format" << endl;
	(*secondOne).displayMatrix();
	SparseMatrix* temp = (*firstOne).Transpose();
	cout << "After Transpose first one" << endl;
	(*temp).displayMatrix();
	cout << "After Transpose second one" << endl;
	temp = (*secondOne).Transpose();
	(*temp).displayMatrix();
	cout << "Multiplication of matrices in sparse matrix form" << endl;
	SparseMatrix* test = (*secondOne).Multiply(*firstOne);
	(*test).display();
	cout << "Addition of matrices in sparse matrix form" << endl;
	temp = (*secondOne).Add(*firstOne);
	(*temp).display();
}
