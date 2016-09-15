/*	
 *	CS537	: Intro to OS, first assignment  (prj1a).
 *	Author	: Pradeep Kashyap Ramaswamy
 *	Email 	: pradeep.kashyap@wisc.edu
 *	This file sorts 'R' records based on key 'K' each with data size 'N'.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include "sort.h"

/* The maximum size for the file name */
#define MAX_FNAME_SZ 50
/* Typedefing to avoid typing full unsigned int */
typedef unsigned int uint;

typedef struct {
	uint R;		/* Number of records */
	uint size;	/* Size of the file */
	uint fd;	/* file descripor */
	char *name;	/* Name of the file */
} file_data_t;

typedef struct {
	void *base;			/* base of one big chunk of memory */
	uint total_size;		/* Total size of memory allocated */
	rec_dataptr_t *rarray_base; 	/* record array base, mostly = base */
	uint rarray_size;		/* size of rarray in bytes */
	void *data;			/* pointer to the data of entire file */
	uint data_size;			/* size of file contents in bytes */
} mem_data_t;

/* This function calculates the total memory required for record array and
 * the file contents. Then it alocates one big buffer for everything.
 */
int
allocate_memory(file_data_t *file, mem_data_t *mem_data)
{
	/* remove R's space which is not required */
	mem_data->data_size = file->size - sizeof(uint);
	if (read(file->fd, &file->R, sizeof(file->R)) == -1) {
		fprintf(stderr, "Error: Read() returned with -1 at %d!\n",
			__LINE__);
		exit(1);
	}

	/* size required for record array */
	mem_data->rarray_size = (file->R * sizeof(rec_dataptr_t));

	mem_data->total_size = mem_data->rarray_size + mem_data->data_size;
	
	mem_data->base = malloc(mem_data->total_size);

	if (mem_data->base == NULL) {
		return -1;
	}
	
	mem_data->rarray_base = (rec_dataptr_t *) mem_data->base;

	mem_data->data = mem_data->base + mem_data->rarray_size;

	return 0;
}

void
deallocate_memory(mem_data_t *mem_data)
{
	/* Just have to free the mem_data->base as every other pointer is just
	 * pointing somewhere withing base + total_size.
	 */
	 free(mem_data->base);
}

int
populate_record_array(file_data_t *file, mem_data_t *mem_data)
{
	int i = 0;
	int R = file->R;
	void *cur_rec_ptr;
	rec_nodata_t *record = NULL;
	/* read the entire file */
	if (read(file->fd, mem_data->data, mem_data->data_size) == -1) {
		fprintf(stderr, "Error: Read() returned with -1 at %d!\n",
			__LINE__);
		return -1;
	}
	
	cur_rec_ptr = mem_data->data;
	for (i = 0; i < R; ++i) {
		record = (rec_nodata_t *) cur_rec_ptr;
		mem_data->rarray_base[i] =  *((rec_dataptr_t *) record);
		mem_data->rarray_base[i].data_ptr = cur_rec_ptr +
			sizeof(*record);
		cur_rec_ptr += (sizeof(*record) + (record->data_ints *
			sizeof(uint)));
	}

	/* TODO: Remove printfs */
	printf("Number of records = %u\n", R);
	for (i = 0; i < R; ++i) {
		printf("Key = %d, N ints = %d\n", mem_data->rarray_base[i].key,
			mem_data->rarray_base[i].data_ints);
	}

	return 0;
}

int 
main(int arg_count, char *arg_vector[])
{	
	file_data_t i_file, o_file;
	int option;
	struct stat stats;
	mem_data_t mem_data;
	/* If there are no arguments to the program, then print usage and 
	 * terminate with error.
	 a*/
if (arg_count < 2) {	
		fprintf(stderr, "Usage: varsort -i inputfile -o outputfile\n");
		/* Exit with error */
		exit(1);
	}
	while ((option = getopt(arg_count, arg_vector, "i:o:")) != -1) {
		switch (option) {
			case 'i':
				i_file.name = strdup(optarg);
				break;
			case 'o':
				o_file.name = strdup(optarg);
				break;
			default:
				fprintf(stderr, "Usage: varsort -i inputfile -o"
					" outputfile\n");
				/* Exit with error */
			exit(1);
		}
	}

	if ((i_file.fd = open(i_file.name, O_RDONLY)) == -1) {
		fprintf(stderr, "Error: Cannot open file %s\n",
			i_file.name);
		exit(1);
	}
	
	/* Fetch file stats */
	fstat(i_file.fd, &stats);
	i_file.size = (uint) stats.st_size;

	/* TODO: remove the printf */
	printf("Size of the file = %d\n", (int)i_file.size);
	
	/* Allocate one chunk of memory of record array and the file contents */
	if (allocate_memory(&i_file, &mem_data) != 0) {	
		fprintf(stderr, "Error: Malloc failure at %d\n", __LINE__);
		exit(1);
	}

	/* Read the file and populate the record array */
	if(populate_record_array(&i_file, &mem_data) != 0) {
		fprintf(stderr, "Error in poluating record array at %d\n",
			__LINE__);
		exit(1);
	}

	o_file = o_file;
	exit(0);
}






