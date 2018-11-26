#include <Stemmer.h>

void Stemmer::step1(string& word)
{
	bool replaced = false;
	region1 = "";
	region2 = "";
	
	if (word.length() > 2){
	
		if (word[0] == '\''){
			// remove first apostrophe
			//word.erase( 0,1 );
			word = word.substr(1);
		}
		
		// if suffix is 's'
		if (word.length() >= 3){
			if (0 == word.compare( word.length() - 3, 3, "'s'")){
				word = word.substr( 0, word.length() - 3 );
				replaced = true;
			}
		}	
		
		// if suffix is 's
		if ( !replaced && word.length() >= 2 ){
			if (0 == word.compare( word.length() - 2, 2, "'s")){
				word = word.substr( 0, word.length() - 2 );
				replaced = true;
			}
		}
		
		// if suffix is '
		if ( !replaced && word.length() >= 1 ){
			if (0 == word.compare( word.length() - 1, 1, "'")){
				word = word.substr( 0, word.length() - 1 );
			}
		}
		
		step2(word);
	}
}

void Stemmer::step2(string& word)
{
	bool replaced = false;
	
	// if suffix is sses
	if (word.length() >= 4){
		if (0 == word.compare( word.length() - 4, 4, "sses")){
			word = word.substr( 0, word.length() - 4 );
			word += "ss";
			replaced = true;
		}
	}
	
	// if suffix is ied or ies
	if ( !replaced && word.length() >= 3 ){
		if (0 == word.compare( word.length() - 3, 3, "ied") || 0 == word.compare( word.length() - 3, 3, "ies")){
			word = word.substr( 0, word.length() - 3 );
			// if preceder contains more than one letter, replace with i. Otherwise replace with ie
			if (word.length() > 1){
				word += "i";
			}else{
				word += "ie";
			}
			replaced = true;
		}
	}
	
	// if suffix is us
	if ( !replaced && word.length() >= 2 ){
		if (0 == word.compare( word.length() - 2, 2, "us")){
			replaced = true;
		}
	}
	
	// if suffix is ss
	if ( !replaced && word.length() >= 2 ){
		if (0 == word.compare( word.length() - 2, 2, "ss")){
			replaced = true;
		}
	}
	
	// if suffix is s
	if ( !replaced && word.length() >= 1 ){
		if (0 == word.compare( word.length() - 1, 1, "s")){
			
			// preceding word part contains a vowel not immediately before the s
			for (unsigned int i = 0; i < word.length() - 2; i++){
				if (isVowel(word, i)){
					word = word.substr( 0, word.length() - 1 );
					//std::cout << word << '\n';
					break;
				}
			}
		}
	}
	
	step3(word);
}

void Stemmer::step3(string& word)
{
	bool replaced = false;
	
	// if suffix is eed or eedly
	if (word.length() >= 3){
		if (0 == word.compare( word.length() - 3, 3, "eed")){
			string R1 = getRegion1(word);
			if (R1.find("eed") != std::string::npos){
				word = word.substr( 0, word.length() - 3 );
				word += "ee";
                replaced = true;
			}			
		}
	} 
	
	if (!replaced && word.length() >= 5){
        if (0 == word.compare( word.length() - 5, 5, "eedly")){
            string R1 = getRegion1(word);
            if (R1.find("eedly") != std::string::npos){
				word = word.substr( 0, word.length() - 5 );
				word += "ee";
                replaced = true;
			}
        }
    }
	
	// if suffix is ed 
	if ( !replaced && word.length() >= 2 ){
		if (0 == word.compare( word.length() - 2, 2, "ed")){
			word = word.substr( 0, word.length() - 2 );
			for (unsigned int i = 0; i < word.length(); i++){
				if(isVowel(word, i)){
					replaced = step3Replace(word);
					break;
				}
			}			
		}
	}
	
	// if suffix is edly
	if ( !replaced && word.length() >= 4 ){
		if (0 == word.compare( word.length() - 4, 4, "edly")){
			word = word.substr( 0, word.length() - 4 );
			for (unsigned int i = 0; i < word.length(); i++){
				if(isVowel(word, i)){
					replaced = step3Replace(word);
					break;
				}
			}
		}
	}
	
	// if suffix is ing
	if ( !replaced && word.length() >= 3 ){
		if (0 == word.compare( word.length() - 3, 3, "ing")){
			word = word.substr( 0, word.length() - 3 );
			for (unsigned int i = 0; i < word.length(); i++){
				if(isVowel(word, i)){
					replaced = step3Replace(word);
					break;
				}
			}
		}
	}	
	
	// if suffix is ingly
	if ( !replaced && word.length() >= 5 ){
		if (0 == word.compare( word.length() - 5, 5, "ingly")){
			word = word.substr( 0, word.length() - 5 );
			for (unsigned int i = 0; i < word.length(); i++){
				if(isVowel(word, i)){
					replaced = step3Replace(word);
					break;
				}
			}
		}
	}
	
	step4(word);
}

