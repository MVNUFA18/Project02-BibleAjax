# Bibleajax program
# Feb 2010, James Skon
# August 2016, Bob Kasper
# February 2019, Dante Cherubini
# updated February 2018 to use paths on cs2.mvnu.edu

# This is the Makefile for the Bible system demo program
# Copy this directory to a location within your home directory. 
# Change the USER name value below to your own user name.
# Then use "make" to build the server program,
# and deploy it to the live web server directory.
# To test the program, go to http://cs2.mvnu.edu/class/csc3004/USER/
# and click on the bibleajax.html link.

USER= dancherubini
all:	bibleajax.cgi PutCGI PutHTML

bibleajax.o:	bibleajax.cpp
			g++ -c bibleajax.cpp
			
# Ref Object
Ref.o : Ref.h Ref.cpp
	$(CC) $(CFLAGS) -c Ref.cpp

# Verse Object
Verse.o : Ref.h Verse.h Verse.cpp
	$(CC) $(CFLAGS) -c Verse.cpp

# Bible Object
Bible.o : Ref.h Verse.h Bible.h Bible.cpp
	$(CC) $(CFLAGS) -c Bible.cpp


# TO DO: add classes from Project 1 to be linked
# in the executable for bibleajax.cgi
bibleajax.cgi:	bibleajax.o Ref.o Verse.o Bible.o
			g++ -o bibleajax.cgi bibleajax.o Ref.o Verse.o Bible.o -lcgicc
			# -l option links with cgicc library
			
PutCGI:	bibleajax.cgi
		chmod 755 bibleajax.cgi
		cp bibleajax.cgi /var/www/html/class/csc3004/$(USER)/cgi-bin
		cp bibleBookNames.txt /var/www/html/class/csc3004/$(USER)/cgi-bin
		cp styles.css /var/www/html/class/csc3004/$(USER)/cgi-bin

		echo "Current contents of your cgi-bin directory: "
		ls -l /var/www/html/class/csc3004/$(USER)/cgi-bin/

PutHTML:
		cp bibleajax.html /var/www/html/class/csc3004/$(USER)

		echo "Current contents of your HTML directory: "
		ls -l /var/www/html/class/csc3004/$(USER)

clean:		
		rm *.o core bibleajax.cgi
