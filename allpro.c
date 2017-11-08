Upper

%{
#include<stdio.h>
#include<ctype.h>
#include<string.h>
char ch;
int choice=0;
FILE *fp,*fp2;
%}

%%

[a-zA-Z|.] {
	if(choice==1)
	{
		ch=toupper(yytext[0]);
		printf("%c",ch);
		fputc(ch,fp2);
	}		
	else if(choice==2)
	{
		ch=tolower(yytext[0]);
		printf("%c",ch);
		fputc(ch,fp2);
	}
	else if(choice==3)
	{
		if(ch==".")
		{
			ch=toupper(yytext[0]);
			printf("%c",ch);
		}
		else
		{
			ch=yytext[0];
			printf("%c",ch);
		}
		fputc(ch,fp2);
	}
	else if(choice==4)
	{
		if(islower(yytext[0]))
		{
			ch=toupper(yytext[0]);
		}
		else if(isupper(yytext[0]))
		{
			ch=tolower(yytext[0]);
		}
		else
		{
			ch=yytext[0];
		}
		printf("%c",ch);
		fputc(ch,fp2);
	}
	else
	{
		ch=yytext[0];
		printf("%c",ch);
		fputc(ch,fp2);	
	}

}
%%
u
void main()
{
	fp2=fopen("op.txt","w");
	printf("Enrter your choine");
	scanf("%d",&choice);
	fp=fopen("ipp.txt","r");
	yyin=fp;
	yylex();
	fclose(fp);
	return;
}
yywrap()
{}


rdp

#include<stdio.h>
#include<string.h>
#include<ctype.h>
 
void E();
void T();
void F();
void Tx();
void Ex();

int error=0;
char input[1000];
int pointer=0;



void E()
{
	printf(" TE' \n");
	printf("T->");
	T();
	printf("E'->");
	Ex();
}

void Ex()
{
	if(input[pointer] == '+')
	{
		printf("+TE' \n");
		pointer++;
		printf("T->");
		T();
		printf("E'->");
		Ex();	
	}
	else
	{
		printf("null \n");
	}
}
void T()
{
	printf(" FT' \n");
	printf("F->");
	F();
	printf("T'->");
	Tx();
}

void Tx()
{
	if(input[pointer] == '*')
	{
		printf("*FT' \n");
		pointer++;
		printf("F->");
		F();
		printf("T'->");
		Tx();
	}
	else
	{
		printf("null \n");
	}
}

void F()
{
	if(isalnum(input[pointer]))
	{
		printf("id \n");
		pointer++;
	}
	else if(input[pointer] == '(')
    	{
    		pointer++;
     		E();
		if(input[pointer] == ')')
             	{
                	pointer++;
                 	printf("(E) \n");
             	}
              	else
                	   error=1;
        }
                          
  	              error=1;
}

int main()
{
	printf("ENETR THE EXPRESSION:\n");
	scanf("%s",input);
	printf("E->");
	E();
	printf("LENGTH OF THE STRING IS :%d\n",(int)strlen(input));
	printf("ERROR Is:%d\n",error);
	if(  pointer == strlen(input) && error !=0)
		printf("String Is Accepted\n");
	else
		printf("String Is REJECTED\n");
	return(0);
}




















Long string

%{
#include<stdio.h>
#include<string.h>
int len=0;
int maxlen=0;
char word[100];
%}

%%
[a-zA-Z0-9]+ {

	printf("%s",yytext);
	len=yyleng;
	if(len>=maxlen)
	{
		maxlen=len;
		strcpy(word,yytext);
	}
}                           
%%
void main()
{
	FILE *fp;
	fp=fopen("abcd.txt","r");
	yyin=fp;
	yylex();
	printf("Logest String is:\t %s \n",word);
	fclose(fp);
	return ;
}
yywrap(){}



















