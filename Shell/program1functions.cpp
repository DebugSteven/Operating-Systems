//
//  program1functions.cpp
//  
//
//  Created by J Haigh on 6/20/15.
//
//

#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <cctype>
#include <fcntl.h>
#include <fstream>
#include "program1functions.h"

void parse(std::string &command, std::string &argv)
{
    int i = 0;
    while (command[i] != '\0') {
        
        if (isspace(command[i]))
            command.erase(i,1);
        
        else if (!isspace(command[i])) {
            
            i++;
            if (isspace(command[i])) {
                
                command.erase(command.begin()+i, command.end());
                i++;
                
                if (!isspace(argv[i]))
                    argv.erase(argv.begin(), argv.begin()+i);
                
                while (argv[i] != '\0') {
                    if (isspace(argv[i]))
                        argv[i] = '\0';
                    
                    i++;
                }
            }
        }
    }
    
    if(command.compare(argv) == 0)
        argv = '\0';
}

int findfunction(char cmd[])
{
    pid_t pid, pid1;
    int status;
    
    pid = fork();
    
    if(pid < 0) {
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    
    else if(pid == 0) {
        execlp("/usr/bin/whereis","whereis",cmd,NULL); 
    }
    
    else {
        waitpid(pid, &status, 0);
        //printf("Child Complete");
    }
    
    return 0;
}

// test path
// compare to whereis path
// return a type of error if it isn't found
// return error if the command isn't found
int testpath(char cmd[], std::string &filepath)
{
	std::string title, test1, test2;

	int stdout = dup(1);
	int fd = open("path.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	dup2(fd, 1);
	findfunction(cmd); 	
	close(fd);
	dup2(stdout, 1);
	close(stdout);

	std::ifstream myfile;
	myfile.open("path.txt");
	myfile >> title;
	myfile >> filepath;

	remove("path.txt");

	if (isspace(filepath[1]) || filepath.empty()) {
		std::cout << title << " Command not found." << std::endl;
		return 1;
	}
}

void output(std::string file, std::string argv, char cmd[], char arg[], char path[])
{
	char file_array[1024];
	stringtoarray(file, file_array);

	int stdout = dup(1);
	int fd = open(file_array, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	dup2(fd, 1);
		
	if (isalnum(argv[1]) || ispunct(argv[1])) {
		execute2(cmd, arg, path);
	}
	
	else
		execute(cmd, path);
	
	close(fd);
	dup2(stdout, 1);
	close(stdout);
}

void input(std::string file, std::string argv, char cmd[], char arg[], char path[])
{
	char file_array[1024];
	stringtoarray(file, file_array);

	int stdin = dup(0);
	int fd = open(file_array, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	dup2(fd, 0);
		
	if (isalnum(argv[1]) || ispunct(argv[1])) {
		execute2(cmd, arg, path);
	}
	
	else
		execute(cmd, path);

	close(fd);
	dup2(stdin, 0);
	close(stdin);
}

void stringtoarray(std::string temp, char array[])
{
    int tempnum = temp.size();
    for (int i = 0; i < tempnum; i++)
        array[i] = temp[i];
}

// clear function for char arrays
void clear(char array[], int size)
{
	for (int i = 0; i < size; i++)
		array[i] = '\0';
}

int execute(char cmd[], char path[])
{
    pid_t pid;
    int status;
    
    pid = fork();
    
    if(pid < 0) {
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    
    else if(pid == 0) {
        execlp(path,cmd,NULL);
    }
    
    else {
        waitpid(pid, &status, 0);
        //printf("Child Complete");
    }
    
    return 0;
}

int execute2(char cmd[], char arg[], char path[])
{
    pid_t pid;
    int status;
    
    pid = fork();
    
    if(pid < 0) {
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    
    else if(pid == 0) {
        execlp(path,cmd,arg,NULL);
    }
    
    else {
        waitpid(pid, &status, 0);
        //printf("Child Complete");
    }
    
    return 0;
}

