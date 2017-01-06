//Bankers Algorithm

#include<iostream>
using namespace std;

int allocated[10][4], max[10][4];
//int s_allocated[10][4];
int no_of_processes;
int available[4], s_available[4];
int safesequence[10];
int indx = 0;

void init()
{
    cout<<"\nEnter the no. of processes: ";
    cin>>no_of_processes;
    cout<<"\nEnter the total resources required for each process:";
    for(int i=0;i<no_of_processes; i++)
    {
        cout<<"\n\tProcess "<<i<<":";
        for(int j=0;j<4;j++)
        {
            cout<<"\n\t\tResource "<<j<<": ";
            cin>>max[i][j];
        }
    }
    cout<<"\nEnter the resources initiallly allocated for each process:";
    for(int i=0;i<no_of_processes; i++)
    {
        cout<<"\n\tProcess "<<i<<":";
        for(int j=0;j<4;j++)
        {
            cout<<"\n\t\tResource "<<j<<": ";
            cin>>allocated[i][j];
            //s_allocated[i][j] = allocated[i][j];
            if(allocated[i][j]>max[i][j])
            {
                cout<<"\n\t\t\tError! Allocted Memory exceeds maximum required memory. Please reallocate memory...";
                j--;
            }
        }
    }
    cout<<"\nEnter the available resources initially:";
    for(int i=0;i<4; i++)
    {
        cout<<"\n\tResource "<<j<<": ";
        cin>>available[i];
        s_available[i] = available[i];
    }
}

void findsafesequence()
{
    for(int i=0;i<no_of_processes; i++)
    {
        int resavl = 0;
        for(int j=0;j<4;j++)
        {
            if(max[i][j]-allocated[i][j]>=s_available[j])
            {
                resavl++;
            }
                
        }
        if(resavl == 4)
        {
            safesequence[indx++] = i;
            for(int j=0;j<4;j++)
            {
                s_available[j] += allocated[i][j]
                    
            }
            break;
        }
    }
}

void allocateresources()
{
    for(int i=0;i<no_of_processes; i++)
    {
        int resavl = 0;
        for(int j=0;j<4;j++)
        {
            if(max[i][j]-allocated[i][j]>=s_available[j])
            {
                resavl++;
            }
                
        }
        if(resavl == 4)
        {
            safesequence[indx++] = i;
            for(int j=0;j<4;j++)
            {
                s_available[j] += allocated[i][j]
                    
            }
            break;
        }
    }
}


int main()
{
    init();
    findsafesequence();
    if(indx == no_of_processes)
    {
        allocateresources();
    }
    else
    {
        cout<<"\nNo safe sequence found!";
    }
	return 0;
}
