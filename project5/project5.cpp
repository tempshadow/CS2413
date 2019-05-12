//============================================================================
// Name        : project5.cpp
// Author      : Nigel Mansell
// Version     :
// Copyright   : Your copyright notice
// Description : Project 5 in C++, Ansi-style
//============================================================================

#include <iostream>
#include <list>
#include <queue>
using namespace std;
//Matrix class is an array of arrays that hold 1 where there is an edge
class AdjacencyMatrixGraph {
protected:
	int **matrix; // for everything but displaying the graph
	int **outMatrix; // for displaying the graph
	int numNodes;
	int *parentArray;
public:
	AdjacencyMatrixGraph();//empty constructor
	AdjacencyMatrixGraph(int numNodes);//constructor
	AdjacencyMatrixGraph(const AdjacencyMatrixGraph &G);//copy constructor
	~AdjacencyMatrixGraph();//destructor
	friend ostream& operator << (ostream &out, AdjacencyMatrixGraph G){ //overloaded out
		G.display();
		return out;
	}
	void AddEdge(int u, int v); //adds an edge to the graph
	void operator=(const AdjacencyMatrixGraph & G); //overloaded = operator for copy
	void display(); //displays the graph
	void breadthFirstSearch(int u); //fills the parent array based on breadth first traversal
	list<int> neighbors(int v); // finds the neighbors of the node
	void DFS(int u); //creates an empty bool array for depth first traversal and passes it
	void depthFirstSearch(int u, bool discovered[]); // fills the parent array based on depth first traversal
	int size(); //gets the size of the list
	void displayParent(); //displays the parent array
	void setRoot(int r); // sets the root
};
AdjacencyMatrixGraph::AdjacencyMatrixGraph() {
	numNodes = 0;
	matrix = new int*[numNodes];
	for(int i = 0; i < numNodes; i++) {//loops through and makes the matrix
		matrix[i] = new int[numNodes];
	}
	outMatrix = new int*[numNodes];
	for(int i = 0; i < numNodes; i++) { //loops through and makes the matrix
		outMatrix[i] = new int[numNodes];
	}
	parentArray = new int[numNodes];
}

AdjacencyMatrixGraph::AdjacencyMatrixGraph(int num) {
	numNodes = num;
	matrix = new int*[numNodes];
	for(int i = 0; i < numNodes; i++) { // makes the matrix
		matrix[i] = new int[numNodes];
	}
	for(int i = 0; i < numNodes; i++) { // these loops fill the graph with zeros
		for(int j = 0; j < numNodes; j++) {
			matrix[i][j] = 0;
		}
	}
	outMatrix = new int*[numNodes];
	for(int i = 0; i < numNodes; i++) { // same as above for a different matrix
		outMatrix[i] = new int[numNodes];
	}
	for(int i = 0; i < numNodes; i++) {
		for(int j = 0; j < numNodes; j++) {
			outMatrix[i][j] = 0;
		}
	}
	parentArray = new int[numNodes];
}
AdjacencyMatrixGraph::~AdjacencyMatrixGraph() {
	for(int i = 0; i < numNodes; i++) { // loops and deletes each array within the array
		delete [] matrix[i];
	}
	delete [] matrix;
}

AdjacencyMatrixGraph::AdjacencyMatrixGraph(const AdjacencyMatrixGraph &G) {
	numNodes = G.numNodes;
	matrix = G.matrix;
	parentArray = G.parentArray;
	outMatrix = G.outMatrix;
}

