/* @filename interp.c */
/*
* @ProgramDescription
* This program simulate assembly instruction implemented in C
* a program that takes the instruction from the keyboard
* Using 1D array, 2D arrays, and structure to handle my program
* 2D array to handle user input and store data
* Struct is to handle the flags
* Program has 5 helper functions and all the actual insturction
* been done in the main function
*/

/*
* @author Ziad Sakr
* @version 1.0 7/25/2019
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LEN 500
#define TRUE 1
#define FALSE 0

/* helper functions declaration*/
void removeChar(char c[]);
void toUpper(char c[]);
void display(char c, char s[], int num);
int test();



/*
* Start of our main funciton
*/
void main(){
	/* Local variable declaration*/

	//Locale variable register to store the 4 registers
	char registers[4];
	//local variable memory to store the 8 memories
	char memory[8];
	//struct to store flags declared as local
	struct{
		int ZF;
		int SF;
		int OF;
	} flag;

	int i, j;
	int condition = TRUE;
	char c[LEN][LEN];

	for(i = 0; i < 4; i++){
			registers[i] = 0;
	}
	for(j = 0; j < 8; j++){
			memory[j] = 0;
	}
	flag.ZF = 0;
	flag.SF = 0;
	flag.OF = 0;

	while(condition == TRUE){
		printf("\nSM$: ");
		scanf("%s", c[0]);
		toUpper(c[0]);

		/*
		* check if user entered READ
		* To store data into a specific register or memory location
		*/
		if(strcmp(c[0], "READ") == 0){
			flag.ZF = 0;
			flag.SF = 0;
			flag.OF = 0;
			if(test() == TRUE){
				continue;
			}
			scanf("%s", c[1]);
			removeChar(c[1]);
			if(test() == TRUE){
				continue;
			}
			scanf("%s", c[2]);
			removeChar(c[2]);
			toUpper(c[2]);
			if((atoi(c[1]) == 0)){
					printf("???");
					continue;
			}

			/*
			* check the flags
			* flag algorithm taken from the assignment instructions
			*/
			if((atoi(c[1]) > 127) || (atoi(c[1]) < -128)){
				flag.OF = 1;
			}
			if(atoi(c[1]) < 0){
				flag.SF = 1;
			}
			if(c[1] == 0){
				flag.ZF = 1;
			}
			/**
			* check if user enter a specific memory or register in order to store
			* it to the specific memory or register we want
			* Handling if user entered outrange memory or register location.
			*/
			if((c[2][0] == 'M') && ((c[2][1] - '0') < 8) && (isdigit(c[2][1]))){
					memory[(c[2][1] - '0')] = atoi(c[1]);
			}
			else if((c[2][0] == 'R') && ((c[2][1] - '0') < 4) && (isdigit(c[2][1]))){
					registers[(c[2][1] - '0')] = atoi(c[1]);
			}
			else {
				printf("???\n");
				continue;
			}
		}
		/*
		* check if user entered WRITE followed by register/ memory location
		* to print the data from the register/ memory location
		*/
		else if(strcmp(c[0], "WRITE") == 0){
			flag.ZF = 0;
			flag.SF = 0;
			flag.OF = 0;
			if(test() == TRUE){
				continue;
			}
			scanf("%s", c[1]);
			removeChar(c[1]);
			toUpper(c[1]);


			/**
			* check if user enter a specific memory or register to print
			* print data
			* Handling if user entered outrange memory or register location.
			*/
			if((c[1][0] == 'M') && ((c[1][1] - '0') < 8) && (isdigit(c[1][1]))){
					printf("value is: %d\n", memory[c[1][1] - '0']);
			}
			else if((c[1][0] == 'R') && ((c[1][1] - '0') < 4) && (isdigit(c[1][1]))){
					printf("value is: %d\n", registers[c[1][1] - '0']);
			}
			else {
				printf("???\n");
				continue;
			}
		}

		/*
		* if user Enter PRNITS
		* display all registers, memories, and flags along with
		* data that they have
		*/
		else if(strcmp(c[0], "PRINTS") == 0){
			/*
			* Calling print function in order to print register and memory
			*/

			//registers
			display('R', registers, 0);
			display('R', registers, 1);
			display('R', registers, 2);
			display('R', registers, 3);
					// memory

					display('M', memory, 0);
					display('M', memory, 1);
					display('M', memory, 2);
					display('M', memory, 3);
					display('M', memory, 4);
					display('M', memory, 5);
					display('M', memory, 6);
					display('M', memory, 7);

						//flags
						printf("\t%2d", flag.ZF);
						printf("\t%2d", flag.SF);
						printf("\t%2d", flag.OF);
			printf("\n");
			printf("--");
			printf("\t--");
			printf("\t--");
			printf("\t--");
				//memory
				printf("\t--");
				printf("\t--");
				printf("\t--");
				printf("\t--");
				printf("\t--");
				printf("\t--");
				printf("\t--");
				printf("\t--");
					//flags
						printf("\t--");
						printf("\t--");
						printf("\t--");
			printf("\n");
			printf("R0");
			printf("\tR1");
			printf("\tR2");
			printf("\tR3");
				//memory
				printf("\tM0");
				printf("\tM1");
				printf("\tM2");
				printf("\tM3");
				printf("\tM4");
				printf("\tM5");
				printf("\tM6");
				printf("\tM7");
					//flags
					printf("\tZF");
					printf("\tSF");
					printf("\tOF");
		printf("\n");

		}

		/*
		* Start of our MOVE instruction
		* check if the instruction will move from memory to a register
		* if yes then move done.
		*/
		else if(strcmp(c[0], "MOVE") == 0){
			if(test() == TRUE){
				continue;
			}
			//scanning first element
			//remove anyspecial char
			scanf("%s",c[1]);
			removeChar(c[1]);
			toUpper(c[1]);
			if(test() == TRUE){
				continue;
			}
			//scanning second elemnt
			//remove anyspecial char
			scanf("%s", c[2]);
			removeChar(c[2]);
			toUpper(c[2]);

			if((c[1][0] == 'M') && ((c[1][1] - '0') < 8) && (isdigit(c[1][1]))){
					if((c[2][0] == 'R') && ((c[2][1] - '0') < 4) && (isdigit(c[2][1]))){
						registers[c[2][1] - '0'] = memory[c[1][1] - '0'];
			}
			else if (c[2][0] == 'M'){
					printf("???");
					continue;
			}
			else {
				printf("???\n");
				continue;
			}

		}
		else if((c[1][0] == 'R') && ((c[1][1] - '0') < 4) && (isdigit(c[1][1]))){
				if((c[2][0] == 'M') && ((c[2][1] - '0') < 8) && (isdigit(c[2][1]))){
					memory[c[2][1] - '0'] = registers[c[1][1] - '0'];
		}
		else if ((c[2][0] == 'R') && ((c[2][1] - '0') < 4) && (isdigit(c[2][1]))){
				registers[c[2][1] - '0'] = registers[c[1][1] - '0'];
		}
		else {
				printf("???\n");
				continue;
		}
	}
		else {
			printf("???\n");
			continue;
		}
	}

	/*
	* Start of our ADD instruction
	* check if the instruction will move from memory to a register
	* if yes then move done.
	*/
	else if(strcmp(c[0], "ADD") == 0){
		if(test() == TRUE){
			continue;
		}
		scanf("%s",c[1]);
		removeChar(c[1]);
		toUpper(c[1]);
		if(test() == TRUE){
			continue;
		}
		scanf("%s", c[2]);
		removeChar(c[2]);
		toUpper(c[2]);

		if((c[1][0] == 'M') && ((c[1][1] - '0') < 8) && (isdigit(c[1][1]))){
				if((c[2][0] == 'R') && ((c[2][1] - '0') < 4) && (isdigit(c[2][1]))){
					if(((memory[c[1][1] - '0'] + registers[c[2][1] - '0']) > 127) || ((memory[c[1][1] - '0'] + registers[c[2][1] - '0']) < -128)){
						flag.OF = 1;
					}
					if((memory[c[1][1] - '0'] + registers[c[2][1] - '0']) < 0){
						flag.SF = 1;
					}
					if((memory[c[1][1] - '0'] + registers[c[2][1] - '0']) == 0){
						flag.ZF = 1;
					}
					registers[0] = memory[c[1][1] - '0'] + registers[c[2][1] - '0'];
		}
		else if (c[2][0] == 'M'){
				printf("You can't use Add operation from memory to memory");
				continue;
		}
		else {
			printf("Invalid storing location\n");
			continue;
		}

	}
		else if((c[1][0] == 'R') && ((c[1][1] - '0') < 4) && (isdigit(c[1][1]))){
			if((c[2][0] == 'M') && ((c[2][1] - '0') < 8) && (isdigit(c[2][1]))){
				if(((memory[c[2][1] - '0'] + registers[c[1][1] - '0']) > 127) || ((memory[c[2][1] - '0'] + registers[c[1][1] - '0']) < -128)){
					flag.OF = 1;
				}
				if((memory[c[2][1] - '0'] + registers[c[1][1] - '0']) < 0){
					flag.SF = 1;
				}
				if((memory[c[2][1] - '0'] + registers[c[1][1] - '0']) == 0){
					flag.ZF = 1;
				}
				registers[0] = memory[c[2][1] - '0'] + registers[c[1][1] - '0'];
	}
		else if((c[1][0] == 'R') && ((c[1][1] - '0') < 4) && (isdigit(c[1][1]))){
				if(((registers[c[2][1] - '0'] + registers[c[1][1] - '0']) > 127) || ((registers[c[2][1] - '0'] + registers[c[1][1] - '0']) < -128)){
					flag.OF = 1;
				}
				if((registers[c[1][1] - '0'] + registers[c[2][1] - '0']) < 0){
					flag.SF = 1;
				}
				if((registers[c[2][1] - '0'] + registers[c[1][1] - '0']) == 0){
					flag.ZF = 1;
				}
				registers[0] = memory[c[2][1] - '0'] + registers[c[1][1] - '0'];
	}
	else {
			printf("???");
			continue;
	}
}
	else {
		printf("???\n");
		continue;
	}
}


	/*
	* Start of our SUB instruction
	* check if the instruction will move from memory to a register
	* if yes then move done.
	*/
	else if(strcmp(c[0], "SUB") == 0){
		if(test() == TRUE){
			continue;
		}
		scanf("%s",c[1]);
		removeChar(c[1]);
		toUpper(c[1]);
		if(test() == TRUE){
			continue;
		}
		scanf("%s", c[2]);
		removeChar(c[2]);
		toUpper(c[2]);

		if((c[1][0] == 'M') && ((c[1][1] - '0') < 8) && (isdigit(c[1][1]))){
				if((c[2][0] == 'R') && ((c[2][1] - '0') < 4) && (isdigit(c[2][1]))){
					if(((registers[c[2][1] - '0'] - memory[c[1][1] - '0']) > 127) || ((registers[c[2][1] - '0'] - memory[c[1][1] - '0']) < -128)){
						flag.OF = 1;
					}
					if((registers[c[2][1] - '0'] - memory[c[1][1] - '0']) < 0){
						flag.SF = 1;
					}
					if((registers[c[2][1] - '0'] - memory[c[2][1] - '0']) == 0){
						flag.ZF = 1;
					}
					registers[0] = registers[c[2][1] - '0'] - memory[c[1][1] - '0'];
		}
		else if (c[2][0] == 'M'){
				printf("???");
				continue;
		}
		else {
			printf("???\n");
			continue;
		}

	}
		else if((c[1][0] == 'R') && ((c[1][1] - '0') < 4) && (isdigit(c[1][1]))){
			if((c[2][0] == 'M') && ((c[2][1] - '0') < 8) && (isdigit(c[2][1]))){
				if(((memory[c[2][1] - '0'] - registers[c[1][1] - '0']) > 127) || ((memory[c[2][1] - '0'] - registers[c[1][1] - '0']) < -128)){
					flag.OF = 1;
				}
				if((memory[c[2][1] - '0'] - registers[c[1][1] - '0']) < 0){
					flag.SF = 1;
				}
				if((memory[c[2][1] - '0'] - registers[c[1][1] - '0']) == 0){
					flag.ZF = 1;
				}
				registers[0] = memory[c[2][1] - '0'] - registers[c[1][1] - '0'];
	}
		else if((c[2][0] == 'R') && ((c[2][1] - '0') < 4) && (isdigit(c[2][1]))){
				if(((registers[c[2][1] - '0'] - registers[c[1][1] - '0']) > 127) || ((registers[c[2][1] - '0'] - registers[c[1][1] - '0']) < -128)){
					flag.OF = 1;
				}
				if((registers[c[2][1] - '0'] - registers[c[1][1] - '0']) < 0){
					flag.SF = 1;
				}
				if((registers[c[2][1] - '0'] - registers[c[1][1] - '0']) == 0){
					flag.ZF = 1;
				}
				registers[0] = memory[c[2][1] - '0'] - registers[c[1][1] - '0'];
	}
	else {
			printf("???");
			continue;
	}
}
	else {
		printf("???\n");
		continue;
	}
}
/*
* Start of our MULT instruction
* check if the instruction will move from memory to a register
* if yes then move done.
*/
else if(strcmp(c[0], "MULT") == 0){
	flag.ZF = 0;
	flag.SF = 0;
	flag.OF = 0;
	if(test() == TRUE){
		continue;
	}
	scanf("%s",c[1]);
	removeChar(c[1]);
	toUpper(c[1]);
	if(test() == TRUE){
		continue;
	}
	scanf("%s", c[2]);
	removeChar(c[2]);
	toUpper(c[2]);

	if((c[1][0] == 'M') && ((c[1][1] - '0') < 8) && (isdigit(c[1][1]))){
			if((c[2][0] == 'R') && ((c[2][1] - '0') < 4) && (isdigit(c[2][1]))){
				if(((registers[c[2][1] - '0'] * memory[c[1][1] - '0']) > 127) || ((registers[c[2][1] - '0'] * memory[c[1][1] - '0']) < -128)){
					flag.OF = 1;
				}
				if((registers[c[2][1] - '0'] * memory[c[1][1] - '0']) < 0){
					flag.SF = 1;
				}
				if((registers[c[2][1] - '0'] * memory[c[2][1] - '0']) == 0){
					flag.ZF = 1;
				}
				registers[0] = registers[c[2][1] - '0'] * memory[c[1][1] - '0'];
	}
	else if (c[2][0] == 'M'){
			printf("???\n");
			continue;
	}
	else {
		printf("???\n");
		continue;
	}

}
	else if((c[1][0] == 'R') && ((c[1][1] - '0') < 4) && (isdigit(c[1][1]))){
		if((c[2][0] == 'M') && ((c[2][1] - '0') < 8) && (isdigit(c[2][1]))){
			if(((memory[c[2][1] - '0'] * registers[c[1][1] - '0']) > 127) || ((memory[c[2][1] - '0'] * registers[c[1][1] - '0']) < -128)){
				flag.OF = 1;
			}
			if((memory[c[2][1] - '0'] * registers[c[1][1] - '0']) < 0){
				flag.SF = 1;
			}
			if((memory[c[2][1] - '0'] * registers[c[1][1] - '0']) == 0){
				flag.ZF = 1;
			}
			registers[0] = memory[c[2][1] - '0'] * registers[c[1][1] - '0'];
}
	else if((c[2][0] == 'R') && ((c[2][1] - '0') < 4) && (isdigit(c[2][1]))){
			if(((registers[c[2][1] - '0'] * registers[c[1][1] - '0']) > 127) || ((registers[c[2][1] - '0'] * registers[c[1][1] - '0']) < -128)){
				flag.OF = 1;
			}
			if((registers[c[2][1] - '0'] * registers[c[1][1] - '0']) < 0){
				flag.SF = 1;
			}
			if((registers[c[2][1] - '0'] * registers[c[1][1] - '0']) == 0){
				flag.ZF = 1;
			}
			registers[0] = memory[c[2][1] - '0'] * registers[c[1][1] - '0'];
}
else {
		printf("???\n");
		continue;
}
}
else {
	printf("???\n");
	continue;
}
}
/*
* Start of our DIV instruction
* check if the instruction will move from memory to a register
* if yes then move done.
*/
else if(strcmp(c[0], "DIV") == 0){
	flag.ZF = 0;
	flag.SF = 0;
	flag.OF = 0;
	if(test() == TRUE){
		continue;
	}
	scanf("%s",c[1]);
	removeChar(c[1]);
	toUpper(c[1]);
	if(test() == TRUE){
		continue;
	}
	scanf("%s", c[2]);
	removeChar(c[2]);
	toUpper(c[2]);

	if((c[1][0] == 'M') && ((c[1][1] - '0') < 8) && (isdigit(c[1][1]))){
			if((c[2][0] == 'R') && ((c[2][1] - '0') < 4) && (isdigit(c[2][1]))){
				if(((memory[c[1][1] - '0'] / registers[c[2][1] - '0']) > 127) || ((memory[c[1][1] - '0'] / registers[c[2][1] - '0']) < -128)){
					flag.OF = 1;
				}
				if((memory[c[1][1] - '0'] / registers[c[2][1] - '0']) < 0){
					flag.SF = 1;
				}
				if((memory[c[1][1] - '0'] / registers[c[2][1] - '0']) == 0){
					flag.ZF = 1;
				}
				registers[0] = memory[c[1][1] - '0'] / registers[c[2][1] - '0'];
	}
	else if (c[2][0] == 'M'){
			printf("???\n");
			continue;
	}
	else {
		printf("???\n");
		continue;
	}

}
	else if((c[1][0] == 'R') && ((c[1][1] - '0') < 4) && (isdigit(c[1][1]))){
		if((c[2][0] == 'M') && ((c[2][1] - '0') < 8) && (isdigit(c[2][1]))){
			if(((registers[c[1][1] - '0'] / memory[c[2][1] - '0']) > 127) || ((registers[c[1][1] - '0'] / memory[c[2][1] - '0']) < -128)){
				flag.OF = 1;
			}
			if((registers[c[1][1] - '0'] / memory[c[2][1] - '0']) < 0){
				flag.SF = 1;
			}
			if((registers[c[1][1] - '0'] / memory[c[2][1] - '0']) == 0){
				flag.ZF = 1;
			}
			registers[0] = registers[c[1][1] - '0'] / memory[c[2][1] - '0'];
}
	else if((c[2][0] == 'R') && ((c[2][1] - '0') < 4) && (isdigit(c[2][1]))){
			if(((registers[c[1][1] - '0'] / registers[c[2][1] - '0']) > 127) || ((registers[c[1][1] - '0'] / registers[c[2][1] - '0']) < -128)){
				flag.OF = 1;
			}
			if((registers[c[1][1] - '0'] / registers[c[2][1] - '0']) < 0){
				flag.SF = 1;
			}
			if((registers[c[1][1] - '0'] / registers[c[2][1] - '0']) == 0){
				flag.ZF = 1;
			}
			registers[0] = registers[c[1][1] - '0'] / registers[c[2][1] - '0'];
}
else {
		printf("???\n");
		continue;
}
}
else {
	printf("???\n");
	continue;
}
}
/*
* Start of our DIV instruction
* check if the instruction will move from memory to a register
* if yes then move done.
*/
else if(strcmp(c[0], "MOD") == 0){
	flag.ZF = 0;
	flag.SF = 0;
	flag.OF = 0;
	if(test() == TRUE){
		continue;
	}
	scanf("%s",c[1]);
	removeChar(c[1]);
	toUpper(c[1]);
	if(test() == TRUE){
		continue;
	}
	scanf("%s", c[2]);
	removeChar(c[2]);
	toUpper(c[2]);

	if((c[1][0] == 'M') && ((c[1][1] - '0') < 8) && (isdigit(c[1][1]))){
			if((c[2][0] == 'R') && ((c[2][1] - '0') < 4) && (isdigit(c[2][1]))){
				if(((memory[c[1][1] - '0'] % registers[c[2][1] - '0']) > 127) || ((memory[c[1][1] - '0'] % registers[c[2][1] - '0']) < -128)){
					flag.OF = 1;
				}
				if((memory[c[1][1] - '0'] % registers[c[2][1] - '0']) < 0){
					flag.SF = 1;
				}
				if((memory[c[1][1] - '0'] % registers[c[2][1] - '0']) == 0){
					flag.ZF = 1;
				}
				registers[0] = memory[c[1][1] - '0'] % registers[c[2][1] - '0'];
	}
	else if (c[2][0] == 'M'){
			printf("???\n");
			continue;
	}
	else {
		printf("???\n");
		continue;
	}

}
	else if((c[1][0] == 'R') && ((c[1][1] - '0') < 4) && (isdigit(c[1][1]))){
		if((c[2][0] == 'M') && ((c[2][1] - '0') < 8) && (isdigit(c[2][1]))){
			if(((registers[c[1][1] - '0'] % memory[c[2][1] - '0']) > 127) || ((registers[c[1][1] - '0'] % memory[c[2][1] - '0']) < -128)){
				flag.OF = 1;
			}
			if((registers[c[1][1] - '0'] % memory[c[2][1] - '0']) < 0){
				flag.SF = 1;
			}
			if((registers[c[1][1] - '0'] % memory[c[2][1] - '0']) == 0){
				flag.ZF = 1;
			}
			registers[0] = registers[c[1][1] - '0'] % memory[c[2][1] - '0'];
}
	else if((c[2][0] == 'R') && ((c[2][1] - '0') < 4) && (isdigit(c[2][1]))){
			if(((registers[c[1][1] - '0'] % registers[c[2][1] - '0']) > 127) || ((registers[c[1][1] - '0'] % registers[c[2][1] - '0']) < -128)){
				flag.OF = 1;
			}
			if((registers[c[1][1] - '0'] % registers[c[2][1] - '0']) < 0){
				flag.SF = 1;
			}
			if((registers[c[1][1] - '0'] % registers[c[2][1] - '0']) == 0){
				flag.ZF = 1;
			}
			registers[0] = registers[c[1][1] - '0'] % registers[c[2][1] - '0'];
		}
		else {
			printf("???\n");
			continue;
		}
	}
	else {
		printf("???\n");
		continue;
		}
	}

/*
* check if user entered READ
* To store data into a specific register or memory location
*/
	else if(strcmp(c[0], "COMP") == 0){
		flag.ZF = 0;
		flag.SF = 0;
		flag.OF = 0;
		if(test() == TRUE){
			continue;
	}
		scanf("%s", c[1]);
		removeChar(c[1]);
		toUpper(c[1]);
		if(test() == TRUE){
			continue;
	}
		scanf("%s", c[2]);
		removeChar(c[2]);
		toUpper(c[2]);


			if((c[1][0] == 'R') && ((c[1][1] - '0') < 4) && (isdigit(c[1][1]))){
					if((c[2][0] == 'M') && ((c[2][1] - '0') < 8) && (isdigit(c[2][1]))){
						if(((registers[c[1][1] - '0'] > registers[c[2][1] - '0']))){
							flag.ZF = 0;
							flag.SF = 1;
						}
						else if(((registers[c[1][1] - '0'] < registers[c[2][1] - '0']))){
							flag.ZF = 0;
							flag.SF = 0;
			}
			else {
				flag.ZF = 1;
				flag.SF = 0;
			}
			}
			else {
					printf("???\n");
					continue;
			}
		}
			else {
				printf("???\n");
				continue;
			}
		}
		else if(strcmp(c[0], "QUIT") == 0){
			condition = FALSE;
		}
		else {
			printf("???\n");
			continue;
		}
	}

}


