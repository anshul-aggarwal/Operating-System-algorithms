//Job Scheduling

#include<iostream>
using namespace std;

struct process
{
	int index;
	float burst_time;
	float rem_burst_time;
	float wait_time;
	float arr_time;
	float stop_time;
	float restart_time;
	float ter_time;
	int completed;          //0: Not started    1: Complete     2: Parially complete
};

float minimum(float a, float b)
{
	if (a >= b) return a;
	else return b;
}

void sort(process p[], char mode, int no_p)
{
	switch (mode)
	{
	case 'a': for (int i = 0; i<no_p; i++) {
				for (int j = i + 1; j<no_p; j++) {
					if (p[j].arr_time < p[i].arr_time) {
						process tmp = p[j];
						p[j] = p[i];
						p[i] = tmp;
					}
				}
			  }
			  break;
	/*case 'b': for (int i = 0; i<no_p; i++) {
		for (int j = i + 1; j<no_p; j++) {
			if ((p[j].arr_time == p[i].arr_time) && (p[j].burst_time < p[i].burst_time) || (p[j].arr_time < p[i].arr_time)) {
				process tmp = p[j];
				p[j] = p[i];
				p[i] = tmp;
			}
		}
	}
			  break;
			  */
	case 'B': for (int i = 0; i<no_p; i++) {
				for (int j = i + 1; j<no_p; j++) {
					if (p[j].burst_time < p[i].burst_time) {
						process tmp = p[j];
						p[j] = p[i];
						p[i] = tmp;
					}
				}
			  }
			  break;
	default: break;
	}
}

void fcfs()
{
	process p[100];
	int no_of_processes, switch_count = 0;
	float avg_wt_time = 0, cur_wt_time = 0;
	cout << "\nEnter the no. of processes: ";
	cin >> no_of_processes;
	for (int i = 0;i<no_of_processes;i++)
	{
		cout << "\nProcess " << i << ":";
		p[i].index = i;
		cout << "\n\tArrival time: ";
		cin >> p[i].arr_time;
		cout << "\n\tBurst time: ";
		cin >> p[i].burst_time;
		p[i].completed = 0;
		p[i].restart_time = p[i].arr_time;
	}
	sort(p, 'a', no_of_processes);       //sort based on arrival time
	for (int i = 0;i<no_of_processes;i++)
	{
		p[i].wait_time = cur_wt_time - p[i].arr_time;
		p[i].ter_time = cur_wt_time + p[i].burst_time;
		avg_wt_time += p[i].wait_time;
		p[i].completed = 1;
		cur_wt_time += p[i].burst_time;
		switch_count++;
	}
	avg_wt_time /= no_of_processes;
	switch_count -= 1;
	cout << "\n\nWaiting time for each process, in order of execution:\n";
	cout << "Process | Wait Time\n" << "-------------------\n";
	for (int i = 0;i<no_of_processes;i++)
	{
		cout << p[i].index << "\t\t" << p[i].wait_time << "\n";
	}
	cout << "Average waiting time for the system is: " << avg_wt_time;
	cout << "\nTotal no. of switches is: " << switch_count;
}

void sjf_np()
{
	process p[100];
	int no_of_processes, switch_count = 0;
	float avg_wt_time = 0, cur_time = 0;
	cout << "\nEnter the no. of processes: ";
	cin >> no_of_processes;
	int new_process = 0;
	process np;
	for (int i = 0;i<no_of_processes;i++)
	{
		cout << "\nProcess " << i << ":";
		p[i].index = i;
		//cout << "\n\tArrival time: ";
		//cin >> p[i].arr_time;
		p[i].arr_time = 0;
		cout << "\n\tBurst time: ";
		cin >> p[i].burst_time;
		p[i].completed = 0;
	}
	cout << "\nNew Process " << no_of_processes << ":";
	np.index = no_of_processes;
	cout << "\n\tArrival time: ";
	cin >> np.arr_time;
	cout << "\n\tBurst time: ";
	cin >> np.burst_time;
	np.completed = 0;
	int next = -1;
	sort(p, 'B', no_of_processes);       //sort based on burst time
	for (int i = 0;i<no_of_processes;i++)
	{
		if (np.burst_time < p[i].burst_time && np.arr_time <= cur_time && np.completed == 0)
		{
			np.wait_time = cur_time - np.arr_time;
			avg_wt_time += np.wait_time;
			cur_time += np.burst_time;
			np.completed = 1;
			switch_count++;
			next = i;
		}
		p[i].wait_time = cur_time;
		//p[i].ter_time = cur_time + p[i].burst_time;
		avg_wt_time += p[i].wait_time;
		p[i].completed = 1;
		cur_time += p[i].burst_time;
		switch_count++;
	}
	avg_wt_time /= (no_of_processes + 1);
	switch_count -= 1;

	cout << "\n\nWaiting time for each process, in order of execution:\n";
	cout << "Process | Wait Time\n" << "-------------------\n";
	for (int i = 0;i<no_of_processes;i++)
	{
		if(i==next) cout << np.index << "(New)\t\t" << np.wait_time << "\n";
		cout << p[i].index << "\t\t" << p[i].wait_time << "\n";
	}
	cout << "Average waiting time for the system is: " << avg_wt_time;
	cout << "\nTotal no. of switches is: " << switch_count;
}