find and replace
%{
#include<stdio.h>
#include<string.h>
FILE *fp,*fp1;
char find[20],replace[20];
%}
%%
[a-zA-Z]+ { 
	if(strcmp(find,yytext)==0)
		  fprintf(fp1,replace);
	else
		  fprintf(fp1,yytext);
       	}
[ ] {fprintf(fp1,yytext);}
%%
int main(int argc,char **argv)
{
	printf("Enter String to be found:");
	scanf("%s",find);
	printf("Enter new String:");
	scanf("%s",replace);
	fp=fopen(argv[1],"r+");
	fp1=fopen("abcd.txt","w");
	yyin=fp;
	yylex();
	fclose(fp);
	fclose(fp1);
	return 0;	
}
yywrap(){}





















parser for simple lauange YACC(llop,for)

yyac
%{
#include<stdio.h>
#include<stdlib.h>
int flag=0;
%}
%token FOR OPBR IF SWITCH COBR SEMIC EQUAL RELOP INCR DICR SPAC ADD SUB ID NUM
%%
S: S1
|S2
|S3 ;
S1: FOR OPBR E1 SEMIC E2 SEMIC E3 COBR
{
	printf("Accept for IF");
	flag=1;
	exit(0);
}
S2: SWITCH OPBR ID COBR
{
	printf("Accept switch");
	flag=1;
	exit(0);
}
S3: IF OPBR E2 COBR
{
	printf("Accept  if");
	flag=1;
	exit(0);
} 
E1: ID EQUAL ID 
	| ID EQUAL NUM 
 	| SPAC
;
E2: ID RELOP ID 
	|ID RELOP NUM
	| SPAC
;
E3: ID INCR
	| ID DICR
	| DICR
	| ID EQUAL ID ADD ID
	| ID EQUAL ID ADD NUM
	| ID EQUAL ID SUB ID
	| ID EQUAL ID SUB NUM
	| ID ADD EQUAL NUM
	| ID SUB EQUAL NUM	
	| ID ADD EQUAL ID
	| ID SUB EQUAL ID
	| SPAC
;
%%

main()
{
	yyparse();
	
}
yyerror(const char *msg)
{
	if(flag==0)
		printf("Not accepted");
		exit(0);
}


lex

%{
#include"y.tab.h"
extern int yylval;
%}
%%
for {return (FOR);}
if {return (IF);}
switch {return (SWITCH);}
"(" {return (OPBR);}
")" {return (COBR);}
";" {return (SEMIC);}
"=" {return (EQUAL);}
"<"|">" {return (RELOP);}
"++" {return (INCR);}
"--" {return (DICR);}
" " {return (SPAC);}
"+" {return (ADD);}
"-" {return (SUB);}
[a-zA-Z]+ {yylval=yytext[0]; return(ID);}
[0-9]+ {yylval=atoi(yytext); return(NUM);}
%%

yywrap()
{
return 1;
}








no of lines
%{
#include<stdio.h>
int cw=0,cc=0,cl=0,cv=0,cd=0;
%}
%%
a|e|i|o|u|A|E|I|O|U {cv++,cc++;}
[a-zA-Z] {cc++;}
[ ] {cw++;}
\n {cl++;}
[0-9] {cd++;}
.
%%
int main(int argc,char **argv)
{
	FILE *fp=fopen(argv[1],"r+");
	yyin=fp;
	yylex();
	printf("\n No of words:%d\n",(cw+cl));
	printf("\n No of Charrecter:%d\n",cc);
	printf("\n No of lines:%d\n",cl);
	printf("\n No of vowels:%d\n",cv);
	fclose(fp);
	return 0;
}
yywrap(){}


























subset of C


%{
#include<stdio.h>
%}
%%
#include|define {printf("\n%s is pre processor",yytext);}
"<"*.">"  {printf("\n%s is header file",yytext);}
printf|scanf  {printf("\n%s is a in built function",yytext);}
"{"  {printf("\n%s is open cruly bracket",yytext);}
int|main|void|char  {printf("\n%s is  a keywords",yytext);}
int|char|float|long|double  {printf("\n%s is  a datatypes",yytext);}
 "+"|"*"|"|"|"/" {printf("\n%s is a operator",yytext);}
