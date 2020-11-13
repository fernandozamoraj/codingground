// Copy and paste your work, or start typing.#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h> // pid_t
#include <unistd.h> //fork
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>


int toggleForeGroundModeOnly = 0;
//Entering foreground-only mode (& is now ignored)
//Exiting foreground-only mode
//https://stackoverflow.com/questions/40098170/handling-sigtstp-signals-in-c

//https://stackoverflow.com/questions/4217037/catch-ctrl-c-in-c
void  INThandler(int sig)
{
	char  c;

	signal(sig, SIG_IGN);
	printf("OUCH, did you hit Ctrl-C?\n"
		"Do you really want to quit? [y/n] ");
	c = getchar();
	if (c == 'y' || c == 'Y')
		exit(0);
	else
		signal(SIGINT, INThandler);
	getchar(); // Get new line character
}

//https://www.geeksforgeeks.org/c-program-replace-word-text-another-given-word/
char* replaceWord(const char* s, const char* oldW,
	const char* newW)
{
	char* result;
	int i, cnt = 0;
	int newWlen = strlen(newW);
	int oldWlen = strlen(oldW);

	// Counting the number of times old word 
	// occur in the string 
	for (i = 0; s[i] != '\0'; i++) {
		if (strstr(&s[i], oldW) == &s[i]) {
			cnt++;

			// Jumping to index after the old word. 
			i += oldWlen - 1;
		}
	}

	// Making new string of enough length 
	result = (char*)malloc(i + cnt * (newWlen - oldWlen) + 1);

	i = 0;
	while (*s) {
		// compare the substring with the result 
		if (strstr(s, oldW) == s) {
			strcpy(&result[i], newW);
			i += newWlen;
			s += oldWlen;
		}
		else
			result[i++] = *s++;
	}

	result[i] = '\0';
	return result;
}

//   abc$$def
//   
void expand(char* modified, char* token, char* sPid) {

	int originalIndex = 0;
	char prevChar = ' ';
	//  [ls]
	//  [ls\0]
	for (int i = 0; i < strlen(token); i++)//attempt to replace $$ with id
	{
		if (token[i] == '$' && token[i + 1] == '$' && prevChar != '|' && i < strlen(token) - 1)
		{
			modified[originalIndex] = '|';
			originalIndex++;
			prevChar = '|';

		}
		else {
			if (token[i] == '$' && prevChar == '|') {
				prevChar = ' ';
			}
			else {
				modified[originalIndex] = token[i];
				originalIndex++;
				prevChar = token[i];
			}
		}
	}

	modified[originalIndex] = '\0';

	char* newVal = replaceWord(modified, "|", sPid);
	strcpy(modified, newVal);
	free(newVal);
}

void extractTokens(char* buffer[], char* inputLine, int* tokenCount) {

	char* token = strtok(inputLine, " ");
	*tokenCount = 0;

	if (token != NULL) {
		buffer[*tokenCount] = malloc(sizeof(char) * strlen(token) + 1);
		strcpy(buffer[*tokenCount], token);
		*tokenCount = *tokenCount + 1;
	}

	while ((token = strtok(NULL, " ")) != NULL) {
		buffer[*tokenCount] = malloc(sizeof(char) * strlen(token) + 1);
		strcpy(buffer[*tokenCount], token);
		*tokenCount = *tokenCount + 1;
	}
}

void sigtstHandler(int n) {

	toggleForeGroundModeOnly = (toggleForeGroundModeOnly + 1) % 2;

	if (toggleForeGroundModeOnly == 1)
		printf("\nEntering foreground-only mode (& is now ignored)");
	else
		printf("\nExiting foreground-only mode");
	fflush(stdin);

}

