/*	
 *	CS537	: Intro to OS, first assignment  (prj1a).
 *	Author	: Pradeep Kashyap Ramaswamy
 *	Email 	: pradeep.kashyap@wisc.edu
 *	This file sorts 'R' records based on key 'K' each with data size 'N'.
 */
#include<stdio.h>
#include<stdlib.h>
#include "sort.h"

/* The maximum size for the file name */
#define MAX_FNAME_SZ 50
/* Typedefing to avoid typing full unsigned int */
typedef unsigned int uint

typedef struct {
	uint R;
	uint filesize;
	char *name;
} file_data_t;

int main(int arg_count, char *argv[])
{	
	char input_filename[MAX_FNAME_SZ] = {0};
	char output_filename[MAX_FNAME_SZ] = {0};

	exit(0);
}
