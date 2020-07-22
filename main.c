#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 50

typedef enum {FAILURE,SUCCESS} status_code;


typedef struct DL_node_tag
{
    int row;
    int col;
    struct DL_node_tag *prev;
    struct DL_node_tag *next;
}Node;

typedef struct Queue_tag
{
    Node * front;
    Node * rear;
}Queue;

typedef struct Priority_Queue_tag
{
    Queue  prq[max];  
}P_Queue;


int IsQEmpty(Queue * qptr)
{
    int ret_val;
    if((qptr->front==NULL) && (qptr->rear==NULL))
    {
        ret_val=1;
    }
    else
    {
        ret_val=0;
    }
    return ret_val;
}

void push(Node * node,Queue *qptr)
{
    status_code sc=SUCCESS;

    Node *nptr;

    nptr = (Node *)malloc(sizeof(Node));

    if(nptr==NULL) sc=FAILURE;
    else
    {
        nptr->row=node->row;
        nptr->col=node->col;
        nptr->next=node->next;
        nptr->prev=node->prev;
        if(IsQEmpty(qptr))
        {
            qptr->front=nptr;
            qptr->rear=nptr;
            nptr->next=NULL;
        }
        else
        {
            qptr->rear->next=nptr;
            qptr->rear=nptr;
        }
    }
    
}

void pop(Node **dptr,Queue *qptr)
{
    status_code sc = SUCCESS;
    Node *ptr;
    
    if(IsQEmpty(qptr)) sc=FAILURE;
    else
    {
        ptr=qptr->front;
        Node *nptr;
        nptr = (Node *)malloc(sizeof(Node));
        nptr->row=ptr->row;
        nptr->col=ptr->col;
        nptr->next=ptr->next;
        nptr->prev=ptr->prev;
        *dptr=nptr;
        qptr->front=(qptr->front)->next;
       
        free(ptr);
        if(qptr->front == NULL)qptr->rear=NULL;

    }

}


void insrt(Node *ptr , int p ,P_Queue *pqptr)
{
    push(ptr,&(pqptr->prq[p]));
}

void dlete(Node **ptr,P_Queue *pqptr )
{
    int i=0;
    while((IsQEmpty((&pqptr->prq[i]))) && i<max)
    {
        i++;
    }
    if(i<max)
        pop(ptr,&(pqptr->prq[i]));
}

int Isvalid(int row,int col,int a_row,int a_col,int Maze[][a_col])
{
    if((row>=0 && col>=0) && (row<a_row && col<a_col) && Maze[row][col]!=-1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    
}

 int main()
 {
     FILE *fptr;
     fptr = fopen("input.txt","r");
     if(fptr==NULL)
     {
         printf("ERROR\n");
     }
     else
     {
         int n,m;
         char ch;
         fscanf(fptr,"%d",&n);
         fscanf(fptr,"%d",&m);
         fscanf(fptr,"%c",&ch);
         int i,j,Maze[n][m];
         for(i=0;i<n;i++)
         {
             for(j=0;j<2*m-1;j++)
             {
                 fscanf(fptr,"%c",&ch);
                 if(ch!=' ')
                 {
                   
                    if(ch=='#')
                        Maze[i][j/2]=-1;
                    else if(ch=='1')
                        Maze[i][j/2]=1;
                    else 
                        Maze[i][j/2]=0;
                 }
             }
             fscanf(fptr,"%c",&ch);
         }
         Node *ans,*start,*end;

         start=(Node *)malloc(sizeof(Node));
         end=(Node *)malloc(sizeof(Node));
         ans=(Node *)malloc(sizeof(Node));

         fscanf(fptr,"%d",&start->row);
         fscanf(fptr,"%d",&start->col);
         
         start->next=NULL;
         start->prev=NULL;
         end->next=NULL;
         end->prev=NULL;
         fscanf(fptr,"%d",&end->row);
         fscanf(fptr,"%d",&end->col);
       

       
       P_Queue pq;

        for(i=0;i<max;i++)
        {
            ((pq.prq[i])).front=NULL;
            ((pq.prq[i])).rear=NULL;
        }

        Node *begin;
        begin=(Node *)malloc(sizeof(Node));
        begin->prev=NULL;
        begin->next=start;
        begin->row=-1;
        begin->col=-1;
        start->prev=begin;
        insrt(start,0,&pq);
        int flg=0;
        int block;
        int rrow[4]={1,-1,0,0};
        int ccol[4]={0,0,1,-1};
       for(i=0;i<max;i++ )
        {
            while(!(IsQEmpty(&(pq.prq[i]))))
            {
                Node *var;
                var=(Node *)malloc(sizeof(Node));
                pop(&var,&(pq.prq[i]));
                
                int pop_row=var->row;
                int pop_col=var->col;
                if( pop_row == end->row && pop_col == end->col )
                {
                    flg=1;
                    ans=var;
                    break;
                }
                Node *vary;
                vary=(Node *)malloc(sizeof(Node));
                block=0;
                for(int k=0;k<4;k++)
                {
                    if(Isvalid(pop_row+rrow[k],pop_col+ccol[k],n,m,Maze)==1)
                    {
                         if( ( pop_row+rrow[k] != (var->prev)->row ) || ( pop_col+ccol[k] != (var->prev)->col ) )
                        {
                            vary->row=pop_row+rrow[k];
                            vary->col=pop_col+ccol[k];
                            vary->next=NULL;
                            vary->prev=var;
                            insrt(vary,i+Maze[pop_row+rrow[k]][pop_col+ccol[k]],&pq);
                            block++;
                        }
                    }
                }
             
                if(block==0)
                {
                    flg=2;
                    break;
                }
            }
            if(flg==1)
            break;
        }
        fclose(fptr);
        if(i==50)
        {
            printf("No path is possible");
        }
        else
        {
                 printf("cost is %d \n",i);
            
        }
        
        fptr = fopen("output.txt","w");
        if(fptr==NULL)
        {
            printf("ERROR o/p\n");
        }
        else
        {
        
            Node *pth,*tp;
            pth=ans->prev;
            pth->next=ans;
            while(pth->row!=start->row || pth->col!=start->col)
            {
                Maze[pth->row][pth->col]=9;
                tp=pth;
                pth=pth->prev;
                pth->next=tp;
            }
            start->next=tp;
            fprintf(fptr,"START\n(%d,%d)\n",start->row,start->col);
            pth=start->next;
            while(pth->row!=end->row && pth->col!=end->col)
            {
                fprintf(fptr,"(%d,%d)\n",pth->row,pth->col);

                pth=pth->next;

            }
            fprintf(fptr,"(%d,%d)\nEND\n",end->row,end->col);
            
            fclose(fptr);
        }
        
        printf("PATH FROM S TO E IS\n");
        for(i=0;i<n;i++)
         {
             for(j=0;j<m;j++)
             {
                 if(i== start->row && j== start->col)printf("S    ");
                 else if(i== end->row && j== end->col)printf("E    ");
                 else if(Maze[i][j]==-1) printf("%d   ",Maze[i][j]);
                 else printf("%d    ",Maze[i][j]);
             }
             printf("\n\n");
         }
     }
    
     return 0;
 }
