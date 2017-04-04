//
//  program1functions.h
//  holds the prototypes for the functions that execute commands
//
//  Created by J Haigh on 6/20/15.
//
//

#ifndef PA1FUNCTIONS_H_HAIGH
#define PA1FUNCTIONS_H_HAIGH

	void parse(std::string &command, std::string &argv);
	int execute(char cmd[], char path[]);
	int execute2(char cmd[], char arg[], char path[]);
	int findfunction(char cmd[]);
	void stringtoarray(std::string temp, char array[]);
	void clear(char array[], int size);
	int testpath(char cmd[], std::string &filepath);
	void output(std::string file, std::string argv, char cmd[], char arg[], char path[]);
	void input(std::string file, std::string argv, char cmd[], char arg[], char path[]);

#endif
