#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
 
#include <sys/types.h>
#include <sys/wait.h>

#include "config.h"
#include "vars.h"

char *var_names[CFG_MAX_VARS];
char *var_value[CFG_MAX_VARS];

int num_curr_vars = 0;

int init_vars()
{
	int i;
	
	for(i = 0; i < CFG_MAX_VARS; i++)
        {
                var_names[i] = malloc(sizeof(char));
                if(var_names == NULL)
                {
                        fprintf(stderr, "Memory allocation error!\n");
                        return -1;
                }
		var_names[i][0] = '\0';
        }
	
	return 0;
}

int define_var(char *name, char *value)
{
	int i;
	int found = FALSE;

	for(i = 0; i < CFG_MAX_VARS; i++)
	{
		if(var_names[i][0] == '\0')
		{
			found = TRUE;
			break;
		}
	}

	if(found == FALSE)
	{
		fprintf(stderr, "No more available variable slots!\n");
		return -1;
	}

        var_value[i] = malloc(sizeof(char) * strlen(value));
        if(var_value[i] == NULL)
        {
                fprintf(stderr, "Memory allocation error!\n");
                return -1;
        }

        free(var_names[i]);
        var_names[i] = malloc(sizeof(char) * strlen(name));
        if(var_names[i] == NULL)
        {
                fprintf(stderr, "Memory allocation error!\n");
                return -1;
        }

	strcpy(var_names[i], name);
	strcpy(var_value[i], value);
	
	num_curr_vars++;
		
	return 0;
}

char *get_var(char *name)
{
	int i;
	
	for(i = 0; i < num_vars(); i++)
		if(strcmp(name, var_names[i]) == 0)
			return var_value[i];
	return NULL;
}

int del_var(char *name)
{
	int i;
	int found = FALSE;
	
	for(i = 0; i < num_vars(); i++)
		if(strcmp(name, var_names[i]) == 0)
		{
			found = TRUE;
			break;
		}
	
	if(found == FALSE)
	{
		fprintf(stderr, "No such variable!\n");
		return 1;
	}
	
        free(var_names[i]);
        var_names[i] = malloc(sizeof(char));
        strcpy(var_names[i], "\0");
        free(var_value[i]);
	return 0;
}

int num_vars(void)
{
	return num_curr_vars;
}