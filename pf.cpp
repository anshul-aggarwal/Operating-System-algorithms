//Page fault and TLB

#include<iostream>
#include<stdlib.h>
#include<time.h>
#define TLB_size 3
#define PT_size 10

int pt_ct = 0;      //Page Table size count

using namespace std;

struct pt_entry{
    int page_no;
    int frame_no;
}PT[PT_size];

pt_entry TLB[TLB_size];

struct page{
    int page_no;
    int line_no;
};

void init_PT()
{
    for(int i=0;i<PT_size;i++)
    {
        PT[i].page_no = -1;
        PT[i].frame_no = -1;
    }
}

void init_TLB()
{
    for(int i=0;i<TLB_size;i++)
    {
        TLB[i].page_no = -1;
        TLB[i].frame_no = -1;
    }
}

int TLB_search(int pg_no)
{
    for(int i=0;i<TLB_size;i++)
    {
        if(TLB[i].page_no == pg_no)
            return TLB[i].frame_no;
    }
    return -1;
}


int PT_search(int pg_no)
{
    for(int i=0;i<PT_size;i++)
    {
        if(PT[i].page_no == pg_no)
        {
            int indx = rand()%TLB_size;        //TLB_replace_index
            TLB[indx].page_no = pg_no;
            TLB[indx].frame_no = PT[i].frame_no;
            return PT[i].frame_no;
        }
    }
    return -1;
}

void LogicalToPhysical()
{
    int la_p, la_l;     //Logical Address
    la_p = rand()%100;
    la_l = rand()%20;
    
    cout<<"\nLogical Address:\n\tPage No.: "<<la_p<<"\n\tLine No.: "<<la_l;
    
    int pa_f, pa_l;     //Physical Address
    pa_l = la_l;
    pa_f = TLB_search(la_p);
    if(pa_f == -1)
    {
        cout<<"\nTLB Miss!";
        pa_f = PT_search(la_p);
        if(pa_f == -1) cout<<"\nPage Fault!";
        else cout<<"\nFound in Page Table";
    }
    else cout<<"\nTLB Hit!";
    if(pa_f !=-1)
        cout<<"\nPhysical Address:\n\tFrame No.: "<<pa_f<<"\n\tLine No.: "<<pa_l;
}

void displayTLB()
{
    for(int i=0;i<TLB_size; i++)
    {
        cout<<"\nPage: "<<TLB[i].page_no<<"\tFrame: "<<TLB[i].frame_no;
    }
}

void displayPT()
{
    for(int i=0;i<PT_size; i++)
    {
        cout<<"\nPage: "<<PT[i].page_no<<"\tFrame: "<<PT[i].frame_no;
    }
}

void menu()
{
    int rpt = 1;
    while(rpt)
    {
        int opt;
        cout<<"\n\n\t\t\tMENU\n\n\t1. Display Page Table\n\t2. Display Translation Lookaside Buffer\n\t3. Generate Logical to Physical address\n\t4. Exit";
        cin>>opt;
        switch(opt)
        {
            case 1: displayPT();
                    break;
            case 2: displayTLB();
                    break;
            case 3: LogicalToPhysical();
                    break;
            case 4: 
            default: rpt = 0;
                     break;
        }
    }
}

int main()
{
    srand (time(NULL));
    char opt;
    cout<<"\nCreate new page table entry?(y/n): ";
    cin>>opt;
    while(opt != 'n')
    {
        int page_no = rand()%100;
        int frame_no = rand()%100;
        PT[pt_ct].page_no = page_no;
        PT[pt_ct].frame_no = frame_no;
        cout<<"\nPage: "<<PT[pt_ct].page_no<<"\tFrame: "<<PT[pt_ct].frame_no;
        pt_ct++;
        cout<<"\nCreate new page table entry?(y/n): ";
        cin>>opt;
    }
    for(int i=0;i<TLB_size;i++)
    {
        int ind = rand()%pt_ct;
        TLB[i] = PT[ind];
    }
    
    menu();
    return 0;
}
