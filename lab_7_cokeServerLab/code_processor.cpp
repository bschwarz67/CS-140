#include <fcntl.h>
#include <unistd.h>
#include "code_processor.h"


#include <set>
#include <deque>
#include <map>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>

	
	
	/* 
		Creates a Prize object and puts an entry into Prizes with the id string as the key and the Prize object as the value.
		Return -1 if: points <=0, quantity <= 0, Prize designated by id already exist. Return 0 upon successful Prize creation
	*/

    int Code_Processor::New_Prize(string id, string description, int points, int quantity) {
        
		/*check that designated Prize points is > 0*/		
		if (points <= 0) {
			return -1;
		}
		/*check that designated Prize quantity is > 0*/
		if (quantity <= 0) {
			return -1;
		}
		/*check that id-Prize pair doesn't exist in Prizes*/
		if (Prizes.find(id) != Prizes.end()) {
			return -1;
		}


		/*Create Prize object, set id, description, points, quantity fields to values specified in function parameters */
		Prize *new_prize = new Prize();
		new_prize->id = id;
		new_prize->description = description;
		new_prize->points = points;
		new_prize->quantity = quantity;


		/*Insert id, pointer to newly created Prize object as key and value into Prizes map*/
		Prizes.insert(make_pair(id, new_prize));
		
		return 0;
    }
    
    
	/* 
		Creates a User object and puts an entry into Names with the username string as the key and
		the User object as the value. Return -1 if: starting_points <=0, User
		designated by username already exists. Return 0 upon successful User creation
	*/
    
	int Code_Processor::New_User(string username, string realname, int starting_points) {
        
		/*check that starting_points is greater than zero, username-User pair does not exist in Names map*/
		if (starting_points < 0) {
			return -1;
		}		
		if (Names.find(username) != Names.end()) {
			return -1;
		}
        

		/*create User object, set username, realname, starting_points fields to values specified in funcion parameters*/
		User *new_user = new User();
		new_user->username = username;
		new_user->realname = realname;
		new_user->points = starting_points;
		
		/*Insert username, pointer to newly created User object as key and value into Names map set new_user
		to NULL to remove dangling pointer*/
		Names.insert(make_pair(username, new_user));

		return 0;
    }
    
    
    /*
		Removes element with the designated User object from Names. Removes Phones entrys designated by strings in User phone_numbers from Phones.
		Manually deletes User object from heap. Return 0 if User is successfully deleted. Return -1 if designated User does not exist.
	*/
    int Code_Processor::Delete_User(string username) {
        
		/*create iterator to iterate over set of phone numbers, and temporary pointer User object to hold User to be deleted*/
		set <string>::iterator pn;
		User *out_user = NULL;				
		
		/*check that designated User object exists*/
		if (Names.find(username) == Names.end()) {
			return -1;
		}
		
		/*use out_user to hold designated user object, remove pair with designated object from Names*/
		out_user = Names.find(username)->second;
		Names.erase(username);

		
		
		/*Remove pairs with a Phone object in phone_numbers set of designated User object from Phones*/
		for (pn = out_user->phone_numbers.begin(); pn != out_user->phone_numbers.end(); pn++) {
			Phones.erase(*pn);
		}
		
		/*manually delete designated User object*/
		delete out_user;
		return 0;
    }
    
    
    /*
		Add element to Phones using phone string as key, and User designated by username string as value. Also add
		phone string to phone_numbers set of designated User. Return -1 if User designated
		by username doesn't exist, Phones entry designated by phone already exists. If Phones entry is succesfully added return 0.
	*/
    int Code_Processor::Add_Phone(string username, string phone) {
		
		/*Check that User with username exists in Names*/
		if(Names.find(username) == Names.end()) {
			return -1;
		}
		/*checks that entry designated by phone does not exists in Phones*/
		if(Phones.find(phone) != Phones.end()) {
			return -1;
		}
		
		/*Inserts phone into phone_numbers set of designated User*/
		Names.find(username)->second->phone_numbers.insert(phone);
		
		/*Inerts phone, designated User pair into Phones*/
		Phones.insert(make_pair(phone, Names.find(username)->second));
		
		return 0;
    }
    
    
    /*Removes designated phone string from designated User phone_numbers set. Removes Phones entry designated by phone. Return -1 if User designated by username
	doesn't exist, Phones entry designated by phone doesn't exist, or the designated Phones entry does not contain the designated User. If
	the Phones entry is removed normally, return 0*/
    int Code_Processor::Remove_Phone(string username, string phone) {
        
		/*Create temporary User pointer to hold User object, set iterator to iterate over User phone_numbers*/
		User *target_user = NULL;
		set <string>::iterator phit;

		/*Check that User designated by username exists*/ 
		if(Names.find(username) == Names.end()) {
			return -1;
		}	
		/*Check that entry designated by phone exists in Phones*/	
		if(Phones.find(phone) == Phones.end()) {
			return -1;
		}
		/*Check that the designated Phones entry contains the designated User*/
		if(Phones.find(phone)->second->username != username) {
			return -1;
		}


		/*set target_user temp to User object designated by username*/
		target_user = Names.find(username)->second;
		
		/*Remove phone string designated by phone from phone_numbers set of designated User*/
		target_user->phone_numbers.erase(phone);
		
		/*Remove Phones entry designated by phone from Phones*/
		Phones.erase(phone);
		
		
		
		
		return 0;
    }
    
    /*
		Return string of phone numbers in designated User's phones_numbers set. Phone numbers are
		in lexicographic order separated by newline. Last phone number is succeeded by newline. If the User
		designated by username does not exist, return "BAD_USER."
	*/
    string Code_Processor::Show_Phones(string username) {
        
		/*Create temporary User pointer to hold designated User object*/
		User *target_user = NULL;
		
		/*Create map to hold, sort elements in designated User phone_numbers set*/
		map <string, string> sorted_phones;
		
		/*create iterator to access the objects in the map of phone numbers*/
		map <string, string>::iterator spit;
		
		/*create set iterator to iterate through phone_numbers set of designated user*/
		set <string>::iterator phit;
		
		/*ordered string of phone numbers to return*/
		string phone_string = "";


		/*check that designated User object exists in Names*/
		if(Names.find(username) == Names.end()) {
			return "BAD USER";
		}

		/*assign temp target_user to User object desginated by username*/
		target_user = Names.find(username)->second;
		
		/*iterate through phone_numbers of User, add each phone string to sorted_phones in order to lexicographically
		sort phone strings*/
		for(phit = target_user->phone_numbers.begin(); phit != target_user->phone_numbers.end(); phit++) {
			sorted_phones.insert(make_pair(*phit, ""));
		}

		/*iterate through sorted_phones to add phone strings to phone_string in lexicographically sorted order,
		separated by new_line characters*/
		for(spit = sorted_phones.begin(); spit != sorted_phones.end(); spit++) {
			phone_string += spit->first;
			phone_string += "\n";
		}
		
		return phone_string;
    }
    
    /*
		Process code for a particular User. If djb hash of code can be divided by 17, designated user gets 10 points,
		if djb hash of code can be divided by 13 and not 17, designated user gets 3 points. Return -1 if User designated
		by username does not exist, code already exists in Codes. If code is successfully processed for User, return 0.
	*/
    int Code_Processor::Enter_Code(string username, string code) {
        
		/*couter for for loop*/
		int i;
  		/*hold hash value from djb hash*/
		unsigned int h;
		/*temporary user variable for designated user*/
		User *target_user = NULL;

		/*check that User designated by username exists in Names*/
		if(Names.find(username) == Names.end()) {
			return -1;
		}

		/*check that code does not exist in used Codes set*/
		if(Codes.find(code) != Codes.end()) {
			return -1;
		}
		
		/*retreive User object to which the phone number is assigned*/
		target_user = Names.find(username)->second;

		/*djb hash function computes hash value for code*/
  		h = 5381;
  		for (i = 0; i < code.size(); i++) {
    		h = (h << 5) + h + code[i];
  		}


		/*add ten points to designated User points if djb hash of code is divisible by 17,
		if not divisible by 17, add 3 points to designated User points is djb hash of code is divisble by
		13, else do nothing. If code is used for points, insert into Codes set*/
		if(h % 17 == 0) {
			target_user->points += 10;
			Codes.insert(code);
			target_user = NULL;
			return 10;
		}
		else if(h % 13 == 0) {
			target_user->points += 3;
			Codes.insert(code);
			target_user = NULL;
			return 3;
		}
		else {
			target_user = NULL;
			return 0;
		}
		
		
    }



    /*
		Process code for a particular User attached to a designated phone number. If djb hash of code can be divided by 17, designated user gets 10 points,
		if djb hash of code can be divided by 13 and not 17, designated user gets 3 points. Return -1 if Phones entry designated by phone
		does not exist, code already exists in Codes. If code is successfully processed for User, return 0.
	*/

    int Code_Processor::Text_Code(string phone, string code) {
		
		/*loop counter*/
		int i;
  		
		/*holds djb hash value*/
		unsigned int h;
		
		/*temp variable for User who is assigned the designated phone number*/
		User *target_user = NULL;

		/*check that phone number is a valid phone number*/
		if(Phones.find(phone) == Phones.end()) {
			return -1;
		}

		/*check that code has not already been used*/
		if(Codes.find(code) != Codes.end()) {
			return -1;
		}
		
		/*retreive User object to which the phone number is assigned*/
		target_user = Phones.find(phone)->second;

		/*djb hash function computes hash value for code*/
  		h = 5381;

  		for (i = 0; i < code.size(); i++) {
    		h = (h << 5) + h + code[i];
  		}


		/*add ten points to designated User points if djb hash of code is divisible by 17,
		if not divisible by 17, add 3 points to designated User points is djb hash of code is divisble by
		13, else do nothing. If code is used for points, insert into Codes set*/
		
		if(h % 17 == 0) {
			target_user->points += 10;
			Codes.insert(code);
			target_user = NULL;
			return 10;
		}
		else if(h % 13 == 0) {
			target_user->points += 3;
			Codes.insert(code);
			target_user = NULL;
			return 3;
		}
		else {
			target_user = NULL;
			return 0;
		}
    }
    
    /*Used to mark a code as used although a user has not entered the code. This is used to reconstruct a server state from a txt file by desginating 
	which codes have been used already. Return -1 if code is invalid or is in codes already, return -1. Else return 0.*/
    int Code_Processor::Mark_Code_Used(string code) {
		
		/*loop counter*/
		int i;
  		
		/*holds djb hash value*/
		unsigned int h;

		/*check that code does not already exist in Codes*/
		if(Codes.find(code) != Codes.end()) {
			return -1;
		}
		
		/*djb hash function computes hash value for code*/
  		h = 5381;

  		for (i = 0; i < code.size(); i++) {
    		h = (h << 5) + h + code[i];
  		}

		
		/*Check that code is valid (code is divisible by 17 or 13). If valid code, inserts code to Codes*/	
		if(h % 17 == 0) {
			Codes.insert(code);
			return 0;
		}
		else if(h % 13 == 0) {
			Codes.insert(code);
			return 0;
		}
		else {
			return -1;
		}
    }
    
    
	/*return the point balance of a designated User. If User does not exist, return -1*/
    int Code_Processor::Balance(string username) {

		/*checks that name does exist in Names*/
		if(Names.find(username) == Names.end()) {
			return -1;
		}
		
		/*return point balance of User object designated by username*/
		return Names.find(username)->second->points;
    }
    
    
    
	/*Called in order to redeem a prize for the User. Return -1 if User or Prize doesn't exist. Return -1 if User does not have enough points.
	Else subtract the number of points for the prize from the users account, and decrement the number of the Prize obect by 1. If the number of the prize becomes 0,
	remove the Prize object from the system. Return 0 for successful redeem*/
	int Code_Processor::Redeem_Prize(string username, string prize) {
		
		/*temp variables to hold designated User, Prize objects*/
		User *target_user = NULL;
        Prize *target_prize = NULL;
		
		/*check that designated User object exists*/
		if(Names.find(username) == Names.end()) {
			return -1;
		}
		/*check that designated Prize object exists*/
		if(Prizes.find(prize) == Prizes.end()) {
			return -1;
		}
		
		/*retreive User, Prize objects designated by username, prize*/
		target_user = Names.find(username)->second;
		target_prize = Prizes.find(prize)->second;

		/*check that designated User has enough points to redeem deisgnated Prize*/
		if(target_user->points < target_prize->points) {
			return -1;
		}

		/*decrement User point total by point cost of Prize*/
		target_user->points -= target_prize->points;

		/*decrement Prize quantity by one*/
		target_prize->quantity--;

		/*remove Prize from the system if Prize quantity is 0*/
		if(target_prize->quantity == 0) {
			Prizes.erase(prize);
			delete target_prize;
			target_prize = NULL;
		}


		return 0;
    }

	/*Destructor. Manually deletes objects that were manually created on the heap*/
    Code_Processor::~Code_Processor() {
		
		/*Iterators to traverse Names and Prizes*/
		map<string, Prize *>::iterator pit;
		map<string, User *>::iterator nit;

		/*Iterate through Prizes and manually delete the Prize object at each element*/
		for(pit = Prizes.begin(); pit != Prizes.end(); pit++) {
			delete pit->second;
			pit->second = NULL;
		}
		/*Iterate through Names and manually delete the User object at each element*/
		for(nit = Names.begin(); nit != Names.end(); nit++) {
			delete nit->second;
			nit->second = NULL;
		}
    }
    
    /*Write the image of the server to a text file in a format such that the text file can be read as ADD_USER, PRIZE, ADD_PHONE and MARK_USED commands to reconstruct the
	server later on and return 0. If file cannot be created/opened, return -1*/
    int Code_Processor::Write(const char *file) {
       	/*fstream used to write to text file*/ 
		fstream out_file;
		
		/*Iterators to iterate though Prizes, Names, Phones, Codes*/
		map<string, Prize *>::iterator pit;
		map<string, User *>::iterator nit;
		map<string, User *>::iterator phit;
		set<string>::iterator cit;
		
		/*Counter used when iterating through Codes to keep track of when to create a new MARK_USED command line*/
		int counter = 0;

		/*open/create a file to save the state of the server to*/
		out_file.open(file, fstream::out);
		
		/*check that file is opened/created*/
		if(!out_file.is_open()) {
			return -1;
		}
		
		/*Write "PRIZE id points quantity description" to file for each Prize in Prizes*/
		for(pit = Prizes.begin(); pit != Prizes.end(); pit++) {
			out_file << "PRIZE" << "   " << pit->second->id << "   " << pit->second->points << "   " << pit->second->quantity << "   " << pit->second->description << endl;
		}
		/*Write "ADD_USER username starting_points realname" to file for each User in Names*/
		for(nit = Names.begin(); nit != Names.end(); nit++) {
			out_file << "ADD_USER" << "   " << nit->second->username << "   " << nit->second->points << "   " << nit->second->realname <<  endl;
		}
		/*Write "ADD_PHONE username phone-number" to file for each Phones entry*/
		for(phit = Phones.begin(); phit != Phones.end(); phit++) {
			out_file << "ADD_PHONE" << "   " << phit->second->username << "   " << phit->first << endl;
		}
		
		/*Begin writing "MARK_USED ... " command line (max 19 codes per line) to file if there are used codes*/
		if(Codes.size() > 0) {
			out_file << "MARK_USED" << "   ";
		}

		/*for every code in Codes, write code string as an argument to MARK_USED command line*/
		for(cit = Codes.begin(); cit != Codes.end(); cit++) {
			
			/*Every 19 codes entered, write a new "MARK_USED ..." command line on the next line in the file*/
			if(counter != 0 && counter % 19 == 0) {
				out_file << endl << "MARK_USED" << "   ";
			}
			
			/*Write a code string as a parameter in the "MARK_USED ..." command line*/
			out_file << *cit << "   ";
			counter++;
		}
		
		out_file << endl;
		
		out_file.close();
		
		return 0;
    }


















/*Written by Dr. Plank*/
void Code_Processor::Double_Check_Internals()
{
  int fd;
  int npn;
  User *u;
  map <string, User *>::iterator uit;
  set <string>::iterator pit;

  npn = 0;
  for (uit = Names.begin(); uit != Names.end(); uit++) {
    u = uit->second;
    for (pit = u->phone_numbers.begin(); pit != u->phone_numbers.end(); pit++) {
      npn++;
      if (Phones.find(*pit) == Phones.end()) {
        cerr << "Error -- phone " << *pit << " from user " << u->username << " is not in Phones.\n";
        exit(1);
      }
      if (Phones[*pit] != u) {
        cerr << "Error -- phone " << *pit << " is not registered to user " << u->username << ".\n";
        exit(1);
      }
    }
  }
  if (npn != Phones.size()) {
    cerr << "Phones.size() does not match the number of user phones.\n";
    exit(1);
  }
  fd = open("/dev/null", O_RDONLY);
  if (fd > 4) {
    cerr << "You have too many files open.\n"; 
    exit(1);
  }
  close(fd);
}
