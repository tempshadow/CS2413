//============================================================================
// Name        : project3.cpp
// Author      : Nigel Mansell 113208927
// Version     :
// Copyright   :
// Description : Project3 in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
/*
 * exceptions
 */
template<class DT>
class LinkedListAttachedToEmpty{};
template<class DT>
class LinkedListMemory{};
template<class DT>
class LinkedListBounds{};

//Linkedlist class taken from the book
template<class DT>
class Linkedlist {
protected:
	DT* _info;
	Linkedlist<DT>* _next;
public:
	Linkedlist();//blank constructor
	Linkedlist(const DT& info);//initialize info
	Linkedlist(const DT& info, Linkedlist<DT>* next);//initialize both info and next
	~Linkedlist();//destructor
	void copy(const Linkedlist<DT>& ll);//copy function
	Linkedlist(const Linkedlist<DT>&ll);//copy constructor
	void operator=(const Linkedlist<DT>& ll);//overloaded equals
	bool isEmpty();//checks is list is empty
	DT info();//gets info
	Linkedlist<DT>* next();//gets next
	int size();//gets size
	DT& infoAt(int position);//gets info at position
	void add(const DT& object);//adds to list
	void insertAt(const DT& obj, int position);//inserts at list
	DT remove();//removes
	DT removeAt(int position);//removes at position
	DT& operator[](int position);//overloads square brackets
	void display();//displays
	void setNext(Linkedlist<DT>* next);//sets the next


};

template<class DT>
void Linkedlist<DT>::setNext(Linkedlist<DT>*next) {
	if(isEmpty()) throw LinkedListAttachedToEmpty<int>();
	_next = (Linkedlist<DT>*) next;
}
template <class DT>
Linkedlist<DT>::Linkedlist() {
	_info = NULL;
	_next = NULL;
}
template <class DT>
Linkedlist<DT>::Linkedlist(const DT& info) {
	_info = new DT(info);
	if (_info == NULL) throw LinkedListMemory<int>();
	_next = NULL;
}

template <class DT>
Linkedlist<DT>::Linkedlist(const DT&info, Linkedlist<DT>* next) {
	_info = new DT(info);
	if(_info == NULL) throw LinkedListMemory<int>();
	_next = next;
}
template<class DT>
Linkedlist<DT>::~Linkedlist(){
	if (_info != NULL) {
		delete _info;
		_info = NULL;
	}
	if (_next != NULL) {
		delete _next;
		_next = NULL;
	}
}
template<class DT>
void Linkedlist<DT>::copy(const Linkedlist<DT>& ll) {
	if(ll._info == NULL) _info = NULL;
	else{
		_info = new DT(*(_info));
		if(_info == NULL) throw LinkedListMemory<int>();
	}
	if (ll._next == NULL) _next = NULL;
	else {
		_next = new Linkedlist<DT>(*(ll._next));
		if (_next == NULL) throw LinkedListMemory<int>();
	}
}
template<class DT>
Linkedlist<DT>::Linkedlist(const Linkedlist<DT>& ll){
	if(ll._info == NULL) _info = NULL;
		else{
			_info = new DT(*(_info));
			if(_info == NULL) throw LinkedListMemory<int>();
		}
		if (ll._next == NULL) _next = NULL;
		else {
			_next = new Linkedlist<DT>(*(ll._next));
			if (_next == NULL) throw LinkedListMemory<int>();
		}
}
template<class DT>
void Linkedlist<DT>::operator =(const Linkedlist<DT>&ll) {
	if(_info != NULL) delete _info;
	if(_next != NULL) delete _next;
	copy(ll);
}
template<class DT>
bool Linkedlist<DT>::isEmpty() {
	return (_info == NULL);
}
template<class DT>
DT Linkedlist<DT>::info(){
	if (isEmpty()) throw LinkedListBounds<int>();
	return *_info;
}
template<class DT>
Linkedlist<DT>* Linkedlist<DT>::next(){
	return _next;
}
template<class DT>
int Linkedlist<DT>::size(){
	if(_next == NULL){
		if(_info == NULL) return 0;
		else return 1;
	}
	else return 1 + _next->size();
}
template<class DT>
DT& Linkedlist<DT>::infoAt(int position){
	if(isEmpty()) throw LinkedListBounds<int>();
	if(position == 0) {return *_info;}
	if(_next == NULL)throw LinkedListBounds<int>();
	return _next->infoAt(position -1);
}
template<class DT>
void Linkedlist<DT>::add(const DT& object){
	if(_info == NULL) {
		_info = new DT(object);
	}
	else {
		Linkedlist<DT>* newList = new Linkedlist<DT>(*_info, _next);
		if(newList == NULL) throw LinkedListMemory<int>();
		*_info = object;
		_next = newList;
	}
}
template<class DT>
void Linkedlist<DT>::insertAt(const DT& obj, int position){
	if(position ==0) add(obj);
	else{
		if(_next == NULL){
			_next = new Linkedlist(obj);
			if(_next == NULL)throw LinkedListMemory<int>();
		}
		else{
			_next->insertAt(obj, position -1);
		}
	}
}
template<class DT>
DT Linkedlist<DT>::remove() {
	if(isEmpty())throw LinkedListBounds<int>();
	DT temp = *_info;
	delete _info;
	if(_next == NULL){_info == NULL;}
	else{
		Linkedlist<DT>* oldnext = _next;
		_info = _next->_info;
		_next = _next->_next;
		oldnext->_info = NULL;
		oldnext->_next = NULL;
		delete oldnext;
	}
	return temp;
}
template<class DT>
DT Linkedlist<DT>::removeAt(int position){
	if(isEmpty())throw LinkedListBounds<int>();
	if(position == 0){return remove();}
	if(_next == NULL)throw LinkedListBounds<int>();
	return _next->removeAt(position -1);
}
template<class DT>
DT& Linkedlist<DT>::operator [](int position){
	return infoAt(position);
}

