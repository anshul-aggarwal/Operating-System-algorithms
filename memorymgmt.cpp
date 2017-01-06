//Memory Management

#include<iostream>
using namespace std;

int mem[100];
int no_of_blocks;
int block_size;


void firstfit(int req)
{
int flag = 0;
    for(int i=0;i<no_of_blocks;i++)
    {
        if (mem[i]>=req)
        {
            mem[i] -= req;
            cout<<"\nMemory assigned at block no. "<<i;
            flag = 1;
            break;
        }
    }
    if (flag == 0)
        cout<<"\nSufficient contiguous space not found!";
}


void bestfit(int req)
{
    int indx = -1;
    int mem_indx = 99999;
    for(int i=0;i<no_of_blocks;i++)
    {
        if (mem[i]>=req && mem[i]<mem_indx)
        {
            indx = i;
            mem_indx = mem[indx];
        }
    }
    if (indx != -1)
    {
        mem[indx] -= req;
        cout<<"\nMemory assigned at block no. "<<indx;
    }
    else
    {
        cout<<"\nSufficient contiguous space not found!";
    }
}


void worstfit(int req)
{
    int indx = -1;
    int mem_indx = req-1;
    for(int i=0;i<no_of_blocks;i++)
    {
        if (mem[i]>=req && mem[i]>mem_indx)
        {
            indx = i;
            mem_indx = mem[indx];
        }
    }
    if (indx != -1)
    {
        mem[indx] -= req;
        cout<<"\nMemory assigned at block no. "<<indx;
    }
    else
    {
        cout<<"\nSufficient contiguous space not found!";
    }
}

void display()
{
    cout<<"\nBlock\tAvailable Space\n---------------------------------";
    for(int i=0;i<no_of_blocks;i++)
    {
        cout<<"\n"<<i<<"\t\t"<<mem[i];
    }
}


int main()
{
    int opt;
    cout<<"\nEnter the no. of blocks in the memory: ";
    cin>>no_of_blocks;
    cout<<"\nEnter the block size: ";
    cin>>block_size;
    cout<<"\nEnter the initial usage for each block:";
    for(int i=0;i<no_of_blocks;i++)
    {
        int usg;
        cout<<"\n\tBlock "<<i<<": ";
        cin>>usg;
        mem[i] = block_size - usg;
    }   
    do
    {
        cout<<"\n\n\t\t.M.E.N.U.\n\t1. First Fit\n\t2. Worst Fit\n\t3. Best Fit\n\t4. Display Memory\n\t5. Exit\n\n\tChoose option: ";
        cin>>opt;
        int req;
        if(opt<=3)
        {
            cout<<"\nEnter the amount of memory to be allocated: ";
            cin>>req;
        }
        switch(opt)
        {
            case 1: firstfit(req);
                    break;
            case 2: worstfit(req);
                    break;
            case 3: bestfit(req);
                    break;
            case 4: display();
                    break;
            case 5: break;
            default: break;
        }
    }while(opt!=5);
    return 0;
}
