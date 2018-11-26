#include <TFIDF.h>

bool TFIDF::compare(ostream& ostr)
{
	double sum;
	//for (unsigned int i = 0; i < documents.size(); i++){
		for (double j = 0; j < documents.size(); j++){
			// populate the intersect vector
			intersection(documents[0], documents[j]);
			sum = 0;
			// For every word in the intersection of the documents, multiply the two TFIDF scores together, and sum those products
			for (double k = 0; k < intersect.size(); k++){
				sum += (tfidf(intersect[k], documents[0]) * tfidf(intersect[k], documents[j]));
			}
			intersect.clear();
			//ostr << sum << " ";
			comparisons.push_back(sum);
		}
		
	    //ostr << endl;
	//}
	return false;
}

double TFIDF::compare(WordCount& doc1, WordCount& doc2)
{
    double sum = 0;
    
    // populate the intersect vector
    intersection(doc1, doc2);
    // For every word in the intersection of the documents, multiply the two TFIDF scores together, and sum those products
    for (double k = 0; k < intersect.size(); k++){
        sum += (tfidf(intersect[k], doc1) * tfidf(intersect[k], doc2));
    }
    intersect.clear();
    
    return sum;
}

double TFIDF::tfidf(string& word, WordCount& document)
{	
	return tf(word, document) * idf(word);
}

double TFIDF::tf(string& word, WordCount& document)
{	
	return document.findWordCount(word);
}

double TFIDF::idf(string& word)
{	
	return log10 (documents.size() / numberOfDocsContainingWord(word));
}

double TFIDF::numberOfDocsContainingWord(string& word)
{
	double count = 0;
	for (double i = 0; i < documents.size(); i++){
		if (documents[i].findWordCount(word) > 0){
			count++;
		}
	}
	
	return count;
}

void TFIDF::intersection(WordCount& doc1, WordCount& doc2)
{
	for (double i = 0; i < doc1.f_words.size(); i++){
		for (double j = 0; j < doc2.f_words.size(); j++){
			if (doc1.f_words[i] == doc2.f_words[j]){
				// words must not be punctuation words...
				if (!isPunct(doc1.f_words[i])) {
					intersect.push_back(doc1.f_words[i]);
					continue;
				}
			}
		}
	}
	
}

bool TFIDF::isPunct(const string& word) const
{
	for (unsigned int i = 0; i < word.length(); i++){
        if (!ispunct(word[i])){
            return false;
        }
    }    
    return true;
}