int main() {
	int pid = getpid();
	char pidString[100];
	sprintf(pidString, "%d", pid);//convert int to string

	char* tokens[512] = { NULL };
	int tokenCount = 0;

	char cmdInput[2048] = { 0 };

	int previousStatus = 0;

	signal(SIGTSTP, sigtstHandler);

	while (1) {

		int lastIndex = 0;
		int argIndex = 0;
		int i = 0;
		char command[100] = { 0 };
		char* processArg[512] = { NULL };
		int runningInBackground = false;

		for (i = 0;i < 512; i++) {
			tokens[i] = NULL;
		}

		for (i = 0;i < 2048;i++) {
			cmdInput[i] = '\0';
		}

		do
		{
			printf("\n: ");
			fflush(stdin);
			fgets(cmdInput, 2048, stdin);
		} while (cmdInput[0] == '#' || cmdInput[0] == ' '); //while not a comment

		lastIndex = strlen(cmdInput) - 2;
		cmdInput[lastIndex + 1] = '\0';

		extractTokens(tokens, cmdInput, &tokenCount);

		if (cmdInput[lastIndex] == '&')
		{
			//TODO executing in background... gets ignored if previously set to be ignored CTL+?
			  //printf("Command is to be executed in the background.\n");
			runningInBackground = true;
		}

		if (tokenCount > 0 && tokens[0][0] != '>' && tokens[0][0] != '<' && tokens[0][0] != '&')
		{
			expand(command, tokens[0], pidString);
		}

		int fdIn = -2;
		int fdOut = -2;
		int BADFILE = 0;
		int readingOrWritingFile = -1;
		char inFileName[100] = { 0 };
		char outFileName[100] = { 0 };
		int fileCount = 0;

		for (i = 0;i < tokenCount; i++)
		{
			if (tokens[i][0] != '>' && tokens[i][0] != '<')
			{

				processArg[argIndex] = malloc(sizeof(char) * strlen(tokens[i]) * 4 + 1);
				expand(processArg[argIndex], tokens[i], pidString);
				argIndex++;

			}
			else if (tokens[i][0] == '<')
			{
				readingOrWritingFile = 1;
				strcpy(inFileName, tokens[i + 1]);
				fdIn = open(inFileName, O_RDONLY);
				if (fdIn == -1) {
					printf("\nCannot open %s for input", inFileName);
					fflush(stdin);
					BADFILE = 1;
				}
				i++;
				fileCount++;
			}
			else if (tokens[i][0] == '>')
			{
				readingOrWritingFile = 2;
				strcpy(outFileName, tokens[i + 1]);
				fdOut = open(outFileName, O_WRONLY | O_TRUNC | O_CREAT, 0644);
				i++;
				fileCount++;
			}
		}


		int forkPid = pid;

        printf("Command: %s", command);
		//do not fork on badfile or exit nor status commands
		if (strlen(command) > 0 && strcmp(command, "exit") != 0 && strcmp(command, "status") != 0) {
			forkPid = fork();
		}

		int status = 0;

		switch (forkPid) {

		case -1: printf("fork failed!"); fflush(stdin); break;

		case 0:


			if (strcmp(command, "cd") == 0) {
				if (tokenCount > 1) {
					chdir(processArg[1]);
				}
			}
			else {
				if (fdIn >= 0) {

					if (readingOrWritingFile == 1 && BADFILE == 0) {
						if (dup2(fdIn, STDIN_FILENO) < 0) {
							perror("dup2"); abort(); 
						}
					}

					if (BADFILE == 0)
						close(fdIn);
				}
				if (fdOut >= 0) {

					if (dup2(fdOut, STDOUT_FILENO) < 0) {
                       perror("dup2"); abort(); 
                    }

					close(fdOut);
				}


				if (argIndex > 2 && strcmp(processArg[argIndex - 1], "&") == 0) {

					free(processArg[argIndex - 1]);
					processArg[argIndex - 1] = NULL;
				}

				if (BADFILE == 0) {
					int tempStatus = 0;
					if ((tempStatus = execvp(command, processArg)) < 0) {
						printf("\n%s: no such file or directory", command);
						exit(tempStatus);
					}
                    else{
						exit(0);
                    }
				}
				else {
					exit(1);
				}
				
			}

			break;
		default:
			if (runningInBackground == false || toggleForeGroundModeOnly == true) {
				waitpid(forkPid, &status, 0);
			}
			else if (runningInBackground == true) {
				printf("\nbackground pid is %d", forkPid);
			}

			if (strcmp(command, "status") == 0) {
				printf("\nexit value %d", WEXITSTATUS(previousStatus));
				fflush(stdin);
			}
			previousStatus = status;

			if (strcmp(command, "exit") == 0) {
				signal(SIGQUIT, SIG_IGN);
				kill(-pid, SIGQUIT);
				exit(0);
			}
			break;
		}
		i = 0;
		for (i = 0; i < argIndex; i++)
		{
			free(processArg[i]);
			processArg[i] = NULL;
		}

		for (i = 0;i < tokenCount;i++) {
			free(tokens[i]);
		}
		fflush(stdin);
	}
	free(cmdInput);

	return 0;
}
