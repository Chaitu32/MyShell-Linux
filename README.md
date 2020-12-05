# MyShell-lunix

## Running Shell

Open Terminal in current folder and run make.

> make

This will create an excutable file shell. Now just run it.

> ./shell

## Files included in the Shell program:

* Main.c : It takes the input line from stdin and divide mulitple commands into strings. Then each command is identified and respective function is called.

* Header.h : Include all header files require for respective function.

* Prompt.c : This file uses syscommands & struct gethostname(), struct passwd , getpwuid() to output username and hostname. Also the current directory address is passed with pointer.

* Cd.c : The file uses commands chdir(), getcwd() to change address of cur_directory and also rewrite address string required for prompt.

* Pwd.c : This file uses getcwd to get current address.

* Echo.c : It prints the input string to stdout similar to echo

* Pinfo.c : It prints information about a pid which is present in /proc/[pid]/ and it also uses read(), open() ,readlink() ,close() to get the info.

* Syscmd.c : it exectes the system command using fork(),execvp(),wait().

* History.c : It stores the commands written in shell in myshell_his.txt (atmax 20 commands). it outputs last n(max 10) commands exeuted by shell.

* Redir.c : handles redirection and calls the imple to implement the command.

* Pipe.c : Creates the pipe between to commands and calls redir for redirection handling.

* Envar.c : It has two functions setenv and unsetenv . These will set enviroment variable and unset it.

* Jobs.c : it will display all background processes. It also has kjob , fg , bg and overkill functions in it.
