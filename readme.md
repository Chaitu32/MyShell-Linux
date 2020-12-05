Read Me:

Files included in the Shell program:

1) Main.c : It takes the input line from stdin and divide mulitple commands into strings. Then each command is identified and respective function is called.

2) Header.h : Include all header files require for respective function.

3) Prompt.c  : This file uses syscommands & struct  gethostname(), struct passwd , getpwuid() to output username and hostname. Also the current directory address is passed with pointer.

4)  Cd.c  : The file uses commands chdir(), getcwd() to change address of cur_directory and also rewrite address string required for prompt.

5) Pwd.c  : This file uses getcwd to get current address.

6) Echo.c : It prints the input string to stdout similar to echo

7)  Pinfo.c : It  prints information about a pid which is present in  /proc/[pid]/ and it also uses read(), open() ,readlink() ,close() to get the info.

8) Syscmd.c : it exectes the system command using fork(),execvp(),wait(). 

9) History.c : It stores the commands written in shell in myshell_his.txt (atmax 20 commands). it outputs last n(max 10) commands exeuted by shell. 

10) Redir.c : handles redirection and calls the imple to implement the command.

11) Pipe.c : Creates the pipe between to commands and calls redir for redirection handling.

12) Envar.c : It has two functions setenv and unsetenv . These will set enviroment variable and unset it.

13) Jobs.c : it will display all background processes. It also has kjob , fg , bg and overkill functions in it.