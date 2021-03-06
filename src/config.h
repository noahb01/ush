#ifndef CONFIG_H
#define CONFIG_H

#define CFG_SHORT_NAME				"uSH"					// The short name of the shell.
#define CFG_LONG_NAME				"uSH: a small shell!"			// The long name of the shell.
#define CFG_PROMPT				":?"					// The default prompt.
#define CFG_PROMPT_VAR				"PROMPT"				// The variable to store the prompt in.
#define CFG_BUFSIZE				2048					// The default size of internal text buffers.
#define CFG_MAX_VARS				2048					// The maximum number of variables allowed in one shell instance.
#define CFG_VERSION				"0.4"					// The version of uSH

#ifndef TRUE
#define TRUE					1					// TRUE should always be 1
#endif

#ifndef FALSE
#define FALSE					0					// FALSE should always be 0
#endif

#ifndef NULL
#define NULL					0					// NULL should always be 0
#endif

#endif
