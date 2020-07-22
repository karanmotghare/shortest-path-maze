#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

typedef enum statuscode{FALSE,TRUE} status; 



struct DL_node
{
	int x;
	int y;
	struct DL_node *prev;
	struct DL_node *next;
};

struct Queue
{
	struct DL_node *front;
	struct DL_node *rear;
};

struct Pr_queue 
{
  struct Queue prq[100];
};

 
void Initialise( struct Queue *qptr)
{
	qptr->front=qptr->rear=NULL;
 }
  
int IsqueueEmpty(struct Queue *qptr)
{
	int retval;
	if((qptr->front==NULL) && (qptr->rear==NULL))
	{
		retval=1;
	}
	else
	{
		retval=0;
	}
	return retval;
}

void push(int row,int column,struct Queue *qptr)
{
	int a;
	struct DL_node *p;
	p=(struct DL_node*)malloc(sizeof(struct DL_node));
	p->x=row;
	p->y=column;
	p->next=NULL;
	p->prev=NULL;
   	a=IsqueueEmpty(qptr);
   	if(a==1)
   	{
   		qptr->front=qptr->rear=p;
	   }
	  else
	  {
	    qptr->rear->next=p;
	    p->prev=qptr->rear;
	    qptr->rear=p;
	   } 
}

struct DL_node* pop(struct Queue *qptr)
{
	struct DL_node *ptr,*dptr;
	dptr=(struct DL_node*)malloc(sizeof(struct DL_node));
	ptr=qptr->front;
	dptr->x=ptr->x;
	dptr->y=ptr->y;
	dptr->next=ptr->next;
	dptr->prev=ptr->prev;
	qptr->front=(qptr->front)->next;
	free(ptr);
	if(qptr->front==NULL)
	{
		qptr->rear=NULL;
	}
	return dptr;
}


