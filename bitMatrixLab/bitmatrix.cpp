#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include "bitmatrix.h"
#include <vector>
#include <string>
Bitmatrix::Bitmatrix(int rows, int cols)
{

    if(rows <= 0 || cols <= 0) {
        printf("0 or less rows or columns specified. Creating 1x1 matrix");
        M.resize(1);
        M[0] = "0";
    }
    else {
        string row_string;
        for(int i = 0; i < cols; i++) {
            row_string += '0';
        }
        M.resize(rows);
        for(int j = 0; j < M.size(); j++) {
            M[j] = row_string;
        }
    }
}

int Bitmatrix::Rows()
{
  return M.size();
}

int Bitmatrix::Cols()
{
  return M[0].size();
}

void Bitmatrix::Set(int row, int col, char val)
{
    M[row][col] = val;
}
  
char Bitmatrix::Val(int row, int col)
{
  return M[row][col];
}
  
void Bitmatrix::Print(int w) 
{
  int i, j;

  //prints every element in the matrix
  //if w is larger than 0, print a blank separator row and column before every xth row, column where x = wy
  for (i = 0; i < M.size(); i++) {
    if (w > 0 && i != 0 && i%w == 0) printf("\n");
    if (w <= 0) {
      cout << M[i] << endl;
    } else {
      for (j = 0; j < M[i].size(); j++) {
        if (j % w == 0 && j != 0) printf(" ");
        printf("%c", M[i][j]);
      }
      cout << endl;
    }
  }
}

void Bitmatrix::Write(string fn) 
{
    fstream file1;
    file1.open(fn, fstream::out);
    for (int i = 0; i < M.size(); i++) {
        file1 << M[i] << endl;
    }
    file1.close();
}

void Bitmatrix::Swap_Rows(int r1, int r2)
{
    string temp;                                                    
    temp = M[r1];
    M[r1] = M[r2];
    M[r2] = temp;
}

void Bitmatrix::R1_Plus_Equals_R2(int r1, int r2)
{
    //perform binary addition of r2 to r1.
    for(int i = 0; i < M[0].size(); i++) { 
        if (M[r1][i] == '0' && M[r2][i] == '0') {
            M[r1][i] = '0';
        }
        else if (M[r1][i] == '1' && M[r2][i] == '0') {
            M[r1][i] = '1';
        }
        else if (M[r1][i] == '0' && M[r2][i] == '1') {
            M[r1][i] = '1';
        }
        else {
            M[r1][i] = '0';
        }
    }

}

Bitmatrix::Bitmatrix(string fn)         //Bitmatrix constuctor that obtains data from a file
{
  ifstream f;
  int i, j;
  string s, row;                //s holds a line of input from file, row holds data from s once it is checked to be correct

  f.open(fn.c_str());
  if (f.fail()) { perror(fn.c_str()); M.resize(1); M[0].resize(1), M[0][0] = '0'; return; }     //perform deault operation when file doesnt open

  //read data, add to bitmatrix, if data is not 1, 0, or blank, perform default operation
  while (getline(f, s)) { 
    row.clear();
    for (i = 0; i < s.size(); i++) {
      if (s[i] == '0' || s[i] == '1') {
        row.push_back(s[i]);
      } else if (s[i] != ' ') {
        fprintf(stderr, "Bad matrix file %s\n", fn.c_str());
        M.resize(1); M[0].resize(1), M[0][0] = '0'; 
        f.close();
        return;
      }
    }
    
    //perform default operation if rows in file are found to contain different numbers of bits
    if (s.size() > 0 && M.size() > 0 && row.size() != M[0].size()) { 
      fprintf(stderr, "Bad matrix file %s\n", fn.c_str());
      M.resize(1); M[0].resize(1), M[0][0] = '0'; 
      f.close();
      return;
    }
    if (s.size() > 0) M.push_back(row);         //if all input was correct, add row of input to bitmatrix
  }
  f.close();
}