void Stemmer::step4(string& word)
{
    // if suffix is y
	if (word.length() > 0){
		if (0 == word.compare( word.length() - 1, 1, "y")){
			//Suffix follows a non-vowel that is not the first letter of the preceder. 
			if (!isVowel(word, word.length() - 2) && ((word.length() - 2) != 0)){
				word = word.substr( 0, word.length() - 1 );
				word += "i";
			}
		}
	}
    
    step5(word);
}

void Stemmer::step5(string& word)
{
    bool replaced = false;
	
	// if suffix is tional
	if (word.length() >= 6){
		if (0 == word.compare( word.length() - 6, 6, "tional")){
			word = word.substr( 0, word.length() - 6 );
			word += "tion";
			replaced = true;
		}
	}
	
	// if suffix is enci
	if ( !replaced && word.length() >= 4 ){
		if (0 == word.compare( word.length() - 4, 4, "enci")){
			word = word.substr( 0, word.length() - 4 );
			word += "ence";
			replaced = true;
		}
	}
	
	// if suffix is anci
	if ( !replaced && word.length() >= 4 ){
		if (0 == word.compare( word.length() - 4, 4, "anci")){
			word = word.substr( 0, word.length() - 4 );
			word += "ance";
			replaced = true;
		}
	}
	
	// if suffix is abli
	if ( !replaced && word.length() >= 4 ){
		if (0 == word.compare( word.length() - 4, 4, "abli")){
			word = word.substr( 0, word.length() - 4 );
			word += "able";
			replaced = true;
		}
	}
	
	// if suffix is entli
	if ( !replaced && word.length() >= 5 ){
		if (0 == word.compare( word.length() - 5, 5, "entli")){
			word = word.substr( 0, word.length() - 5 );
			word += "ent";
			replaced = true;
		}
	}
	
	// if suffix is izer
	if ( !replaced && word.length() >= 4 ){
		if (0 == word.compare( word.length() - 4, 4, "izer")){
			word = word.substr( 0, word.length() - 4 );
			word += "ize";
			replaced = true;
		}
	}
	
	// if suffix is ization
	if ( !replaced && word.length() >= 7 ){
		if (0 == word.compare( word.length() - 7, 7, "ization")){
			word = word.substr( 0, word.length() - 7 );
			word += "ize";
			replaced = true;
		}
	}
	
	// if suffix is ational
	if ( !replaced && word.length() >= 7 ){
		if (0 == word.compare( word.length() - 7, 7, "ational")){
			word = word.substr( 0, word.length() - 7 );
			word += "ate";
			replaced = true;
		}
	}
	
	// if suffix is ation
	if ( !replaced && word.length() >= 5 ){
		if (0 == word.compare( word.length() - 5, 5, "ation")){
			word = word.substr( 0, word.length() - 5 );
			word += "ate";
			replaced = true;
		}
	}
	
	// if suffix is ator
	if ( !replaced && word.length() >= 4 ){
		if (0 == word.compare( word.length() - 4, 4, "ator")){
			word = word.substr( 0, word.length() - 4 );
			word += "ate";
			replaced = true;
		}
	}
	
	// if suffix is alism
	if ( !replaced && word.length() >= 5 ){
		if (0 == word.compare( word.length() - 5, 5, "alism")){
			word = word.substr( 0, word.length() - 5 );
			word += "al";
			replaced = true;
		}
	}
	
	// if suffix is aliti
	if ( !replaced && word.length() >= 5 ){
		if (0 == word.compare( word.length() - 5, 5, "aliti")){
			word = word.substr( 0, word.length() - 5 );
			word += "al";
			replaced = true;
		}
	}
	
	// if suffix is alli
	if ( !replaced && word.length() >= 4 ){
		if (0 == word.compare( word.length() - 4, 4, "alli")){
			word = word.substr( 0, word.length() - 4 );
			word += "al";
			replaced = true;
		}
	}
	
	// if suffix is fulness
	if ( !replaced && word.length() >= 7 ){
		if (0 == word.compare( word.length() - 7, 7, "fulness")){
			word = word.substr( 0, word.length() - 7 );
			word += "ful";
			replaced = true;
		}
	}
	
	// if suffix is ousli
	if ( !replaced && word.length() >= 5 ){
		if (0 == word.compare( word.length() - 5, 5, "ousli")){
			word = word.substr( 0, word.length() - 5 );
			word += "ous";
			replaced = true;
		}
	}
	
	// if suffix is ousness
	if ( !replaced && word.length() >= 7 ){
		if (0 == word.compare( word.length() - 7, 7, "ousness")){
			word = word.substr( 0, word.length() - 7 );
			word += "ous";
			replaced = true;
		}
	}
	
	// if suffix is iveness
	if ( !replaced && word.length() >= 7 ){
		if (0 == word.compare( word.length() - 7, 7, "iveness")){
			word = word.substr( 0, word.length() - 7 );
			word += "ive";
			replaced = true;
		}
	}
	
	// if suffix is iviti
	if ( !replaced && word.length() >= 5 ){
		if (0 == word.compare( word.length() - 5, 5, "iviti")){
			word = word.substr( 0, word.length() - 5 );
			word += "ive";
			replaced = true;
		}
	}
	
	// if suffix is biliti
	if ( !replaced && word.length() >= 6 ){
		if (0 == word.compare( word.length() - 6, 6, "biliti")){
			word = word.substr( 0, word.length() - 6 );
			word += "ble";
			replaced = true;
		}
	}
	
	// if suffix is bli
	if ( !replaced && word.length() >= 3 ){
		if (0 == word.compare( word.length() - 3, 3, "bli")){
			word = word.substr( 0, word.length() - 3 );
			word += "ble";
			replaced = true;
		}
	}
	
	// if suffix is ogi
	if ( !replaced && word.length() >= 3 ){
		if (0 == word.compare( word.length() - 3, 3, "ogi")){
            //Suffix preceded by l
            if (word[word.length() - 4] == 'l'){
                word = word.substr( 0, word.length() - 3 );
                word += "og";
                replaced = true;
            }
		}
	}
	
	// if suffix is fulli
	if ( !replaced && word.length() >= 5 ){
		if (0 == word.compare( word.length() - 5, 5, "fulli")){
			word = word.substr( 0, word.length() - 5 );
			word += "ful";
			replaced = true;
		}
	}
	
	// if suffix is lessli
	if ( !replaced && word.length() >= 6 ){
		if (0 == word.compare( word.length() - 6, 6, "lessli")){
			word = word.substr( 0, word.length() - 6 );
			word += "less";
			replaced = true;
		}
	}
	
	// if suffix is li
	if ( !replaced && word.length() >= 2 ){
		if (0 == word.compare( word.length() - 2, 2, "li")){
            //Preceder ends in a valid li ending
            if (validLIEnding(word, 2)){
                word = word.substr( 0, word.length() - 2 );
                replaced = true;
            }
		}
	}
	
	step6(word);
}

