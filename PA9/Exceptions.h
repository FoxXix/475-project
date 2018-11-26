#ifndef EXCEPTIONS_H_INCLUDE
#define EXCEPTIONS_H_INCLUDE

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

using std::endl;
using std::vector;
using std::string;
using std::istream;

class Exceptions {
public:
	
    bool Read (istream& istr);
    bool isException(string& word);
    
    vector<string> exc_words;
    vector<string> exc_stems;

private:
    
    

};

#endif // EXCEPTIONS_H_INCLUDE
