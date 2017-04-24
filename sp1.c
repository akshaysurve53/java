
#include<stdio.h> 
#include<string.h> 

FILE *sp,*ip,*tp; 
char POT[][7]={"START","END","LTORG","EQU","ORIGIN","DC","DS"}; 
char MOT[][6]={"MOVER","MOVEM","ADD","SUB","MUL","DIV"}; 
char reg[][5]={"AREG","BREG","CREG","DREG"}; 
int err=0; 
int counts=0; 

typedef struct symbol 
{ 
 int symbol_no; 
 char symbol_name[10]; 
 int symbol_addr; 
}symbol; 

symbol s[10]; 

int search_in_POT(char tok1[10]) 
{ 
   int i,e; 
   for(i=0;i<5;i++) 
   { 
      e=strcmp(tok1,POT[i]); 
      if(e==0) 
	 return(i+1); 
   } 
return -1; 
} 

int search_in_MOT(char tok1[10]) 
{ 
   int i,e; 
   for(i=0;i<6;i++) 
   { 
      e=strcmp(tok1,MOT[i]); 
      if(e==0) 
	 return(i+1); 
   } 
return -1; 
} 
 
int search_in_reg(char tok1[10]) 
{ 
   int i,e; 
   for(i=0;i<4;i++) 
   { 
      e=strcmp(tok1,reg[i]); 
      if(e==0) 
	 return(i+1); 
   } 
return -1; 
} 

int search_in_symbol_tab(char tok1[10],int counts) 
{ 
   int i,e; 
   for(i=0;i<=counts;i++) 
   { 
      e=strcmp(tok1,s[i].symbol_name); 
      if(e==0) 
	 return(i); 
   } 
return -1; 
} 

void display_intermediate() 
{ 
int n; 
char buffer[80],tok1[10], tok2[10],tok3[10], tok4[10],tok5[10],tok6[10]; 
ip=fopen("inter.txt","r"); 
printf("\n Intermediate File\n"); 
while(fgets(buffer,80,ip)) 
{ 
   n=sscanf(buffer,"%s%s%s%s%s%s",tok1,tok2,tok3,tok4,tok5,tok6); 
   if(n==2) 
     printf(" %s  %s\n",tok1,tok2); 
   if(n==4) 
     printf(" %s  %s  %s  %s\n",tok1,tok2,tok3,tok4); 
   if(n==5) 
     printf(" %s  %s  %s  %s  %s\n",tok1,tok2,tok3,tok4,tok5); 
   if(n==6) 
     printf("%s  %s  %s  %s  %s  %s\n",tok1,tok2,tok3,tok4,tok5,tok6); 
} 
fclose(ip); 
} 
 
