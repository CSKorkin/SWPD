//Imports for standard functions.
#include <stdio.h>
#include <stdlib.h>


//Main. argc is the number of arguments passed from the command line, which is how the GUI will interact with the C++ program.
//argc will always be >=1 as the first argument is always the name of the program.
//Note that "int argc, char *argv[]" is the same reason that the main method in Java has "String[] args". Both are for command line arguments.
//The major difference is that C++ doesn't include the length of either arrays or strings. They have to be given that information.
//If we were not given argc, we would continue reading random bits of memory that were stored after each string.
//Note that we do not have "String[] args", but instead "char *argv". This is what Java does behind its complexity.
//Each String is not stored in the array, but rather as a memory reference. This is what we call a pointer. In C++, pointers are made with *.
//So, this really takes an array of pointers, which each "point" to a single character. Of course, this is only a character.
//We rarely use pointers to a single character, though, so it is understood that this is a pointer to the beginning of a string, and you have to continue on to read the whole string.
//Of course, C++ has no idea where to stop going forward. To do this, we often use null-terminated strings. This means that when we hit a "null" character, we stop.
//So a string is usually the array of characters from the first character that is referenced by the pointer to the next null character.
int main(int argc, char *argv[])
{
	//Fails if the program isn't supplied with a directory. The printf statement provides an error message.
	//Keep in mind that the first argument is the program name, so it is always at least one. We need it to be 2.
	if(argc<2){
		printf("Needs arguments.\n\nUsage: %s [directory]", argv[0]);
		return EXIT_FAILURE;
	}


	return EXIT_SUCCESS;
}


