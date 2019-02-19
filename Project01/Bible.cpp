// Bible class function definitions
// Computer Science, MVNU

#include "Ref.h"
#include "Verse.h"
#include "Bible.h" 
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;


//Bible::Bible() { infile = "/home/class/csc3004/Bibles/kjv-complete"; }	// Default constructor
//Bible::Bible(const string s) { infile = s; }						    // Constructor – pass bible filename

Bible::Bible() { infile = "/home/class/csc3004/Bibles/kjv-complete", version = 1; }						// Default constructor - kjv and version 1
Bible::Bible(const string s, int i) { infile = s; version = i; }										// Default Constructor – pass bible filename




//Main lookup function - will forward along all other overloads to this function using dummy data
Verse* Bible::lookup(const int numberOfVerses, Ref ref, LookupResult &status, Ref& prev) {
	//initialize status to 'OTHER'
	status = OTHER;	

	//start with error check
	if (ref.getBook() < MIN_BOOK || ref.getBook() > MAX_BOOK) {
		status = NO_BOOK;
	}
	if (ref.getChap() < 1) {
		status = NO_CHAPTER;
	}
	if (ref.getVerse() < 1) {
		status = NO_VERSE;
	}
	else {

		ifstream bibleFile(infile.c_str());
		string currentLine;

		while (getline(bibleFile, currentLine)) {
			//load the Ref object with data
			Ref readRef = Ref(currentLine);

			//if our ref object's book is equal to ref.getBook() and ref object's chapter is higher than ref.getChap(), then there is no associated verse (went beyond chapter)
			if ((readRef.getBook() == ref.getBook()) && (readRef.getChap() > ref.getChap())) {
				status = NO_VERSE;
				break;
			}
			//if our ref object's book is higher than ref.getBook() there is no associated chapter (we went too far - went beyond book)
			else if (readRef.getBook() > ref.getBook()) {
				status = NO_CHAPTER;
				break;
			}
			//if the ref and ref object are identical, we found a match
			else if (ref == readRef) {
				status = SUCCESS;

				//create an array, loop through for each number of verses and add one verse to the array each time.
				Verse* arrayOfVerses = new Verse[numberOfVerses];
				arrayOfVerses[0] = Verse(currentLine);
				for (int i = 1; i < numberOfVerses && getline(bibleFile, currentLine); i++) {
					arrayOfVerses[i] = Verse(currentLine);
				}
				return arrayOfVerses;
			}
			else {
				prev = readRef;
			}
		}

	}
	cout << error(status);
	return NULL;
}

//If only one verse is needed, pass along to overloaded lookup function with a 1 for the 'numberOfVerses' parameter
Verse* Bible::lookup(Ref ref, LookupResult& status) { 
	return lookup(1,ref, status);
}

//If multiple verses are needed, but not the 'prev' reference, passes along a Ref 'r' to fulfill this prev parameter.
Verse* Bible::lookup(const int numberOfVerses, Ref ref, LookupResult& status)
{
	Ref r;
	return lookup(numberOfVerses, ref, status, r);
}

//string Bible::parseLine(string buffer) {
//	string localDelim = "\",\"";
//	string parsed;
//	for (int x = 0; x < version; x++) {
//		parsed = GetNextToken(buffer, localDelim);
//	}
//	parsed.erase(std::remove(parsed.begin(), parsed.end(), '"'), parsed.end());
//	return parsed;
//}



const Ref Bible::next(const Ref ref, LookupResult& status){
	//Gets a verse AND the next verse, but only returns the verse after the first verse, effectively returning the 'next'.
	Verse* tempVerse = lookup(2, ref, status);
	Verse nextVerse = tempVerse[1];
	Ref r = nextVerse.getRef();
	delete[] tempVerse;
	return r;
};

const Ref Bible::prev(const Ref ref, LookupResult& status) {
	Ref previous;
	Verse* verse = lookup(1,ref,status,previous);
	delete[] verse;
	return previous;
};

// Return an error message string to describe status
const string Bible::error(LookupResult status){
	return "Error - " + LookupResultStrings[status] + "\n";
};
	
void Bible::display() {
	cout << "Bible file: " << infile << endl;
}