void pass1() 
{ 
  int lc=0,ch,i=0,j,p,n,m,m1,m2,m3,m4,countl=0,k1,d,d1; 
  char buffer[80],tok1[10], tok2[10],tok3[10], tok4[10],tok5[10]; 
  sp=fopen("source.txt","r"); 
  ip=fopen("inter.txt","w"); 
  while(fgets(buffer,80,sp)) 
  { 
   n=sscanf(buffer,"%s%s%s%s",tok1,tok2,tok3,tok4); 
   switch(n) 
   { 
      case 1: // START 
	  m=search_in_POT(tok1); 
	  
	    if(m==1) 
	    { 
	       lc=0; 
	       fprintf(ip,"%d (AD, 0%d) - (C, %d)\n",lc,m,lc); 
	    } 
	    else 
	    {//ORIGIN 
	    	if(m==4) 
	    	{ 
	    		lc=0; 
	    	} 
	    	else 
	    	{//END 
	    	fprintf(ip,"%d (AD, 0%d)   \n",lc,m); 
	    	} 
	    } 
	    break; 
      case 2: 
	    m=search_in_POT(tok1); 
	    //START 100 
	     if(m==1) 
	     { 
	       lc=atoi(tok2); 
	       fprintf(ip,"(AD, 0%d) (C, %d)\n",m,lc); 
	     } 
	     else 
	     { //ORIGIN 200 
		d=atoi(tok2); 
		if(isdigit(d)) 
		{ 
			lc=d; 
	     } 
	     else 
	     { 
	     	m4=search_in_symbol_tab(tok2,counts); 
			lc=s[m4].symbol_addr; 
	     } 
	     } 
	     if(m==-1) 
	     { 
	       fprintf(ip,"Assembly Directive not Present"); 
	       err++; 
	     } 
	     break; 
       case 3: 
		m1=search_in_MOT(tok1); 
		m2=search_in_reg(tok2); 
		m3=search_in_POT(tok2); 
		if(m1>=1) 
		{ // MOVER AREG A OR ADD BREG B 
		   
		      int m11=search_in_symbol_tab(tok3,counts); 
		      if(m11==-1) 
		      { 
			 s[counts].symbol_no=counts+1; 
			 strcpy(s[counts].symbol_name,tok3); 
		      } 
			 fprintf(ip,"%d (IS, 0%d) %d (S, %d)\n",lc,m1,m2,s[counts].symbol_no); 
			 counts++; 
		    
		  } 
		   else 
		    {  // A DC 6 
			// A DS 5 
		      if(strcmp(tok2,"DC")==0) 
		      { 
			m4=search_in_symbol_tab(tok1,counts); 
			s[m4].symbol_addr=lc; 
			//k1=atoi(tok3); 
			fprintf(ip,"%d (AD, 06) - (C, %s)\n",lc,tok3); 
		      } 
		      else if(strcmp(tok2,"DS")==0) 
		      { 
			m4=search_in_symbol_tab(tok1,counts); 
			s[m4].symbol_addr=lc; 
			k1=atoi(tok3); 
			 
			fprintf(ip,"%d (AD, 07) - (C, %d)\n",lc,k1); 
			lc=lc+atoi(tok3)-1; 
		      } 
		    } 
		    if(m3==4) 
		    {  // LOOP1 EQU LOOP 
		       m4=search_in_symbol_tab(tok3,counts); 
		       s[counts].symbol_no=counts+1; 
		       strcpy(s[counts].symbol_name,tok1); 
		       s[counts].symbol_addr=s[m4].symbol_addr; 
		       counts++; 
		       lc--; 
		     } 
		 
			lc++; 
			break; 
       case 4: // LOOP MOVER AREG B 
	     s[counts].symbol_no=counts+1; 
	     strcpy(s[counts].symbol_name,tok1); 
	     s[counts].symbol_addr=lc; 
	     counts++; 
	     m1=search_in_MOT(tok2); 
	     m2=search_in_reg(tok3); 
	     if(m1>=01) 
	     { 
		   int m11=search_in_symbol_tab(tok4,counts); 
		   if(m11==-1) 
		   { 
		      s[counts].symbol_no=counts+1; 
		      strcpy(s[counts].symbol_name,tok4); 
		      fprintf(ip,"%d (IS, 0%d) %d (S, %d)\n",lc,m1,m2,s[counts].symbol_no); 
		      counts++; 
		   } 
		   else 
		   { 
		   	 
		  	 fprintf(ip,"%d (IS, 0%d) %d (S, %d)\n",lc,m1,m2,s[counts].symbol_no); 
		   } 
		   
		 
	     } 
	     else 
	     { // LOOP A DC 6 OR 
		//LOOP A DS 5 
		if(strcmp(tok3,"DC")==0) 
		{ 
		    m4=search_in_symbol_tab(tok2,counts); 
		    s[m4].symbol_addr=lc; 
		    k1=atoi(tok4); 
		    fprintf(ip,"%d (AD, 06) - (C, %d)\n",lc,k1); 
		} 
		else 
		if(strcmp(tok3,"DS")==0) 
		{ 
		    m4=search_in_symbol_tab(tok2,counts); 
		    s[m4].symbol_addr=lc; 
		    k1=atoi(tok4); 
		    fprintf(ip,"%d (AD, 07) - (C, %d)\n",lc,k1); 
		 } 
	      } 
	      lc++; 
	      break; 
	} 
    } 
    fclose(ip); 
      
    printf("\n -----Symbol Table------\n"); 
    printf("s_no\ts_name\ts_addr\n"); 
    printf("-----------------------------\n"); 
    for(p=0;p<counts;p++) 
    { 
     printf("\n%d\t%s\t%d\t\n",s[p].symbol_no,s[p].symbol_name,s[p].symbol_addr); 
    }    
 } 


