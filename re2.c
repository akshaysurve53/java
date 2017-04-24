 
#include<stdio.h> 
#include <stdlib.h>
#include<string.h> 


typedef struct tree 
{ 
   char ch; 
   int pos; 
   int nullable; 
   int fpos[5]; 
   int lpos[5]; 
   struct tree * lc; 
   struct tree * rc; 
}node; 

typedef struct foll 
{ 
   int follpos[10]; 
   char ch; 
}follpos; 

follpos folltab[100]; 
char inpt[10]; 
int dfaa[30],df=0,state[10][10];; 

node* alloc(char ch) 
{ 
    node * temp; 
    temp=(node *)malloc(sizeof(node)); 
    temp->nullable=1; 
    temp->lc=NULL; 
    temp->rc=NULL; 
    temp->ch=ch; 
    temp->fpos[0]=-1; 
    temp->lpos[0]=-1; 
    return temp; 
} 

void print_follow(int n) 
{ 
    int i; 
    printf("FOLLOWPOS\n"); 
    printf("POS\tNAME\tFOLLOWPOS\n"); 
    for(i=1;i<=n;++i) 
    { 
        printf("%d\t%c\t",i,folltab[i].ch); 
        int j=0; 
        while(folltab[i].follpos[j]!=-1) 
        { 
            printf("%d ",folltab[i].follpos[j]); 
            j++; 
        } 
        printf("\n"); 
    } 
} 
void print_nullable(node *root) 
{ 
    if(root!=NULL) 
    { 
        print_nullable(root->lc); 
        print_nullable(root->rc); 
        printf("%c\t",root->ch); 
        int i=0; 
        while(root->fpos[i]!=-1) 
        { 
            printf("%d ",root->fpos[i]); 
            i++; 
        } 
        printf("\t"); 
        i=0; 
        while(root->lpos[i]!=-1) 
        { 
            printf("%d ",root->lpos[i]); 
            i++; 
        } 
        printf("\n"); 
    } 
} 
node * create(char str[],int *l) 
{ 
    node * nw; 
    nw=alloc(str[*l]); 
    if(str[*l]=='*'||str[*l]=='|'||str[*l]=='.') 
    { 
        if(str[*l]!='*') 
        { 
            (*l)--; 
            nw->nullable=0; 
            nw->rc=create(str,l); 
        } 
        (*l)--; 
        nw->lc=create(str,l); 
    } 
    else 
        nw->nullable=0; 
    return nw; 
} 
void inorder(node *root) 
{ 
    if(root!=NULL) 
    { 
        inorder(root->lc); 
        printf("%c",root->ch); 
        inorder(root->rc); 
    } 
} 
void create_nullable(node *root,int *pos) 
{ 
    if(root->lc!=NULL) 
    { 
        create_nullable(root->lc,pos); 
        //printf("\t%c ",root->lc->ch); 
    } 

    if(root->rc!=NULL){ 
        create_nullable(root->rc,pos); 
        //printf("\t%c ",root->lc->ch); 
    } 
    if(root->lc==NULL && root->rc==NULL) 
    { 
        root->pos=(*pos); 
        root->fpos[0]=root->lpos[0]=(*pos); 
        root->fpos[1]=root->lpos[1]=-1; 
        folltab[*pos].ch=root->ch; 
        folltab[*pos].follpos[0]=-1; 
        (*pos)++; 
    } 
    else 
    { 
        if(root->ch=='|') 
        { 
                if(root->lc->nullable==1 || root->rc->nullable==1) 
                    root->nullable=1; 
                else 
                    root->nullable=0; 

            unio(root->fpos,root->lc->fpos); 
            unio(root->fpos,root->rc->fpos); 
            unio(root->lpos,root->lc->lpos); 
            unio(root->lpos,root->rc->lpos); 

        } 
        else if(root->ch=='*') 
        { 
            unio(root->fpos,root->lc->fpos); 
            unio(root->lpos,root->lc->lpos); 
        } 
        else if(root->ch=='.') 
        { 
            if(root->lc->nullable==1 && root->rc->nullable==1) 
                root->nullable=1; 
            else 
                root->nullable=0; 

            if(root->lc->nullable==1) 
            { 
                unio(root->fpos,root->rc->fpos); 
            } 
            unio(root->fpos,root->lc->fpos); 

            if(root->rc->nullable==1) 
            { 
                unio(root->lpos,root->lc->lpos); 
            } 
            unio(root->lpos,root->rc->lpos); 
        } 
        follow(root); 
    } 
} 
int  follow(node *root) 
{ 
    int i=0; 
    if(root->ch=='*') 
    { 
        while(root->lpos[i]!=-1) 
        { 
            unio(folltab[root->lpos[i]].follpos,root->fpos); 
            i++; 
        } 
    } 
    else if(root->ch=='.') 
    { 
        while(root->lc->lpos[i]!=-1) 
        { 
            unio(folltab[root->lc->lpos[i]].follpos,root->rc->fpos); 
            i++; 
        } 
    }return 0; 
} 
int  unio(int arr1[],int arr2[]) 
{ 
    int i=0; 
    while(arr1[i]!=-1) 
        i++; 
    int j=0;int k=0; 
    while(arr2[j]!=-1) 
    { 
        for(k=0;k<i;++k) 
        { 
            if(arr2[j]==arr1[k]) 
            break; 
        } 
        if(k==i) 
        { 
            arr1[i]=arr2[j]; 
            i++; 
        } 
        j++; 
    } 
    arr1[i]=-1; return 0;
} 

