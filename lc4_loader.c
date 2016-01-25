#include <stdio.h>
#include "lc4_memory.h"
#include <stdlib.h>
/* declarations of functions that must defined in lc4_loader.c */

FILE* open_file(char* file_name)
{
	/*opens the file if it exist and is present in argv[1]*/
	if(file_name == NULL){
	printf("ERROR! NO FILE FOUND! \n");
	return NULL ;
	} else {
	return fopen(file_name, "rb");
	}


}

int parse_file (FILE* my_obj_file, row_of_memory** memory)
{
	/*I tried to initalize as much variables as I can think of for the valgrind notices, but there are still a lot left*/
	int byte_read, head_one , head_two, addr_one, addr_two, cont_one, cont_two, n_one, n_two;
	int n2 = 0;
	int i = 0;
	int p = 0;
	int l = 0;
	int len = 0;
	int j, k, m;
	short unsigned int address;
	short unsigned int contents;
	short unsigned int n;
	char *lab_char = NULL;
	row_of_memory *row_of_memory1 = NULL;
	int list;


	while (byte_read != EOF) { 
		/*the file is being read byte by byte*/
		byte_read = fgetc (my_obj_file) ; 
		
		/*printf("byte read%d = %x \n", i, byte_read);*/
		if (i%2 == 0){
			head_one = byte_read ;
		} else {
			head_two = byte_read ;
		}
		/*The following codes parses the CODE Section*/
		if(head_one == 202 & head_two == 222){
			/*printf("Found CODE! \n");*/
			j=i;
			k=i;
		}
			
		if (i == j+1){
			addr_one = byte_read;
			/*printf("addr_one = %x \n", addr_one);*/
		}
		if (i == j+2){
			addr_two = byte_read;
			/*printf("addr_two = %x \n", addr_two);*/
			
			address = (addr_one<<8) + addr_two;
			/*printf("address = %x \n", address);*/
		}
		if (i == k+3){
			n_one = byte_read;
		}
		if (i == k+4){
			n_two = byte_read;
			n = (n_one<<8) + n_two;
			/*printf("n = %d \n", n);*/
			n = n*2;
		}
		/*once the contents and address are determined, the variables are passed onto the add_to_list function*/
		if(n > 0 & i > (k+4)){

			if (i%2 == 0 ){
				cont_one = byte_read;
			} else {
				cont_two = byte_read;
				contents = (cont_one<<8) + cont_two;
				/*printf("contents = %x \n", contents);*/
				list = add_to_list(memory, address, contents);
				address++;
			}

			n--;
		}
		
		/*The following codes parses the DATA Section. It is pretty much the same as CODE*/
		if(head_one == 218 & head_two == 218){
			/*printf("Found DATA! \n");*/
			j=i;
			k=i;
		}

		/*The following codes parses the SYMBOL Section*/
		if(head_one == 195 & head_two == 183){
			/*printf("Found SYMBOL! \n");*/
			m = i;
			l = i;
		}
		if (i == m+1){
			addr_one = byte_read;
		}
		if (i == m+2){
			addr_two = byte_read;
			
			address = (addr_one<<8) + addr_two;
			/*printf("address = %x \n", address);*/
		}
		if (i == l+3){
			n_one = byte_read;
		}
		if (i == l+4 & l != 0){
			n_two = byte_read;
			n2 = (n_one<<8) + n_two;
			/*printf("n2 = %d \n", n2);*/
			lab_char = malloc (n2+1) ;	
			p = 0;
		}
		/*the bytes are added one by one into the char array*/
		if(n2 > 0 & i > (l+4)){
			lab_char[p] = byte_read ;
			p++;
			n2--;
			if(n2 ==0){
				lab_char[p] = '\0' ;
			}

		} 
		/*the label is written into the corresponding node*/
		if(n2 ==0 & lab_char != NULL){
			
			fread(lab_char, sizeof(char), n, my_obj_file);
			/*printf("lab_char = %s \n", lab_char);*/
			row_of_memory1 = search_address(*memory, address); 
			/*if the search function cannot find address, return NULL*/
			if(row_of_memory1 == NULL){
				printf("ERROR! Node does not exist!\n");
				return 2;
			}
			row_of_memory1->label =lab_char;
			p = 0;
		}

		i++;

	} 

	if(!byte_read){
		printf("ERROR! Parse failed!\n");
		return 2;
	}

	return 0 ;
}
