#include <stdio.h>
#include "lc4_memory.h"
#include "lc4_loader.h"
#include "lc4_disassembler.h"

/* program to mimic pennsim loader and disassemble object files */


int main (int argc, char** argv) {

	/**
	 * main() holds the linked list &
	 * only calls functions in other files 
	 */

	/* step 1: create head pointer to linked list: memory 	*/

	/*short unsigned int contents = 0;
	short unsigned int address = 0;*/
	row_of_memory* memory = NULL ;


	/* step 2: determine filename, then open it		*/
	/*   TODO: extract filename from argv, pass it to open_file() */
	   	FILE *in_obj;
	   	int parse;
	   	int rev;
		int delete;

		if (argc < 2){
			printf("Error: incorrect command");
			return 1;
		}

		/*open the file in argv[1]*/
		in_obj=open_file(argv[1]);
		if(&open_file == NULL){
			return 1;
		}
		printf("You are opening %s \n", argv[1] );


	/* step 3: call function: parse_file() in lc4_loader.c 	*/
	/*   TODO: call function & check for errors		*/
		parse = parse_file(in_obj, &memory);

		if (parse == 0){
			printf("parse success!\n");
			fclose(in_obj);
		} else {
			printf("something went wrong during parsing!\n");
			delete = delete_list(&memory);
		}
	

	/* step 4: call function: reverse_assemble() in lc4_disassembler.c */
	/*   TODO: call function & check for errors		*/
		rev = reverse_assemble(memory);

		if (rev == 0){
			printf("reverse assemble success!\n");
			
		} else {
			printf("something went wrong during reverse assemble operation!\n");
			return 1;
		}

	/* step 5: call function: print_list() in lc4_memory.c 	*/
	/*   TODO: call function 				*/
		print_list(memory);

	/* step 6: call function: delete_list() in lc4_memory.c */
	/*   TODO: call function & check for errors		*/
		delete = delete_list(&memory);
		if (delete == 0){
			printf("delete success!\n");
			
		} else {
			printf("something went wrong during deletion!\n");
			return 1;
		}
	/* only return 0 if everything works properly */
	return 0 ;
}
