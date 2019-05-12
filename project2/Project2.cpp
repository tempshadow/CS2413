//============================================================================
// Name        : Project2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

//Exception for add
template <class DT>
class ExceptionAdd{};

//exception for multiply
template <class DT>
class ExceptionMultiply{};

//exception for common value
template <class DT>
class ExceptionCV{};

//Sparse Rows class acts like an array and has getters and setter for values
template <class DT>
class SparseRow{
protected:
	int row;
	int col;
	DT value;
public:
	SparseRow();//empty constructor
	SparseRow(int r, int c, DT& v);//constructor
	virtual ~SparseRow();//destructor
	void display();//displays
	void setRow(int n);//sets the rows
	void setCol(int m);//sets columns
	void setValue(DT v);//sets values
	int getRow();//gets row
	int getCol();//gets columns
	DT getValue();//gets value
};
/*
 * empty constructor sets row to -1, col to -1 and value to 0
 */
template<class DT>
SparseRow<DT>::SparseRow(){
	row = -1;
	col = -1;
	value = 0;
}
/*
 * regular constructor
 */
template<class DT>
SparseRow<DT>::SparseRow(int r, int c, DT& v) {
	row = r;
	col = c;
	value = v;
}
/*
 * destructor
 */
template<class DT>
SparseRow<DT>::~SparseRow(){}

/*
 * displays rows column and value
 */
template<class DT>
void SparseRow<DT>::display() {
	cout << row << ", " << col << ", " << value << endl;
}

/*
 * sets row
 */
template<class DT>
void SparseRow<DT>::setRow(int n){
	row = n;
}

/*
 * sets column
 */
template<class DT>
void SparseRow<DT>::setCol(int m){
	col = m;
}

/*
 * sets value
 */
template<class DT>
void SparseRow<DT>::setValue(DT v){
	value = v;
}

/*
 * gets the row
 */
template<class DT>
int SparseRow<DT>::getRow(){
	return row;
}

/*
 * gets column
 */
template<class DT>
int SparseRow<DT>::getCol(){
	return col;
}

/*
 * gets value
 */
template<class DT>
DT SparseRow<DT>::getValue(){
	return value;
}

/*
 * Has a vector, constructor, destructor, getters, setters, overloaded !, *, and + operators.
 */
template <class DT>
class SparseMatrix {
protected:
	int size;// used for addition
	int noRows; //Number of rows of the original matrix
	int noCols; //Number of columns of the original matrix
	int commonValue; //read from input
	vector<SparseRow<DT> >* myMatrix;//dynamic vector
public:
	SparseMatrix();//empty constructor
	SparseMatrix(int n, int m, int cv);//constructor
	void sparseAdd();//adds a set number of objects to vector
	virtual ~SparseMatrix();//destructor
	SparseMatrix<DT>* operator*(SparseMatrix<DT> M);//overloaded operator for multiplication
	void setSparseRow (int pos, int r, int c, DT& v);//sets the sparse row
	int getRows();//gets rows
	int getCols();//gets columns
	int getCV();//gets common value
	/*
	 * friend call to overload ! operator for transpose
	 */
	friend SparseMatrix<DT>* operator!(SparseMatrix<DT> M) {
		SparseMatrix<DT>* tempMatrix = new SparseMatrix<DT>(M.noCols, M.noRows, M.commonValue);
		tempMatrix->sparseAdd();
		//loops through and sets tempmatrix matrix values to the transpose of M.matrix
		for(int i = 0; i < static_cast<int>(M.myMatrix->size()); i++) {
			tempMatrix->myMatrix->at(i).setRow(M.myMatrix->at(i).getCol());
			tempMatrix->myMatrix->at(i).setCol(M.myMatrix->at(i).getRow());
			tempMatrix->myMatrix->at(i).setValue(M.myMatrix->at(i).getValue());
		}

		return tempMatrix;
	}
	SparseMatrix<DT>* operator+(SparseMatrix<DT> M);//opverloaded operator for addition
    void display();//Display the sparse matrix
    void displayMatrix (); //Display the matrix in its original format
    void read(SparseMatrix<DT> M, int n, int m, int v);//takes in the inputs and sets sparsematrix
    /*
     * friend call to overload << to display the values of M.matrix
     */
    friend ostream& operator << (ostream &out, SparseMatrix<DT> *M){
    	//loops through and displays M.matrix values
    	for(int i = 0; i <static_cast<int>(M->myMatrix->size()); i++) {
    		if (M->myMatrix->at(i).getValue() != M->commonValue) {
    			M->myMatrix->at(i).display();
    		}
    	}
    	return out;
    }
};

/*
 * returns number of rows
 */
template <class DT>
int SparseMatrix<DT>::getRows() {return noRows;}

/*
 * return number of columns
 */
