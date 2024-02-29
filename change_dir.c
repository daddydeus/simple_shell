#include "thomas_shellby.h"

/**
 * change_dir_dot – This is a command that changes the current directory to the parent directory
 * @shellby_data_store: This is the relevant environment
 * Return: no return
 */
void change_dir_dot(data_in_shellby *shellby_data_store)
{
	char pwdir[PATH_MAX];
	char *dir, *cp_pwdir, *cp_stringtoken_pwdir;

	getcwd(pwdir, sizeof(pwdir));
	cp_pwdir = _strdup(pwdir);
	set_environment("OLDPWD", cp_pwdir, shellby_data_store);
	dir = shellby_data_store->arguments[1];
	if (_strcmp(".", dir) == 0)
	{
		set_environment("PWD", cp_pwdir, shellby_data_store);
		free(cp_pwdir);
		return;
	}
	if (_strcmp("/", cp_pwdir) == 0)
	{
		free(cp_pwdir);
		return;
	}
	cp_stringtoken_pwdir = cp_pwdir;
	rev_string(cp_stringtoken_pwdir);
	cp_stringtoken_pwdir = _stringtoken(cp_stringtoken_pwdir, "/");
	if (cp_stringtoken_pwdir != NULL)
	{
		cp_stringtoken_pwdir = _stringtoken(NULL, "\0");

		if (cp_stringtoken_pwdir != NULL)
			rev_string(cp_stringtoken_pwdir);
	}
	if (cp_stringtoken_pwdir != NULL)
	{
		chdir(cp_stringtoken_pwdir);
		set_environment("PWD", cp_stringtoken_pwdir, shellby_data_store);
	}
	else
	{
		chdir("/");
		set_environment("PWD", "/", shellby_data_store);
	}
	shellby_data_store->last.status = 0;
	free(cp_pwdir);
}

/**
 * change_dir_to – This is a command that changes the current directory to a given directory specified by the user
 *
 * @shellby_data_store: This is the data store relevant directories
 * Return: no return
 */
void change_dir_to(data_in_shellby *shellby_data_store)
{
	char pwdir[PATH_MAX];
	char *dir, *cp_pwdir, *cp_dir;

	getcwd(pwdir, sizeof(pwdir));

	dir = shellby_data_store->arguments[1];
	if (chdir(dir) == -1)
	{
		get_error(shellby_data_store, 2);
		return;
	}

	cp_pwdir = _strdup(pwdir);
	set_environment("OLDPWD", cp_pwdir, shellby_data_store);

	cp_dir = _strdup(dir);
	set_environment("PWD", cp_dir, shellby_data_store);

	free(cp_pwdir);
	free(cp_dir);

	shellby_data_store->last.status = 0;

	chdir(dir);
}

/**
 * change_dir_previous – This is a command that changes the current directory to the previous directory
 * @shellby_data_store: This is the relevant environment
 * Return: no return
 */
void change_dir_previous(data_in_shellby *shellby_data_store)
{
	char pwdir[PATH_MAX];
	char *p_pwdir, *p_oldpwdir, *cp_pwdir, *cp_oldpwdir;

	getcwd(pwdir, sizeof(pwdir));
	cp_pwdir = _strdup(pwdir);

	p_oldpwdir = _setenvironment("OLDPWD", shellby_data_store->_environment);

	if (p_oldpwdir == NULL)
		cp_oldpwdir = cp_pwdir;
	else
		cp_oldpwdir = _strdup(p_oldpwdir);

	set_environment("OLDPWD", cp_pwdir, shellby_data_store);

	if (chdir(cp_oldpwdir) == -1)
		set_environment("PWD", cp_pwdir, shellby_data_store);
	else
		set_environment("PWD", cp_oldpwdir, shellby_data_store);

	p_pwdir = _setenvironment("PWD", shellby_data_store->_environment);

	write(STDOUT_FILENO, p_pwdir, _strlen(p_pwdir));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwdir);
	if (p_oldpwdir)
		free(cp_oldpwdir);

	shellby_data_store->last.status = 0;

	chdir(p_pwdir);
}

/**
 * change_dir_to_home – This is a command that changes the current directory to home directory
 * @shellby_data_store: This is the data relevant environment
 * Return: no return
 */
void change_dir_to_home(data_in_shellby *shellby_data_store)
{
	char *p_pwdir, *home;
	char pwdir[PATH_MAX];

	getcwd(pwdir, sizeof(pwdir));
	p_pwdir = _strdup(pwdir);

	home = _setenvironment("HOME", shellby_data_store->_environment);

	if (home == NULL)
	{
		set_environment("OLDPWD", p_pwdir, shellby_data_store);
		free(p_pwdir);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error(shellby_data_store, 2);
		free(p_pwdir);
		return;
	}

	set_environment("OLDPWD", p_pwdir, shellby_data_store);
	set_environment("PWD", home, shellby_data_store);
	free(p_pwdir);
	shellby_data_store->last.status = 0;
}
