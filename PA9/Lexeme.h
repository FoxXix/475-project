#ifndef LEXEME_H_INCLUDE
#define LEXEME_H_INCLUDE

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using std::endl;
using std::vector;
using std::string;


class Lexeme {
public:
	bool isPunct(const char& c) const;
	bool isAlnum(const char& c) const;
	bool isCommaPartOfWord(const int index, const string& word) const;
	bool isPeriodPartOfWord(const int index, const string& word) const;
	bool isAcronym(const string& word) const;
	bool isAlphaNumeric(const string& word) const;
	
	bool containsDigit(const string& word) const;
	bool containsPEQ(const string& word) const;

private:

};

#endif // LEXEME_H_INCLUDE
