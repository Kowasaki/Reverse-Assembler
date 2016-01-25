#include <stdio.h>
#include "lc4_memory.h"
#include <stdlib.h>


/* 
 * adds a new node to the end of a linked list pointed to by head 
 */
int add_to_list (row_of_memory** head, 
		 short unsigned int address, 
		 short unsigned int contents) 
{	
	row_of_memory *current = *head ;
	row_of_memory *old_end = NULL;
	/* allocate memory for a single node */
	row_of_memory *new_node = NULL ;
	char *label = NULL;
	char *assembly = NULL;

	new_node = malloc (sizeof(row_of_memory)) ;


	/* populate fields in newly allocated node w/ address&contents */
	new_node -> address = address ;
	new_node -> contents = contents ;
	/*initalizing label and assembly here too*/
	new_node -> label = label;
	new_node -> assembly = assembly;

	/* if head==NULL, node created is the new head of the list! */
	if (*head == NULL) {
		*head = new_node;
		return 0;
	}
	/* otherwise, traverse linked list until we reach the end */
	while (current != NULL){
		/*find the current end of list*/
		old_end = current ;
		current = current->next;
	}

	/* add node to the end of list */
	new_node -> next  = NULL ;
	old_end ->next = new_node;
	/* return 0 for success, -1 if malloc fails */
	/*printf("success!\n");*/
	return 0 ;

	if (new_node == NULL) return -1 ;
}


/* 
 * search linked list by address field, returns node if found 
 */
row_of_memory* search_address (row_of_memory* head, 
			       short unsigned int address ) 
{
	row_of_memory *current = head ;

	short unsigned int *contents = 0;

	/* traverse linked list, searching each node for "address"  */

	while (current!=NULL) {
	/* return pointer to node in the list if item is found */
		if (current -> address == address){

			/*printf ("\tFOUND IT: %x \n", address) ;*/
			return current ;
		}
		
		current = current->next ;
	}
	
	/* return NULL if list is empty or if "address" isn't found */
	 
	if (current == NULL){
		printf ("\tNOT FOUND \n") ;
		return NULL ;
	} 
	return NULL;
}

/* 
 * search linked list by opcode field, returns node if found 
 */
row_of_memory* search_opcode  (row_of_memory* head, 
				      short unsigned int opcode  ) 
{	
	row_of_memory *current = head ;
	short unsigned int contents;
	
	/* traverse linked list until node is found with matching opcode
	AND "assembly" field of node is empty */
	while (current!=NULL) {
		contents = current->contents;
		if (contents>>12 == opcode && current -> assembly == NULL){
			/*printf ("\tFOUND OPCODE: %x \n", contents) ;*/
			/* return pointer to node in the list if item is found */
			return current ;
		}

		current = current->next ;
	}
	

	/* return NULL if list is empty or if no matching nodes */
	if (current == NULL){
		/*printf ("\tNOT FOUND \n") ;*/
		return NULL ;
	} 
	return NULL;
}

/*prints label, address, contents, and assembly of nodes*/
void print_list (row_of_memory* head ) 
{	
	int i = 0 ;

	/* make sure head isn't NULL */
	if(head == NULL) printf ("\tError! No list found! \n") ;
	/* print out a header */
	printf ("\t<label>  <address>  <contents>  <assembly>\n") ;
	/* traverse linked list, print contents of each node */	
	while (head != NULL){

		printf ("\t %s     %04x       %04x     %-10s \n", head->label ,  head->address, head->contents, head->assembly) ;
		head = head -> next;

	}

	return ;
}

/* 
 * delete entire linked list
 */
int delete_list    (row_of_memory** head ) 
{
	row_of_memory *current = *head ;
	row_of_memory *temp = NULL ;
	char *label = NULL;
	char *assembly = NULL;
	/* delete entire list node by node */
	while (current!=NULL) {
	/*set up temp node for deletion*/
	temp = current;
	/*labels need to be deleted too*/
	label = current -> label;
	assembly = current -> assembly;
	current = current->next ;
	free(assembly);
	free(label);
	free(temp);
	
	}
	/* if no errors, set head = NULL upon deletion */
	if (current == NULL){
		head = NULL;
	}
	/* return 0 if no error, -1 for any errors that may arise */
	return 0 ;
	if (head == NULL){
		printf("Error! Head pointer not found!\n");
		return -1;
	} 
}