void Stemmer::step6(string& word)
{
    bool replaced = false;
	
	// if suffix is tional
	if (word.length() >= 6){
		if (0 == word.compare( word.length() - 6, 6, "tional")){
			string R1 = getRegion1(word);
			if (R1.find("tional") != std::string::npos){
				word = word.substr( 0, word.length() - 6 );
				word += "tion";
                replaced = true;
			}			
		}
	}
	
	// if suffix is ational
	if (!replaced && word.length() >= 7){
		if (0 == word.compare( word.length() - 7, 7, "ational")){
			string R1 = getRegion1(word);
			if (R1.find("ational") != std::string::npos){
				word = word.substr( 0, word.length() - 7 );
				word += "ate";
                replaced = true;
			}			
		}
	}
	
	// if suffix is alize
	if (!replaced && word.length() >= 5){
		if (0 == word.compare( word.length() - 5, 5, "alize")){
			string R1 = getRegion1(word);
			if (R1.find("alize") != std::string::npos){
				word = word.substr( 0, word.length() - 5 );
				word += "al";
                replaced = true;
			}			
		}
	}
	
	// if suffix is icate
	if (!replaced && word.length() >= 5){
		if (0 == word.compare( word.length() - 5, 5, "icate")){
			string R1 = getRegion1(word);
			if (R1.find("icate") != std::string::npos){
				word = word.substr( 0, word.length() - 5 );
				word += "ic";
                replaced = true;
			}			
		}
	}
	
	// if suffix is iciti
	if (!replaced && word.length() >= 5){
		if (0 == word.compare( word.length() - 5, 5, "iciti")){
			string R1 = getRegion1(word);
			if (R1.find("iciti") != std::string::npos){
				word = word.substr( 0, word.length() - 5 );
				word += "ic";
                replaced = true;
			}			
		}
	}
	
	// if suffix is ical
	if (!replaced && word.length() >= 4){
		if (0 == word.compare( word.length() - 4, 4, "ical")){
			string R1 = getRegion1(word);
			if (R1.find("ical") != std::string::npos){
				word = word.substr( 0, word.length() - 4 );
				word += "ic";
                replaced = true;
			}			
		}
	}
	
	// if suffix is ful
	if (!replaced && word.length() >= 3){
		if (0 == word.compare( word.length() - 3, 3, "ful")){
			string R1 = getRegion1(word);
			if (R1.find("ful") != std::string::npos){
				word = word.substr( 0, word.length() - 3 );
                replaced = true;
			}			
		}
	}
	
	// if suffix is ness
	if (!replaced && word.length() >= 4){
		if (0 == word.compare( word.length() - 4, 4, "ness")){
			string R1 = getRegion1(word);
			if (R1.find("ness") != std::string::npos){
				word = word.substr( 0, word.length() - 4 );
                replaced = true;
			}			
		}
	}
	
	// if suffix is ative
	if (!replaced && word.length() >= 5){
		if (0 == word.compare( word.length() - 5, 5, "ative")){
			string R2 = getRegion2(word);
			if (R2.find("ative") != std::string::npos){
				word = word.substr( 0, word.length() - 5 );
                replaced = true;
			}			
		}
	}
	
	step7(word);
}

