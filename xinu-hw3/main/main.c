/**
 * COSC 3250 - Project 3
 * Explain briefly the functionality of the program.
 * @author Emma Claire Kinnison David Santiago
 * Instructor Dr. Brylow
 * TA-BOT:MAILTO emma.kinnison@marquette.edu david.santiago@marquette.edu
 */
/**
 * @file     main.c
 */
/* Embedded Xinu, Copyright (C) 2009, 2022.  All rights reserved. */

#include <xinu.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>'
/**
 * Main process.  You can modify this routine to customize what Embedded Xinu
 * does when it starts up.
 */

//this gets rid of my magic numbers
#define SPACE_ASCII 32
#define BACKSLASH_R_ASCII 13
#define ENTER_ASCII 10
#define NUM_ALPHA_PLUS_ONE 27
#define DECODED_SPACE 0
#define UPPER_E_ASCII 69
#define EOT 4
#define ADJUSTER 64
#define MAXKEY 27

//this prints out the result of the decoder once it has figured out what the correct result is
void decoder_ring_printer(int* data, int key, int index) {
	int c = 0;			//initilization
	int previousc = 0;
	int previous = 0;
	int sum = 0;
	int y = 0;
	while (y < index) {	//auto cast the input char to an uppercase letter, run while loop while not the EOF char
		c = data[y];
		if ((c == EOT)||(c==EOF)) {
			y = 129;
		}
		else {	//do this
			if ((isalpha(c)) || (isspace(c))) {
				if (c == SPACE_ASCII) {	//if its  a space, force it to 0
					c = DECODED_SPACE;
				}
				else if (c == ENTER_ASCII) {	//if its an enter, reset everything, make c a non reachable number otherwise
					c = 100;
					kprintf("\n");

				}
				else {	//make the value 0 to 26
					c = c - ADJUSTER;
				}
				sum = c - ((previous + key) % NUM_ALPHA_PLUS_ONE);	//decode
				if (sum < 0) {
					sum = sum + NUM_ALPHA_PLUS_ONE;
				}

				int i = 0;


				if ((c != 100)) {		//these are our enter and spaces
					if (sum < 0) {	//add to 64
						kputc(previous + ADJUSTER);
					}
					if (sum == DECODED_SPACE) {		//make a space
						kprintf(" ");

					}
					else {		//make the correct uppercase value
						kputc(sum + ADJUSTER);
					}
				}
				else {
					if (c = 100) {		//reset

					}
				}
				if (c == 100) {

				}
				else {
					previous = c;		//maintain variables 

				}
			}
			else {
				if (c == ENTER_ASCII) {
					c = DECODED_SPACE;
					previous = 0;
					sum = 0;
					kprintf("\n");
				}
				else {
					kprintf(" ");
				}
			}
		}
		y++;
	}
}


int decoder_ring(int* data, int key) {
	int z = 0;
	int y = 0;
	int c = 0;
	int sum = 0;
	int previous = 0;
	int j = 0;
	int decoded_data[128];
	while (y < 128) {	//auto cast the input char to an uppercase letter, run while loop while not the EOF char
		c = data[y];

		if ((c == EOF)||(c== EOT)) {
			y = 129;
		}
		else {	//do this
			if ((isalpha(c)) || (isspace(c))) {
				if (c == SPACE_ASCII) {	//if its  a space, force it to 0
					c = DECODED_SPACE;
				}
				else if (c == BACKSLASH_R_ASCII) {
					c = 100;
				}
				else if (c == ENTER_ASCII) {	//if its an enter, reset everything, make c a non reachable number otherwise
					c = 100;
				}
				else {	//make the value 0 to 26
					c = c - ADJUSTER;
				}
				//sum=c-previous-key;	//decode
				sum = c - ((previous + key) % NUM_ALPHA_PLUS_ONE);	//decode
				if (sum < 0) {
					sum = sum + NUM_ALPHA_PLUS_ONE;
				}
				int i = 0;

				if ((c != 100)) {		//these are our enter and spaces
					if (sum < 0) {	//add to 64
						//putchar(previous+64);
						decoded_data[j] = previous + ADJUSTER;
						j++;
					}
					if (sum == DECODED_SPACE) {		//make a space
						//printf(" ");
						decoded_data[j] = DECODED_SPACE;
						j++;
					}
					else {		//make the correct uppercase value
					//	putchar(sum+64);
						decoded_data[j] = sum + ADJUSTER;
						j++;
					}
				}
				else {
					if (c = 100) {		//reset
					}
				}
				if (c == 100) {
				}
				else {
					previous = c;		//maintain variables 
				}
			}
			else {
				if (c == ENTER_ASCII) {
					c = DECODED_SPACE;
					previous = 0;
					sum = 0;
					//printf("\n");
					decoded_data[j] = ENTER_ASCII;
					j++;
				}
				else if (c == BACKSLASH_R_ASCII) {

				}
				else {
					//printf(" ");
					decoded_data[j] = DECODED_SPACE;
					j++;
				}
			}
		}
		y++;
	}

	int counter = 0;
	int k = 0;
	while (k < 128) {
		if (decoded_data[k] == UPPER_E_ASCII) {
			counter++;
		}
		else {
		}
		k++;
	}
	return counter;
}

void codebreaker(){
	int c = 0;			//initilization
	int previousc = 0;
	int previous = 0;
	int key = 0;
	int sum = 0;
	int textarr[128];
	textarr[127] = EOF;
	int j = 0;

	while (j < 128) {         //populate with zeros
		textarr[j] = 0;
		j++;
	}

	int index = 0;    //more initiailizing
	int indexlooper = 0;
	int keykey = 0;
	int first = 0;
	int second = -1;
	int temp = 0;
	int keyfirst = 0;
	int keysecond = 0;
	int keytemp = 0;
	kprintf("Enter your codebreaker text:\n");

	while ((c = kgetc()) != EOF & c != EOT) {
		
			c = toupper(c);
			kputc(c);
			textarr[index] = c;
			index++;
		


	}
	textarr[index] = -1;		 //this signifies EOF
	while (indexlooper < MAXKEY) {						//make sure all the different indexes work
		keykey = decoder_ring(textarr, indexlooper);
		if (second == keykey) {
		}
		else if (second < keykey) {	//do all the switches so that the second most is identified
			if (keykey > first) {
				temp = first;
				first = keykey;
				second = temp;

				keytemp = keyfirst;
				keyfirst = indexlooper;
				keysecond = keytemp;
			}
			else {
				second = keykey;
				keysecond = indexlooper;
			}
		}
		indexlooper++;
	}


	kprintf("Most probable key is %d\n", keysecond);	//print it

	decoder_ring_printer(textarr, keysecond, index);
	kprintf("\n");
}





process main(void)
{
    kprintf("Hello Xinu World!\n");


   // testcases();
    // TODO: Put your main program for codebreaker here.
    //       Replace any calls to printf() with kprintf().
    //       Replace any calls to getchar() with kgetc().
    codebreaker();
	kprintf("===TEST END===");

    while (1)
        ;

    return 0;
}
