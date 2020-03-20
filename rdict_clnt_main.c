/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "rdict.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/*------------------------------------------------------------------------
 * nextin - read a command and (possibly) a word from the next input line
 *------------------------------------------------------------------------
 */
int
nextin(char *cmd, char *word)
{
	int	i, ch;

	ch = getc(stdin);
	while (isspace(ch))
		ch = getc(stdin);
	if (ch == EOF)
		return -1;
	*cmd = (char) ch;
	ch = getc(stdin);
	while (isspace(ch))
		ch = getc(stdin);
	if (ch == EOF)
		return -1;
	if (ch == '\n')
		return 0;
	i = 0;
	while (!isspace(ch)) {
		if (++i > MAXWORD) {
			printf("error: word too long.\n");
			exit(1);
		}
		*word++ = ch;
		ch = getc(stdin);
	}
	return i;
}


void
rdictprog_1(char *host)
{
	CLIENT *clnt;
	int  *result_1;
	char *initw_1_arg;
	int  *result_2;
	char * insertw_1_arg;
	int  *result_3;
	char * deletew_1_arg;
	int  *result_4;
	char * lookupw_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, RDICTPROG, RDICTVERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */
	char	word[MAXWORD+1]; /* space to hold word from input line	*/
	char	cmd;
	int	wrdlen;		/* length of input word			*/

	while (1) {
		wrdlen = nextin(&cmd, word);
		if (wrdlen < 0)
			exit(0);
		word[wrdlen] = '\0';
		printf("Command : %s\n", &cmd);
		switch (cmd) {
		case 'I':	/* "initialize" */
			result_1 = initw_1((void*)&initw_1_arg, clnt);
			if (result_1 == (int *) NULL) {
				clnt_perror (clnt, "call failed");
			}
			printf("Dictionary initialized to empty.\n");
			break;
		case 'i':	/* "insert" */
			insertw_1_arg = word;
			result_2 = insertw_1(&insertw_1_arg, clnt);
			if (result_2 == (int *) NULL) {
				clnt_perror (clnt, "call failed");
				printf("%s not inserted.\n",word);
			} else {
				printf("%s inserted.\n",word);
			}
			break;
		case 'd':	/* "delete" */
			deletew_1_arg = word;
			result_3 = deletew_1(&deletew_1_arg, clnt);
			if (result_3 == (int *) NULL) {
				clnt_perror (clnt, "call failed");
				printf("%s not found.\n",word);
			} else {
				printf("%s deleted.\n",word);
			}
			break;
		case 'l':	/* "lookup" */
			lookupw_1_arg = word;
			result_4 = lookupw_1(&lookupw_1_arg, clnt);
			if (result_4 == (int *) NULL) {
				clnt_perror (clnt, "call failed");
				printf("%s was not found.\n",word);
			} else {
				printf("%s was found.\n",word);
			}
			break;
		case 'q':	/* quit */
			printf("program quits.\n");
			exit(0);
		default:	/* illegal input */
			printf("command %c invalid.\n", cmd);
			break;
		}
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{

	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	rdictprog_1 (host);
exit (0);
}