//Term class has a coefficient and exponent, getters and setters.
class Term {
protected:
	int coefficient;
	int exponent;
public:
	Term();//empty constructor
	Term(int c, int e);//initializes both
	int getCoefficient();//gets coefficient
	void setCoefficient(int c);//sets coefficient
	int getExponent();//gets exponent
	void setExponent(int e);//sets exponent
	void display();//displays
};
Term::Term() {
	coefficient = 0;
	exponent = 0;
}
Term::Term(int c, int e) {
	coefficient = c;
	exponent = e;
}
int Term::getCoefficient(){
	return coefficient;
}
void Term::setCoefficient(int c){
	coefficient = c;
}
int Term::getExponent(){
	return exponent;
}
void Term::setExponent(int e) {
	exponent = e;
}
void Term::display() {
	cout << "(" << coefficient << "," << exponent << ")";
}
//polynomial class has a linked list and does various functions
class Polynomial {
protected:
	Linkedlist<Term>* myPoly;
public:
	Polynomial();//constructor
	void addTerm(int coefficient,int exponent);//adds a term to linked list
	void printPolynomial();//prints the linked list
	//overloads << and calls function
	friend ostream& operator << (ostream &out, Polynomial P){
		P.printPolynomial();
		return out;
	}
	void evaluatePoly(int x);//evaluates based on input
	void deleteTerm(int exponent);//sets coefficient to 0
	bool test(int exponent);
	void addPolynomial(Polynomial P);//adds two polynomials linked lists together
	void multiplyPolynomial(Polynomial P);//multiplies two polynomial linked list together
	void operator+(Polynomial P);//overloaded + calls addPolynomial
	void operator*(Polynomial P);//overloaded * calls multiplyPolynomail
};
void Polynomial::operator*(Polynomial P) {
	multiplyPolynomial(P);
}
void Polynomial::operator+(Polynomial P) {
	addPolynomial(P);
	cout << endl;
}
bool Polynomial::test(int exponent) {
	int count = 0;
	for(int i = 0; i < myPoly->size(); i++) {//loops through this linked list
		if((*myPoly)[i].getExponent() != exponent) {
			count +=1;
		}
	}
	if(count == myPoly->size()) {
		return false;
	}
	else {
		return true;
	}
}
void Polynomial::multiplyPolynomial(Polynomial p) {
	Polynomial *temp = new Polynomial();
	for(int i = 0; i < myPoly->size();i++) {
		for(int k = 0; k < p.myPoly->size(); k++) {
			temp->addTerm(myPoly->infoAt(i).getCoefficient()* (p.myPoly->infoAt(k).getCoefficient()), myPoly->infoAt(i).getExponent() + (p.myPoly->infoAt(k).getExponent()));
		}
	}
	temp->printPolynomial();
	cout << endl;
}
void Polynomial::addPolynomial(Polynomial P) {
	Polynomial *temp = new Polynomial();
	for(int i = 0; i < P.myPoly->size(); i++) {
		temp->addTerm(P.myPoly->infoAt(i).getCoefficient(), P.myPoly->infoAt(i).getExponent());
	}
	for(int i = 0; i < myPoly->size(); i++) {
		temp->addTerm(myPoly->infoAt(i).getCoefficient(), myPoly->infoAt(i).getExponent());
		}
	temp->printPolynomial();
	cout << endl;
}
void Polynomial::deleteTerm(int exponent) {
	for(int i = 0; i < myPoly->size(); i++) {//loops through this linked list
		if((*myPoly)[i].getExponent() == exponent) {
			(*myPoly)[i].setCoefficient(0);
		}
	}
}
void Polynomial::evaluatePoly(int x) {
	int result = 0;
	for(int i = 0; i < myPoly->size(); i++) {//loops through this linked list
		int temp = 1;
		for(int j = 0; j < (*myPoly)[i].getExponent(); j++) {
			temp *= x;
		}
		result +=(temp * (*myPoly)[i].getCoefficient());
	}
	cout << result << endl;
}
void Polynomial::printPolynomial() {
	for(int i = 0; i < myPoly->size(); i++) {//loops through this linked list
		if(i == myPoly->size()-1) {
			(*myPoly)[i].display();
		}
		else {
			(*myPoly)[i].display();
			cout << " + ";
		}
	}
}
Polynomial::Polynomial(){
	myPoly = new Linkedlist<Term>();
}
void Polynomial::addTerm(int coefficient, int exponent) {
	Term* temp = new Term(coefficient, exponent);
	bool test = false;
	for(int i = 0; i < myPoly->size();i++) {//loops through this linkedlist
		if((*myPoly)[i].getExponent() == exponent) {
			test = true;
			int tempCoe = (*myPoly)[i].getCoefficient();
			(*myPoly)[i].setCoefficient(tempCoe + coefficient);

		}
	}
	if(test == false) {
		if(myPoly->size() == 0){
			myPoly->add(*temp);
		}
		else{
			for(int i = 0; i < myPoly->size(); i++) {//loops through this linkedlist
				if ((*myPoly)[i].getExponent() > exponent) {
					if(i == myPoly->size()-1) {
						myPoly->insertAt(*temp, i+1);
						break;
					}
					continue;

				}
				else {
					myPoly->insertAt(*temp, i);
					break;
				}
			}
		}
	}
}
int main() {
	Polynomial *Polynomials = new Polynomial[10];
	char command;
	int polynum, coefficient, exponent;
	int i, j;
	int value;
	cin >> command;
	while(!cin.eof()) {
		switch(command) {
		case 'I' : cin >> polynum >> coefficient >> exponent;
		if(polynum > 9) {
			cout << "Failed to add polynomial: Polynomial of choice must be 0 - 9" << endl;
		}
		else if(polynum < 0) {
			cout << "Failed to add polynomial: Polynomial of choice must be 0 - 9" << endl;
		}
		else {
			Polynomials[polynum].addTerm(coefficient, exponent);
			cout << "successfully added to Polynomial " << polynum;
			cout << endl;
		}
		break;
		case 'D': cin >> polynum >> coefficient >> exponent;
		if(polynum > 9) {
			cout << "Failed to delete: Polynomial of choice must be 0-9" << endl;
		}
		else if (polynum < 0) {
			cout << "Failed to delete: Polynomial of choice must be 0-9" << endl;
		}
		else {
			if(Polynomials[polynum].test(exponent) == true) {
				Polynomials[polynum].deleteTerm(exponent);
				cout << "delete successful" << endl;
			}
			else {
				cout << "there is no term in polynomial " << polynum <<" with an exponent of 0";
				cout << endl;
			}
		}
		break;
		case 'A': cin >> i >> j;
		if((i < 0) | (j < 0) ) {
			cout << "Addition failed: Both inputs must be 0-9" << endl;
		}
		else if((i > 9) | (j > 9)) {
			cout << "Addition failed: Both inputs must be 0-9" << endl;
		}
		else{
			Polynomials[i]+Polynomials[j];
		}
		break;
		case 'M' : cin >> i >> j;
		if((i < 0) | (j < 0) ) {
			cout << "Multiplication failed: Both inputs must be 0-9" << endl;
		}
		else if((i > 9) | (j > 9)) {
			cout << "Multiplication failed: Both inputs must be 0-9" << endl;
		}
		else {
			Polynomials[i]*Polynomials[j];
		}
		break;
		case 'E': cin >> polynum >> value;
		if(polynum > 9) {
			cout << "Evaluation failed: Polynomial of choice must be 0-9" << endl;
		}
		else if(polynum < 0) {
			cout << "Evaluation failed: Polynomial of choice must be 0-9" << endl;
		}
		else {
			Polynomials[polynum].evaluatePoly(value);
		}
		break;
		case 'P': cin >> polynum;
		if(polynum > 9) {
			cout << "Failed to print: Polynomial of choice must be 0-9" << endl;
		}
		else if (polynum < 0) {
			cout << "Failed to print: Polynomial of choice must be 0-9" << endl;
		}
		else{
			cout << "Polynomial " << polynum << ": ";
			cout << Polynomials[polynum];
			cout << endl;
		}
		break;
		default: cout << "I missed something" << endl;
		}
		cin >> command;
	}
	return 0;
}