void AdjacencyMatrixGraph::displayParent() {
	for(int i = 0; i < numNodes; i++) { // loops and displays
		cout << i << ":" << parentArray[i] << " ";
	}
}
void AdjacencyMatrixGraph::AddEdge(int u, int v) {
	outMatrix[u][v] = 1;
	matrix[u][v] = 1;
	matrix[v][u] = 1;
}
void AdjacencyMatrixGraph::operator =(const AdjacencyMatrixGraph & G) {
	numNodes = G.numNodes;
	matrix = G.matrix;
	outMatrix = G.outMatrix;
	parentArray = G.parentArray;
}
void AdjacencyMatrixGraph::setRoot(int r) {
	parentArray[r] = -1;
}
void AdjacencyMatrixGraph::display() {
	int count = 0;
	int counter = 0;
	for(int i = 0; i < numNodes; i++) { // these two loops are for getting the number of edges
		for(int j = 0; j < numNodes; j++) {
			if(outMatrix[i][j] == 1) {
				count++;
			}
		}
	}
	for(int i = 0; i < numNodes; i++) { //these loops are for displaying
		for(int j = 0; j < numNodes; j++) {
			if(outMatrix[i][j] == 1) {
				counter++;
				if(counter == count) {
					cout << "(" << i << ", " << j << ")" << endl;
				}
				else {
					cout << "(" << i << ", " << j << "), ";
				}
			}
		}
	}
}
int AdjacencyMatrixGraph::size() {
	return numNodes;
}
list<int> AdjacencyMatrixGraph::neighbors(int v) {
	list<int> r;
	if((v < 0)||( v >= numNodes)) return r;
	for(int i = 0; i < numNodes; i++) {// loops and adds nodes neighbor in a list
		if(matrix[v][i] != 0) r.push_back(i);
	}
	return r;
}
void AdjacencyMatrixGraph::breadthFirstSearch(int u) {
	parentArray[u] = -1;
	bool *visited = new bool[numNodes];
	int v;
	list<int> nbors;
	for(int i = 0; i < numNodes; i++) { // fills visited with false
		visited[i] = false;
	}
	queue<int> *Q = new queue<int>[numNodes];
	visited[u] = true;
	Q->push(u);
	while(!Q->empty()) { // loops while queue isnt empty
		v = Q->front();
		Q->pop();
		nbors = neighbors(v);
		for(list<int>::iterator it = nbors.begin(); it != nbors.end(); it++) { // iterator loops through each node of nbors
			if(!visited[*it]) {
				parentArray[*it] = v;
				visited[*it] = true;
				Q->push(*it);
			}
		}
	}
	for(int i = 0; i < numNodes; i++) { // loops and displays
		cout << i << ":" << parentArray[i] << " ";
	}
}