void minimum_cost_path(int n,int m,char B[][m],int a1,int b1,int a2,int b2)
{
   status A[n][m];
   int i,a,j,flag=0,pop_row,pop_col,b;
   struct Pr_queue pq;
   struct DL_node *dptr,*lptr,*pt;
    
    if((B[a1][b1]=='#') || (B[a2][b2]=='#'))
    {
    	printf("starting or destination point can't be reached");
	}
	else
	{
	 for(i=0;i<n;i++)
	 {
	 	for(j=0;j<m;j++)
	 	{
	 		A[i][j]=FALSE;
		 }
	 }
	  
	  for(i=0;i<100;i++)
	  {
         Initialise(&(pq.prq[i]));
	  }
	  
	  a=B[a1][b1]-'0';
	  push(a1,b1,&(pq.prq[a]));
	
	  A[a1][b1]=TRUE;
	  lptr=NULL;
	  for(i=0;i<100 && flag==0;i++)
	  {
	  	while(!(IsqueueEmpty(&(pq.prq[i]))))
	  	{
	  
	  		dptr=pop(&(pq.prq[i]));
	  		pop_row=dptr->x;
	  		pop_col=dptr->y;
	  	 
				if(lptr==NULL)
				{
					dptr->prev=NULL;
				    dptr->next=NULL;
				    lptr=dptr;
				}
				
				else
				{
					lptr->next=dptr;
					dptr->prev=lptr;
					dptr->next=NULL;
					lptr=dptr;
				}
			    	
				if((pop_row+1<n && pop_col<m ) && (pop_row+1>=0 && pop_col>=0) && (A[pop_row+1][pop_col]==FALSE))
				{
					A[pop_row+1][pop_col]=TRUE;
					if(B[pop_row+1][pop_col]!='#')
					{
						b=B[pop_row+1][pop_col]-'0';
						push(pop_row+1,pop_col,&(pq.prq[i+b]));
						if(pop_row+1==a2 && pop_col==b2)
						{
							dptr=(struct DL_node*)malloc(sizeof(struct DL_node));
							dptr->x=pop_row+1;
							dptr->y==pop_col;
							lptr->next=dptr;
							dptr->prev=lptr;
							dptr->next=NULL;
							flag=1;
							printf("The cost of path is %d \n",i+b);
						}
					}
				}
				if((pop_row-1<n && pop_col<m) && (pop_row-1>=0 && pop_col>=0) && (A[pop_row-1][pop_col]==FALSE))
				{
					A[pop_row-1][pop_col]=TRUE;
					if(B[pop_row-1][pop_col]!='#')
					{
						b=B[pop_row-1][pop_col]-'0';
						push(pop_row-1,pop_col,&(pq.prq[i+b]));
						if(pop_row-1==a2 && pop_col==b2)
						{
							dptr=(struct DL_node*)malloc(sizeof(struct DL_node));
							dptr->x=pop_row-1;
							dptr->y==pop_col;
							lptr->next=dptr;
							dptr->prev=lptr;
							dptr->next=NULL;
							flag=1;
							printf("The cost of path is %d \n",i+b);
						}
					}
					
				}
				if((pop_row<n && pop_col+1<m) && (pop_row>=0 && pop_col+1>=0) && (A[pop_row][pop_col+1]==FALSE))
				{
					A[pop_row][pop_col+1]=TRUE;
					if(B[pop_row][pop_col+1]!='#')
					{
						b=B[pop_row][pop_col+1]-'0';
						push(pop_row,pop_col,&(pq.prq[i+b]));
						if(pop_row==a2 && pop_col+1==b2)
						{
							dptr=(struct DL_node*)malloc(sizeof(struct DL_node));
							dptr->x=pop_row;
							dptr->y==pop_col+1;
							lptr->next=dptr;
							dptr->prev=lptr;
							dptr->next=NULL;
							flag=1;
							printf("The cost of path is %d \n",i+b);
						}
					}
			    }
			    	if((pop_row<n && pop_col-1<m) && (pop_row>=0 && pop_col-1>=0) && (A[pop_row][pop_col-1]==FALSE))
				{
					A[pop_row][pop_col-1]=TRUE;
					if(B[pop_row][pop_col-1]!='#')
					{
						b=B[pop_row][pop_col-1]-'0';
						push(pop_row,pop_col,&(pq.prq[i+b]));
						if(pop_row==a2 && pop_col-1==b2)
						{
							dptr=(struct DL_node*)malloc(sizeof(struct DL_node));
							dptr->x=pop_row;
							dptr->y==pop_col-1;
							lptr->next=dptr;
							dptr->prev=lptr;
							dptr->next=NULL;
							flag=1;
							printf("The cost of path is %d \n",i+b);
						}
					}
			    }
				
			
	  		
		}
	  }
	  
	  
	  
	   
    } 
	
} 

int main() {
    char c[10],A[1000],ch;
    int i=0,j,m,n,a1,b1,a2,b2,t;
    FILE *fptr;
	fptr = fopen("input.txt", "r");
    if (fptr == NULL)
	 { 
	    printf("Error! opening file");
     }
     else
    {
		while(!feof(fptr))
		{	
		
    		fscanf(fptr, "%s", c);
    	    j=0;
			while(j<strlen(c))
    	    {
    	    	if(c[j] !=" ")
    	    	A[i++]=c[j];
    	    	j++;
			}
       }
       n=A[0]-'0';
       m=A[1]-'0';
      char B[n][m];
       a1=A[2]-'0';
       b1=A[3]-'0';
       a2=A[4]-'0';
       b2=A[5]-'0';
       t=6;
       for(i=0;i<n;i++)
       {
       	for(j=0;j<m;j++)
       	{
          	   B[i][j]=A[t];  
			  printf("%c ",A[t]);
			t++;	  	
		}
		printf("\n");
	   } 
       printf("The source point is (%d,%d) \n",a1,b1);
       printf("The destination point is (%d,%d) \n",a2,b2);
	   fclose(fptr);
       minimum_cost_path(n,m,B,a1,b1,a2,b2);         
	}
    return 0;
}

