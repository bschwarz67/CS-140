#include <fstream>
#include <sstream>
#include <algorithm>
#include "bitmatrix.h"


//this is the client program for the bitmatrix editor application.
//once the program is run, the user can input commands to edit bitmatrices, store bitmatrices in a hash table, 
//or perform operations on bitmatrices.

//program ends when user enters 'QUIT' command

void bye_bye()
{
  printf("ERROR: The original bitmatrix was modified.\n");
  exit(1);
}

void check_equal(Bitmatrix *b1, Bitmatrix *b2) //check for equality of two different bit matrices
{
  int i, j;

  if (b1 == NULL || b2 == NULL) { //check that pointers refer to different objects
    if (b1 == b2) return;
    bye_bye();
  }

  if (b1->Rows() != b2->Rows()) bye_bye();                            //check that # rows are the same
  if (b1->Cols() != b2->Cols()) bye_bye();                            //check that # columns are the same
  for (i = 0; i < b1->Rows(); i++) for (j = 0; j < b1->Cols(); j++) { //check that value at each index is the same
    if (b1->Val(i, j) != b2->Val(i, j)) bye_bye();
  }
  return;
}

vector <string> StoSVec(string &s)      //return command and parameters from a line of input in a vector of strings
{
  istringstream ss;
  string t;
  vector <string> rv;

  ss.str(s);
  while (ss >> t) rv.push_back(t);
  return rv;
}