";"|","|"("|")"  {printf("\n%s is  a delemeters",yytext);}
"}"  {printf("\n%s isan closing curly bracket",yytext);}
[0-9]  {printf("\n%s is an numbers",yytext);}
[a-zA-Z]+"["[a-zA-Z0-9]"]"  {printf("\n%s is an array",yytext);}






%%
int main(int argc,char **argv)
{
FILE *fp;
fp=fopen("abc1.txt","r");
yyin=fp;
yylex();
fclose(fp);
return 0;
}
int yywrap()
{
return 0;
}














Binary

#include<stdio.h>
#include<cstdlib>
#include<ctime>
void merge(int *arr,int low,int high,int mid);
void mergesort(int *arr,int low,int high);
int binarysearch(int *arr,int low,int high);
int n,search;
int binarysearch(int *arr,int low,int high)
{
	int mid=(low+high)/2;
	if(search==arr[mid])
	{
		return mid;
	}
	else if(arr[mid]<search)
	{
		binarysearch(arr,mid+1,high);
	}
	else if(arr[mid]>search)
	{
		binarysearch(arr,low,mid);
	}
	else
	{
     		printf("Wrong number");
	}
}
void mergesort(int *arr,int low,int high)
{
	int mid;
	if(low<high)
	{
		mid=(low+high)/2;
		mergesort(arr,low,mid);
		mergesort(arr,mid+1,high);
		merge(arr,low,high,mid);
	}
	return;
}
void merge(int *arr,int low,int high,int mid)
{
	int i,j,k,c[n];
	i=low;
	k=low;
	j=mid+1;
	while(i<=mid && j<=high)
	{
		if(arr[i]<arr[j])
		{
			c[k]=arr[i];
			k++;	
			i++;
		}
		else
		{
			c[k]=arr[j];
			k++;
			j++;	
		}
	}
	while(i<=mid)
	{
		c[k]=arr[i];
		k++;
		i++;
	}
	while(j<=high)
	{
		c[k]=arr[j];
		k++;
		j++;
	}
	for(i=low;i<k;i++)
	{
		arr[i]=c[i];
	}
}
int main()
{
	printf("\n Enter n number:");
	scanf("%d",&n);
	int a[n];
	for(int i=0;i<n;i++)
	{
		a[i] = (rand() % n) + 1;
		printf("\n%d",a[i]);
	}
	mergesort(a, 0, n-1);
	printf("\n Sorted array is:");
	for(int i=0;i<n;i++)
	{
		printf("\n%d",a[i]);
	}
	printf("\n Enter no. to be searched:");
	scanf("%d",&search);
	int loc=binarysearch(a,0,n-1);
	printf("It found at location:%d\n",loc);
	return 0;
}



Quick

#include<stdio.h>
#include<cstdlib>
#include<omp.h>
int partiton(int *arr,int low,int high)
{
	int pi=arr[high],i=low-1,j,temp;
	for(j=low;j<high;j++)
	{
		if(arr[j]<pi)
		{
			i++;
			temp=arr[i];
			arr[i]=arr[j];
			arr[j]=temp;
		}
	}
	i++;
	temp=arr[i];
	arr[i]=arr[j];
	arr[j]=temp;
	return i;
}
void quicksort(int *arr,int low,int high)
{
	int pi;
	if(low<high)
	{
		pi=partiton(arr,low,high);
		#pragma omp parallel section
		{
			#pragma omp section
				quicksort(arr,low,pi-1);
			#pragma omp section
				quicksort(arr,pi+1,high);  
		}
	}
}

