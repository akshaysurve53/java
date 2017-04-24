#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 

#define MAX 20				//Maximum entries for symbol table 
#define M_MAX 11			//Maximum number of mnemonics 
#define AD_MAX 5 			//Maximum number of assembler directives 
#define R_MAX 4			        //Maximum number of registers 
#define C_MAX 6			        //Maximum number of conditional codes 



//Variables 

static int errFlag; 
int LitCnt, PoolCnt,symcnt=0, TokCnt, LC, i,j,k; 
char Tok1[MAX], Tok2[MAX], Tok3[MAX], Tok4[MAX], Tok5[MAX], Buffer[80], temp[MAX]; 
FILE *fp1, *fp2, *fp, *fpErr;			 



//Data Structures 

int POOLTAB[MAX]; 
char MOTAB[][10]    =  {"STOP", "ADD", "SUB", "MULT", "MOVER", "MOVEM", "COMP", "BC", "DIV", "READ", "PRINT"}; 
char REGTAB[][10]   =  {"AREG", "BREG", "CREG","DREG"}; 
char CONDTAB[][10]  =  {"LT", "LE", "EQ", "GT", "GE", "ANY"}; 
char ADTAB[][10]    =  {"START", "END", "ORIGIN", "EQU", "LTORG"}; 


struct LITTAB 
{ 
	char Lit[5]; 
	int Addr; 
}L[MAX]; 



struct symbol 
{ 
	char sym[5]; 
	int Addr; 
}s[MAX]; 

//Functions 

int Searchsym(char *k) 
{ 
	int i; 
	for(i =0; i < symcnt; i++) 
	{ 
		if(strcmp(s[i].sym,k) == 0) 
			return(i); 
	} 
	return(-1); 
} 
int SearchLit(char *s) 
{ 
	int i; 
	for(i = POOLTAB[PoolCnt]; i < LitCnt; i++) 
	{ 
		if(strcmp(L[i].Lit,s) == 0) 
			return(i); 
	} 
	return(-1); 
} 

int SearchOp(char *s) 
{ 
	int i; 
	for(i = 0; i < M_MAX; i++) 
	{ 
		if(strcmp(MOTAB[i],s) == 0) 
			return(i); 
	} 
	return (-1); 
} 

int SearchDirective(char *s) 
{ 
	int i; 
	for(i = 0; i < AD_MAX; i++) 
	{ 
		if(strcmp(ADTAB[i],s) == 0) 
			return(i); 
	} 
	return (-1); 
} 

int SearchReg(char *s) 
{ 
	int i; 
	for(i = 0; i < R_MAX; i++) 
	{ 
		if(strcmp(REGTAB[i],s) == 0) 
			return(i); 
	} 
	return(-1); 
} 

int SearchCON(char *s) 
{ 
        int i; 
        for(i=0;i< C_MAX;i++) 
        { 
                if(strcmp(CONDTAB[i],s)==0) 
                      return i; 
        } 
      return -1; 
} 