template <class DT>
int SparseMatrix<DT>::getCols() {return noCols;}

/*
 * return the common value
 */
template <class DT>
int SparseMatrix<DT>::getCV() {return commonValue;}

/*
 * overloaded + operator for addition..converted from project one
 */
template <class DT>
SparseMatrix<DT>* SparseMatrix<DT>::operator+(SparseMatrix<DT> M) {
	SparseMatrix<DT>* temp = new SparseMatrix<DT>(noRows,noCols,commonValue);
	try {
		if((noRows != M.noRows) | (noCols != M.noCols)) {
			throw ExceptionAdd<int>();
		}
	}
	catch(ExceptionAdd<int> &e) {
		cout << "The rows and the columns of both the matrices don’t match." << endl;
		return temp;
	}
	try {
		if(commonValue != M.commonValue) {
			throw ExceptionCV<int>();
		}
	}
	catch(ExceptionCV<int> &e) {
		cout << "The common values of both the matrices don’t match." << endl;
		return temp;
	}
	temp->sparseAdd();
	int i = 0;
	int j;
	int valueToAdd;
	bool found;
	bool* mArray = new bool[static_cast<int>(M.myMatrix->size())];
	//loops and sets all values to false
	for (int k=0; k < static_cast<int>(M.myMatrix->size()); k++)
		mArray[k] = false;
	while (i < static_cast<int>(M.myMatrix->size())) {
		j = 0;
		found = false;
		(*temp).myMatrix->at((*temp).size).setRow(myMatrix->at(i).getRow());
		(*temp).myMatrix->at((*temp).size).setCol(myMatrix->at(i).getCol());
		valueToAdd = 0;
		while ((j < static_cast<int>(M.myMatrix->size())) && (!found)) {
			if ((myMatrix->at(i).getRow() == M.myMatrix->at(j).getRow()) &&
					(myMatrix->at(i).getCol() == M.myMatrix->at(j).getCol()) ) {
				found = true;
				valueToAdd = M.myMatrix->at(j).getValue();
				mArray[j] = true;
			}
			else {j++;};
		}

		(*temp).myMatrix->at((*temp).size++).setValue(myMatrix->at(i).getValue() + valueToAdd);
		i++;
	}
	//loops and sets temp matrix specified element values to current matrix k position values
	for (int k=0; k < static_cast<int>(M.myMatrix->size()); k++) {
		if (!mArray[k]) {
			(*temp).myMatrix->at((*temp).size).setRow(myMatrix->at(k).getRow());
			(*temp).myMatrix->at((*temp).size).setCol(myMatrix->at(k).getCol());
			(*temp).myMatrix->at((*temp).size++).setValue(myMatrix->at(k).getValue());
		}
	}
	delete [] mArray;
	return temp;
}
/*
 * overloaded * operator for multiplication. Uses sparse matrix to handle both square and non square matrix multiplication
 */
template <class DT>
SparseMatrix<DT>* SparseMatrix<DT>::operator *(SparseMatrix<DT> M) {
	SparseMatrix<DT>* tempMatrix = new SparseMatrix<DT>(noRows, M.noCols, commonValue);
	try {
		if (noCols != M.noRows) {
			throw ExceptionMultiply<int>();
		}
	}
	catch(ExceptionMultiply<int> &e) {
		cout << "The columns of the first matrix does not match the rows of the second matrix." << endl;
		return tempMatrix;
	}
	try {
		if(commonValue != M.commonValue) {
			throw ExceptionCV<int>();
		}
	}
	catch(ExceptionCV<int> &e) {
		cout << "The common values of both the matrices don’t match." << endl;
		return tempMatrix;
	}
	int* temp = new int[(noRows * M.noCols)];
	for(int i = 0; i < (noRows * M.noCols); i++) temp[i] = 0;
	int count = 0;
	int one = 0;
	int two = 0;
	for(int i = 0; i < noRows; i++) { // loops through current rows
		for(int j = 0; j < M.noCols; j++) { // loops through M columns
			for(int k = 0; k < noCols; k++) { // loops through current columns, adds temp[count] the product of one and two
				for(int l = 0; l < static_cast<int>(M.myMatrix->size()); l++) { //loops through M matrix
					if((M.myMatrix->at(l).getRow() == k) && (M.myMatrix->at(l).getCol() == j)) {
						one = M.myMatrix->at(l).getValue();// when matched, sets one to that value
					}
				}
				for(int l = 0; l < static_cast<int>(myMatrix->size()); l++) { // loops through current matrix
					if((myMatrix->at(l).getRow() == i) && (myMatrix->at(l).getCol() == k)) {
						two = myMatrix->at(l).getValue();//when matched, sets two to that value
					}
				}
				temp[count] += (one * two);
				one = 0;
				two = 0;
			}
			count++;// for moving through the indexs of temp
		}
	}
	int x;
	int counter = 0;
	int tempcounter = 0;
	for(int i = 0; i < noRows; i++) {//loops through current rows
		for(int j = 0; j < M.noCols; j++) {//loops through M columns
			x = temp[tempcounter];
			if(x != commonValue) {
				(*tempMatrix).setSparseRow(counter, i, j, x);
				counter++;
			}
			tempcounter++;
		}
	}
	delete [] temp;
	return (tempMatrix);
}
/*
 * puts a specific number of elements into matrix
 */
