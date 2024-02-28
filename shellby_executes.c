#include "thomas_shellby.h"

/*
 * This is the file that will handle execution of commands inputed by the user into Thomas Shellby
 * @execve is the system call that is in charge of execution
 * @snprintf to display output if needed
 * @pid_pikin is the child pid
 * @execut_er is a previously called function declared in th header file
 * @wait is used to avoid parent process termination until child process completion
 */

#define UI "user_input"

void execut_er(char *user_input)
{
	pid_t pid_pikin = fork();
	char user_input_path[256];
	char *args[] = {UI};

	if (pid_pikin == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid_pikin == 0)
	{
		snprintf(user_input_path, sizeof(user_input_path), "/bin/%s", user_input);

		execve(user_input, args, NULL);

		perror("execve");
		exit(EXIT_FAILURE);
	}
	else 
	{
		wait(NULL);
	}
}