void PassOne() 
{ 
	//fp1 - ptr of source file 
	//fp2 - ptr of Intermediate code file 
	int k; 
	fp1 = fopen("sr.txt", "r"); 
	if(fp1 == NULL) 
	{ 
		printf("\nCannot open the file"); 
		exit(0); 
	} 
	 
	fp2 = fopen("IC.txt", "w"); 
	if(fp2 == NULL) 
	{ 
		printf("\nCannot create the file"); 
		exit(0); 
	} 
	 
	while(fgets(Buffer,50,fp1)) 
	{ 
		//Initialise tokens to null 
		strcpy(Tok1,""); 
		strcpy(Tok2,""); 
		strcpy(Tok3,""); 
		strcpy(Tok4,""); 
		 
		TokCnt = sscanf(Buffer, "%s %s %s %s",Tok1, Tok2, Tok3, Tok4);   
		 
		switch(TokCnt) 
		{ 
			case 1 :  //STOP,START,LTORG,END 
				 
				 i = SearchOp(Tok1); 
				 if(i == 0)			//STOP 
				 { 
				 	fprintf(fp2,"(IS, %02d)\n",i); 
				 	break; 
				 } 
				 
				 i = SearchDirective(Tok1); 
				 
				 if(i == 0) 
				 { 
					fprintf(fp2,"(AD, %02d)\n",i); 
					LC = -1; 
				 } 
				 
				 else if(i==4 || i==1)	//END or LTORG 
				 { 
				 	fprintf(fp2,"(AD, %02d)\n",i); 
				 	 
				 	for(k = POOLTAB[PoolCnt]; k < LitCnt; k++) 
				 		L[k].Addr = LC++; 
				 		 
				 	POOLTAB[++PoolCnt] = LitCnt; 
				 	LC--; 
				 } 
				 break;		//end of case 1 			 
			 
			 
			case 2 : //READ, PRINT, START, ORIGIN		 
				 i = SearchOp(Tok1);		// i for search in opcodes 
				 k = SearchDirective(Tok1);    //Search in ADTAB 
				 
				 
				 if(k == 0 || k == 2)	       //START or ORIGIN 
				 { 
				 	i=Searchsym(Tok2); 
				 	if(i!=-1) 
				 		LC=s[i].Addr; 
				 	else 
				 	LC = atoi(Tok2) - 1; 
				 	 
				 	fprintf(fp2, "(AD, %02d) (C, %03d)\n",k,LC+1); 
				 	break; 
				 } 
				 else if(i!=-1) 
				{ 
				 
				if(Tok2[1] == '=')      //Literal 
                                        { 
                                                j = SearchLit(Tok2); 
                                                
                                                if(j == -1)     //Literal not present 
                                                { 
                                                        sprintf(temp,"(L, %02d)",LitCnt); 
                                                        strcpy(L[LitCnt++].Lit,Tok2); 
                                                } 
                                                else 
                                                        sprintf(temp,"(L, %02d)",j); 
                                          
				fprintf(fp2,"(IS, %02d) %s\n",i,temp); 
					} 
				else 
				    { 
				    j = SearchReg(Tok2); 
                                                
                                          fprintf(fp2,"(IS, %02d) %d\n",i,j); 
				} 
				} 
				 
				else 
				 { 
				 	fprintf(fp2, "%s --- Invalid Instruction\n", Tok1); 
				 	errFlag = 1; 
				 	break; 
				 } 
				 break;         //end of case 2 
				 
				 
			case 3 : //ADD to DIV 
                                 
                                 i = SearchOp(Tok1); 
                                
                                 if(i >= 1 && i <= 8)           //if Assembler directive 
                                 { 
                                        if(Tok3[1] == '=')      //Literal 
                                        { 
                                                j = SearchLit(Tok3); 
                                                
                                                if(j == -1)     //Literal not present 
                                                { 
                                                        sprintf(temp,"(L, %02d)",LitCnt); 
                                                        strcpy(L[LitCnt++].Lit,Tok3); 
                                                } 
                                                
                                                else 
                                                        sprintf(temp,"(L, %02d)",j); 
                                         }     //end of literal case                                         
                                          
                                          
                                          Tok2[strlen(Tok2) - 1] = '\0'; 
                                          
                                          if(i == 7)    //first token is BC 
                                                j = SearchCON(Tok2); 
                                                
                                          else 
                                                j = SearchReg(Tok2); 
                                                
                                          fprintf(fp2,"(IS, %02d) (%d) %s\n",i,j,temp); 
                                          break; 
                                   } // end of i 1 to 8 
                                   else 
                                   { 
                        	           i = SearchOp(Tok2); 
                        	           if(i!=-1) 
                        	           { 
                        	        		strcpy(s[symcnt].sym,Tok1); 
                      					s[symcnt].Addr=LC; 
                      					symcnt++; 
                                		   if(Tok3[1] == '=')      //Literal 
                                		        { 
                                		                j = SearchLit(Tok3); 
                                		                
                                		                if(j == -1)     //Literal not present 
                                		                { 
                                		                        sprintf(temp,"(L, %02d)",LitCnt); 
                                		                        strcpy(L[LitCnt++].Lit,Tok3); 
                                		                } 
                                		                else 
                                		                        sprintf(temp,"(L, %02d)",j); 
                                	         
							fprintf(fp2,"(IS, %02d) %s\n",i,temp); 
							} 
						else 
						    { 
						    j = SearchReg(Tok2); 
                        		                        
                        		                  fprintf(fp2,"(IS, %02d) %d\n",i,j); 
						} 
                        		           } 
                                   } 
                                   
                                 break;                //end of case 3 
                      

                      case 4 : strcpy(s[symcnt].sym,Tok1); 
                      		s[symcnt].Addr=LC; 
                      		symcnt++; 
                      	 	i = SearchOp(Tok2); 
                    		 
                    		if(i >= 1  &&  i <= 8)			//add-div 
                    			if(Tok4[1] == '=')		//operand is literal 
                    			{ 
                    				j = SearchLit(Tok4); 
                    				if(j == -1) 
                    				{ 
                    					sprintf(temp, "(L, %02d)",LitCnt); 
                    					strcpy(L[LitCnt++].Lit,Tok4); 
                    				} 
                    				 
                    				else 
                    					sprintf(temp,"(L, %02d)",j); 
                    			} 
                    		 
                    		 
                    		Tok3[strlen(Tok3) - 1] = '\0';		//remove 
                    		 
                    		if(i == 7) 				//first oerand is reg or cond 
                    			j = SearchCON(Tok3); 
                    		else 
                    			j = SearchReg(Tok3); 
                    			fprintf(fp2,"(IS, %02d) (%d) %s\n",i,j,temp); 
                    			 
                    		break;				//end case 4 
                    					 

		} //end of switch 
		 
		LC++; 
	}// end of while 
	fcloseall(); 
}//End of PassOne 