template <class DT>
void SparseMatrix<DT>::sparseAdd(){
	//loops and adds to mymatrix
	for(int i = 0; i < (noRows * noCols); i++) {
		myMatrix->push_back(* new SparseRow<DT>());
	}
}
/*
 * takes in a sparseMatrix and takes input from user to set the rows in it
 */
template <class DT>
void SparseMatrix<DT>::read(SparseMatrix<DT> M, int n, int m, int v){
	int x;
	int count = 0;
	for(int i = 0; i < n; i++) {//loops through rows
		for(int j = 0; j < m; j++) {//loops through columns
			cin >> x;
			if(x != v) {
				M.setSparseRow(count, i, j, x); //sets the sparseRow
				count++;
			}
		}
	}
}
/*
 * constructor for sparseMatrix, sets rows, columsn, common value, size, and mymatrix
 */
template <class DT>
SparseMatrix<DT>::SparseMatrix(int n, int m, int cv) {
	noRows = n;
	noCols = m;
	commonValue = cv;
	size = 0;
	myMatrix = new vector<SparseRow<DT>>();//dynamic
}

/*
 * empty constructor sets all zero
 */
template <class DT>
SparseMatrix<DT>::SparseMatrix() {
	noRows = 0;
	noCols = 0;
	commonValue = 0;
	size = 0;
	myMatrix =  new vector<SparseRow<DT>>();
}

/*
 * destructor
 */
template <class DT>
SparseMatrix<DT>::~SparseMatrix() {}

/*
 * adds an element of sparseRows to mymatrix and sets that sparseRows values
 */
template <class DT>
void SparseMatrix<DT>::setSparseRow(int pos, int r, int c, DT& v) {
	myMatrix->push_back(SparseRow<DT>());
	myMatrix->at(pos).setRow(r);
	myMatrix->at(pos).setCol(c);
	myMatrix->at(pos).setValue(v);
	size++;//for addition
}

/*
 * displays matrix
 */
template <class DT>
void SparseMatrix<DT>::display() {
	//loops through and calls each element of sparseRow display function
	for(int i = 0; i < static_cast<int>(myMatrix->size()); i++) {
		myMatrix->at(i).display();
	}
}

/*
 * displays matrix in normal matrix format
 */
template <class DT>
void SparseMatrix<DT>::displayMatrix() {
	bool test;
	int point;
	for(int i = 0; i < noRows; i++) {//loops through rows
		for(int j = 0; j < noCols; j++) {//loops through columns
			for(int k = 0; k < static_cast<int>(myMatrix->size()); k++) {//loops through mymatrix
				if (myMatrix->at(k).getRow() == i && myMatrix->at(k).getCol() ==j) {
					test = true;
					point = myMatrix->at(k).getValue();
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
int main() {
	int
	n, m, cv;
	SparseMatrix<int>* temp;
	cin >> n >> m >> cv;
	SparseMatrix<int>* firstOne = new SparseMatrix<int>(n, m, cv);
	(*firstOne).read(*firstOne, n, m, cv);
	cout << "First one in sparse matrix format" << endl;
	cout << firstOne;
	cout << "First one in normal matrix format" << endl;
	(*firstOne).displayMatrix();
	cin >> n >> m >> cv;
	SparseMatrix<int>* secondOne = new SparseMatrix<int>(n, m, cv);
	(*secondOne).read(*secondOne, n, m, cv);
	cout << "Second one in sparse matrix format" << endl;
	cout << secondOne;
	cout << "Second one in normal matrix format" << endl;
	(*secondOne).displayMatrix();
	temp = !(*firstOne);
	cout << "After Transpose first one in normal format" << endl;
	(*temp).displayMatrix();
	temp = !(*secondOne);
	cout << "After Transpose second one in normal format" << endl;
	(*temp).displayMatrix();
	cout << "Multiplication of matrices in sparse matrix form:" << endl;
	temp = (*secondOne) * (*firstOne);
	cout << temp;
	cout << "Addition of matrices in sparse matrix form:" << endl;
	temp = (*secondOne) + (*firstOne);
	cout << temp;
	delete firstOne;
	delete secondOne;
	delete temp;
	return 0;
}
