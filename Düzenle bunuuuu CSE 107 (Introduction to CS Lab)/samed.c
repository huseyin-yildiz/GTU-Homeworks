#include <stdio.h>
#include <stdlib.h>

#define SIZE 10
 typedef struct queue{
    char * deger[SIZE];
    int front;
    int rear;


}queue;

queue * createQueue()
{

        queue *q;
        q = (queue *)malloc(sizeof(queue));

        q->front = -1;
        q->rear = -1;
        return q;
};

short cmp(char[] , char[] );

void enQueue(queue *q,char *value)
{
    if (q->front==-1 && q->rear==-1)
    {
        q->front=q->rear=0;
        q->deger[q->rear]=value;
        printf("%s",q->deger[q->rear]);
    }
    else if((q->rear+1)%SIZE==q->front)
    {
        printf("queue is full");
    }
    else
    {
        q->rear=(q->rear+1)%SIZE;
        q->deger[q->rear] = (char *) malloc((sizeof value + 1)* sizeof(char));
       q->deger[q->rear]=value;
       printf("%s",q->deger[q->rear]);
    }
}

char* deQueue(queue* q)
{
    if(q->front==-1 && q->rear==-1)
    {

        return "*******";
    }
    else if(q->front==q->rear)
    {
        q->front=q->rear=-1;
        return q->deger[q->front];
    }
    else
    {

        q->front=(q->front+1)%SIZE;
        return q->deger[q->front-1];

    }
}

int main()
{

    queue *q;

     char k1[20],k2[10];
    int sayi;
    int i=0;

    FILE *dosya;
    dosya=fopen("input.txt","r");
    while(!feof(dosya))
        {

        fscanf(dosya,"%s",&k1);
        fscanf(dosya,"%s",&k2);
        fscanf(dosya,"%d",&sayi);

        if( cmp(k1,"serviceCustomer") )
            enQueue(q,k2);


        i++;
    }

    printf("%s",deQueue(q));

fclose(dosya);

    return 0;
}

short cmp(char str1[], char str2[])
{
    int i=0;
    while(str1[i]!='\0')
    {
        if(str1[i] != str2[i])
            return 0;
        i++;
    }
    if(str1[i] != str2[i])
        return 0;
    return 1;
}

