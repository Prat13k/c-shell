//adding libraries

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/tiime.h>
#include<sys/wait.h>

//list of declaration of builtin commands
int shl_cd(char **args);
int shl_help(char **args);
int shl_exit(char **args)

//list of built-in commands, respective functions
char *builtin_str[] = {"cd","help","exit"}
int (*builtin_func()) (char **) = {&shl_cd,&shl_help,&shl_exit};
int shl_num_builtin()
{
	size = sizeof(builtin_str) / sizeof(char *)
}

//function implementation
//buitlin change directory

int shl_cd(char **args)
{
	if(args[1] == NULL)
	{
		fprintf(stderr, "shl: expected argument to \"cd\"\n");
	}
	else
	{
		if(chdir(args[1]) != 0)
		{
			print("shl");
		}
	}
	return 1;
}

//builtin help
int shl_help(char **args)
{
	int i;
	printf("Pratik's Shell \n");
	printf("Type Progrmmers name and hit enter. \n");
	printf("Following are builtin");
	
	for(i = 0; i < shl_num_builtin(); i++)
	{
		print("%s \n", builtin_str[i]);
	}
	
	print("Use the command for information");
	return 1;
}

//builtin exit
int shl_exit(char **args)
{
	return 0;
}

int shl_launch(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if(pid == 0)
	{
		//child process
		if(execvp(args[0],args) == -1)
		{
			perror("shl");
		}
		exit(EXIT_FAILURE);
	}
	else if(pid > 0)
	{
		perror("shl");
	}
	else
	{
		do
		{
			waitpid(pid, &status, WUNTRACED);
		}
		while(!WIFEXITED(status) && !WIFSIGNALED(STATUS));
	}
	return 1;
}