int main(int argc, char **argv)
{
  Bitmatrix *bm, *bm2, *bm3, *bm4, *bm5;
  BM_Hash *ht;
  int i, r, c, w, v, p, b;
  string s;
  vector <string> sv;                                                                               //vector to hold strings of user commands
  istringstream ss;
  string prompt = "";
  HTVec all;                                                                                        //vector to hold all entries in hash table when using ALL
  vector <int> ind;                                                                                 //vector to hold all indices to be printed when using SUBMATRIX

  if (argc > 2) {
    cerr << "usage: matrix_editor [prompt]\n";
    exit(1);
  }
  if (argc == 2) prompt = argv[1];
  if (prompt.size() > 0) prompt += " ";
  bm = NULL;

  ht = new BM_Hash(10000);                                                                          //create a new hash table in which to store Bitmatrix objects created in the program
  while (1) {

    cout << prompt;
    cout.flush();

    if (!getline(cin, s)) exit(0);     
                                        
    sv = StoSVec(s);
    if (sv.size() > 0 && sv[0][0] != '#') {
      if (sv[0] == "EMPTY") {                                                       
        if (sv.size() != 3 || sscanf(sv[1].c_str(), "%d", &r) != 1 || r <= 0 ||
                              sscanf(sv[2].c_str(), "%d", &c) != 1 || c <= 0) {                     //checks that parameters in command are in the correct format                                                                            
          printf("Should be: EMPTY rows cols\n");
        } else {                                                                    
          if (bm != NULL) delete bm;                                                                //free up memory space for new matrix in case that the variable is not null
          bm = new Bitmatrix(r, c);
        }
      } else if (sv[0] == "SET") {                                                 
        if (sv.size() != 4 || sscanf(sv[1].c_str(), "%d", &r) != 1 || r < 0 ||
                              sscanf(sv[2].c_str(), "%d", &c) != 1 || c < 0 ||
                              (sv[3] != "0" && sv[3] != "1")) {                                     //checks that parameters in command are in the correct format
          printf("Should be: SET r c 0|1\n");                                    
        } 
        
        //statements check that matrix isn't null, that index parameters dont exceed largest matrix indices
        else if (bm == NULL) {                                                  
          printf("No current matrix.\n");
        } else if (r >= bm->Rows()) {                                              
          printf("r must be less than %d\n", bm->Rows());
        } else if (c >= bm->Cols()) {                                               
          printf("c must be less than %d\n", bm->Cols());                           
        } else {                                                                 
          bm->Set(r, c, sv[3][0]);
        }
      } else if (sv[0] == "VAL") {                                                
        if (sv.size() != 3 || sscanf(sv[1].c_str(), "%d", &r) != 1 || r < 0 ||
                              sscanf(sv[2].c_str(), "%d", &c) != 1 || c < 0) {                      //checks that parameters in command are in correct format
          printf("Should be: VAL r c\n");                                          
        } 
        
        //statements check that matrix isnt null, that index paremeters not exceed largest matrix indices
        else if (bm == NULL) {                                                                                       
          printf("No current matrix.\n");
        } else if (r >= bm->Rows()) {                                               
          printf("r must be less than %d\n", bm->Rows());
        } else if (c >= bm->Cols()) {
          printf("c must be less than %d\n", bm->Cols());                         
        } else {                                                                    
          printf("%c\n", bm->Val(r, c));                                           
        }
      } else if (sv[0] == "SWAP") {                                                             
        if (sv.size() != 3 || sscanf(sv[1].c_str(), "%d", &r) != 1 || r < 0 ||
                              sscanf(sv[2].c_str(), "%d", &c) != 1 || c < 0) {                      //checks that parameters in command are in correct format
          printf("Should be: SWAP r1 r2\n");
        }

        //statements check that matrix is not null, index parameters do no exceed largest matrix indices
        else if (bm == NULL) {                                                                    
          printf("No current matrix.\n");
        } else if (r >= bm->Rows()) {                                               
          printf("r must be less than %d\n", bm->Rows());
        } else if (c >= bm->Rows()) {
          printf("c must be less than %d\n", bm->Rows());                           
        } else {
          bm->Swap_Rows(r, c);                                                    
        }
      } else if (sv[0] == "+=") {                                                 
        if (sv.size() != 3 || sscanf(sv[1].c_str(), "%d", &r) != 1 || r < 0 ||
                              sscanf(sv[2].c_str(), "%d", &c) != 1 || c < 0) {                      //checks that parameters in command are in correct format     
          printf("Should be: R1+=R2 r1 r2\n");
        }

        //statements check that matrix is not null, index parameters do no exceed largest matrix indices
        else if (bm == NULL) {                                                    
          printf("No current matrix.\n");
        } else if (r >= bm->Rows()) {                                              
          printf("r must be less than %d\n", bm->Rows());
        } else if (c >= bm->Rows()) {
          printf("c must be less than %d\n", bm->Rows());                           
        } else {
          bm->R1_Plus_Equals_R2(r, c);                                              
        }
      } else if (sv[0] == "PRINT") {                                                
        w = -1;
        if (sv.size() == 1) {                                                                       //checks to see if there are no parameters
          w = 0;
        } else if (sv.size() != 2 || sscanf(sv[1].c_str(), "%d", &w) != 1 || w < 0) {
          printf("Should be: PRINT [w]\n");                                                         //if there are parameters, checks that parameters in command are in correct format
          w = -1;
        }
        if (w >= 0) {                                                                              //try to print matrix only if parameter was in correct format
          if (bm == NULL) {
            printf("No current matrix.\n");
          } else {
            bm->Print(w); 
          }
        }
      } else if (sv[0] == "WRITE") {
        if (sv.size() != 2) {                                                                       //prints error if parameter has wrong format
          printf("Should be: WRITE filename\n");
        } else if (bm == NULL) {
          printf("No current matrix.\n");
        } else {
          bm->Write(sv[1]);
        }
      } else if (sv[0] == "PGM") {

        //statements check that parameters are in correct format
        if (sv.size() != 4) {
          printf("Should be: PGM filename pixels border\n");
        } else if (sscanf(sv[2].c_str(), "%d", &p) == 0 || p <= 0) {
          printf("Should be: PGM filename pixels border -- pixels > 0\n");
        } else if (sscanf(sv[3].c_str(), "%d", &b) == 0 || b < 0) {
          printf("Should be: PGM filename pixels border -- border >= 0\n");
        } else {
          bm->PGM(sv[1], p, b);
        }
      } else if (sv[0] == "READ") {
        if (sv.size() != 2) {                                                                       //check that parameter is in correct format
          printf("Should be: READ filename\n");
        } else {
          if (bm != NULL) delete bm;                                                                //free up space in current matrix variable for new matrix
          bm = new Bitmatrix(sv[1]);
        }
      } else if (sv[0] == "STORE") {
        if (sv.size() != 2) {                                                                       //check that parameter is in correct format
          printf("Should be: STORE key\n");
        } else {
          bm2 = ht->Recall(sv[1]);                                                                  //check if key already exists in table
          if (bm2 != NULL) delete bm2;                                                              //clear memory space for new hash table element if key already exists in table
          ht->Store(sv[1], bm->Copy());
        }
      } else if (sv[0] == "RECALL") {
        if (sv.size() != 2) {                                                                       //check that parameter is in correct format
          printf("Should be: RECALL key\n");
        } else {
          bm2 = ht->Recall(sv[1]);
          if (bm2 == NULL) {
            printf("No matrix with key %s\n", sv[1].c_str());
          } else {                                                                                  //put a copy of recalled matrix into current matrix varaible
            if (bm != NULL) delete bm;                                                              //free up memory space of current matrix varaible for recalled matrix                                                            
            bm = bm2->Copy();
          }
        }
      } else if (sv[0] == "ALL") {
        if (sv.size() != 1) {                                                                       //check that command is in correct format
          printf("Should be: ALL\n");
        } else {
          all = ht->All();
          for (i = 0; i < all.size(); i++) {
            printf("%-30s %3d X %3d\n", all[i]->key.c_str(), all[i]->bm->Rows(), all[i]->bm->Cols());
          }
        }
      } else if (sv[0] == "SUM") {
        if (sv.size() != 3) {                                                                       //check that parameters are in correct format
          printf("Should be: SUM key1 key2\n");
        } else {                                                                                    
          bm2 = ht->Recall(sv[1]);
          bm3 = ht->Recall(sv[2]);

          //statements check that matrices exist, can be added
          if (bm2 == NULL) {
            printf("No matrix %s\n", sv[1].c_str());
          } else if (bm3 == NULL) {
            printf("No matrix %s\n", sv[2].c_str());
          } else if (bm2->Rows() != bm3->Rows()) {
            printf("Rows don't match\n");
          } else if (bm2->Cols() != bm3->Cols()) {
            printf("Cols don't match\n");
          } else {                                                                                  
            if (bm != NULL) delete bm;                                                              //free up current matrix variable for sum
            bm4 = bm2->Copy();                                                                      //make copy of matrix to protect original matrix data
            bm5 = bm3->Copy();                                                                      //             ""
            bm = Sum(bm2, bm3);
            check_equal(bm2, bm4);                                                                  //check to see if original matrix data was changed
            check_equal(bm3, bm5);                                                                  //check to see if original matrix data was changed
            delete bm4;
            delete bm5;
          }
        }
      } else if (sv[0] == "PRODUCT") {
        if (sv.size() != 3) {                                                                       //check that parameters are in correct format
          printf("Should be: PRODUCT key1 key2\n");
        } else {
          bm2 = ht->Recall(sv[1]);
          bm3 = ht->Recall(sv[2]);
          
          //statements check that matrices exist, can be multiplied
          if (bm2 == NULL) {
            printf("No matrix %s\n", sv[1].c_str());
          } else if (bm3 == NULL) {
            printf("No matrix %s\n", sv[2].c_str());
          } else if (bm2->Cols() != bm3->Rows()) {
            printf("Dimensions don't match\n");
          } else {
            bm4 = bm2->Copy();                                                                      //make copy of matrix to protect original matrix data
            bm5 = bm3->Copy();                                                                      //                ""
            if (bm != NULL) delete bm;                                                              //free up current matrix variable for product
            bm = Product(bm2, bm3);
            check_equal(bm2, bm4);                                                                  //check to see if original matrix was changed
            check_equal(bm3, bm5);                                                                  //                ""
            delete bm4;
            delete bm5;
          }
        }
      } else if (sv[0] == "SUBMATRIX") {
        if (sv.size() < 2) {                                                                        //check that parameters are in correct format
          printf("Should be: SUBMATRIX rows...\n");
        } else if (bm == NULL) {
          printf("No matrix %s\n", sv[1].c_str());
        } else {
          ind.clear();                                                                              //clear index vector of previous indices
          for (i = 1; i < sv.size(); i++) {                                                         //loop through parameters input by user
            if (sscanf(sv[i].c_str(), "%d", &r) != 1 || r < 0 || r >= bm->Rows()) {                 //check that each row index can access a row in the matrix
              printf("Bad row %s. Should be a number between 0 and %d\n", 
                sv[i].c_str(), bm->Rows()-1);
              i = sv.size() + 10;                                                                   //ends for loop if any index is bad
            } else {
              ind.push_back(r);                                                                     //add index to list of indices to be used
            }
          }
          if (i == sv.size()) {                                                                     //only create submatrix if each parameter was valid
            bm3 = bm->Copy();                                                                       //make a copy of orignial matrix to protect data
            bm2 = Sub_Matrix(bm, ind);
            check_equal(bm, bm3);                                                                   //check to see if original matrix was changed
            delete bm3;
            delete bm;                                                                              //free up current matrix variable for new submatrix
            bm = bm2;                                                                               //make the current matrix the submatrix
          }
        }
      } else if (sv[0] == "INVERT") {
        if (sv.size() != 1) {
          printf("Should be: INVERT\n");                                                            //check that command is in correct format
        } 

        //statements check that matrix exists, can be inverted
        else  if (bm == NULL) {
          printf("No matrix %s\n", sv[1].c_str());
        } else if (bm->Rows() != bm->Cols()) {
          printf("Can't invert -- not a square matrix\n");
        } else {
          bm3 = bm->Copy();                                                                         //make a copy of original matrix to protect data
          bm2 = Inverse(bm);
          check_equal(bm, bm3);                                                                     //check to see if original matrix was changed
          delete bm3;
          if (bm2 == NULL) {
            printf("Matrix not invertible.\n");
          } else {
            delete bm;                                                                              //free up space in current matrix variable for inverted matrix
            bm = bm2;                                                                               //make current matrix inverted matrix
          }
        }
      } else if (sv[0] == "QUIT") {                                                                 //check that command is in correct format
        exit(0);
      } else { 
        printf("Unknown command %s\n", sv[0].c_str());
      }
    }
  }
}