int main()
{
	int no,n;
	printf("Enter the no of elements");
	scanf("%d",&n);
	int arr[n];
	if(n<10)
	{
		printf("Enter the elemts:");
		for(int i=0;i<n;i++)
		{
			scanf("%d",&arr[i]);
		}
	}
	else 
	{
		for(int i=0;i<n;i++)
		{
			arr[i]=rand() % (n*4);
		}
		printf("Following elemets:\n");
		for(int i=0;i<n;i++)	
		{
			printf("%d\n",arr[i]);
		}
	}
	int low=0,high=n-1;
	quicksort(arr,low,high);
	printf("Sorted arrays :\n");
	for(int i=0;i<n;i++)
	{
		printf("%d\n",arr[i]);
	}
	return 0;
}





























calsi

lex
%{
#include"y.tab.h"
#include<string.h>
#include<math.h>
%}
%%
[0-9]+|[0-9]*\.[0-9]+ {yylval.p= atof(yytext); return num;}
sin {strcpy(yylval.d,yytext); return SIN;}
cos {strcpy(yylval.d,yytext); return COS;}
tan {strcpy(yylval.d,yytext); return TAN;}
log {strcpy(yylval.d,yytext); return LOG;}
sqrt {strcpy(yylval.d,yytext); return SQRT;}
[\t];
\n return 0;
.  return yytext[0];
%%

yacc
%{
#include<stdio.h>
#include<math.h>
%}
%union
{
float p;
char d[10];
}
%token <p>num
%token <d>SIN COS TAN LOG SQRT
%type <p>exp
%left '+''-'
%left '*''/'
%nonassoc uminus
%%

ss:exp {printf("=%g\n",$1);}
 exp: exp'+'exp {$$=$1+$3;}
|exp'-'exp {$$=$1-$3;}
|exp'*'exp {$$=$1*$3;}
|exp'/'exp {
		if($3==0)
		{
			printf("Divide By Zero");
			exit(0);
		}
		else $$=$1/$3;
	}
|'-'exp  {$$=-$2;}
|'('exp')' {$$=$2;}
|SIN'('exp')' {$$=sin($3);}
|COS'('exp')' {$$=cos($3);}
|TAN'('exp')' {$$=tan($3);}
|LOG'('exp')' {$$=log($3);}
|SQRT'('exp')' {$$=sqrt($3);}
|num;
%%
main()
{
	do
	{
		printf("Enter expression:\n");
		yyparse();
	}while(1);
}
yyerror()
{}






None

%{
#include<stdio.h>
%}
%%
shubham|ravi|prashant {printf("\n %s is noun",yytext);}
my|i|she|mine|am {printf("\n %s is pronoun",yytext);}
is {printf("\n %s is verb",yytext);}
beautiful {printf("\n %s is adjective",yytext);}
a|an|the {printf("\n %s is artical",yytext);}
[]
[a-z]+ {printf("\n %s is a plain text",yytext);}
%%
void main()
{
	yylex();
}
yywrap(){}













0-1 knapsack
 #include <queue>
#include <iostream>
using namespace std;

struct node
{
	int level;
	int profit;
	int weight;
	int bound;
};

int bound(node u, int n, int W, vector<int>pVa, vector<int>wVa)
{
	int j = 0, k = 0;
	int totweight = 0;
	int result = 0;

	if (u.weight> W)
		{
			return 0;
		}
	else
		{
			result = u.profit;
		  	j = u.level + 1;
			totweight = u.weight;

	while ((j < n) && (totweight + wVa[j] < W))
		    {
				totweight = totweight + wVa[j];
				result = result + pVa[j];
				j++;
		    }

	k = j;

	if (k < n)
		    {
				result = result + (W - totweight) * pVa[k]/wVa[k];
		    }
		     cout<<"\nLevel:"<<u.level<<"\t";
		     cout<<"Profit:"<<u.profit<<"\t";
		      cout<<"Weight:"<<u.weight<<"\t";
		       cout<<"Upper Bound:"<<result<<endl<<endl;
	return result;
		}
}