void Stemmer::step7(string& word)
{
    bool replaced = false;
	
	// if suffix is al
	if (word.length() >= 2){
		if (0 == word.compare( word.length() - 2, 2, "al")){
			string R2 = getRegion2(word);
			if (R2.find("al") != std::string::npos){
				word = word.substr( 0, word.length() - 2 );
                replaced = true;
			}			
		}
	}
	
	// if suffix is ance
	if (!replaced && word.length() >= 4){
		if (0 == word.compare( word.length() - 4, 4, "ance")){
			string R2 = getRegion2(word);
			if (R2.find("ance") != std::string::npos){
				word = word.substr( 0, word.length() - 4 );
                replaced = true;
			}			
		}
	}
	
	// if suffix is ence
	if (!replaced && word.length() >= 4){
		if (0 == word.compare( word.length() - 4, 4, "ence")){
			string R2 = getRegion2(word);
			if (R2.find("ence") != std::string::npos){
				word = word.substr( 0, word.length() - 4 );
                replaced = true;
			}			
		}
	}
	
	// if suffix is er
	if (!replaced && word.length() >= 2){
		if (0 == word.compare( word.length() - 2, 2, "er")){
			string R2 = getRegion2(word);
			if (R2.find("er") != std::string::npos){
				word = word.substr( 0, word.length() - 2 );
                replaced = true;
			}			
		}
	}
	
	// if suffix is ic
	if (!replaced && word.length() >= 2){
		if (0 == word.compare( word.length() - 2, 2, "ic")){
			string R2 = getRegion2(word);
			if (R2.find("ic") != std::string::npos){
				word = word.substr( 0, word.length() - 2 );
                replaced = true;
			}			
		}
	}
	
	// if suffix is able
	if (!replaced && word.length() >= 4){
		if (0 == word.compare( word.length() - 4, 4, "able")){
			string R2 = getRegion2(word);
			if (R2.find("able") != std::string::npos){
				word = word.substr( 0, word.length() - 4 );
                replaced = true;
			}			
		}
	}
	
	// if suffix is ible
	if (!replaced && word.length() >= 4){
		if (0 == word.compare( word.length() - 4, 4, "ible")){
			string R2 = getRegion2(word);
			if (R2.find("ible") != std::string::npos){
				word = word.substr( 0, word.length() - 4 );
                replaced = true;
			}			
		}
	}
	
	// if suffix is ant
	if (!replaced && word.length() >= 3){
		if (0 == word.compare( word.length() - 3, 3, "ant")){
			string R2 = getRegion2(word);
			if (R2.find("ant") != std::string::npos){
				word = word.substr( 0, word.length() - 3 );
                replaced = true;
			}			
		}
	}
	
	// if suffix is ement
	if (!replaced && word.length() >= 5){
		if (0 == word.compare( word.length() - 5, 5, "ement")){
			string R2 = getRegion2(word);
			if (R2.find("ement") != std::string::npos){
				word = word.substr( 0, word.length() - 5 );
                replaced = true;
			}			
		}
	}
	
	// if suffix is ment
	if (!replaced && word.length() >= 4){
		if (0 == word.compare( word.length() - 4, 4, "ment")){
			string R2 = getRegion2(word);
			if (R2.find("ment") != std::string::npos){
				word = word.substr( 0, word.length() - 4 );
                replaced = true;
			}			
		}
	}
	
	// if suffix is ent
	if (!replaced && word.length() >= 3){
		if (0 == word.compare( word.length() - 3, 3, "ent")){
			string R2 = getRegion2(word);
			if (R2.find("ent") != std::string::npos){
				word = word.substr( 0, word.length() - 3 );
                replaced = true;
			}			
		}
	}
	
	// if suffix is ism
	if (!replaced && word.length() >= 3){
		if (0 == word.compare( word.length() - 3, 3, "ism")){
			string R2 = getRegion2(word);
			if (R2.find("ism") != std::string::npos){
				word = word.substr( 0, word.length() - 3 );
                replaced = true;
			}			
		}
	}
	
	// if suffix is ate
	if (!replaced && word.length() >= 3){
		if (0 == word.compare( word.length() - 3, 3, "ate")){
			string R2 = getRegion2(word);
			if (R2.find("ate") != std::string::npos){
				word = word.substr( 0, word.length() - 3 );
                replaced = true;
			}			
		}
	}
	
	// if suffix is iti
	if (!replaced && word.length() >= 3){
		if (0 == word.compare( word.length() - 3, 3, "iti")){
			string R2 = getRegion2(word);
			if (R2.find("iti") != std::string::npos){
				word = word.substr( 0, word.length() - 3 );
                replaced = true;
			}			
		}
	}
	
	// if suffix is ous
	if (!replaced && word.length() >= 3){
		if (0 == word.compare( word.length() - 3, 3, "ous")){
			string R2 = getRegion2(word);
			if (R2.find("ous") != std::string::npos){
				word = word.substr( 0, word.length() - 3 );
                replaced = true;
			}			
		}
	}
	
	// if suffix is ive
	if (!replaced && word.length() >= 3){
		if (0 == word.compare( word.length() - 3, 3, "ive")){
			string R2 = getRegion2(word);
			if (R2.find("ive") != std::string::npos){
				word = word.substr( 0, word.length() - 3 );
                replaced = true;
			}			
		}
	}
	
	// if suffix is ize
	if (!replaced && word.length() >= 3){
		if (0 == word.compare( word.length() - 3, 3, "ize")){
			string R2 = getRegion2(word);
			if (R2.find("ize") != std::string::npos){
				word = word.substr( 0, word.length() - 3 );
                replaced = true;
			}			
		}
	}
	
	// if suffix is ion
	if (!replaced && word.length() >= 3){
		if (0 == word.compare( word.length() - 3, 3, "ion")){
			string R2 = getRegion2(word);
			string preceder = word.substr(0, word.length() - 3);
			//Suffix must appear in Region2 and the preceder must end with an s or t.
			if (R2.find("ion") != std::string::npos && (preceder.back() == 's' || preceder.back() == 't')){
				word = word.substr( 0, word.length() - 3 );
                replaced = true;
			}			
		}
	}
	
	step8(word);
}

