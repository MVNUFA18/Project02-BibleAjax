/* Demo program for Bible lookup using AJAX
 * By James Skon, Febrary 10, 2011
 * updated by Bob Kasper, February 2019
 * updated by Dante Cherubini, February 2019
 * Mount Vernon Nazarene University
 * 
 * This sample program works using the cgicc AJAX library to
 * allow live communication between a web page and a program running on the
 * same server that hosts the web server.
 *
 * This program is run by a request from the associated html web document.
 * A Javascript client function invokes an AJAX request,
 * passing the input form data as the standard input string.
 *
 * The cgi.getElement function parses the input string, searching for the matching 
 * field name, and returing a "form_iterator" oject, which contains the actual
 * string the user entered into the corresponding field. The actual values can be
 * accessed by dereferencing the form iterator twice, e.g. **verse
 *     refers to the actual string entered in the form's "verse" field.
 */

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Ref.h"
#include "Verse.h"
#include "Bible.h"
using namespace std;

/* Required libraries for AJAX to function */
#include "/home/class/csc3004/cgicc/Cgicc.h"
#include "/home/class/csc3004/cgicc/HTTPHTMLHeader.h"
#include "/home/class/csc3004/cgicc/HTMLClasses.h"
using namespace cgicc;

int main() {
  Cgicc cgi;  // object used to access CGI request data

  // GET THE INPUT DATA
  // browser sends us a string of field name/value pairs from HTML form
  // retrieve the value for each appropriate field name

  form_iterator stIterator = cgi.getElement("search_type");
  form_iterator bookIterator = cgi.getElement("book");
  form_iterator chapterIterator = cgi.getElement("chapter");
  form_iterator verseIterator = cgi.getElement("verse");
  form_iterator nvIterator = cgi.getElement("num_verse");
  form_iterator versionIterator = cgi.getElement("version");

  /* This passes the required response header with content type
   * back to the associated client web page.
   * For an AJAX request, our response is not a complete HTML document,
   * so the response type is just plain text to insert into the web page.
   */
  cout << "Content-Type: text/plain\n\n";

  // Convert and check input data
  bool validInput = false;

  //Check for any Negative or Zero values before setting validInput to true
  if (chapterIterator != cgi.getElements().end() && verseIterator != cgi.getElements().end() && nvIterator != cgi.getElements().end()) {
	 int chapter = chapterIterator->getIntegerValue();
	 int verse = verseIterator->getIntegerValue();
	 int verseCount = nvIterator->getIntegerValue();
	 if (chapter <= 0) {
		 cout << "<p> No negative or zero chapters! </p>" << endl;
	 }
	 else if (verse <= 0) {
		 cout << "<p> No negative or zero verse! </p>" << endl;
	 }
	 else if (verseCount < 0) {
		 cout << "<p> No negative verse count! </p>" << endl;
	 }
	 else
		 validInput = true;
  }

  /* SEND BACK THE RESULTS
   * Finally we send the result back to the client on the standard output stream
   * in HTML text format.
   * This string will be inserted as is inside the web page, 
   * so we must include HTML formatting commands to make things look presentable!
   */

  if (validInput) {
	cout << "Search Type: <b>" << **stIterator << "</b>" << endl;
	cout << "<p>";

	//initialize values to integer versions of what was grabbed from the form iterator
	int chapter = chapterIterator->getIntegerValue();
	int verse = verseIterator->getIntegerValue();
	int verseCount = nvIterator->getIntegerValue();
	int book = bookIterator->getIntegerValue();
	int version = versionIterator->getIntegerValue();

	if (verseCount == 0)
		verseCount = 1;
	
	Verse* verseObj;
	Bible bible(BookVersionString[version], version);
	LookupResult result;

	//We shouldn't need this check anymore - selecting from a dropdown no longer allows for the book to fall out of range
		//if (book < 1 || book > 66) {
		//	cerr << "Error: No book #" << book << " exists!" << endl;
		//}

	Ref ref(book, chapter, verse);
	verseObj = bible.lookup(verseCount, ref, result);

	if (result == SUCCESS) {
		//loop through for each verse 
		for (int i = 0; i < verseCount; i++) {

			//If we move to a different book or chapter, display book name and chapter again.
			if (verseObj[i].getRef().getBook() != verseObj[i - 1].getRef().getBook() || verseObj[i].getRef().getChap() != verseObj[i - 1].getRef().getChap())
				cout << "</p><p align =\"center\" padding=\"250px\"><b>" << verseObj[i].getRef().getBookName() << " " << verseObj[i].getRef().getChap() << "</b></br>" << endl;

			else if (result == OTHER) {
				//print the new chapter
				cout << "<br/><b>" << ref.getBookName() << " " << ref.getChap() << "</b><br>";
			}
			verseObj[i].display();
			cout << endl;
		}
	}
	cout << "</p>" << endl;
  }

  return 0;
}
