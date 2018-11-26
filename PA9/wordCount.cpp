#include <wordCount.h>

bool WordCount::Read (istream& istr) 
{
	string word;
	
	// read in words
	while(istr >> word) {
		
		while (!word.empty()){
			// if alpha numeric
			if (lex.isAlnum(word[0])){				
				addAlnum(word);
                word_count++;
			}
			// if punctuation
			if (lex.isPunct(word[0])){
				if (lex.isPeriodPartOfWord(0, word)){
					addPunct(word);
				} else // not period
				{
					addOther(word);
				}
			}
		}
	}
	
	if (istr.eof()){
        if (!words.empty()){
			// check for ambiguous words, then resolve (and stem if lowercase)
            resolveAmbiguous();
			
			sort(words.begin(), words.end());
            
			finalWordCounts();
			
			return true;
		} 
        else return false;
	}else if (istr.fail()) {
		return false;
	}
	
	return false;
}

bool WordCount::ReadExceptions (istream& istr)
{
    return exc.Read(istr);
}

void WordCount::addAlnum(string& word)
{
	string end, subword;
	
	for (unsigned int i = 0; i <= word.length(); i++){
		if (!lex.isCommaPartOfWord(i, word)){
			if (!lex.isPeriodPartOfWord(i, word)){
				if (!lex.isAlnum(word[i])){
					subword = word.substr(0,i);
					//stem.step1(subword);
					words.push_back(subword);
					word = word.substr(i);
					
					end = words.back();
					letter_count += end.length();
					// if capital letter, not acronym, doesn't contain digit, and is start of sentence
					if (isupper(end[0]) != 0 && !lex.isAcronym(end) && !lex.containsDigit(end) && isStartOfSentence((words.size()) - 1)){
						words.back() = "+" + words.back();
					}
					
					string w = words.back();
					if (!any_of(w.begin(), w.end(), &::isupper) && w[0] != '+' && !any_of(w.begin(), w.end(), ::isdigit)){
                        // if word is in exception, switch it. Otherwise stem it
                        if (!exc.isException(words.back())){
                            stem.step1(words.back());
                        }
					}
					
					break;
				}
			}
		}
	}
}

void WordCount::addPunct(string& word)
{
	for (unsigned int i = 1; i <= word.length(); i++){
		if (!lex.isAlnum(word[i])){
			// as long as there are periods that belong in the word, keep them there and don't split
			if (word[i] == '.' && lex.isPeriodPartOfWord(i, word))
				continue;
			words.push_back(word.substr(0,i));
			word = word.substr(i);
			// see if it ends a sentence
            if (lex.containsPEQ(words.back())){
                sentence_count++;
            } 
			break;
		}
	}
}

void WordCount::addOther(string& word)
{
	for (unsigned int i = 0; i <= word.length(); i++){
		if (!lex.isPunct(word[i])){
			words.push_back(word.substr(0,i));
			word = word.substr(i);
			// see if it ends a sentence
            if (lex.containsPEQ(words.back())){
                sentence_count++;
            } 
			break;			
		}		
	}
}

bool WordCount::isStartOfSentence(const int index) const
{
	if (lex.isAlphaNumeric(words[index])){
		// first word of file or word before contains period, exclamation or question mark
		if (index == 0 || lex.containsPEQ(words[index - 1])) return true;		
	}	
	return false;
} 

void WordCount::resolveAmbiguous()
{
	string bare_word, bare_word_lower;	
	
	for (double i = 0; i < words.size(); i++){
		
		// if word has a '+', check it!
        if (words[i][0] == '+'){
			bare_word = words[i].substr(1);
			
			// and if there's one or more of the same UNambiguous word
			if (findWordCount(bare_word) >= 1){
				
				// appears more than once, so remove +
				words[i] = bare_word;
				
			} else {
				// otherwise remove + and uncapitalize first letter
				words[i] = words[i].substr(1);
				words[i][0] = tolower(words[i][0]);
                
                // if word is in exception, switch it. Otherwise stem it
                if (!exc.isException(words[i])){
                    stem.step1(words[i]);
                }
			}
		}
	}
}

int WordCount::findWordCount(const string& word) const
{
    int count = 0;
    for (double i = 0; i < words.size(); i++){
        if (words[i] == word){
            count++;
        }
    }
    
    return count;
}

void WordCount::finalWordCounts()
{
	int count = 1;
	for (double i = 0; i < words.size(); i++){
	  
		if (words[i] == words[i+1]){
			count++;
		} else {
			f_words.push_back(words[i]);
			f_count.push_back(count);
			count = 1;
		}	
	}
}

bool WordCount::Write(ostream& ostr) const
{
  if (ostr.fail()) return false;

  int count = 1;
  for (double i = 0; i < words.size(); i++){
      
    if (words.operator[](i) == words.operator[](i+1)){
        count++;
    } else {
        ostr << words.operator[](i) << " " << count;
        ostr << endl;
        count = 1;
    }	
  }

  return true;
}


// false = punctuation string
bool WordCount::isWord(const string& word) const
{
    for (double i = 0; i < word.length(); i++){
        if (!ispunct(word[i])){
            return true;
        }
    }
    
    return false;
}

double WordCount::getReadingLevel()
{
    return 0.0588*L() - 0.296*S() - 15.8;
}

// total number of letters in the word strings in the file/(100 * words)
double WordCount::L()
{
    return (letter_count/word_count) * 100;
}

// number of sentences/(100 * number of words)
double WordCount::S()
{
    return (sentence_count/word_count) * 100;
}
