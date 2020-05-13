#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define MAX 5

int landqueue=0;
int tOffqueue=0;
int landTotal=0;
int tOffTotal=0;
int idleRun=0;
int handled=0;
int refuse=0;
typedef struct plane
{ 
    int num;
    int ops;
    int wait;
} Plane;

typedef struct landing
{ 
    Plane data;  
    struct landing * link; 
} Land;
Land *HeadLand;
Land *TailLand;

typedef struct takeoff
{ 
    Plane data;
    struct takeoff * link; 
} Leave;
Leave *HeadTo;
Leave *TailTo;


void addLandQueue(Plane dat);
void addTOQueue(Plane dat);
void Landed(int run);
void Takenoff(int run);
void newPlanes(int acs);
void ATC(int lim);
void refused(int planeOps, Plane dat);
void stats();

void addLandQueue(Plane dat)
{
    Land * temp = malloc(sizeof(Land)); 
    
    temp->data = dat;
    printf("\nPlane %d is ready to land",dat.num);
    if(HeadLand==NULL)
    {
        HeadLand=temp;
        TailLand=temp;
    } 
    else
    {
        if(landqueue==MAX)
        {
            refused(0,dat);
        }
        else
        {
            TailLand->link=temp;
            TailLand=temp; 
        }
        
    } 
    temp = NULL; 
    free(temp);  
    landqueue++;
}

void addTOQueue(Plane dat)
{
    Leave * temp = malloc(sizeof(Land)); 
    
    temp->data = dat;
    printf("\nPlane %d is ready to depart",dat.num);
    if(HeadTo==NULL)
    {
        HeadTo=temp;
        TailTo=temp;
    } 
    else 
    {
        if(tOffqueue==MAX)
        {
            refused(1,dat);
        }
        else
        {
            TailTo->link=temp;
            TailTo=temp; 
        }   
    }
    temp = NULL; 
    free(temp);  
    tOffqueue++;
}

void Landed(int run)
{
    Land *temp=malloc(sizeof(Land));
    if(HeadLand==NULL)
    {
        printf("\nLanding queue is empty");
    }
    else 
    {
        temp=HeadLand;
        printf("\nPlane number %d has landed on runway %d",(temp->data).num,run);
        HeadLand = HeadLand->link;
        landqueue--;
    }
    free(temp);
    
}


void Takenoff(int run)
{
    Leave *temp=malloc(sizeof(Leave));
    if(HeadTo==NULL)
    {
        printf("\nno planes to depart");
    }
    else 
    {
        temp=HeadTo;
        printf("\nPlane number %d has taken off from runway %d",(temp->data).num,run);
        HeadTo = HeadTo->link;
        tOffqueue--;
    }

    free(temp);
}

void newPlanes(int acs)
{
    Plane new;
    for(int i=0;i<acs;i++)
    {
        handled++;
        new.num=handled;
        new.ops=rand()%2;
        new.wait=0;
        if(new.ops==0)
        {
            addLandQueue(new);
        }
        else
        {
            addTOQueue(new);
        }   
        //printf("made a plane boii");
    }
}


void ATC(int lim)
{
    int noDep=0;
    //srand(time(0));
    //int num =(rand()%(5-1+1))+1;
    newPlanes(3);
    for(int i=0;i<lim;i++)
    {
        if(HeadLand==NULL && noDep==1)
        {
            noDep=0;
            printf("\nAll planes in the air have landed");
        }
        if(HeadTo==NULL && HeadLand==NULL)
        {
            idleRun++;
            printf("\nrunway is idle");
        }
        else
        {
            if(landqueue==MAX)
            {
                noDep=1;
                printf("\nHeavy traffic, both runways will be used to land planes\n");
            }
            //runway 0 ops
            if(HeadLand==NULL)
            {
                Takenoff(1);
            }
            else
            {
                Landed(1);
            }
            
            //runway 1 ops
            if(noDep==0)
                Takenoff(2);
            else
                Landed(2);
        }
        //srand(time(0));
        //num =(rand()%(5-1+1))+1;
        newPlanes(3);
    }
}
void refused(int planeOps, Plane dat)
{
    if(planeOps==0)
        printf("\nPlane %d is directed to another airport",dat.num);
    else
    {
        printf("\nPlane %d is asked to try again later",dat.num);
    }
    refuse++;
    
}
int main()
{

    printf("Runway 1 is for landing\n");
    printf("Runway 2 is for takeoffs\n");
    srand(time(0));
    int n;
    //printf("for how many units of time does the simulation need to run? : ");
    //scanf("%d",&n);
    ATC(5);
    stats();
    /*printf("How many arrivals per unit time? : ");
    scanf("%f",&expArrive);
    printf("How many departures per unit time? : ");
    scanf("%f",&expDepart);
    ATC(n,expArrive,expDepart);*/

}

void stats()
{
    printf("\nstats");
}