/*
* function remove that takes one paramter
* this function role is to remove the unnessary character which * is the comma and empty spaces in this case
* @param char c[]
* return nothing
* inspired by lab 3 that we implemented similar function to it
*/
void removeChar(char c[]){
	int i, j;
	while(c[i] != '\0'){
		if((c[i] == ',') || c[i] == ' '){
			j = i;
			while (c[j] != '\0'){
				c[j] = c[j+1];
				j++;
			}
		}
		i++;
	}
}
/*
* function toUpper that takes one paramter
* this function role is to convert from lower to upper case
* @param char c[]
* return nothing
* inspired by lab 4 that we implemented similar function to it
*/
void toUpper(char c[]){
	int i = 0;
	while(c[i] != '\0'){
		if(c[i] >= 'a' && c[i] <= 'z'){
			c[i] = c[i] - 32;
		}
		i++;
	}
}
/*
* function print_test that takes three paramter
* this function will print '?' if register, memory, and/or flags * is empty and print the data if available
* @param char case
*	@param signed char s[]
* @param num
* return nothing
*/
void display(char c, char s[], int num){

		if(c == 'R'){
			if(num == 0){
				if(s[num] == 0){
					printf("%c", '?');
				}
				else {
					printf("%d", s[num]);
				}
			}
			else {
				if(s[num] == 0){
					printf("\t%2c", '?');
				}
				else {
					printf("\t%2d", s[num]);
				}
			}
		}
		else {
			if(s[num] == 0){
				printf("\t%2c", '?');
			}
			else {
				printf("\t%2d", s[num]);

			}
		}
}



/**
* test funtion to check if user enter a not valid instruction
* for ex: read 3, and then didn't enter the memory it will give you error
* @return -1 if invalid instruction
* @return 0 if valid instruction been entered
*/
int test(){
	char c;
	c = getchar();
	if(c == '\n'){
		printf("???\n");
		return TRUE;
	}
	return FALSE;

}
