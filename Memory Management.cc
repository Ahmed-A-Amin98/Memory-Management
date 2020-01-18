#include <iostream>
#include <queue>
#include <string.h>
using namespace std;
queue <int> A;

void Read();

int *TableAlloc,faultNo,Displacer;
bool Hit;



int* initalize (int);


// prototype of techniques
void FIFO(int);
void LRU(int);
void Clock(int);
void Optimal(int);

// prototype Util
int reachLRU(int *,int );
int reachOP(int,int *,int,int,int * );
void print(int);

int main()
{
    int input, PageAllocNumber;
    char way [10] ;
    scanf("%d",&PageAllocNumber);
    scanf("%s",way);
    if (strcasecmp(way, "FIFO")==0)
    {
        input = 1 ;
        Read();
        printf("Replacement Policy = %s\n-------------------------------------\n",way);
        FIFO(PageAllocNumber);
    }
    else if(strcasecmp(way, "LRU")==0)
    {
        input=1;
        Read();
        printf("Replacement Policy = %s\n-------------------------------------\n",way);
        LRU(PageAllocNumber);
    }
    else if(strcasecmp(way, "CLOCK")==0)
    {
        input=1;
        Read();
        printf("Replacement Policy = %s\n-------------------------------------\n",way);
        Clock(PageAllocNumber);
    }
    else if(strcasecmp(way, "OPTIMAL")==0)
    {
        input=1;
        Read();
        printf("Replacement Policy = %s\n-------------------------------------\n",way);
        Optimal(PageAllocNumber);
    }
    else
        printf("Invalid input please");

    return 0;
}





void FIFO (int PageAllocNumber)
{
    int i=0,buffer,x;
    bool Hit;
    faultNo=0, Displacer=0;
    int TableAlloc[PageAllocNumber];
    printf( "Page   Content of Frames\n----   -----------------\n");
    while (i < PageAllocNumber)
    {
        TableAlloc[i] = -1 ;
        i++ ;
    }
    while(A.size() > 0)
    {
        Hit=0;
        buffer = A.front();
        A.pop();
        i=0;
        while(i<PageAllocNumber)
        {
            if(TableAlloc[i]==-1 || TableAlloc[i] == buffer)
            {
                TableAlloc[i]=buffer;
                Hit=1;
                break;
            }
            i++;
        }
        print(buffer);
        if(Hit == 0)
        {
            printf(" F   ");
            TableAlloc[Displacer] = buffer;
            Displacer++;
            faultNo++;
        }
        else
        {
            printf ("     ");
        }
        i =0;
       while(i<PageAllocNumber)
        {
            if(TableAlloc[i]!=-1)
            {
            int printx = TableAlloc[i] < 10  ?  printf("0%d ",TableAlloc[i]):printf("%d ",TableAlloc[i]);
            }
            i++;
        }
        int printx = Displacer >= PageAllocNumber ? Displacer=0:x=1 ;

        printf("\n");
    }
    printf("-------------------------------------\nNumber of page faults = %d\n",faultNo);

}

void LRU(int PageAllocNumber)
{
        int Displacer = 0,faultNo=0,i=0,buffer;
        bool Hit;
    printf("Page   Content of Frames\n----   -----------------\n");
    int TableAlloc[PageAllocNumber],AllocHistory[PageAllocNumber];
    while(i     <    PageAllocNumber)
    {
        TableAlloc[i]=-1;
        AllocHistory[i]=-1;
        i++;
    }
    while(A.size() > 0)
    {
        Hit=0;

        buffer = A.front();
        A.pop();
        i=0;
       while(i<PageAllocNumber)
        {
            if(TableAlloc[i]==-1 )
            {
                TableAlloc[i]=buffer;
                AllocHistory[i]=0;
                Hit=1;
                break;
            }
            else if (TableAlloc[i] == buffer)
            {
               TableAlloc[i]=buffer;
                AllocHistory[i]=0;
                Hit=1;
                break;
            }
            i++;
        }
        print(buffer);
        if(Hit == 0)
        {
            printf(" F   ");
            Displacer = reachLRU(AllocHistory,PageAllocNumber);
            TableAlloc[Displacer]=buffer;
            AllocHistory[Displacer]=0;
            faultNo++;
        }
        else
        {
            printf("     ");
        }
        i=0;
        while(i<PageAllocNumber)
        {
            if(TableAlloc[i]!=-1)
            {
                AllocHistory[i]++;
                int printx = TableAlloc[i] < 10  ?  printf("0%d ",TableAlloc[i]):printf("%d ",TableAlloc[i]);
            }
            i++;
        }
        printf("\n");
    }
    printf("-------------------------------------\nNumber of page faults = %d\n",faultNo);
}

