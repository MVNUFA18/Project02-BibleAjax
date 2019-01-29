#include "pch.h"
#include "biblereader.h"
#include "Ref.h"
#include "Verse.h"
#include "Bible.h"
#include <iostream>
#include <fstream>
#include <string> 
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void bibleLookup(const int book, const int chapter, const int verse, const int numberOfVerses) {
	Bible kjv("/home/class/csc3004/Bibles/kjv-complete");
	LookupResult result;
	Ref ref(book, chapter, verse);
	Verse* v = kjv.lookup(numberOfVerses, ref, result);

	if (result == SUCCESS) {
		//Display book name and chapter
		cout << v[0].getRef().getBookName() << " " << v[0].getRef().getChap() << endl;
		v[0].display();

		//If there is more than one verse, loop through and display again for each numberOfVerses
		for (int i = 1; i < numberOfVerses; i++) {
			//When we move to a different book (or chapter in a book), display book name and chapter again.
			if (v[i].getRef().getBook() != v[i - 1].getRef().getBook() || v[i].getRef().getChap() != v[i - 1].getRef().getChap())
				cout << v[i].getRef().getBookName() << " " << v[i].getRef().getChap() << endl;
				v[i].display();
		}
	}

	delete[] v;
}

void bibleLookup(int book, int chapter, int verse) {
	//if only one verse
	bibleLookup(book, chapter, verse, 1);
}


int main(int argc, char ** argv) {
	ifstream bibleFile; /* input file descriptor */

	int book, chapter, verse, numVerses;

	/* Check that arguments are in range*/
	if (argc == 4) {
		bibleLookup(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
	}
	else if (argc == 5) {
		bibleLookup(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
	}
	else {
		cerr << "Error: Please format your input as: Bible Book Number (1-66), Chapter Number (1-150), Verse Number, and number of verses (optional).\n" << endl;
		//the 2 status indicates unexpected arguments
		exit(2);
	}
	return 0;
}

//main (int argc, char **argv) {
//	// Create Bible object to process the raw text file
//	Bible kjv("/home/class/csc3004/Bibles/kjv-complete");
//	
//	Verse verse;
//	int bookNumber, chapterNumber, verseNumber;
//	LookupResult result;
//
//	//TEMPORARY COMMENT
//	//cout << "Using Bible from: ";
//	//kjv.display();
//
//	// Prompt for input: get reference to lookup
//	// TODO: your program should get input from command line arguments instead.
//
//	//TEMPORARY COMMENT
//	//cout << "What book, chapter and verse? " << flush;
//	//cin >> b >> c >> v;	
//
//	//Gather Book, Chapter, Verse from user
//
//
//	// Create a reference from the numbers
//	Ref ref(b, c, v);
//
//	// Use the Bible object to retrieve the verse by reference
//	cout << "Looking up reference: ";
//	ref.display();
//	cout << endl;
//
//	verse = kjv.lookup(ref, result);
//	cout << "Result: " << endl;
//	verse.display();
//	cout << endl;
//}