int knapsack(int n, int p[], int w[], int W)
{
	queue<node> Q;
	node u, v;
	vector<int>pV;
	vector<int>wV;
	Q.empty();

	for (int i = 0; i < n; i++)
		{
	pV.push_back(p[i]);
	wV.push_back(w[i]);
		}

	v.level = -1;
	v.profit = 0;
	v.weight = 0;

	int maxProfit = 0,maxWeight=0,maxBound=0,maxLevel=0;

		//v.bound = bound(v, n, W, pV, wV);
	Q.push(v);

	while (!Q.empty())
		{
		    v = Q.front();
	Q.pop();

	if (v.level == -1)
		    {
	u.level = 0;
		    }
	else if (v.level != (n - 1))
		    {
	u.level = v.level + 1;
		    }

	u.weight = v.weight + w[u.level];
	u.profit = v.profit + p[u.level];

	u.bound = bound(u, n, W, pV, wV);

	if(u.weight<= W &&u.profit>maxProfit)
		    {
	maxProfit = u.profit;
	maxWeight = u.weight;
	maxBound = u.bound;
	maxLevel = u.level;
		    }

	if(u.bound>maxProfit)
	   {
	Q.push(u);
		    }

	u.weight = v.weight;
	u.profit = v.profit;

	u.bound = bound(u, n, W, pV, wV);

	if(u.bound>maxProfit)
		    {
	Q.push(u);
		    }
	    
		}
	cout<<"Max Profit found as "<<maxProfit<<" at level "<<maxLevel<<" with Weight "<<maxWeight<<" and upper bound as "<<maxBound<<endl ;	
	
	
	return maxProfit;
}

int main()
{
	int n ;
	int W,p[10],w[10];
	cout<<"Enter no. of objects\n";
	cin>>n;
	cout<<"Enter weights and profits of objects\n";
	for(int i=0;i<n;i++)
		{
		        cout<<"Object "<<i+1<<"\n Weight : ";
		        cin>>w[i];
		        cout<<" Profit : ";
		        cin>>p[i];
		}
	cout<<"\nEnter knapsack capacity\n";
	cin>>W;

	//cout<<"\nMaximum profit : ";
	knapsack(n, p, w, W);

	return 0;
}