void Bitmatrix::PGM(string fn, int pixels, int border)
{
    fstream file1;
    string borderstring;        //string of 0s to be added to the beginning and end of pixel data as many times as the border designates
    string gapstring;           //string of 0s to be added in between each zerostring or onestring that represents one line of a square representing one bit in pgm file
    string zerostring;          //string of 255 values representing one row of a pixels*pixels square representing a zero character from bitmatrix in pgm file
    string onestring;           //string of 100 values representing one row of a pixels*pixels square representing a one character from bitmatrix in pgm file
    file1.open(fn, fstream::out);

    //add header to pgm file
    file1 << "P2" << endl;
    file1 << M[0].size()*pixels + M[0].size()*border + border << " " << M[0].size()*pixels + M[0].size()*border + border << endl;
    file1 << 255 << endl;
    
    
    //create borderstring
    for(int i = 0; i < M[0].size()*pixels + M[0].size()*border + border; i++) {
        if (i < M[0].size()*pixels + M[0].size()*border + border - 1) {
            borderstring += "0 ";
        }
        else {
            borderstring += "0";
        }
    }

    //create gapstring
    for(int i = 0; i < border; i++) {
        gapstring += "0 ";
    }

    //create zerostring
    for(int i = 0; i < pixels; i++) {
        zerostring += "255 ";
    }
    
    //create onestring
    for(int i = 0; i < pixels; i++) {
        onestring += "100 ";
    }

    //in the case that user desingates a border
    if(border > 0) { 
    
        
        //add top border to pixels of width = border
        for (int i = 0; i < border; i++) { 
            file1 << borderstring << endl;
        } 
       
        //add matrix of pixel*pixel squares, each padded on the sides, top, bottom by border of width = border
        for (int i = 0; i < M.size(); i++) {             
            for (int j = 0; j < pixels; j++) {      
                file1 << gapstring;
                for (int k = 0; k < M[0].size(); k++) {
                    if (M[i][k] == '0') {
                        file1 << zerostring;
                        file1 << gapstring;
                    }
                    else {
                        file1 << onestring;
                        file1 << gapstring;
                    }
                }
                file1 << endl;
            }
            if(i < M.size()) {
                for (int i = 0; i < border; i++) {
                    file1 << borderstring << endl;
                }
            }
        }
    }
    else { 
        
        //add matrix of pixel*pixel squares with no padding for squares
        for (int i = 0; i < M.size(); i++) {
            for (int j = 0; j < pixels; j++) {
                for (int k = 0; k < M[0].size(); k++) {
                    if (M[i][k] == '0') {
                        file1 << zerostring;
                    }
                    else {
                        file1 << onestring;
                    }
                }
                file1 << endl;
            }
        }
    }
    
    file1.close();
}


Bitmatrix *Bitmatrix::Copy()
{
    //create reference to a new Bitmatrix of the size of the matrix to be copied
    Bitmatrix *cpp = new Bitmatrix(M.size(), M[0].size());
    
    //copy data from original matrix to new matrix
    for(int i = 0; i < M.size(); i++) {
        for(int j = 0; j < M[i].size(); j++) {
            cpp->Set(i, j, M[i][j]);
        }
    }
    return cpp;
}



BM_Hash::BM_Hash(int size)
{
    table.resize(size);
}

void BM_Hash::Store(string &key, Bitmatrix *bm)
{
    //djb hash function computes hash value
    int i;
    unsigned int h;
  
    h = 5381;
    for (i = 0; i < key.size(); i++) {
        h = (h << 5) + h + key[i];
    }

    //hash value is taken modulo the table size to compute an index
    h = h % table.size();
    
    //check to see if key already exists in a hash table entry. If so, set the matrix at that entry to refer to bm and return
    for(int j = 0; j < table[h].size(); j++) {
        if(table[h][j]->key == key) {
            table[h][j]->bm = bm;
            return;
        }
    }

    //if there was no entry with key, create a reference to a new hash table entry
    HTE* new_entry = new HTE;
    
    //set the entry key variable to key
    new_entry->key = key;
    
    //set the enry bm variable to bm
    new_entry->bm = bm;
    
    //add the new entry to the hash table
    table[h].push_back(new_entry);
}

Bitmatrix *BM_Hash::Recall(string &key)
{
    
    //djb hash function computes hash value
    int i;
    unsigned int h;
  
    h = 5381;

    for (i = 0; i < key.size(); i++) {
        h = (h << 5) + h + key[i];
    }
    
    //hash value is taken modulo the table size to compute an index
    h = h % table.size();
    
    //check to see if key exists in a hash table entry. If so, return the bitmatrix at this entry
    if(table[h].size() > 0) {
        for(int j = 0; j < table[h].size(); j++) {
            if(table[h][j]->key == key) {
                return table[h][j]->bm;
            }
        } 
    }

    //return no if no correct entry is found
    return NULL;
}  
HTVec BM_Hash::All() {
    HTVec rv;

    //create a vector of every entry in the hash table
    for(int i = 0; i < table.size(); i++) {
        for(int j = 0; j < table[i].size(); j++) {
            rv.push_back(table[i][j]);
        }
    }
    return rv;
}


Bitmatrix *Sum(Bitmatrix *m1, Bitmatrix *m2)
{
    //create pointer to a new bitmatrix of the dimensions of the sum of m1, m2
    Bitmatrix *sum = new Bitmatrix(m1->Rows(), m1->Cols());
        
        //perform binary addition of m1, m2. Set sum to values computed by this addition.
        for(int i = 0; i < m1->Rows(); i++) {
            for(int j = 0; j < m1->Cols(); j++) {
                if(m1->Val(i,j) == '0' && m2->Val(i,j) == '0') {
                    sum->Set(i,j, '0');
                }
                else if(m1->Val(i,j) == '1' && m2->Val(i,j) == '0') {
                    sum->Set(i,j, '1');
                }
                else if(m1->Val(i,j) == '0' && m2->Val(i,j) == '1') {
                    sum->Set(i,j, '1');
                }
                else {
                    sum->Set(i,j, '0');
                }
            }
        }
        return sum;
}

