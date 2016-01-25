#include <stdio.h>
#include "lc4_memory.h"
#include <stdlib.h>

int reverse_assemble (row_of_memory* memory) 
{
	/*The codes to check for is 0x0001*/
	int opcode = 0x0001;
	char *assembly = NULL;
	short unsigned int contents;
	row_of_memory *row_of_memory2 = NULL;
	/*This loop will serach for nodes with the opcode and translate its content into instructions*/
	while(memory != NULL){
		row_of_memory2 = search_opcode(memory, opcode);
		if(row_of_memory2 != NULL){
			
			assembly = malloc (15) ;
			contents = row_of_memory2 -> contents;
			
			short unsigned int shft_cont3 = contents<<10;
			short unsigned int op = shft_cont3>>13;
			short unsigned int shft_cont1 = contents<<4;
			short unsigned int d = shft_cont1>>13;
			short unsigned int shft_cont2 = contents<<7;
			short unsigned int s = shft_cont2>>13;
			short unsigned int shft_cont4 = contents<<13;
			short unsigned int t = shft_cont4>>13;
			short unsigned int shft_cont5 = contents<<11;
			int I = shft_cont5>>11;
			/*printf("I = %d \n", I );*/

			/*This switch determines which arithmetic operation is called for*/
			/*printf("op= %d \n", op);*/
			switch(op){
				case 0x00:
				assembly[0]= 'A';
				assembly[1]= 'D';
				assembly[2]= 'D';
				assembly[3]= 32;
				break;
				case 0x01:
				assembly[0]= 'M';
				assembly[1]= 'U';
				assembly[2]= 'L';
				assembly[3]= 32;
				break;
				case 0x02:
				assembly[0]= 'S';
				assembly[1]= 'U';
				assembly[2]= 'B';
				assembly[3]= 32;
				break;
				case 0x03:
				assembly[0]= 'D';
				assembly[1]= 'I';
				assembly[2]= 'V';
				assembly[3]= 32;
				break;
			}
			/*This switch determines which register is called for in d*/
			/*printf("d= %d \n", d);*/
			switch(d){
				case 0x00:
				assembly[4]= 'R';
				assembly[5]= '0';
				assembly[6]= ',';
				break;
				case 0x01:
				assembly[4]= 'R';
				assembly[5]= '1';
				assembly[6]= ',';
				break;
				case 0x02:
				assembly[4]= 'R';
				assembly[5]= '2';
				assembly[6]= ',';
				break;
				case 0x03:
				assembly[4]= 'R';
				assembly[5]= '3';
				assembly[6]= ',';
				break;
				case 0x04:
				assembly[4]= 'R';
				assembly[5]= '4';
				assembly[6]= ',';
				break;
				case 0x05:
				assembly[4]= 'R';
				assembly[5]= '5';
				assembly[6]= ',';
				break;
				case 0x06:
				assembly[4]= 'R';
				assembly[5]= '6';
				assembly[6]= ',';
				break;
				case 0x07:
				assembly[4]= 'R';
				assembly[5]= '7';
				assembly[6]= ',';
				break;
			}
			/*This switch determines which register is called for in s*/
			switch(s){
				case 0x00:
				assembly[7]= 'R';
				assembly[8]= '0';
				assembly[9]= ',';
				break;
				case 0x01:
				assembly[7]= 'R';
				assembly[8]= '1';
				assembly[9]= ',';
				break;
				case 0x02:
				assembly[7]= 'R';
				assembly[8]= '2';
				assembly[9]= ',';
				break;
				case 0x03:
				assembly[7]= 'R';
				assembly[8]= '3';
				assembly[9]= ',';
				break;
				case 0x04:
				assembly[7]= 'R';
				assembly[8]= '4';
				assembly[9]= ',';
				break;
				case 0x05:
				assembly[7]= 'R';
				assembly[8]= '5';
				assembly[9]= ',';
				break;
				case 0x06:
				assembly[7]= 'R';
				assembly[8]= '6';
				assembly[9]= ',';
				break;
				case 0x07:
				assembly[7]= 'R';
				assembly[8]= '7';
				assembly[9]= ',';
				break;
			}
			/*This switch determines which register is called for in t*/
			/*printf("t= %d \n", t);*/
			switch(t){
				case 0x00:
				assembly[10]= 'R';
				assembly[11]= '0';
				assembly[12]= '\0';
				break;
				case 0x01:
				assembly[10]= 'R';
				assembly[11]= '1';
				assembly[12]= '\0';
				break;
				case 0x02:
				assembly[10]= 'R';
				assembly[11]= '2';
				assembly[12]= '\0';
				break;
				case 0x03:
				assembly[10]= 'R';
				assembly[11]= '3';
				assembly[12]= '\0';
				break;
				case 0x04:
				assembly[10]= 'R';
				assembly[11]= '4';
				assembly[12]= '\0';
				break;
				case 0x05:
				assembly[10]= 'R';
				assembly[11]= '5';
				assembly[12]= '\0';
				break;
				case 0x06:
				assembly[10]= 'R';
				assembly[11]= '6';
				assembly[12]= '\0';
				break;
				case 0x07:
				assembly[10]= 'R';
				assembly[11]= '7';
				assembly[12]= '\0';
				break;
			}
			/*The if statement deals with IMM5. Since IMM5 have 5 digits it could overflow to the op variable, */
			/*which is why op with range from 4-7 are all included*/
			if (op == 4 | op == 5| op == 6| op ==7){
				/*printf("I = %d \n", I);*/
				assembly[0]= 'A';
				assembly[1]= 'D';
				assembly[2]= 'D';
				assembly[3]= 32 ;
				switch(d)
				;
				switch(s)
				;
				assembly[10]= '#';
				if(I>15){
				I = abs(I-32);
				/*printf("abs I = %d \n", I);*/
				/*ascii 45 is a minus sign*/
				assembly[11]= 45;
				assembly[12]= (I/10) + '0';
				assembly[13]= (I%10) + '0';
				assembly[14]= '\0';
				} else{
				assembly[11]= (I/10) + '0';
				/*printf("assembly[11] %c\n",assembly[11] );*/
				assembly[12]= (I%10) + '0';
				/*printf("assembly[12] %c\n",assembly[12] );*/
				assembly[13]= '\0';
				}
			}
			/*once the array is filled, the result is added into the node*/
			row_of_memory2 -> assembly = assembly;
		} 
		memory = memory -> next;
	}
	


	return 0 ;
}