void display_Err() 
{ 
	fpErr = fopen("Error.txt", "r"); 
	if( fpErr == NULL) 
	{ 
		printf("\nCannot Open File"); 
		exit(0); 
	} 
	while(fgets(Buffer,80,fpErr)) 
		printf("%s",Buffer); 
	fclose(fpErr); 
} 


void PassTwo() 
{ 
	int i,j,k,p,t; 
	LC = 0; 
	 
	if((fp1 = fopen("IC.txt","r")) == NULL) 
	{ 
		printf("\nCannot open Intermediate Code file"); 
		exit(0); 
	} 
	 
	if((fp2 = fopen("target.txt","w")) == NULL) 
	{ 
		printf("\nCannot open Target Code file"); 
		exit(0); 
	} 
	 
	while(fgets(Buffer,80,fp1)) 
	{ 
		TokCnt = sscanf(Buffer,"%s %s %s %s %s",Tok1,Tok2,Tok3,Tok4,Tok5); 
		Tok1[strlen(Tok1) - 1] = '\0'; 
		Tok2[strlen(Tok2) - 1] = '\0'; 
		Tok3[strlen(Tok3) - 1] = '\0'; 
		Tok4[strlen(Tok4) - 1] = '\0'; 
		Tok5[strlen(Tok5) - 1] = '\0'; 
	 
		switch(TokCnt) 
		{ 
			case 2 : if(strcmp(Tok1+1,"AD")==0) //START 
 				 { 
 				 	p=atoi(Tok2); 
 					for(j=0;j<PoolCnt;j++) 
					 	if(L[POOLTAB[j]].Addr==LC) 
						 	break; 
				 
				 	for(i=POOLTAB[j];i<POOLTAB[j+1];i++) 
 					{ 
 					t=0; 
				 		strcpy(temp,L[i].Lit); 
				 		while(temp[t]!='\0') 
				 			{ 
				 			temp[t]=temp[t+1]; 
				 			t++; 
				 			} 
				 		temp[i]='\0'; 
				 		temp[strlen(temp)-1]='\0'; 
				 		fprintf(fp2,"%d %d 0 %03d\n",LC++,p,atoi(temp)); 
 					} 
 					 
 					LC--; 
 				} 
 	 
		 		else if(strcmp(Tok1+1,"IS")==0) //STOP 
 			 		fprintf(fp2,"%d 00 0 000\n",LC); 
 				 
 				break; 
				 
			case 4 : if(strcmp(Tok1 + 1,"AD") == 0)	//START,ORIGIN 
				 	LC = atoi(Tok4) - 1; 
				 
				 else if(strcmp(Tok1 + 1,"IS") == 0)	//READ,PRINT 
				 	fprintf(fp2,"%d %02d 0 %03d\n",LC,atoi(Tok2),L[atoi(Tok4)].Addr); 
				 
				 break; 
				 
			case 5 : fprintf(fp2,"%d %02d %d %03d\n",LC,atoi(Tok2),atoi(Tok3+1),L[atoi(Tok5)].Addr); 
				 break; 
		}//end of switch 
		LC++; 
	}//end of while 
	fcloseall(); 
}//end of PassTwo 


