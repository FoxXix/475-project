#ifndef Stemmer_H_INCLUDE
#define Stemmer_H_INCLUDE

#include <string>
#include <iostream>

using std::string;

class Stemmer {
public:


	void step1(string& word);
	string getRegion1(string& word);
	string getRegion2(string& word);

private:

	void step2(string& word);
	void step3(string& word);
    void step4(string& word);
    void step5(string& word);
	void step6(string& word);
	void step7(string& word);
	void step8(string& word);
    
	bool isVowel(const string& word, int index) const;
	
    bool isShort(string& word);
    bool endsShortSyllable(const string& word) const;
    bool step3Replace(string& word);
    bool containsSuffix(const string& word, string suffix) const;
    bool replace(string& word, string suffix, string replacement);
    bool validLIEnding(string& word, int suffixSize);
	
	string region1, region2;
	string doubles[9] = {"bb", "dd", "ff", "gg", "mm", "nn", "pp", "rr", "tt"};
};

#endif // Stemmer_H_INCLUDE
