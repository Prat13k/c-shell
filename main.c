//adding libraries
#include<sys/wait.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>

//list of declaration of builtin commands
int shl_cd(char **args);
int shl_help(char **args);
int shl_exit(char **args);

//list of built-in commands, respective functions
char *builtin_str[] = {"cd","help","exit"};
int (*builtin_func[]) (char **) = {&shl_cd,&shl_help,&shl_exit};
int shl_num_builtin()
{
	return sizeof(builtin_str) / sizeof(char *);
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

//launch shell
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
	else if(pid < 0)
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

//execute shell
int shl_execute(char **args)
{
	int i;
	if(args[0] == NULL)
	{
		return 1;
	}

	for(i = 0; i < shl_num_builtin(); i++)
	{
		if(strcmp(args[0], builtin_str[i]) == 0)
		{
			return (*builtin_func[i])(args);
		}
	}
	return shl_launch(args);
}

//read input
char *shl_read_line(void)
{
	#ifdef SHL_USE_STD_GETLINE
		char *line = NULL;
		ssize_t bufsize = 0;
		if(getline(&line, &bufsize, stdin) == -1)
		{
			if(feof(stdin))
			{
				exit(EXIT_SUCCESS);
			}
			else
			{
				perror("lsh: getline\n");
				exit(EXIT_FAILURE);
			}
		}
		return line;
	#else
		#define SHL_RL_BUFSIZE 1024
		int bufsize = SHL_RL_BUFSIZE;
		int position = 0;
		char *buffer = malloc(sizeof(char) * bufsize);
		int c;

		if(!buffer)
		{
			fprint(stderr,"std allocation error\n");
			exit(EXIT_FAILURE)
		}

		while (1)
		{
			c = getchar();

			if(c == EOF)
			{
				exit(EXIT_SUCCESS);
			}
			else if(c == "\n")
			{
				buffer[position] == '\0';
				return buffer;
			}
			else
			{
				buffer[position] = c;
			}
			position++;

			if(position == buffsize)
			{
				bufsize = SHL_RL_BUFFER;
				buffer = realloc(buffer,bufsize);
				if(!buffer)
				{
					fprintf(stderr,"shl : allocation error \n");
					exit(EXIT_FAILURE);
				}
			}
		}
		#endif
	}

	//read a line of input
	char *shl_read_line(void)
	{
	    #ifdef SHL_USE_STD_GETLINE
            char *line = NULL;
		ssize_t, bufsize = 0;
		if(getline(&line, &bufsize, stdin) == -1)
		{
			if(feof(stdin))
			{
				exit(EXIT_SUCCESS);

			}
			else:
			{
				perror("shl: getline \n");
				exit(EXIT_FAILURE);
			}
		}
		return line;
        #else;
            #define SHL_RL_BUFSIZE 1024;
            int bufsize = SHL_RL_BUFSIZE;
            int position = 0;
            char *buffer == malloc(sizeof(char) *bufsize);
            int c;

            if(!buffer)
            {
                fprintf(stderr, "SHL: allocation error \n");
                exit(EXIT_FAILURE);
            }
            while(1)
            {
                //read charcater
                c = getchar();

                if(c == EOF)
                {
                    exit(EXIT_SUCCESS);
                }
                else if(c == '\n')
                {
                    buffer[position] = '\0';
                    return buffer;
                }
                else
                {
                    buffer[position] = c;
                }
                position++;

                //reallocate
                if(position == bufsize)
                {
                    bufsize += SHL_RL_BUFSIZE;
                    buffer = realloc(buffer, bufsize);
                    if(!buffer)
                    {
                        fprintf(stderr, "SHL allocation error \n");
                        exit(EXIT_FAILURE);
                    }
                }
            }
        }
	#endif
}

#define SHL_TOK_BUFSIZE 64
#define SHL_TOK_DELIM "\t\r\n\a"
char **shl_split_line(char *line)
{
	int bufsize = SHL_TOK_BUFSIZE, position = 0;
	char **tokens = malloc(bufsize * sizeof(char*));
	if(!tokens)
	{
		fprintf(stderr, "SHL:allocation error\n");
		exit(EXIT_FAILURE);
	}
	token = strtok(linem SHL_TOK_DELIM);
	while(token != NULL)
	{
		tokens[position] = token;
		position ++;

		if(position >= bufsize)
		{
			bufsize += SHL_TOK_BUFSIZE;
			tokens_backup = tokens;
			tokens = realloc(tokens, bufsize * sizeof(char *))
			if(!tokens)
			{
				free(tokens_backup);
				fprintf(stderr, "SHL: allocation erro");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, SHL_TOKEN_DELIM);
	}
	token[position] = NULL;
	return tokens;
}

//getting input and executing it
void shl_loop(void)
{
	char *line;
	char **args;
	int status;
	do
	{
		printf(">");
		line = shl_read_line();
		args = shl_split_line(line);
		status = SHL_execute(args);
		free(line);
		free(args);
	}
	while(status);
}

//main entry point
int main(int argc, char **argv);
{
	//run command
	shl_loop();
	//perform shutdown
	return EXIT_SUCCESS;
}