void display_Littab() 
{ 
        int i; 
        
        printf("\n****Literal Table****"); 
        printf("\nLiteral\t\tAddress\n");         
        for(i = 0; i < LitCnt; i++) 
        { 
                printf("%s\t\t%d\n",L[i].Lit,L[i].Addr);              
        } 
        
        printf("\nSymbol\t\tAddress\n");         
        for(i = 0; i < symcnt; i++) 
        { 
                printf("%s\t\t%d\n",s[i].sym,s[i].Addr);              
        } 
        printf("\n****Pool Table****"); 
        printf("\nPool No.\t\tAddress\n");         
        for(i = 0; i < PoolCnt; i++) 
        { 
                printf("%d\t\t\t%d\n",i+1,POOLTAB[i]);              
        } 

                
} 


int main() 
{ 
	PassOne(); 
	display_Littab(); 
	PassTwo(); 
	 
	return 0; 
} 












/*
output:
sr.txt
START 100 
MOVER AREG, '=1' 
LOOP MOVEM BREG, '=2' 
ADD AREG, '=1' 
LTORG 
MOVER CREG, '=3' 
ADD BREG, '=4' 
ORIGIN LOOP 
LABEL READ '=89' 
LTORG 
ADD BREG, '=4' 
READ '=3' 
END 




intermediate code:
(AD, 00) (C, 100) 
(IS, 04) (0) (L, 00) 
(IS, 05) (1) (L, 01) 
(IS, 01) (0) (L, 00) 
(AD, 04) 
(IS, 04) (2) (L, 02) 
(IS, 01) (1) (L, 03) 
(AD, 02) (C, 102) 
(IS, 09) (L, 04) 
(AD, 04) 
(IS, 01) (1) (L, 05) 
(IS, 09) (L, 06) 
(AD, 01)




target code:
100 04 0 103 
101 05 1 104 
102 01 0 103 
103 4 0 000 
104 4 0 000 
105 04 2 103 
106 01 1 104 
102 09 0 105 
103 4 0 000 
104 4 0 000 
105 01 1 108 
106 09 0 109





Output:
@ubuntu:~/Desktop$ gcc sp2.c
gayatri@ubuntu:~/Desktop$ ./a.out

****Literal Table****
Literal		Address
'=1'		103
'=2'		104
'=3'		103
'=4'		104
'=89'		105
'=4'		108
'=3'		109

Symbol		Address
LOOP		101
LABEL		102

****Pool Table****
Pool No.		Address
1			0
2			2
3			5
gayatri@ubuntu:~/Desktop$ */
