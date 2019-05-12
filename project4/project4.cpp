//============================================================================
// Name        : project4.cpp
// Author      : Nigel Mansell
// Version     :
// Copyright   : Your copyright notice
// Description : Project 4 in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

/***
 * Tree class holds a parent array, along with variables for number of nodes and dealing with the preoder function.
 ***/
class Tree {
protected:
	int *parentArray; //int array used to construct tree
	int numNodes; // for the size of the array
	int x; // used for preorder function to keep track of place in tree.
public:
	Tree(); //  Default constructor
	Tree(int numNodes); // Non-default constructor
	~Tree(); // Destructor
	Tree(const Tree& T); // Copy constructor
	/***
	 * Overloaded << operator to print the array.
	 ***/
	friend ostream& operator << (ostream &out, Tree T){
		T.display();
		return out;
	}
	void setParent(int node, int parent); // Sets the parent by using node as index and parent as index's element.
	void setRoot(int root); // Sets the root by going to parameter values index in the array and setting its element to -1
	void display(); // Displays in the style shown in the output example
	int Root(); // Gets the root of the tree.
	int LCA(int nodeA, int nodeB); // Least Common Ancestor takes in two values and give the LCA of those two.
	void Children(int node); // Gets the children of the parameter value.
	void Siblings(int node); // Gets the siblings of the parameter value.
	void nodesAtLevel(int level); // Gets all nodes and the level specified.
	int height(); // Returns the height of the tree.
	int level(int node); // Returns the level of the given node.
	int Parent(int node); // Returns the parent of the given node.
	void Preorder(); // Displays the preorder traversal of the tree based on the parent array.
	void setX(int num); // Sets the variable x.
};
Tree::Tree() {
	numNodes = 0;
	parentArray = new int[0];
	x = 0;
}
Tree::Tree(int nuNodes) {
	numNodes = nuNodes;
	parentArray = new int[numNodes];
	x = 0;
}
Tree::Tree(const Tree& T) {
	numNodes = T.numNodes;
	parentArray = T.parentArray;
	x = 0;
}
Tree::~Tree() {
	//delete []parentArray;
}
void Tree::setParent(int node, int parent) {
	parentArray[node] = parent;
}
void Tree::setRoot(int root) {
	parentArray[root] = -1;
}
void Tree::display() {
	for(int i = 0; i < numNodes; i++) { // Loops through the array for outputting.
		cout << i <<": "<< parentArray[i]<<"  ";
	}
}
int Tree::Root() {
	int found;
	for(int i = 0; i < numNodes; i++) { // Loops through the array
		if(parentArray[i] == -1) {
			found = i;
		}
	}
	this->setX(found);
	return found;
}
int Tree::LCA(int nodeA, int nodeB) {
	int found = nodeA;
	while (parentArray[nodeA] != -1) { // continues until indexes element does not equal -1.
		found = parentArray[nodeA];
		if(parentArray[nodeA] == nodeB) {
			break;
		}
		else if(parentArray[nodeA] == parentArray[nodeB]) {
			break;
		}
		nodeA = parentArray[nodeA];
	}
	return found;
}
void Tree::Children(int node) {
	for(int i = 0; i < numNodes; i++) { // Loops through the array.
		if(this->Parent(i) == node) {
			cout << i << " ";
		}
		if(i == numNodes-1) {
			cout << endl;
		}
	}
}
void Tree::Siblings(int node) {
	for(int i = 0; i < numNodes; i++) { // Loops through the array.
		if(i == node) {
			continue;
		}
		else if(parentArray[i] == parentArray[node]) {
			cout << i << " ";
		}
		if(i == numNodes-1) {
			cout << endl;
		}
	}
}
void Tree::nodesAtLevel(int level) {
	int count;
	int temp;
	for(int i = 0; i< numNodes; i++) { // Loops through the array.
		count = 1;
		temp = i;
		while(parentArray[temp] != -1) { // Continues until indexes element does not equal -1
			count++;
			temp = parentArray[temp];
		}
		if(count == level) {
			cout << i << " ";
		}
	}
	cout << endl;
}
int Tree::height() {
	int level;
	int height = 1;
	int temp;
	for(int i = 0; i < numNodes; i++) { // Loops through the array.
		level = 1;
		temp = i;
		while(parentArray[temp] != -1) { // Continues until indexes element does not equal -1
			level++;
			temp = parentArray[temp];
		}
		if(level > height) {
			height = level;
		}
	}
	return height;
}
int Tree::level(int node) {
	int level = 1;
	while(parentArray[node] != -1) { // Continues until indexes element does not equal -1
		level++;
		node = parentArray[node];
	}
	return level;
}
void Tree::setX(int num){
	x = num;
}
int Tree::Parent(int node) {
	return parentArray[node];
}
void Tree::Preorder() {
	if(parentArray[x] == -1) {
		cout << x << " ";
	}
	for(int i = 0; i < numNodes; i++) { // Loops through the array.
		if(parentArray[i] == x) {
			cout << i << " ";
			this->setX(i);
			this->Preorder(); // Recursive call
		}
	}
	this->setX(parentArray[x]);
}
int main() {
	Tree *myTree;
	int numNodes, node, parent;
	cin >> numNodes;
	myTree = new Tree(numNodes);
	for(int i = 0; i < numNodes; i++) {
		cin >> node >> parent;
		(*myTree).setParent(node, parent);
		if(parent == -1) {
			(*myTree).setRoot(node);
		}
	}
	cout << "The tree that we just read is:" << endl;
	cout << *myTree << endl;

	Tree* newTree = new Tree(*myTree);
	cout << "The tree that we just copied is:" << endl;
	cout << *newTree << endl;

	cout << "The root of the tree is: " << (*myTree).Root() << endl;

	cout << "The least common ancestor of nodes 3 and 8 is: " << (*newTree).LCA(3,8) << endl;
	cout << "The least common ancestor of nodes 13 and 8 is: " << (*newTree).LCA (13,8) << endl;
	cout << "The least common ancestor of nodes 13 and 11 is: " << (*myTree).LCA (13,11) << endl;
	cout<< "The children of node 12 is/are: "<< endl;
	(*myTree).Children (12);
	cout << "The children of node 10 is/are: "<< endl;
	(*myTree).Children (10);
	cout << "The siblings of node 3 is/are: "<< endl;
	(*myTree).Siblings (3);
	cout << "The siblings of node 12 is/are: "<< endl;
	(*myTree).Siblings (12);
	cout << "The nodes at level 3 is/are: "<< endl;
	(*myTree).nodesAtLevel (3);
	cout << "The height of the tree is: " << (*myTree).height() << endl;
	cout << "The level of node 3 in the tree is: " << (*myTree).level(3) << endl;
	cout << "The level of node 12 in the tree is: " << (*myTree).level(12) << endl;
	cout << "The preorder traversal of the tree is/are:	"<<	endl;
	(*myTree).Preorder();
	cout << endl;

	delete myTree;
	//delete newTree;
	return 0;
}