void sjf_p()
{
	process p[100];
	int no_of_processes, switch_count = 0;
	float avg_wt_time = 0, cur_time = 0;
	cout << "\nEnter the no. of processes: ";
	cin >> no_of_processes;
	int new_process = 0;
	process np;
	for (int i = 0;i<no_of_processes;i++)
	{
		cout << "\nProcess " << i << ":";
		p[i].index = i;
		//cout << "\n\tArrival time: ";
		//cin >> p[i].arr_time;
		p[i].arr_time = 0;
		cout << "\n\tBurst time: ";
		cin >> p[i].burst_time;
		p[i].rem_burst_time = p[i].burst_time;
		p[i].completed = 0;
	}
	cout << "\nNew Process " << no_of_processes << ":";
	np.index = no_of_processes;
	cout << "\n\tArrival time: ";
	cin >> np.arr_time;
	cout << "\n\tBurst time: ";
	cin >> np.burst_time;
	np.completed = 0;
	int next = -1;
	sort(p, 'B', no_of_processes);       //sort based on burst time
	for (int i = 0;i<no_of_processes;i++)
	{
		p[i].wait_time = cur_time;
		avg_wt_time += p[i].wait_time;
		while (p[i].completed != 1)
		{
			if (np.burst_time < p[i].rem_burst_time && np.arr_time <= cur_time && np.completed == 0)
			{
				if (p[i].rem_burst_time < p[i].burst_time) switch_count++;
				np.wait_time = cur_time - np.arr_time;
				avg_wt_time += np.wait_time;
				p[i].wait_time += np.burst_time;	//For extra wait by p[i]
				avg_wt_time += np.burst_time;	//For extra wait by p[i]
				cur_time += np.burst_time;
				np.completed = 1;
				switch_count++;
				next = i;
			}
			cur_time++;
			p[i].rem_burst_time--;
			if(p[i].rem_burst_time == 0) p[i].completed = 1;
		}
		switch_count++;
	}
	avg_wt_time /= (no_of_processes + 1);
	switch_count -= 1;

	cout << "\n\nWaiting time for each process, in order of execution completion:\n";
	cout << "Process | Wait Time\n" << "-------------------\n";
	for (int i = 0;i<no_of_processes;i++)
	{
		if (i == next) cout << np.index << "(New)\t\t" << np.wait_time << "\n";
		cout << p[i].index << "\t\t" << p[i].wait_time << "\n";
	}
	cout << "Average waiting time for the system is: " << avg_wt_time;
	cout << "\nTotal no. of switches is: " << switch_count;
}

