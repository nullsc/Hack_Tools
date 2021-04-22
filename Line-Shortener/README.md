## Line Shortener

Work in progress

Small tool built in C++ used for editing text lists

C++ used for speed so it can handle larger files easier

Compiled with Visual Studio

### To Use

* Either compile the source or run LINET.exe
* Enter your text file names as command line arguments eg. LINET.exe input.txt output.txt
* Then enter which menu options you want
* Click enter!
* The output file will be generated with the new list

### Features

* Shorten the string from the left or right
* Delete before or after a substring eg. email@gmail.com -> @gmail.com
* Delete all blank lines
* Trim all whitespace in string (or just left/right side)
* Remove duplicate lines
* Line append


### TODO
* File joiner
* Maybe a search feature
* Add multithreading

To compile: Open files in Visual Studio, main function is in shortener.cpp then build solution.