void dfa() 
{ 
    int j=0,k=0,temp[10],i; 
    temp[0]=-1; 
    int nos=1; 
    for(i=0;i<10;++i) 
        state[i][0]=-1; 
    i=0; 
    int m; 
    unio(state[0],folltab[1].follpos); 
    while(1) 
    { 
        for(i=0;inpt[i]!=0;++i) 
        { 
            for(j=0;state[k][j]!=-1;++j) 
            { 

                if(folltab[state[k][j]].ch==inpt[i]) 
                { 
                    unio(temp,folltab[state[k][j]].follpos); 
                } 
            } 
            m=check(temp,nos); 
            if(m==-1) 
            { 
                unio(state[nos++],temp); 
                m=nos-1; 
            } 
            dfaa[df++]=m; 
            temp[0]=-1; 
        } 
        if(k==nos-1) 
        break; 
        k++; 
    } 
} 
int check(int temp[],int nos) 
{ 
    int i,j; 
    for(i=0;i<nos;++i) 
    { 
        for(j=0;temp[j]!=-1;++j) 
        { 
            if(temp[j]!=state[i][j]) 
            break; 
        } 
        if(temp[j]==-1 && state[i][j]==-1) 
        return i; 
    } 
    return -1; 
} 
void display_dfa() 
{ 
    int i,j,k; 
    printf("\nDFA TABLE\n "); 
    for(i=0;inpt[i]!=0;i++) 
        printf("\t%c",inpt[i]); 
    for(j=0;j<(df/i);j++) 
    { 
        printf("\n%c\t",j+65); 
        for(k=j*i;k<(j*i)+i;k++) 
            printf("%c\t",dfaa[k]+65); 
    } 

} 

void main() 
{ 
    int i; 
    char str[50]; 
    inpt[0]; 
    printf("Enter the postfix expression\n"); 
    scanf("%s",str); 
    node *root; 
    int l; 
    strcat(str,"#.\0"); 
    l=strlen(str); 
  //  printf("\n%d\n",l); 
    l--; 
    int j=0; 
    for(i=0;i<l-1;++i) 
    { 
        j=0; 
        while(inpt[j]!=0) 
        { 
            if(inpt[j]==str[i]) 
                break; 
            j++; 
        } 
        if(inpt[j]!=str[i] && str[i]!='|' && str[i]!='*' && str[i]!='.') 
        { 
            inpt[j]=str[i]; 
            inpt[j+1]; 
        } 
    } 
    int pos=1; 
    root=create(str,&l); 
    create_nullable(root,&pos); 
    printf("\nElement\tFPOS\tLPOS\n"); 
    print_nullable(root->lc); 
    print_follow(pos-2); 
    dfa(); 
    display_dfa(); 
}
/*OUTPUT : 
gayatri@ubuntu:~$ cd Desktop
gayatri@ubuntu:~/Desktop$ gcc re2.c
gayatri@ubuntu:~/Desktop$ ./a.out
Enter the postfix expression
ab|*a.b.b.

Element	FPOS	LPOS
a	1 	1 
b	2 	2 
|	1 2 	1 2 
*	1 2 	1 2 
a	3 	3 
.	3 1 2 	3 
b	4 	4 
.	3 1 2 	4 
b	5 	5 
.	3 1 2 	5 
FOLLOWPOS
POS	NAME	FOLLOWPOS
1	a	1 2 3 
2	b	1 2 3 
3	a	4 
4	b	5 
5	b	6 

DFA TABLE
 	a	b
A	B	A	
B	B	C	
C	B	D	
D	B	A	gayatri@ubuntu:~/Desktop$ 
	*/