K-mean

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <iomanip>  
using namespace std;
int main()
{
	int k;
	cout<<"Enter the no. of clusters : ";
	cin>>k;
	float dim[k][4],dim1[k][4];								//Dimension of Cluster Centroid 
	for(int i=0;i<k;i++)
	{
		dim[i][0]=i+4;
		dim[i][1]=i+3;
		dim[i][2]=i+2;
		dim[i][3]=i;
		cout<<dim[i][0]<<" "<<dim[i][1]<<" "<<dim[i][2]<<" "<<dim[i][3]<<"\n";
	}

	float x[4],dist[4],f[k],ARRAY[150][4];
	int flag[150];
	FILE *fp;
	char str[255];
        fp = fopen("IRIS.csv", "r");
        int c=0;
        while(fgets(str, 255, (FILE*)fp))
		{
			const char s[10] = {','};
		    char *token;
		    int cnt=0;
		    token = strtok(str, s);
		    while(cnt<4&&token != NULL ) 
		    {
				ARRAY[c][cnt]=strtof (token,NULL);
				//cout<<ARRAY[c][cnt]<<" "<<c<<endl;
				token = strtok(NULL, s);
				cnt++;
		    }
			c++;
		}
	int same=0;
	int itr=0;
	while(same==0)	
	{//repeat starts
		itr++;
		int c=0;
		while(c<150)
		{
			   for(int i=0;i<k;i++)
			   {
				dist[0]= ARRAY[c][0]-dim[i][0];
				dist[1]= ARRAY[c][1]-dim[i][1];
				dist[2]= ARRAY[c][2]-dim[i][2];
				dist[3]= ARRAY[c][3]-dim[i][3];
				//cout<<dist[0]<<" "<<dist[1]<<" "<<dist[2]<<" "<<dist[3]<<"\n";
				dist[0]=dist[0]*dist[0];
				dist[1]=dist[1]*dist[1];
				dist[2]=dist[2]*dist[2];
				dist[3]=dist[3]*dist[3];
				float d=dist[0]+dist[1]+dist[2]+dist[3];
				d=sqrt(d);
				f[i]=d;
				//cout<<d<<endl;
 }
			   int min=9999,m;
			   for(int i=0;i<k;i++)
			   {
			      if(f[i]<min)
			      {
				min=f[i];
				m=i;
			      }
			   }
			   flag[c]=m;
			   c++;
		}
		cout<<"\nIteration No. :"<<itr<<endl;
		for(int i=0;i<150;i++)
		{
			cout<<flag[i]<<"\t";
		}
		cout<<"\n";
		int cntr=0;
		float sum[4]={0,0,0,0};
		for(int j=0;j<k;j++) 						
		{
			cntr=0;
			sum[0]=0.0;sum[1]=0.0;sum[2]=0.0;sum[3]=0.0;
			for(int i=0;i<150;i++)
			{
				if(flag[i]==j)
				{
					sum[0]=sum[0]+ ARRAY[i][0];
					sum[1]=sum[1]+ ARRAY[i][1];
					sum[2]=sum[2]+ ARRAY[i][2];
					sum[3]=sum[3]+ ARRAY[i][3];
					cntr++;
				}
		
			}
			dim1[j][0]=sum[0]/cntr;
			dim1[j][1]=sum[1]/cntr;
			dim1[j][2]=sum[2]/cntr;
			dim1[j][3]=sum[3]/cntr;
		}
		//same=1 if dim==dim1
		for(int i=0;i<k;i++)
		{
			//cout<<dim[i][0]<<" "<<dim[i][1]<<" "<<dim[i][2]<<" "<<dim[i][3]<<"\n"<<dim1[i][0]<<" "<<dim1[i][1]<<" "<<dim1[i][2]<<" "<<dim1[i][3]<<" ";
			if(dim[i][0]==dim1[i][0]&&dim[i][1]==dim1[i][1] && dim[i][2]==dim1[i][2] && dim[i][3]==dim1[i][3])
			{
				same=1;
			}
		}
		if(same!=1)
		{
			for(int i=0;i<k;i++)
			{
				dim[i][0]=dim1[i][0];
				dim[i][1]=dim1[i][1];
				dim[i][2]=dim1[i][2];
				dim[i][3]=dim1[i][3];
			}
		}	

	}//repeat ends
	for(int h=0;h<k;h++)
	{
		cout<<"\nCLUSTER : "<<h<<endl;
		for(int i=0;i<150;i++)
		{
			if(flag[i]==h)
			{
				for(int j=0;j<4;j++)
				{
					cout<<ARRAY[i][j]<<"\t";
				}
				cout<<endl;
			}
		}
	}
	return 0;
}




subset program C

%{
	#include<stdio.h>
	FILE *fp;


%}

letter [a-zA-Z]+
digit [0-9]
under [-]
%%
void |
incude |
main |
if |
for |
break |
while {					
		printf("\n\n%s is a keyword\n",yytext);
}
"+" |
"-" |
"*" |
"/" {
	printf("\n\n%s is a binary operator\n",yytext);
}
"{" 
	 
	
{
	printf("\n\n%s is a Staring of a block\n",yytext);
}
"}" {
	printf("\n\n%s is a End of a block\n",yytext);
}

printf |
scanf {
	printf("\n\n%s is a built in function\n",yytext);
}

char |
int |
float |
double {
	printf("\n\n%s is a Data type\n",yytext);
}
{letter}"["{digit}*"]" {
	printf("\n\n%s is an array\n",yytext);
}
";" {
	printf("\n\n%s is a delimiter\n",yytext);
}

{digit}+ {printf("\n\n%s is a Integer Constant \n",yytext);}
{letter}({letter}|{digit}|{under})* {printf("\n\n%s is a 	identifier\n",yytext);}


#include<{letter}*.h> |
#define {
	printf("\n\n%s is a Header\n",yytext);
}