void Stemmer::step8(string& word)
{
    bool replaced = false;
	
	// if suffix is e
	if (word.length() >= 1){
		if (0 == word.compare( word.length() - 1, 1, "e")){
			string R1 = getRegion1(word);
			string R2 = getRegion2(word);
			string preceder = word.substr(0, word.length() - 1);
			//Suffix appears in Region2 OR suffix appears in Region1 and preceder does not end in a short syllable
			if ((R2.find("e") != std::string::npos) || ((R1.find("e") != std::string::npos) && !endsShortSyllable(preceder))){
				word = word.substr( 0, word.length() - 1 );
				replaced = true;
			}
			//if (((R1.find("e") != std::string::npos) || (R2.find("e")) != std::string::npos) && (!endsShortSyllable(preceder))){
			//	word = word.substr( 0, word.length() - 1 );
             //   replaced = true;
			//}			
		}
	}
	
	// if suffix is l
	if (!replaced && word.length() >= 1){
		if (0 == word.compare( word.length() - 1, 1, "l")){
			string R2 = getRegion2(word);
			string preceder = word.substr(0, word.length() - 1);
			//Suffix appears in Region2 and preceder ends in l (so word ends in ll)
			if (R2.find("l") != std::string::npos && preceder.back() == 'l'){
				word = word.substr( 0, word.length() - 1 );
			}			
		}
	}
}

