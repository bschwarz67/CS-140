#include "dl_hash.h"
using namespace std;

/*create hash table with the number of indexes equal to size*/
DL_Hash::DL_Hash(int size) {
	for(int i = 0; i < size; i++) {
		table.push_back(new Dlist());
	}
}

/*destructor for hash table, manually deletes every pointer to a Dlist*/
DL_Hash::~DL_Hash() {
	for(int i = 0; i < table.size(); i++) {
		delete table[i];
		table[i] = NULL;
	}
}

/*inserts a new node at the index in the table specified by the hash function, if node with s already exists, do nothing*/
void DL_Hash::Insert(string &s) {

	int i;
	unsigned int h;

	if(Present(s) == 0) { /*if s is not in table, use djb hash to compute index to store s at*/
		h = 5381;

		for (i = 0; i < s.size(); i++) {
			h = (h << 5) + h + s[i];
		}
		
		h = h % table.size();
		table[h]->Push_Front(s); /*insert node to table at computed index*/
		
	}
	return;
}

/*Return 1 if string s is present in table, return 0 otherwise*/
int DL_Hash::Present(string &s) {
	int i;
	unsigned int h;
  	Dnode *current;
	h = 5381;

	/*use djb hash to compute index of where node with s would be stored*/
	for (i = 0; i < s.size(); i++) {
    	h = (h << 5) + h + s[i];
  	}
	
	h = h % table.size();
	
	current = table[h]->Begin();
	for (i = 0; i < table[h]->Size(); i++) { /*for every node in the Dlist at the index computed, check if node has s*/
		if(current->s == s) {
			return 1;
		}
		current = current->flink;
	}
	return 0;
}

/*erase node in table containing s if exists, do nothing otherwise*/
void DL_Hash::Erase(string &s) {	
	int i;
	unsigned int h;
  	Dnode *current;
	h = 5381;
	
	if(Present(s) == 1) { /*if node containing s is present in the table, compute index where node is stored at*/
		for (i = 0; i < s.size(); i++) {
				h = (h << 5) + h + s[i];
			}
			
		h = h % table.size();
		current = table[h]->Begin();
		
		for (i = 0; i < table[h]->Size(); i++) { /*search table at index h for node containing s, remove that node*/
			if(current->s == s) {
				table[h]->Erase(current);
				return;
			}
			current = current->flink;
		}
	
	}
	return;

}


/*Erase all nodes containing string with substring s*/
void DL_Hash::Strip_All_Substring(string &s) {
	Dnode *current, *temp;
	int k;
	int l;
	

	for(int i = 0; i < table.size(); i++) { /*iterate through entire hash table*/
		current = table[i]->Begin();
		while(current != table[i]->End()) { /*iterate through each Dlist in the table*/
			for(int j = 0; j < current->s.size(); j++) { /*check for substring s starting at each index of the current node's s*/
				k = 0;
				l = j;
				

				while(s[k] == current->s[l]) { /*if there is a substring s within the node s, remove the node and stop checking for the substring*/
					if(k == s.size() - 1) {
						temp = current;
						current = current->flink;
						table[i]->Erase(temp);
						j = current->s.size();
						break;
					}
					k++;
					l++;
				}
				
				if(s.size() > current->s.size() - j - 1) { /*terminate checking this node if substring is larger than remaining # characters to check*/
					current = current->flink;
					j = current->s.size();
					break;
				}
			
			
			
			}
		}		
	}
	return;
}

/*prints out every string string in stored in table. String proceeded by hash index where its node is stored, justified right, padded
4x, then a space*/

void DL_Hash::Print() {
	Dnode *current;
	for(int i = 0; i < table.size(); i++) { /*iterate through all indexes in hash table*/
		current = table[i]->Begin();
		while(current != table[i]->End()) { /*iterate through every node at index i*/
			
			printf("%4d %s\n", i, current->s.c_str()); /*print formatted string at each node*/

			current = current->flink;

		}		
	}
}

