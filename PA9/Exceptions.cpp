#include <Exceptions.h>

bool Exceptions::Read (istream& istr) 
{
	string word, stem, line, test;
	
	// read in exceptions into two separate vectors
    // vector indexes will be
	while (std::getline(istr, line)){
		std::istringstream iss(line);
		
		// if the line is empty, not an error
		if (line.empty())
			continue;
		// check if exception has a stem ( > 1 word in line)
		if (!(iss >> word >> stem))
			return false;
		// check if there are more than 2 words per line
		if (iss >> test)
			return false;
		
		exc_words.push_back(word);
		exc_stems.push_back(stem);
	}
	
	if (istr.eof()){
        // every word needs to have a corresponding stem
        if (exc_words.size() == exc_stems.size()){
            return true;
        } else {
            return false;
        }
	}else if (istr.fail()) {
		return false;
	}
	
	return false;
}

// checks if the word is an exception and replaces it
bool Exceptions::isException (string& word) 
{
    for (double i = 0; i < exc_words.size(); i++){
        if ( word == exc_words[i] ){
            word = exc_stems[i];
            return true;
        }
    }
    
    return false;
}
