#include <Lexeme.h>

bool Lexeme::isPunct(const char& c) const
{
	if ( c == '\'') return false;
	return ispunct(c);
}

bool Lexeme::isAlnum(const char& c) const
{
	if (c == '\'') return true;
	return isalnum(c);
}

bool Lexeme::isCommaPartOfWord(const int index, const string& word) const
{
	if (word[index] == ',' && isdigit( word[index - 1]) && isdigit( word[index + 1])) 
		return true;	
	return false;
}

bool Lexeme::isPeriodPartOfWord(const int index, const string& word) const
{
	if (word[index] == '.' && isdigit( word[index + 1]) && ( index == 0 || isdigit( word[index - 1]) ))
		return true;
	return false;
}

bool Lexeme::isAcronym(const string& word) const
{
    bool result = false;
    if (word.length() == 1){
        return result;
    } else {
        if (!isalpha(word[0])) return false;
        for (unsigned int i = 1; i < word.length(); i++){
            if (!isalpha(word[i])) return false;
            if (isupper(word[i])) result = true;
        }
    }
    return result;
}

bool Lexeme::isAlphaNumeric(const string& word) const
{
    for (unsigned int i = 0; i < word.length(); i++){
        if (!isAlnum(word[i])){
            return false;
        }
    }
    return true;
}

bool Lexeme::containsDigit(const string& word) const
{
	if (word.length() == 1 && isdigit(word[0])){
		if (isdigit(word[0]))
			return true;
		else
			return false;
	} else {
		for (unsigned int i = 0; i < word.length(); i++){
            if (isdigit(word[i])) return true;
        }
		return false;
	}
}

bool Lexeme::containsPEQ(const string& word) const
{
	for (unsigned int i = 0; i < word.length(); i++){
		if (word[i] == '.' || word[i] == '!' || word[i] == '?') return true;		
	}
	return false;
}