Bitmatrix *Product(Bitmatrix *m1, Bitmatrix *m2)
{
    //create pointer to a new bitmatrix of the dimensions of the product of m1, m2
    Bitmatrix *prod = new Bitmatrix(m1->Rows(), m2->Cols());
    
    //perform binary multiplication of m1, m2. Set product to values computed by this multiplication.
    for(int i = 0; i < m1->Rows(); i++) {
        int line_product = 0;
        for(int j = 0; j < m2->Cols(); j++) {
            for(int k = 0; k < m1->Cols(); k++) {
                if((m1->Val(i,k) == '0') && (m2->Val(j,k) == '0')) {
                    line_product += 0;   
                }
                
                else if((m1->Val(i,k) == '1') && (m2->Val(j,k) == '0')) {
                    line_product += 1;
                }
                else if((m1->Val(i,k) == '0') && (m2->Val(j,k) == '1')) {
                    line_product += 1;
                }
                else {
                    line_product += 2;
                }
            }
            line_product = line_product % 2;
            if (line_product == 0) {
                prod->Set(i, j, '0');
            }
            else {
                prod->Set(i, j, '1');
            }
        }
    }
    return prod;
}

Bitmatrix *Sub_Matrix(Bitmatrix *m, vector <int> &rows)
{
    //create pointer to a new bitmatrix that has the same number of columns as m. The number of rows in designated by the number size of the vector containing
    //the indices of the rows to be appended to the submatrix
    Bitmatrix *sub = new Bitmatrix(rows.size(), m->Cols());
    
    //append each row of m designated by the rows vector to sub, repeated rows allowed
    for(int i = 0; i < rows.size(); i++) {
        for(int j = 0; j < m->Cols(); j++) {
            if(m->Val(rows[i],j) == '0') {
                sub->Set(i, j, '0');
            }
            else {
                sub->Set(i, j, '1');
            }           
        }
    }
    return sub;
}

Bitmatrix *Inverse(Bitmatrix *m)
{
    //create pointer to a new bitmatrix of dimensions m to be the inverse of m
    Bitmatrix *Inv = new Bitmatrix(m->Rows(), m->Cols());
    
    //create pointer to a new bitmatrix to hold a copy of m
    Bitmatrix *Cp = m->Copy();
    
    //make Inv into an identity matrix
    for(int i = 0; i < Inv->Rows(); i++) {
        Inv->Set(i, i, '1');
    }

    //to invert bitmatrix:

    //note, all operations are performed on Cp as well as Inv.

    //go through every row i in Cp starting at the first row. If Cp[i][i] is not 1, find a row j, j > i where Cp[j][i] is 1 and swap i and j. 
    //If there is no such row j in Cp, the matrix is not invertable.
    //if there is such a j, look at every row j, j > i. If Cp[j][i] is one, set j equal to the sum of row i, row j.
    for(int i = 0; i < Cp->Rows(); i++) {
        if(Cp->Val(i,i) != '1') {
            int j = i + 1;
            bool rowfound = false;
            while( j < Cp->Rows()) {
                if(Cp->Val(j,i) == '1') {
                    Inv->Swap_Rows(i, j);
                    Cp->Swap_Rows(i, j);
                    rowfound = true;
                    j++;
                }
                else {
                    j++;
                }
            }
            if(rowfound == false) {
                cout << "matrix not invertible, sorry" << endl;
                return NULL;
            }
            for(int j = i + 1; j < Cp->Rows(); j++) {
                if(Cp->Val(j, i) == '1') {
                    Cp->R1_Plus_Equals_R2(j, i);
                    Inv->R1_Plus_Equals_R2(j, i);
                }
            }
        }         
     
        else {
            for(int j = i + 1; j < Cp->Rows(); j++) {
                if(Cp->Val(j, i) == '1') {
                    Cp->R1_Plus_Equals_R2(j, i);
                    Inv->R1_Plus_Equals_R2(j, i);
                }
            }
        }
    }
    
    //after the first step, Cp is a upper triangular matrix. Next, iterate through Cp starting at the last row. At each row i, if there is any row j, j > i, replace row
    //i with the sum of row i, j. After this iteration is complete, Inv is the inversion of m.
    for(int i = Cp->Rows() - 1; i >= 0; i--) {
        int j = i + 1;
        while( j < Cp->Rows()) {
            if(Cp->Val(i,j) == '1') {
                Inv->R1_Plus_Equals_R2(i, j);
                Cp->R1_Plus_Equals_R2(i, j);
                j++;
            }
            else {
                j++;
            }
        }
    }


   
    
    return Inv;
}