int remove_bracket(char tok5[10]) 
{ 
	int tok; 
	tok=strlen(tok5); 
	tok5[tok--]='\0'; 
	return (atoi(tok5)); 
} 


void pass2() 
{ 
int n,ntok3,ntok4,ntok5,ntok6,i,addr; 
char buffer[80],tok1[10], tok2[10],tok3[10], tok4[10],tok5[10],tok6[10]; 


ip=fopen("inter.txt","r"); 
tp=fopen("target.txt","w"); 
while(fgets(buffer,80,ip)) 
{ 

n=sscanf(buffer,"%s%s%s%s%s%s",tok1,tok2,tok3,tok4,tok5,tok6); 
if(n==5) 
{ 
	ntok3=remove_bracket(tok3); 
	ntok4=remove_bracket(tok5); 
	fprintf(tp,"%s 0%d  %d\n",tok1, ntok3, ntok4); 
} 
else if(n==6) 
{	 
	ntok3=remove_bracket(tok3); 
	if(tok5[1]=='S') 
	{ 
		ntok6=remove_bracket(tok6); 
		for(i=0;i<counts;i++) 
		{ 
			if(s[i].symbol_no==ntok6) 
			{ 
				addr=s[i].symbol_addr; 
			} 
		} 
		fprintf(tp,"%s 0%d %s %d\n",tok1, ntok3, tok4, addr); 
	} 
	else 
	{ 
		ntok6=remove_bracket(tok6); 
		if(ntok6==6) 
		fprintf(tp,"%s 0%d %s 0%d\n",tok1, ntok3, tok4, ntok6); 
		else 
		fprintf(tp,"%s 0%d %s 00\n",tok1, ntok3, tok4); 
		 
		 
	} 
	 
} 
} 
fclose(ip); 
fclose(tp); 
} 

void display_target() 
{ 
int n; 
char buffer[80],tok1[10], tok2[10],tok3[10], tok4[10],tok5[10],tok6[10]; 
tp=fopen("target.txt","r"); 
printf("\n Target File\n"); 
while(fgets(buffer,80,tp)) 
{ 
   n=sscanf(buffer,"%s%s%s%s%s%s",tok1,tok2,tok3,tok4,tok5,tok6); 
   if(n==2) 
     printf(" %s  %s\n",tok1,tok2); 
   if(n==4) 
     printf(" %s  %s  %s  %s\n",tok1,tok2,tok3,tok4); 
   if(n==5) 
     printf(" %s  %s  %s  %s  %s\n",tok1,tok2,tok3,tok4,tok5); 
   if(n==6) 
     printf("%s  %s  %s  %s  %s  %s\n",tok1,tok2,tok3,tok4,tok5,tok6); 
} 
fclose(tp); 
} 

  void main() 
  { 
     pass1(); 
     display_intermediate(); 
     pass2(); 
     display_target(); 
 
   } 











/* 
OUTPUT:- u:~$ cd Desktop/
gayatri@ubuntu:~/Desktop$ gcc sp1.c
gayatri@ubuntu:~/Desktop$ ./a.out

 -----Symbol Table------
s_no	s_name	s_addr
-----------------------------

1	'=1'	0	

2	LOOP	101	

3	'=2'	0	

0		0	

5	'=3'	0	

6	'=4'	0	

0		0	

 Intermediate File
 (AD,  01)  (C,  100)
100  (IS,  01)  -1  (S,  1)
101  (IS,  02)  -1  (S,  3)
102  (IS,  03)  -1  (S,  0)
103  (IS,  01)  -1  (S,  5)
104  (IS,  03)  -1  (S,  6)
102  (IS,  03)  -1  (S,  0)
Assembly  Directive  not  Present0  (AD,  02)

 Target File
 100  01  -1  0
 101  02  -1  0
 102  03  -1  0
 103  01  -1  0
 104  03  -1  0
 102  03  -1  0
 Assembly  00  Present0  00
gayatri@ubuntu:~/Desktop$ 

*/ 
