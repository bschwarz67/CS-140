#include <string>
#include <iostream>
#include <vector>
using namespace std;
class Bitmatrix {
  public:
    Bitmatrix(int rows, int cols);   // Create an empty bitmatrix
    Bitmatrix(string fn);            // create a birmatrix from a file
    void Write(string fn);           // Write t to a file either as hex or zeros & ones
    void Print(int w);               // Print on standard ouptput with spaces & blank lines 
    void PGM(string fn, int pixels, int border);  // Write it to a pgm file 
    int Rows();                           // Return the number of rows
    int Cols();                           // Return the number of columns
    void Set(int row, int col, char val); // Set the specified element to val
    char Val(int row, int col);           // Return the specified element
    void Swap_Rows(int r1, int r2);       //swap rows of r1, r2 in bitmatrix
    void R1_Plus_Equals_R2(int r1, int r2);   //add row r2 to r1 in bitmatrix
    Bitmatrix *Copy();      //return a reference to a copy of this bitmatrix
  protected:    
    vector <string> M; // The matrix.  Elements are '0' or '1'.
};

Bitmatrix *Sum(Bitmatrix *a1, Bitmatrix *a2); //return sum of two bitmatrices of the same dimensions
Bitmatrix *Product(Bitmatrix *a1, Bitmatrix *a2); //return product two bitmatrices where # of columns of a1 = # rows of a2
Bitmatrix *Sub_Matrix(Bitmatrix *a1, vector <int> &rows); //return new matrix of specified rows in the given matrix, repeats allowed
Bitmatrix *Inverse(Bitmatrix *m); //return inverse of m

class HTE { //hash table entry contains pointer to bitmatrix as well as key
  public:
    string key;
    Bitmatrix *bm;
};

typedef vector <HTE *> HTVec; //vector of pointers to hash table entries

class BM_Hash {     //hash table class for the management of hash table containing entries containing bitmatrices.
  public:
    BM_Hash(int size); //initialized table vector to size of argument
    void Store(string &key, Bitmatrix *bm); //stores bitmatrix, key as entry in table vector, replaces entry if key is already in table
    Bitmatrix *Recall(string &key); //return bitmatrix from the index that the key maps to
    HTVec All(); //returns vector of all table entries
  protected:
    vector <HTVec> table;   //holds entries containing bitmatrices
};
