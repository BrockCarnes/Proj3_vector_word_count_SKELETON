/*
 * fileio.cpp
 *
 *  Created on: October 10, 2020
 *      Author: Brockton
 */

#include "../includes/utilities.h"
#include "../includes/fileio.h"

using namespace std;


bool openFile(std::fstream& myfile, const std::string& myFileName,
		std::ios_base::openmode mode){	//= std::ios_base::in only in header

	myfile.open(myFileName);
	if(!myfile.is_open()){
		return false;
	}
	else
		return true;
}

/*iff myfile is open then close it*/
void closeFile(std::fstream& myfile){
	if(myfile.is_open()){
		return myfile.close();
	}
}

/* serializes all content in entries to file outputfilename
 * check out utils for helpful type conversion functions
 * returns  FAIL_FILE_DID_NOT_OPEN if cannot open outputfilename
 * 			FAIL_NO_ARRAY_DATA if there are 0 entries in myEntryArray
 * 			SUCCESS if all data is written and outputfilename closes OK
 * */
int writetoFile(std::vector<constants::entry>  &entries, const std::string &outputfilename){
	ofstream my_ofile;
	my_ofile.open(outputfilename);

	if(!my_ofile.is_open()){
		return constants::FAIL_FILE_DID_NOT_OPEN;
	}
	if (entries.size() == 0){
		return constants::FAIL_NO_ARRAY_DATA;
	}
	for (int i = 0; i < entries.size(); i++){
		my_ofile<<entries[i].word<<" "<<entries[i].number_occurences<<endl;;
	}
	my_ofile.close();
	return constants::SUCCESS;
}







