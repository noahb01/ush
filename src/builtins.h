#ifndef BUILTIN_H
#define BUILTIN_H

int builtin_help(char argc, char **arguments);
int builtin_exit(char argc, char **arguments);
int builtin_cd(char argc, char **arguments);
int builtin_pwd(char argc, char **arguments);
int builtin_setvar(char argc, char **arguments);
int builtin_getvar(char argc, char **arguments);
int builtin_delvar(char argc, char **arguments);
int builtin_lsvar(char argc, char** arguments);
int builtin_buffer(char argc, char** arguments);

int check_builtin(char *name);
int run_builtin(char **args);

#endif
