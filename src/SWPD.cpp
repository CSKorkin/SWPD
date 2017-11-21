//Imports for standard functions.
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <dirent.h>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>

std::vector<std::string> ls(char* target);

//The main function, which is called when the program is executed.
//Note that "int argc, char *argv[]" is the same as what the main method in Java has, "String[] args". Both are for command line arguments.
//The major difference is that C++ doesn't include the length of either arrays or strings. It has to be given that information.
//That is what argc is, the number of arguments passed from the command line, which is how the GUI will interact with the C++ program.
//If we were not given argc, we would continue reading random bits of memory that were stored after the array. There is no "Out of Bounds Exception" to catch you when you do this.
//argc will always be >=1 as the first argument is always the name of the program.

//Note that we do not have "String[] args", but instead "char *argv". This is what Java does behind its complexity.
//Each String is not stored in the array, but rather as a memory reference. This is what we call a pointer. In C++, pointers are made with *.
//So, this really takes an array of pointers, which each "point" to a single character. Of course, this is only a character.
//We rarely use pointers to a single character, though, so it is understood that this is a pointer to the beginning of a string, and you have to continue on to read the whole string.
//Of course, C++ has no idea where to stop going forward. To do this, we often use null-terminated strings. This means that when we hit a "null" character, we stop.
//So a string is usually the array of characters from the first character that is referenced by the pointer to the next null character.
int main(int argc, char *argv[]) {

	//Fails if the program isn't supplied with a directory. The printf statement provides an error message.
	//Keep in mind that the first argument is the program name, so it is always at least one. We need it to be 2.
	if (argc < 2) {
		printf("Needs arguments.\n\nUsage: %s [directory]", argv[0]);
		std::cerr << "Needs arguments.\n\nUsage: " << argv[0] << " [directory]";
		return EXIT_FAILURE;
	}

	//Fails if the program is supplied with more than 2 arguments. The printf statement provides an error message.
	//If there are more than 2 arguments, that means that there is more than just the program name and directory.
	if (argc > 2) {
		printf("Too many arguments.\n\nUsage: %s [directory]", argv[0]);
		return EXIT_FAILURE;
	}

	//Creates a string representing our target directory, because we will be recursing. Starts out as the passed directory
	char* target = argv[1];

	//PRINTS OUT THE PATH AND OPENS THE FILE FOR TESTING PURPOSES
	for (std::string str : ls(target)) {
		std::cout << str << std::endl;
		std::ifstream file(str);
		if(file){
			puts("in");
		}
	}

	//Program ran successfully if we reached this point.
	return EXIT_SUCCESS;
}



//returns a vector of entry names.. Close to the equivalent of an Arraylist in Java.
std::vector<std::string> ls(char* target) {

	//Makes a vector for our list of files.
	std::vector<std::string> list;

	//Makes a pointer that will point to our directory
	DIR *dir;

	//Makes a pointer that will point to a file as we are reading it.
	struct dirent *ent;

	//A null pointer is returned if we couldn't open the directory, which means it didn't exist. Goes to the else statement.
	if ((dir = opendir(target)) != NULL) {

		//Stops when the directory is out of files to read.
		while ((ent = readdir(dir)) != NULL) {

			//Doesn't add "." or ".." to the list, which represent the current directory and the parent directory respectively.
			if(strcmp(ent->d_name,".")==0||strcmp(ent->d_name,"..")==0){

				//Doesn't finish this loop, but continues to the next iteration.
				continue;

			}

			//Makes the full path of the file
			char* path=(char*)calloc(strlen(target)+strlen(ent->d_name)+2, 1);
			strcat(path, target);
			strcat(path, "/");
			strcat(path, ent->d_name);

			//Checks if the current file is a directory
			DIR* subdir = opendir(path);
			if (subdir != NULL) {

				//Recurse through the directory if it is one.
				std::vector<std::string> sublist = ls(path);

				//Add the results to the end of our current list.
				for(std::string str: sublist){
					list.push_back(str);
				}

			}else{

				//Adds the current file name to the vector we made earlier if it is not a directory.
				std::string librarypath = std::string(path);
				list.push_back(librarypath);

			}

		}

		//Makes sure to close the directory when we are done with it.
		closedir(dir);

		//Returns the vector.
		return list;

	} else {

		//Fails if the directory doesn't exist. The puts statement provides an error message.
		puts("Directory doesn't exist.");
		exit(EXIT_FAILURE);
	}
}
