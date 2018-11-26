#ifndef TFIDF_H_INCLUDE
#define TFIDF_H_INCLUDE

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
#include "wordCount.h"

using std::endl;
using std::vector;
using std::string;


class TFIDF {
public:
    TFIDF() {};
	TFIDF(vector<WordCount>& docs) : documents(docs) {};
	
	bool compare(ostream& ostr);
    double compare(WordCount& doc1, WordCount& doc2);
	vector<double> comparisons;

private:

	double tfidf(string& word, WordCount& document);
	double tf(string& word, WordCount& document);
	double idf(string& word);
	void intersection(WordCount& doc1, WordCount& doc2);
	double numberOfDocsContainingWord(string& word);
	bool isPunct(const string& word) const;
	
	vector<WordCount> documents;
	vector<string> intersect;
	int num_documents;
};

#endif // TFIDF_H_INCLUDE