void AdjacencyMatrixGraph::depthFirstSearch(int u, bool discovered[]) {
	discovered[u] = true;
	list<int> nbors;
	nbors = neighbors(u);
	for(list<int>::iterator it = nbors.begin(); it != nbors.end(); it++) {//iterator for each node of nbors
		if(!discovered[*it]) {
			parentArray[*it] = u;
			depthFirstSearch(*it, discovered); // recursive call
		}
	}
}
void AdjacencyMatrixGraph::DFS(int u) {
	setRoot(u);
	bool *temp = new bool[numNodes];
	for(int i = 0; i < numNodes; i++) { // fills temp with false
		temp[i] = false;
	}
	depthFirstSearch(u, temp);
	displayParent();
	cout << endl;
}
// This class is an array of lists
class AdjacencyListGraph {
protected:
	list<int> *lArray; // for everything but displaying the graph
	list<int> *out; // for displaying the graph
	int numNodes;
	int *parentArray;
public:
	AdjacencyListGraph(); // empty constructor
	AdjacencyListGraph(int num); // constructor
	AdjacencyListGraph(const AdjacencyListGraph &G); // copy constructor
	~AdjacencyListGraph(); // destructor
	friend ostream& operator << (ostream &out, AdjacencyListGraph G){ // overloaded out
		G.display();
		return out;
	}
	void operator=(const AdjacencyListGraph &G); // overloaded = operator does copy
	void AddEdge(int u, int v); // adds edge
	list<int> neighbors(int v); // gets the neighbor of node
	void breadthFirstSearch(int u); // displays the parent array given the breadth first traversal
	void display(); // displays the graph
	void depthFirstSearch(int u, bool discover[]); //fills a parent array with the depth first traversal
	void listArraySort(); // sorts the each list within the array
	int size(); // gets the size of each list within the array
	void displayParent(); // displays the parent array
	void setRoot(int r); // sets the root
	void DFS(int u); // fills a bool array with false, calls depth first search and outputs parent array
};
AdjacencyListGraph::AdjacencyListGraph() {
	numNodes = 0;
	lArray = new list<int>[0];
	out = new list<int>[0];
	parentArray = new int[0];
}
AdjacencyListGraph::AdjacencyListGraph(int num) {
	numNodes = num;
	lArray = new list<int>[numNodes];
	out = new list<int>[numNodes];
	parentArray = new int[numNodes];
}
AdjacencyListGraph::AdjacencyListGraph(const AdjacencyListGraph &G){
	numNodes = G.numNodes;
	lArray = G.lArray;
	out = G.out;
	parentArray = G.parentArray;
}
AdjacencyListGraph::~AdjacencyListGraph() {

}
void AdjacencyListGraph::operator =(const AdjacencyListGraph &G) {
	numNodes = G.numNodes;
	lArray = G.lArray;
	out = G.out;
	parentArray = G.parentArray;
}
void AdjacencyListGraph::AddEdge(int u, int v) {
	out[u].push_back(v);
	lArray[u].push_back(v);
	lArray[v].push_back(u);
}
void AdjacencyListGraph::listArraySort() {
	for(int i = 0; i < numNodes; i++) { // loops and sorts, gets rid of duplicates if there are any
		lArray[i].sort();
		lArray[i].unique();
		out[i].sort();
		out[i].unique();
	}
}
list<int> AdjacencyListGraph::neighbors(int v) {
	list<int> r;
	if((v < 0)||( v >= numNodes)) return r;
	for(list<int>::iterator it = lArray[v].begin(); it != lArray[v].end(); it++) { // iterator gets the neighbors of the node
		if(*it != 0) r.push_back(*it);
	}return r;
}
void AdjacencyListGraph::depthFirstSearch(int u, bool discover[]) {
	discover[u] = true;
	list<int> nbors;
	nbors = neighbors(u);
	for(list<int>::iterator it = nbors.begin(); it != nbors.end(); it++) { //iterator gets each node of nbors
		if(!discover[*it]) {
			parentArray[*it] = u;
			depthFirstSearch(*it, discover);
		}
	}
}
void AdjacencyListGraph::DFS(int u) {
	setRoot(u);
	bool *temp = new bool[numNodes];
	for(int i = 0; i < numNodes; i++) { // fills temp with false
		temp[i] = false;
	}
	depthFirstSearch(u, temp);
	displayParent();
}
void AdjacencyListGraph::breadthFirstSearch(int u) {
	parentArray[u] = -1;
	bool *visited = new bool[numNodes];
	int v;
	list<int> nbors;
	for(int i = 0; i < numNodes; i++) { // fills visited with false
		visited[i] = false;
	}
	queue<int> *Q = new queue<int>[numNodes];
	visited[u] = true;
	Q->push(u);
	while(!Q->empty()) { // loops while queue isnt empty
		v = Q->front();
		Q->pop();
		nbors = neighbors(v);
		for(list<int>::iterator it = nbors.begin(); it != nbors.end(); it++) { // iterator for each node of nbors
			if(!visited[*it]) {
				parentArray[*it] = v;
				visited[*it] = true;
				Q->push(*it);
			}
		}
	}
	for(int i = 0; i < numNodes; i++) { // loops and displays
		cout << i << ":" << parentArray[i] << " ";
	}
}
void AdjacencyListGraph::display() {
	int counter = 0;
	for(int i = 0; i < numNodes; i++) { // these loops get each node for displaying edges
		for(list<int>::iterator it = out[i].begin(); it != out[i].end(); it++) {
			if(i == numNodes-1) {
				counter++;
				if(counter == static_cast<int>(out[i].size())) {
					cout << "(" << i << ", " << *it << ")" << endl;
				}
				else {
					cout << "(" << i << ", " << *it << "), ";
				}
			}
			else {
				cout << "(" << i << ", " << *it << "), ";
			}
		}
	}
}
int AdjacencyListGraph::size() {
	return numNodes;
}
void AdjacencyListGraph::displayParent() {
	for(int i = 0; i < numNodes; i++) { // loops and displays
		cout << i << ":" << parentArray[i] << " ";
	}
}
void AdjacencyListGraph::setRoot(int r) {
	parentArray[r] = -1;
}
int main() {
	int numNodes, u, v;
	cin >> numNodes;
	AdjacencyMatrixGraph *Matrix = new AdjacencyMatrixGraph(numNodes);
	AdjacencyListGraph *List = new AdjacencyListGraph(numNodes);
	while(!cin.eof()) { // gets input for edge to add
		cin >> u >> v;
		Matrix->AddEdge(u, v);
		List->AddEdge(u, v);
	}
	List->listArraySort();
	cout << "The adjacency matrix that we just read in is: " << endl;
	cout << *Matrix << endl;
	cout << "The adjacency list that we just read in is: " << endl;
	cout << *List << endl;
	AdjacencyMatrixGraph *copyM = new AdjacencyMatrixGraph(*Matrix);
	cout << "The copy of adjacency matrix without overloaded = " << endl;
	cout << *copyM << endl;
	AdjacencyMatrixGraph *overloadedM;
	overloadedM = Matrix;
	cout << "The copy of adjacency matrix with overloaded = " << endl;
	cout << *overloadedM;
	AdjacencyListGraph *copyL = new AdjacencyListGraph(*List);
	cout << "The copy of adjacency list without overloaded = " << endl;
	cout << *copyL;
	AdjacencyListGraph *overloadedL;
	overloadedL = List;
	cout << "The copy of adjacency list with overloaded = " << endl;
	cout << *overloadedL;
	cout << "BFS(0) Matrix Graph" << endl;
	Matrix->breadthFirstSearch(0);
	cout << endl;
	cout << "BFS(0) List Graph" << endl;
	List->breadthFirstSearch(0);
	cout << endl;
	cout << "DFS(0) Matrix Graph" << endl;
	Matrix->DFS(0);
	cout << "DFS(0) List Graph" << endl;
	List->DFS(0);
	return 0;
}