/*

void sjf_p()
{
	process p[100];
	int no_of_processes, switch_count = 0, completed_processes = 0;
	float avg_wt_time = 0, cur_time = 0;
	int new_process = 0;
	process np;
	cout << "\nEnter the no. of processes: ";
	cin >> no_of_processes;
	for (int i = 0;i<no_of_processes;i++)
	{
		cout << "\nProcess " << i << ":";
		p[i].index = i;
		cout << "\n\tArrival time: ";
		cin >> p[i].arr_time;
		cout << "\n\tBurst time: ";
		cin >> p[i].burst_time;
		p[i].completed = 0;
		p[i].                                                                                      /// HeRE
	}
	//sort(p, 'b', no_of_processes);       //sort based on arrival time
	while (completed_processes < no_of_processes)
	{
		float sj_burst = 99999999;
		int sj_index = -1;
		int sj_found = 0;
		for (int i = 0;i<no_of_processes;i++)
		{
			if ((p[i].arr_time < cur_time) && (minimum(p[i].burst_time, p[i].rem_burst_time) < sj_burst) && (p[i].complete != 1))
			{
				sj_index = i;
				sj_found = 1;
			}
			if (sj_found != 1)
			{
				cur_time++;
			}
		}
		int j = sj_index;
		while (p[j].rem_burst_time != 0)
		{
			if ((new_process == 1) && (np.burst_time < p[j].rem_burst_time))
			{
				p[j].stop_time = cur_time;
				break;
			}
			else
			{
				if (p[j].burst_time == p[j].rem_burst_time)
				{
					p[j].wait_time = cur_time - p[j].arr_time;
					p[j].ter_time = cur_time + p[j].burst_time;
					avg_wt_time += p[j].wait_time;
					p[i].completed = 1;
					cur_time += p[i].burst_time;
					switch_count++;
				}
			}
		}
		avg_wt_time /= no_of_processes;
		switch_count -= 1;
		cout << "\n\nWaiting time for each process, in order of execution:\n";
		cout << "Process | Wait Time\n" << "-------------------\n";
		for (int i = 0;i<no_of_processes;i++)
		{
			cout << p[i].index << "\t\t" << p[i].wait_time << "\n";
		}
		cout << "Average waiting time for the system is: " << avg_wt_time;
		cout << "\nTotal no. of switches is: " << switch_count;
	}
*/

void roundrobin()
{
	process p[100];
	int no_of_processes, switch_count = 0, quanta, cur_time = 0;
	int completed_count = 0;
	float avg_wt_time = 0;
	cout << "\nEnter the time quanta: ";
	cin >> quanta;
	cout << "\nEnter the no. of processes: ";
	cin >> no_of_processes;

	for (int i = 0;i<no_of_processes;i++)
	{
		cout << "\nProcess " << i << ":";
		p[i].index = i;
		cout << "\n\tArrival time: ";
		cin >> p[i].arr_time;
		cout << "\n\tBurst time: ";
		cin >> p[i].burst_time;
		p[i].completed = 0;
		p[i].stop_time = p[i].arr_time;
		p[i].wait_time = 0;
		p[i].rem_burst_time = p[i].burst_time;
	}
	sort(p, 'a', no_of_processes);       //sort based on arrival time
	int stopper = 0;
	while (completed_count < no_of_processes) {
		for (int i = 0;i < no_of_processes && stopper == 0;i++)
		{
			if (p[i].arr_time <= cur_time)
			{
				if (p[i].stop_time == p[i].arr_time) p[i].completed = 1;
				if (p[i].completed != 2)
				{
					p[i].wait_time += cur_time - p[i].stop_time;
					if (p[i].rem_burst_time <= quanta)
					{
						cur_time += p[i].rem_burst_time;
						p[i].rem_burst_time = 0;
						p[i].completed = 2;
						completed_count++;
						if (completed_count == no_of_processes) {
							stopper = 1;
							break;
						}
					}
					else {
						cur_time += quanta;
						p[i].rem_burst_time -= quanta;
					}
					p[i].stop_time = cur_time;
					switch_count++;
				}
			}
		}
	}
	//avg_wt_time /= no_of_processes;
	//switch_count -= 1;
	cout << "\n\nWaiting time for each process, in order of execution beginning:\n";
	cout << "Process | Wait Time\n" << "-------------------\n";
	for (int i = 0;i<no_of_processes;i++)
	{
		cout << p[i].index << "\t\t" << p[i].wait_time << "\n";
		avg_wt_time += p[i].wait_time;
	}
	cout << "Average waiting time for the system is: " << avg_wt_time/no_of_processes;
	cout << "\nTotal no. of switches is: " << switch_count;
}

int main()
{
	int opt, repeat = 1;
	while (repeat)
	{
		cout << "\n\n\t\t\tMENU\n\t1. First Come First Serve\n\t2. Shortest Job First (Pre-emptive)\n\t3. Shortest Job First (Non Pre-emptive)\n\t4. Round Robin\n\t5. Exit\n\t\tChoose option... ";
		cin >> opt;
		switch (opt)
		{
		case 1: fcfs();
			break;
		case 2: sjf_p();
			break;
		case 3: sjf_np();
			break;
		case 4: roundrobin();
			break;
		case 5: repeat = 0;
			break;
		default: repeat = 0;
		}
	}
	return 0;
}
