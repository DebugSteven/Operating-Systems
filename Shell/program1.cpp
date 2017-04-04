//
//  program1.cpp
//  
//
//  Created by J Haigh on 6/20/15.
//
//

#include <iostream>
#include <string>
#include <stdio.h>
#include <cctype>
#include "program1functions.h"

int main()
{
    bool run = true;
    std::string command, argv, filepath, stream, file;
    char cmd[1024], arg[1024], path[1024];
    clear(cmd, 1024);
    clear(arg, 1024);
    clear(path, 1024);    

    while(run) {
	
        int error = 0;
        int exe_check = 0;
        std::size_t found;

        std::cout << "myshell> ";
        std::getline (std::cin, command);
        found = command.find_first_of("<>");
        
        if (found!=std::string::npos) {
            stream = command.substr(found);
            file = stream;
            command = command.substr(0, found-1);
        }
        
        argv = command;
        
        parse(command, argv);   // parse the command into pieces
       
      	stringtoarray(command, cmd);
        stringtoarray(argv, arg);
        
        // if exit is typed the program will quit
        if (command.compare("exit") == 0)
            run = false;

        // find the command
        error = testpath(cmd, filepath);
	
        // if there is an error skip this iteration of the loop
        if (error == 1) {
            //clear char arrays
            clear(cmd, 1024);
            clear(arg, 1024);
            clear(path, 1024);
            filepath = '\0';
            stream = '\0';
            file = '\0';
            continue;
        }
        
        stringtoarray(filepath, path);
        
        //executes commands that are redirected to or from a file
        if (!stream.empty()) {
            if (stream.compare(1,1,"<") || stream.compare(1,1,">")) {
                parse(stream, file);
                
                if (stream[0] == 62) { // output
                    output(file, argv, cmd, arg, path);
                    exe_check = 1;
                }
                
                else { // input
                    input(file, argv, cmd, arg, path);
                    exe_check = 1;
                }
            }
        }
        
        //execute the function
        if (exe_check == 0) {
            
            if (isalnum(argv[1]) || ispunct(argv[1])) {
                execute2(cmd, arg, path);
            }
            
            else
                execute(cmd, path);
        }
        
        //clear char arrays
        clear(cmd, 1024);
        clear(arg, 1024);
        clear(path, 1024);
        filepath = '\0';
        stream = '\0';
        file = '\0';
    }
    
    return 0;
}