{digit}({letter}|{digit}|{under})* {printf("\n\n%s wrong 	declaration of variable\n",yytext);}
. { }
%%					
int main(int argc,char **argv)
{
	fp=fopen("test.c","rw+");
	yyin=fp;
	yylex();
	return 1;
}
yywrap()
{}



























KNN

//program to implement knn classification
#include<iostream>
#include<cmath>
#include<string.h>
#include<fstream>
#include<stdlib.h>

using namespace std;

struct node 
{
    float s_length;
    float s_width;
    float p_length;
    float p_width;
    string species;
}a[150],test;

struct ranking
{
float distance;
string label;
}t[150];


void rank()
{
    for(int i=0;i<150;i++)
    {
        for(int j=i+1;j<150;j++)
        {
            if(t[j].distance < t[i].distance)
            {
                float temp=t[j].distance;
                string tl=t[j].label;
                t[j].distance=t[i].distance;
                t[j].label=t[i].label;
                t[i].distance=temp;
                t[i].label=tl;
            }
        }
    }
}
void calculate_dist()
{
    float dist;
    for(int i=0;i<150;i++)
    {
        dist=pow((test.s_length-a[i].s_length),2)+pow((test.s_width-a[i].s_width),2)+pow((test.p_length-a[i].p_length),2)+pow((test.p_width-a[i].p_width),2);
        t[i].distance = sqrt(dist);
        t[i].label=a[i].species;
    }
}


void classify(int k)
{
    int count_setosa=0;
    int count_versicolor=0;
    int count_virginica=0;
    string s1("Iris-setosa");
    string s2("Iris-versicolor");
    string s3("Iris-virginica");

    int j;
    for(int i=0;i<k;i++)
    {
        if(s1.compare(t[i].label)==-1)
        {
        	count_setosa++; 
        }
        else if(s2.compare(t[i].label)==-1)
        {
        	count_versicolor++;
        }
        else if(s3.compare(t[i].label)==-1)
        {
            count_virginica++;
        }
        else
        {cout<<"invalid label\n";}
  
    }
   
    cout<<"\n-------------------FINAL VOTES-------------------------\n";
    cout<<"setosa:"<<count_setosa<<endl;
    cout<<"versicolor:"<<count_versicolor<<endl;
    cout<<"virginica:"<<count_virginica<<endl;  
    
    if(count_setosa>count_versicolor && count_setosa > count_virginica)
        cout<<"species predicted is: \t setosa"<<endl;
    else if(count_setosa < count_versicolor && count_versicolor > count_virginica)
        cout<<"species predicted is: \t versicolor"<<endl;
    else if(count_virginica > count_versicolor && count_setosa < count_virginica)
        cout<<"species predicted is: \t virginica"<<endl;
    else
        cout<<"cannot predict";

}

int main()
{
    string line;
    
    ifstream infile;
    infile.open("IRIS.csv");

    //load dataset into structure
    if (infile.is_open())
    {
        for(int i=0;i<150;i++)
		{	 
            getline (infile,line,',');
            a[i].s_length=atof(line.c_str());
            
            getline (infile,line,',');
            a[i].s_width=atof(line.c_str());
            
            getline (infile,line,',');
            a[i].p_length=atof(line.c_str());
            
            getline (infile,line,',');
            a[i].p_width=atof(line.c_str());
            
            getline (infile,line);
            a[i].species=line;
		}
        infile.close();
    }
  
    //ask for test data
    
    cout<<"enter sepal length:\t";
    cin>>test.s_length;
    cout<<"enter sepal width:\t";
    cin>>test.s_width;
    cout<<"enter petal length:\t";
    cin>>test.p_length;
    cout<<"enter petal width:\t";
    cin>>test.p_width;
    
    //calculate distance;
    calculate_dist();
    rank();
    int k;
    cout<<"enter nearest neighbours (k value)";
    cin>>k;
    classify(k);
    
    return 0;
}



















