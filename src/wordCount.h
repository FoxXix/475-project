#ifndef WORDCOUNT_H_INCLUDE
#define WORDCOUNT_H_INCLUDE

/*! \file wordCount.h: Declares the WordCount class 
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "Lexeme.h"
#include "Stemmer.h"
#include "Exceptions.h"

using std::istream;
using std::ostream;
using std::endl;
using std::vector;
using std::string;
using std::sort;
using std::all_of;
using std::any_of;

/** The idea is to read in the file
 * and place every word in a vector.
 * After all words are in the vector,
 * I sort it.
 * With all words in lexical order,
 * I traverse the vector counting duplicates
 * as I print the output.
 */

class WordCount {
public:
  /// Constructor 

  /* simple accessors */
  
  /**\param ostr output stream
   * \return boolean showing if function worked
   */
  bool Write(ostream& ostr) const;
  /**\param index location of character
   * \return boolean whether char is at the beginning of sentence or not
   */
  bool isStartOfSentence(const int index) const;
    /**\param word string to be counted
   * \return int number of words found in document
   */
  int findWordCount(const string& word) const;
  /**\param word string to checked
   * \return bool returns true if word is not a punctuation string
   */
  bool isWord(const string& word) const; 
  /**\param none
   * \return double returns reading level of document
   */  
  double getReadingLevel();
  
  /* Mutators */  
  
  /**\param istr input stream
   * \return boolean if function successfully read document
   */ 
  bool Read (istream& istr);
  /**\param istr input stream
   * \return boolean if function successfully read exception document
   */ 
  bool ReadExceptions (istream& istr);
  /**\param word string to be checked
   * \return void
   */ 
  void addAlnum(string& word);
  /**\param word string to be checked
   * \return void
   */ 
  void addPunct(string& word);
  /**\param word string to be checked
   * \return void
   */ 
  void addOther(string& word);
  /**\param none
   * \return void
   */ 
  void resolveAmbiguous();
  /**\param none
   * \return void
   */ 
  void finalWordCounts();
  /**\param none
   * \return double word count letters
   */ 
  double L();
  /**\param none
   * \return doube sentence count
   */ 
  double S();
  
  inline double getWordCount(){ return word_count; };
  inline double getLetterCount(){ return letter_count; };
  inline double getSentenceCount(){ return sentence_count; };
  
  vector<string> words;
  vector<string> f_words;
  vector<int> f_count; 

private:
    
	Lexeme lex;
	Stemmer stem;
    Exceptions exc;
    
    double word_count = 0;
	double letter_count = 0;
	double sentence_count = 0;
};

#endif // WORDCOUNT_H_INCLUDE
