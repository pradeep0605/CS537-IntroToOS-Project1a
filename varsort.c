/*	
 *	CS537	: Intro to OS, first assignment  (prj1a).
 *	Author	: Pradeep Kashyap Ramaswamy
 *	Email 	: pradeep.kashyap@wisc.edu
 *	This file sorts 'R' records based on key 'K' each with data size 'N'.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sort.h"
#include <string.h>

/* The maximum size for the file name */
#define MAX_FNAME_SZ 50
/* Typedefing to avoid typing full unsigned int */
typedef unsigned int uint;

typedef struct {
	uint R;
	uint filesize;
	char *name;
} file_data_t;

int 
main(int arg_count, char *arg_vector[])
{	
	char *input_filename;
	char *output_filename;
	int option;

	if (arg_count < 2) {	
		fprintf(stderr, "Usage: varsort -i inputfile -o outputfile\n");
		/* Exit with error */
		exit(1);
	}
	while ((option = getopt(arg_count, arg_vector, "i:o:")) != -1) {
		switch (option) {
			case 'i':
				input_filename = strdup(optarg);
				printf("IFile = %s\n", input_filename);
				break;
			case 'o':
				output_filename = strdup(optarg);
				printf("OFile = %s\n", output_filename);
				break;
			default:
				fprintf(stderr, "Usage: varsort -i inputfile -o"
					" outputfile\n");
				/* Exit with error */
				exit(1);
		}
	}
	exit(0);
}