bool Stemmer::validLIEnding(string& word, int suffixSize)
{
    string preceder = word.substr(0, word.length() - suffixSize);
    char c = preceder[preceder.length()-1];
    
    switch (c){
        case 'c':
        case 'd':
        case 'e':
        case 'g':
        case 'h':
        case 'k':
        case 'm':
        case 'n':
        case 'r':
        case 't':
            return true;
        default:
            return false;            
    }
}

bool Stemmer::replace(string& word, string suffix, string replacement)
{
    return false;
}

bool Stemmer::containsSuffix(const string& word, string suffix) const
{
    return (0 == word.compare( word.length() - suffix.length(), suffix.length(), suffix));
}

bool Stemmer::step3Replace(string& word)
{
    // if preceder ends in at, bl, or iz, add an e
    if (0 == word.compare( word.length() - 2, 2, "at") ||
        0 == word.compare( word.length() - 2, 2, "bl") ||
        0 == word.compare( word.length() - 2, 2, "iz") ){
            word += "e";
            return true;
        } 
        
        // if preceder ends in a double, remove the last letter
        //for (unsigned int i = 0; i < sizeof(doubles); i++){
		for (const string& text : doubles){
            if (0 == word.compare( word.length() - 2, 2, text)){
                word = word.substr(0, word.length() - 1);
                return true;
            }
        }
        
        //if the preceder is short, add an e
        if (isShort(word)){
            word += "e";
            return true;
        }        
        
        return false;
}

bool Stemmer::isShort(string& word)
{
    if (endsShortSyllable(word) && getRegion1(word).empty())
        return true;
    else
        return false;
}

bool Stemmer::endsShortSyllable(const string& word) const
{
	if (word.length() == 2 && isVowel(word, 0) && !isVowel(word, 1)){
        //The string is only two characters long, and is a vowel followed by a non-vowel
        return true;
    }
    //It ends with a non-vowel followed by a vowel followed by a non-vowel that is not one of {‘w’, ‘x’ or ‘y’}
    if (!isVowel(word, word.length()-1) && (word[word.length()-1] != 'w' || word[word.length()-1] != 'x' || word[word.length()-1] != 'y')){
        if (isVowel(word, word.length()-2)){
            if (!isVowel(word, word.length()-3)){
                return true;   
            }
        }
    } 
    
    return false;
}

//Region1 is the substring that follows the first consonant (non-vowel) that follows a vowel
string Stemmer::getRegion1(string& word)
{
	region1 = "";
	// go through the word, find the first vowel
	for (unsigned int i = 0; i < word.length(); i++){
		if (isVowel(word, i)){
			// after vowel, find if next char is a consonant
			if ( i+1 < word.length() && !isVowel(word, i+1))
				
				if ( i+2 < word.length()){
					region1 = word.substr(i+2);
					break;
				}
		}
	}
	return region1;
}

//Region2 is the Region1 of Region1
string Stemmer::getRegion2(string& word)
{
	string R1 = "";
	// go through the word, find the first vowel
	for (unsigned int i = 0; i < word.length(); i++){
		if (isVowel(word, i)){
			// after vowel, find if next char is a consonant
			if ( i+1 < word.length() && !isVowel(word, i+1)){
				
				if ( i+2 < word.length()){
					R1 = word.substr(i+2);
					break;					
				}
			}
		}
	}
	
	int pos = word.find(R1);
	region2 = "";
	for (double i = 0; i < R1.length(); i++){
		if (isVowel(word, i + pos)){
			if ( i+pos+1 < word.length() && !isVowel(word, i+pos+1)){
				
				if ( i+pos+2 < word.length()){
					region2 = word.substr(i+pos+2);
					break;					
				}
			}
		}
	}
	
	return region2;
}

bool Stemmer::isVowel(const string& word, int index) const
{
	char c = word[index];
	
	switch (tolower(c)){
		case 'a':
		case 'e':
		case 'i':
		case 'o':
		case 'u':
			return true;
		case 'y':
			if (index == 0){
				return false;
			}
			if (isVowel(word, index -1))
				return false;
			return true;
		default:
			return false;
	}	
}