void Clock(int PageAllocNumber)
{
     int faultNo=0,location=0,i=0,buffer,x;
     bool Hit;
    printf("Page   Content of Frames\n----   -----------------\n");
    int TableAlloc[PageAllocNumber],AllocHistory[PageAllocNumber];

    while(i<(PageAllocNumber))
    {
        TableAlloc[i]=-1;
        AllocHistory[i]=-1;
        i++;
    }
    while(A.size()> 0)
    {
         Hit=0;
         buffer = A.front();
        A.pop();
        i=0;
       while(i<PageAllocNumber)
        {
            if(TableAlloc[i]==-1)
            {
                TableAlloc[i]=buffer;
                AllocHistory[i]=1;
                location++;
                Hit=1;
                break;
            }
            if(TableAlloc[i] == buffer)
            {
                AllocHistory[i]=1;
                Hit=1;
                break;
            }
            i++;
        }
        print(buffer);
        if(Hit == 0)
        {
            printf(" F   ");
            while(AllocHistory[location]==1)
            {
                AllocHistory[location]=0;
                location++;

                int printx = location == PageAllocNumber ? location=0 : x=0;

            }
            switch (AllocHistory[location])
            {
            case 0:
                    TableAlloc[location]=buffer;
                AllocHistory[location]=1;
                location++;
                break;


            }

            faultNo++;
        }
        else
        {
            printf("     ");
        }
        i=0;
        while(i<PageAllocNumber)
        {
            if(TableAlloc[i]!=-1)
            {
                int printx = TableAlloc[i] < 10  ?  printf("0%d ",TableAlloc[i]):printf("%d ",TableAlloc[i]);
            }
            i++;
        }
        if(location >= PageAllocNumber)
        {
            location=0;
        }
        printf("\n");
    }
    printf("-------------------------------------\nNumber of page faults = %d\n",faultNo);
}


void Optimal(int PageAllocNumber)
{       int Displacer = 0,faultNo=0,sizeofQ=A.size(),buffer;
    bool   boolean;
    printf("Page   Content of Frames\n----   -----------------\n");
    int TableAlloc[PageAllocNumber],i=0, ArrPages[A.size()];


    while(i<PageAllocNumber)
    {
        TableAlloc[i]=-1;
        i++;
    }
    i=0;
    while( i<sizeofQ)
    {
        ArrPages[i]=A.front();
        A.pop();
        i++;
    }
    int k =0;
    while(k < sizeofQ)
    {
        boolean=0;
         buffer = ArrPages[k];
         i=0;
       while(i<PageAllocNumber)
        {
            if(TableAlloc[i]==-1 || TableAlloc[i] == buffer)
            {
                TableAlloc[i]=buffer;
                boolean=1;
                break;
            }
            i++;
        }
        print(buffer);

        switch (boolean)
        {
        case 0 :
             printf(" F   ");
            Displacer=reachOP(sizeofQ,TableAlloc,PageAllocNumber,k,ArrPages);
            TableAlloc[Displacer] = buffer;
            faultNo++;
            break;
        default:
            printf("     ");
            break;

        }

        i=0;
        while(i<PageAllocNumber)
        {
            if(TableAlloc[i]!=-1)
            {
            int printx = TableAlloc[i] < 10  ?  printf("0%d ",TableAlloc[i]):printf("%d ",TableAlloc[i]);

            }
            i++;
        }
        k++;
        printf("\n");
    }
    printf("-------------------------------------\nNumber of page faults = %d\n",faultNo);
}
void print(int temp)
{

    if(temp <= 9)
    {
        printf("0%d",temp);
    }
    else
    {
        printf("%d",temp);
    }
}

void Read()
{
    int temp;

    while(true)
    {
        scanf("%d",&temp);
        if(temp == -1)
        {
            break;
        }
        A.push(temp);
    }
}

int reachLRU(int a[],int PageSize)
{   int i=0;
    int MaxIndex=0,index;
    while( i<PageSize)
    {
        if(a[i] > MaxIndex)
        {
            MaxIndex=a[i];
            index=i;
        }
        i++;
    }
    return index;
}

int reachOP(int PgC,int allocTable[],int alloccount,int index,int Pages[])
{

    int Mindex=0;
    int counter;
    int output,i=0, j;
    while(i<alloccount)
    {
        j=index;
        counter=0;
       while(j < PgC)
        {

            if(allocTable[i]==Pages[j])
            {
                if(counter<=Mindex)
                {

                    break;
                }
                else
                {  Mindex=counter;
                    output=i;
                    break;
                }
            }
            if(j==PgC-1)
            {
                return i;
            }
            counter++;
            j++;
        }
        i++;
    }
    return output;
}
