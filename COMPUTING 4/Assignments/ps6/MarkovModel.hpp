/*
 * MarkovModel.hpp
 * Credits: Prof Fred Martin
 */


#include <string>
#include <map>

class MarkovModel {
 public:
  MarkovModel(std::string text, int k); /*  create a Markov model of order k from given text
					    Assume that text has length at least k. */
  //~MarkovModel();
  int order(); // order k of Markov model
  int freq(std::string kgram); /* number of occurrences of kgram in text
				(throw an exception if kgram is not of length k)*/
  int freq(std::string kgram, char c); // number of times that character c follows kgram
  char randk(std::string kgram); /* random character following given kgram
				    (Throw an exception if kgram is not of length k.
				    Throw an exception if no such kgram.)*/
  std::string gen(std::string kgram, int T); /* generate a string of length T characters
                            by simulating a trajectory through the corresponding
                            Markov chain.  The first k characters of the newly
                            generated string should be the argument kgram.
                            Throw an exception if kgram is not of length k.
                            Assume that T is at least k.
           <<               overload the stream insertion operator and display
                            the internal state of the Markov Model. Print out
                            the order, the alphabet, and the frequencies of
                            the k-grams and k+1-grams.*/

  friend std::ostream& operator<< (std::ostream &out, MarkovModel &mm);

 private:
  int _order;
  std::map <std::string, int> _kgrams;  // must #include <map>
  std::string _alphabet;
  std::string charString;
};
