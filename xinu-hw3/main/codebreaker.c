/**
 * COSC 3250 - Project 2 Breaking the code
 * This code takes a user input from the key board, and a key, and decodes it into another 
 * another message. And is able to do this until the user quits 
 * Date 2/2/22
 * @author Emma Claire Kinnison
 * Instructor Dr. Brylow
 * TA-BOT:MAILTO emma.kinnison@marquette.edu
 */


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
int SPACE_ASCII = 32;
int ENTER_ASCII = 10;
int NUM_ALPHA_PLUS_ONE = 27;
int DECODED_SPACE = 0;
int UPPER_E_ASCII = 69;

void decoder_ring_printer(int* data, int key, int index){
    int c= 0;			//initilization
	int previousc=0;
	int previous=0;
	int sum=0;
    int y=0;
	while(y<index){	//auto cast the input char to an uppercase letter, run while loop while not the EOF char
		c=data[y];
        if(c==EOF){
            y=1026;
		}
		else{	//do this
			if((isalpha(c))||(isspace(c))){
				if(c== SPACE_ASCII){	//if its  a space, force it to 0
					c= DECODED_SPACE;
				}
				else if(c== ENTER_ASCII){	//if its an enter, reset everything, make c a non reachable number otherwise
					c=100;
					kprintf("\n");

				}
				else{	//make the value 0 to 26
					c=c-64;
				}
				sum=c-((previous+key)%NUM_ALPHA_PLUS_ONE);	//decode
				if(sum<0){
					sum=sum+NUM_ALPHA_PLUS_ONE;
				}
			
				int i=0;
			

				if((c!=100)){		//these are our enter and spaces
					if(sum<0){	//add to 64
						kputc(previous+64);
					}
					if(sum==DECODED_SPACE){		//make a space
						kprintf(" ");

					}
					else{		//make the correct uppercase value
						kputc(sum+64);
					}
				}
				else{
					if(c=100){		//reset
						
					}
				}
				if(c==100){

				}
				else{
					previous=c;		//maintain variables 

				}
			}
			else{
				if(c== ENTER_ASCII){
					c=DECODED_SPACE;
					previous=0;
					sum=0;
					kprintf("\n");
				}
				else{
					kprintf(" ");
				}
			}
		}
            y++;			
	}
}


int decoder_ring(int* data, int key){
    int z =0;
    int y=0;
    int c=0;
    int sum=0;
    int previous=0;
    int j=0;
    int decoded_data[1025];
    while(y<1025){	//auto cast the input char to an uppercase letter, run while loop while not the EOF char
        c=data[y];
        
        if(c==EOF){
            y=1026;
		}
		else{	//do this
			if((isalpha(c))||(isspace(c))){
				if(c== SPACE_ASCII){	//if its  a space, force it to 0
					c=DECODED_SPACE;
				}
				else if(c== ENTER_ASCII){	//if its an enter, reset everything, make c a non reachable number otherwise
					c=100;
				}
				else{	//make the value 0 to 26
					c=c-64;
				}
				//sum=c-previous-key;	//decode
				sum=c-((previous+key)%NUM_ALPHA_PLUS_ONE);	//decode
				if(sum<0){
					sum=sum+NUM_ALPHA_PLUS_ONE;
				}
				int i=0;
					
				if((c!=100)){		//these are our enter and spaces
					if(sum<0){	//add to 64
						//putchar(previous+64);
                        decoded_data[j] =previous+64;
                        j++;
					}
					if(sum==DECODED_SPACE){		//make a space
						//printf(" ");
                        decoded_data[j] =DECODED_SPACE;
                        j++;
					}
					else{		//make the correct uppercase value
					//	putchar(sum+64);
                        decoded_data[j] =sum+64;
                        j++;
					}
				}
				else{
					if(c=100){		//reset
					}
				}
				if(c==100){
				}
				else{
					previous=c;		//maintain variables 
				}
			}
			else{
				if(c==ENTER_ASCII){
					c=DECODED_SPACE;
					previous=0;
					sum=0;
					//printf("\n");
                    decoded_data[j] =ENTER_ASCII;
                    j++;
				}
				else{
					//printf(" ");
                    decoded_data[j] =DECODED_SPACE;
                    j++;
				}
			}
		}
        y++;
	}

    int counter=0;
    int k=0;
    while(k<1025){
        if(decoded_data[k]==UPPER_E_ASCII){
            counter++;
        }
        else{
        }
        k++;
    }
    return counter;
}


int main(int argc, char **argv){

	int c= 0;			//initilization
	int previousc=0;
	int previous=0;
	int key=0;
	int sum=0;
    int textarr[1025];
    textarr[1025]=EOF;
    int j=0;

    while (j<1025){         //populate with zeros
        textarr[j]=0;
        j++;
    }

    int index=0;    //more initiailizing
    int indexlooper=0;
    int keykey=0;
    int first=0;
    int second=-1;
    int temp=0;
    int keyfirst=0;
    int keysecond=0;
    int keytemp=0;

    while((c=toupper(getchar()))!=EOF){
        if(index>=1025){
        }
        else{
            textarr[index]=c;
            index++;
		}
	}

	while(indexlooper<27){
		keykey=decoder_ring(textarr, indexlooper);
		if(second==keykey){
		}
		else if(second<keykey){
			if(keykey>first){
				temp=first;
				first=keykey;
				second=temp;

				keytemp=keyfirst;
				keyfirst=indexlooper;
				keysecond=keytemp;
			}
			else{
				second=keykey;
				keysecond=indexlooper;
			}
		}
		indexlooper++;
	}
  

    printf("Most probable key is %d\n", keysecond);

    decoder_ring_printer(textarr, keysecond, index);
	printf("\n");
    
}
