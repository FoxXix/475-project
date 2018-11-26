/*! \file main.cpp: main function for assigment 5 */
#include <wordCount.h>
#include <TFIDF.h>
#include <iostream>
#include <math.h>
#include <sstream>
using std::cout;
using std::cerr;
using std::endl;
#include <fstream>
using std::ifstream;
using std::istringstream;

/// Print the correct usage in case of user syntax error.
int Usage(char* arg0, int file)
{
    switch (file){
        case 1:
            cout << "Usage: " << arg0 << " exceptionList wordList" << endl;
            cout << "where arg1 contains an exception list." << endl;
            cerr << "Exception list doesn't exist or is invalid." << endl;
            break;
        case 2:
            cout << "Usage: " << arg0 << " exceptionList wordList" << endl;
            cout << "where arg1 contains an exception list." << endl;
            cout << "Arg2 contains words." << endl;
            cerr << "Arg2 either contains no words" << endl;
            cerr << "or doesn't exist." << endl;
            break;
		case 3:
            cout << "Usage: " << arg0 << " exceptionList wordList" << endl;
            cout << "where arg1 contains an exception list." << endl;
            cerr << "Target doesn't exist or is invalid." << endl;
            break;
		case 4:
            cout << "Usage: " << arg0 << " exceptionList wordList" << endl;
            cout << "where arg1 contains an exception list." << endl;
            cerr << "Target read exceptions list doesn't exist or is invalid." << endl;
            break;
		case 5:
            cout << "Usage: " << arg0 << " exceptionList wordList" << endl;
            cout << "where arg1 contains an exception list." << endl;
            cerr << "Document read exceptions list doesn't exist or is invalid." << endl;
            break;
		case 6:
            cout << "Usage: " << arg0 << " exceptionList wordList" << endl;
            cout << "where arg1 contains an exception list." << endl;
            cerr << "Index is invalid." << endl;
            break;
        default:
            cout << "Usage: " << arg0 << " exceptionList wordList" << endl;
            cout << "where file contains words." << endl;
            cerr << "File either contains no words" << endl;
            cerr << "or doesn't exist." << endl;
    }
  
    return -1;
}

int main(int argc, char* argv[])
{ 
    if (argc != 5) return Usage(argv[0], 0);  
    
    // check if bounds are valid
    istringstream lower(argv[3]);
    istringstream higher(argv[4]);
    double lower_bound, higher_bound;
    if (!(lower >> lower_bound) || !(higher >> higher_bound) || lower_bound > higher_bound){
        return Usage(argv[0], 0);
    }

    // this vector stores all document objects
    vector<WordCount> wc;

    // get second file (first filename is exceptions file)
    ifstream files_istr(argv[2]);
    if (files_istr.fail()) return Usage(argv[0], 1);    

    string file;
    vector<string> files;
    //vector<string> file_names;

    // read in files
    while(files_istr >> file) {
        files.push_back(file);
        //cout << file << endl;
    }

    // get exception file
    ifstream exc_istr(files[0]);
    if (exc_istr.fail()) return Usage(argv[0], 1);   
    
    ifstream target(argv[1]);
    if (target.fail()) return Usage(argv[0], 3);  
    
    WordCount target_doc;
    if (!target_doc.ReadExceptions(exc_istr)) return Usage(argv[0], 4);
    if (!target_doc.Read(target)) return Usage(argv[0], 0); 
	
	wc.push_back(target_doc);

    // document 1 starts at index 1 of files vector
    for (unsigned int i = 1; i < files.size(); i++){
        // get the document
        ifstream istr(files[i]);
        if (istr.fail()) return Usage(argv[0], 2);
        
        WordCount document;
        if (!document.ReadExceptions(exc_istr)) return Usage(argv[0], 5);
        if (!document.Read(istr)) return Usage(argv[0], 0);   
        
        //document.Write(cout);
        
        wc.push_back(document);
    }
    
    TFIDF tfidf(wc);
	tfidf.compare(cout);
	
	double highest = -100000;
	double index = -1;
	
    // only documents within reading range
    for (unsigned int i = 1; i < wc.size(); i++){
        double RL = wc[i].getReadingLevel();
		//cout << RL << endl;
		double value = tfidf.comparisons[i];
		if (value > highest && RL >= lower_bound && RL <= higher_bound) {
			highest = value;
			index = i;
		}
    }	
	
	if (index == -1){
		return Usage(argv[0], 6);
	}else {
		cout << files[index] << endl;
	}	
    
    return 0;
}
