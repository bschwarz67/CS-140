#include "dlist.h"
using namespace std;

/* create new double linked list */
Dlist::Dlist() {
	/*create sentinel node*/
	sentinel = new Dnode();
	
	/*initialize links to point to self in order so that list is double linked*/
	sentinel->flink = sentinel;
	sentinel->blink = sentinel;
	
	/*s is dummy variable set to blank string*/
	sentinel->s = "";

	size = 0;
}


/*return the first Dnode in the list*/
Dnode *Dlist::Begin() {
	return sentinel->flink;
}

/*return the one past the last Dnode in the list*/
Dnode *Dlist::End() {
	return sentinel;
}


/*return the last node in the list*/
Dnode *Dlist::Rbegin() {
	return sentinel->blink;
}


/*return one past the first Dnode in the list*/
Dnode *Dlist::Rend() {
	return sentinel;
}

/*return the size of the dlist*/
int Dlist::Size() {
	return size;
}


/*inserts new Dnode with s string in the first position of the list after the sentinel*/
void Dlist::Push_Front(string s) {
	Dnode *new_node = new Dnode();
	new_node->s = s;
	
	sentinel->flink->blink = new_node;
	new_node->flink = sentinel->flink;
	sentinel->flink = new_node;
	new_node->blink = sentinel;
	size++;
}


/*inserts new Dnode with s string in the last position of the list before the sentinel*/
void Dlist::Push_Back(string s) {
	Dnode *new_node = new Dnode();
	new_node->s = s;

	sentinel->blink->flink = new_node;
	new_node->flink = sentinel;
	new_node->blink = sentinel->blink;
	sentinel->blink = new_node;
	size++;
}

/*removes the first Dnode in the Dlist*/
string Dlist::Pop_Front() {

	Dnode *deleted_node = sentinel->flink;
	string s;
	s = deleted_node->s;
	sentinel->flink->flink->blink = sentinel;
	sentinel->flink = sentinel->flink->flink;
	delete deleted_node;
	deleted_node = NULL;
	size--;
	return s;
}

/*removes the last Dnode in the Dlist*/
string Dlist::Pop_Back() {
	Dnode *deleted_node = sentinel->blink;
	string s;
	s = deleted_node->s;
	sentinel->blink->blink->flink = sentinel;
	sentinel->blink = sentinel->blink->blink;
	delete deleted_node;
	deleted_node = NULL;
	size--;
	return s;
}

/*inserts Dnode with string s before Dnode n*/
void Dlist::Insert_Before(string s, Dnode *n) {
	Dnode *current = sentinel->flink;
	while(current != sentinel) {
		if(current == n) {
			Dnode *new_node = new Dnode();
			new_node->s = s;
			current->blink->flink = new_node;
			new_node->flink = current;
			new_node->blink = current->blink;
			current->blink = new_node;
			size++;
			return;
		}
		else {
			current = current->flink;
		}
	}

	return;

}

/*inserts Dnode with string s after Dnode n*/
void Dlist::Insert_After(string s, Dnode *n) {
	Dnode *current = sentinel->flink;
	while(current != sentinel) {
		if(current == n) {
			Dnode *new_node = new Dnode();
			new_node->s = s;
			current->flink->blink = new_node;
			new_node->blink = current;
			new_node->flink = current->flink;
			current->flink = new_node;
			size++;
			return;
		}
		else {
			current = current->flink;
		}
	}
	return;
}

/*Erase Dnode n from the Dlist*/
void Dlist::Erase(Dnode *n) {
	Dnode *current = sentinel->flink;
	while(current != sentinel) {
		if(current == n) {
			current->blink->flink = current->flink;
			current->flink->blink = current->blink;
			delete current;
			size--;
			return;
		}
		else {
			current = current->flink;
		}
	}
	return;
	
}

/*removes every Dnode from the Dlist*/
Dlist::~Dlist() {
	Dnode *current = sentinel->flink;
	while(current != sentinel) {
		Dnode *deleted_node;
		current->blink->flink = current->flink;
		current->flink->blink = current->blink;
		deleted_node = current;
		current = current->flink;
		delete deleted_node;	
	}
	current->flink = NULL;
	current->blink = NULL;
	delete current;
	return;
}

/*returns 1 if list is empty and 0 if it has nodes*/
int Dlist::Empty() {
	
	if(size == 0) {
		return 1;
	}
	else {
		return 0;
	}
}





