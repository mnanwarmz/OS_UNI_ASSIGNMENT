#include <iostream>
#include <iomanip>
#include <cmath>
#include <windows.h>
using namespace std;

const char HORZ = 196;
const char VERT = 179;
const char TL   = 218;
const char TM   = 194;
const char TR   = 191;
const char BL   = 192;
const char BM   = 193;           
const char BR   = 217;
const char VH   = 197;
const char VR   = 195;
const char VL   = 180;

int main()
{
	//rezie the window
	HWND console = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);
	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 1100, 500, TRUE);
   
	int tJobs, choice, quantum, change, total;
	int arrived = 0, done = 0, time = 0, count = 0, z = 0;
	int *order, *clock;
	float temp;
	void printTable(float avgWait[], float wCount[], float avg[], float sum[], int tJobs, int turnAround[], int finish[], float arrive[], int waiting[], float burst[], float priority[]);
	void printGanttChart(int count, int order[], int clock[]);
	void sort(int start, int end, float type[], float aTime[], float jTime[], int name[], float priority[]);
	
	do{
		cout<<"Enter the amount of processes: ";
		cin>>tJobs;
		
		if(tJobs < 3 || tJobs > 10)
			cout<<"Please enter between 3 to 10 processes."<<endl;

	}while(tJobs < 3 || tJobs > 10);
	
	int name[tJobs], finish[tJobs], turnAround[tJobs], waiting[tJobs];
	float sum[2] = {0}, avg[2] = {0}, wCount[tJobs] = {0}, avgWait[tJobs] = {0}, blank[tJobs] = {0};
	float aTime[tJobs], jTime[tJobs], arrive[tJobs], burst[tJobs], priority[tJobs];
	
	cout<<endl<<"Select Scheduling Algoriths: "<<endl;
	cout<<"[1] Round Robin"<<endl;
	cout<<"[2] Non Preemptive Priority"<<endl;
	cout<<"[3] Non Preemptive SJF"<<endl;
	cout<<"Enter choice: ";
	cin>>choice;
	
	if(choice == 2)
		cout<<endl<<"Enter burst time, arrival time and priority for each process: "<<endl;
	else
		cout<<endl<<"Enter burst time and arrival time for each process: "<<endl;
		
	for(int i = 0; i < tJobs; i++)
	{
		cout<<endl<<"Process "<<i<<": "<<endl;
		cout<<"Burst time: ";
		cin>>jTime[i];
		cout<<"Arrival Time: ";
		cin>>aTime[i];
		if(choice == 2)
		{
			cout<<"Priority: ";
			cin>>priority[i];
		}
		name[i] = i;
	}
	
	for(int i = 0; i < tJobs; i++)
	{
		burst[i] = jTime[i];
		arrive[i] = aTime[i];
	}
	
	switch (choice)
	{
		//case 1 start
		case 1:
			cout<<"Enter Time Quantum: ";
			cin>>quantum;

			sort(0, tJobs, aTime, aTime, jTime, name, blank);
			
			for(int i = 0; i < tJobs; i++)
			{
				count += ceil(jTime[i] / quantum);
				time += jTime[i];
			}
			
			time = 0;
			for(int i = 0; i < tJobs; i++)
			{
				if(time >= aTime[i])
					time += jTime[i];
				else
				{
					time += quantum;
					count++;
					i--;
				}
			}
			
			order = new int[count];
			clock = new int[count];
			
			time = 0;
			do
			{
				total = 0; //reset total
				change = 0; //reset change
				if(aTime[0] <= time) //check if arrived 
				{
					if((jTime[0]-quantum) > 0) 
					{ 
						time += quantum;
						jTime[0] = jTime[0] - quantum;
						change = 1;
					}
					else if((jTime[0]-quantum) <= 0 && jTime[0] != 0)
					{
						time += jTime[0];
						jTime[0] = jTime[0] - jTime[0];
						change = 1;
						finish[name[0]] = time;
					}	
					
					if(change == 1)
					{	
						order[z] = name[0];
						clock[z] = time;
						z++;
						for(int x = 1; x < tJobs; x++)				
						{
							if(aTime[x] < time && jTime[x] != 0)
								wCount[name[x]]++;
						}
						
						if(jTime[0] > 0)
							aTime[0] = time;
						else
							aTime[0] = 0;	
					}
					
					if(jTime[0] == 0) //check if burst time == 0
					{
						for(int x=0; x < tJobs; x++) 
						{
							if(x+1 != tJobs) //move processes forward 
							{
								temp = name[x];
								jTime[x] = jTime[x+1];
								aTime[x] = aTime[x+1];
								name[x] = name[x+1];
								name[x+1] = temp;
							}
							else
							{
								name[x] = temp;
								jTime[x] = 0;
								aTime[x] = 0;
							}
						}
					}
					else
						for(int x = 0; x < tJobs; x++) //move first process to the correct position in queue
						{
							if(x+1 != tJobs)
							{
								if(aTime[x+1] <= aTime[x])
								{
									temp = aTime[x];
									aTime[x] = aTime[x+1];
									aTime[x+1] = temp;
									temp = jTime[x];
									jTime[x] = jTime[x+1];
									jTime[x+1] = temp;
									temp = name[x];
									name[x] = name[x+1];
									name[x+1] = temp;
								}
							}
						}
				}
				else //skip time if no process arrived
				{	
					time += quantum;
					order[z] = -1;
					clock[z] = time;
					z++;
				}
				
				for(int i=0; i < tJobs; i++)
					total += jTime[i];
				
			}while(total > 0);
				
			printTable(avgWait, wCount, avg, sum, tJobs, turnAround, finish, arrive, waiting, burst, blank);
			printGanttChart(count, order, clock);
			break;
			//case 1 end
			
		//case 2 start
		case 2:
			sort(0, tJobs, aTime, aTime, jTime, name, priority);
			count = tJobs;	
			
			if(aTime[0] != 0)
				count++;
			
			time = aTime[0];
			for(int i = 0; i < tJobs; i++)
			{
				if(time >= aTime[i])
					time += jTime[i];
				else
					count++;		
			}
			
			order = new int[count];
			clock = new int[count];
			
			time = 0;			
			for(int y = arrived; y < tJobs; y++) //count how many arrived
			{
				if(aTime[y] <= time && jTime[y] != 0)
					arrived++;
			}
			sort(0, tJobs, priority, aTime, jTime, name, priority);
			for(int i = 0; i < tJobs ; i++)
			{
				if(time < aTime[i])
				{
					time = aTime[i];
					wCount[name[i]]++;
					order[z] = -1;
					clock[z] = time;
					z++;
				}
				
				time += jTime[i];
				jTime[i] -= jTime[i];
				finish[name[i]] = time;
				done++;
				order[z] = name[i];
				clock[z] = time;
				z++;
				
				for(int y = arrived; y < tJobs; y++) //count how many arrived
				{
					if(aTime[y] <= time && jTime[y] != 0)
						arrived++;
				}

				for(int x = 0; x < tJobs; x++)
				{
					if(aTime[x] < time && jTime[x] != 0)
						wCount[name[x]]++;	
				}

				sort(done, arrived, priority, aTime, jTime, name, priority);
			}
			printTable(avgWait, wCount, avg, sum, tJobs, turnAround, finish, arrive, waiting, burst, priority);	
			printGanttChart(count, order, clock);
			break;
			//case 2 end
			
		//case 3 start
		case 3:
			time = 0;
			count = tJobs;
			
			if(aTime[0] != 0)
				count++;
			
			time = aTime[0];
			for(int i = 0; i < tJobs; i++)
			{
				if(time >= aTime[i])
					time += jTime[i];
				else
					count++;		
			}
			
			order = new int[count];
			clock = new int[count];
			
			time = 0;
			sort(0, tJobs, aTime, aTime, jTime, name, blank);
			for(int i = arrived; i < tJobs; i++) //count how many arrived
			{
				if(aTime[i] <= time && jTime[i] != 0)
					arrived++;
			}
			sort(0, arrived, jTime, aTime, jTime, name, blank);
			for(int i = 0; i < tJobs ; i++)
			{
				if(time < aTime[i])
				{
					time = aTime[i];
					wCount[name[i]]++;
					order[z] = -1;
					clock[z] = time;
					z++;
				}
				
				time += jTime[i];
				jTime[i] -= jTime[i];
				finish[name[i]] = time;
				done++;	
				order[z] = name[i];
				clock[z] = time;
				z++;
				
				for(int y = arrived; y < tJobs; y++) //count how many arrived
				{
					if(aTime[y] <= time)
						arrived++;
				}
				
				for(int x = 0; x < tJobs; x++)
				{
					if(aTime[x] < time && jTime[x] != 0)
						wCount[name[x]]++;
				}
				
				sort(done, arrived, jTime, aTime, jTime, name, blank);
			}
			printTable(avgWait, wCount, avg, sum, tJobs, turnAround, finish, arrive, waiting, burst, blank);
			printGanttChart(count, order, clock);
			break;
			//case 3 end
	}
	return 0;
}

void sort(int start, int end, float type[], float aTime[], float jTime[], int name[], float priority[])
{
	float temp;
	for(int x = start; x < end; x++)
	{
		for(int y = x+1; y < end; y++)
		{
			if(type[y] < type[x])
			{
				temp = aTime[x];
				aTime[x] = aTime[y];
				aTime[y] = temp;
				temp = jTime[x];
				jTime[x] = jTime[y];
				jTime[y] = temp;
				temp = name[x];
				name[x] = name[y];
				name[y] = temp;
				temp = priority[x];
				priority[x] = priority[y];
				priority[y] = temp;
			}
		}
	}
}

void printGanttChart(int count, int order[], int clock[])
{
	cout<<endl<<endl<<"Gantt Chart: "<<endl;
	cout<<TL;
	for(int i = 0; i < count; i++)
	{
		for(int x = 0; x < 6; x++)
			cout<<HORZ;
		if(i+1 != count)
			cout<<TM;
	}
	cout<<TR<<endl;
	for(int i = 0; i < count; i++)
	{
		cout<<VERT;
		if(order[i] != -1)
			cout<<"  P"<<order[i]<<"  ";
		else
			cout<<"  XX  ";
	}
	cout<<VERT<<endl<<BL;
	for(int i = 0; i < count; i++)
	{
		for(int x = 0; x < 6; x++)
			cout<<HORZ;
		if(i+1 != count)
			cout<<BM;
	}
	cout<<BR;
	cout<<endl<<"0";
	for(int i = 0; i < count; i++)
			cout<<setw(7)<<clock[i];
}

void calculate(float avgWait[], float wCount[], float avg[], float sum[], int tJobs, int turnAround[], int finish[], float arrive[], int waiting[], float burst[])
{
	for(int i = 0; i < tJobs; i++)
	{
		turnAround[i] = finish[i] - arrive[i];
		sum[0] += turnAround[i];
		waiting[i] = turnAround[i] - burst[i];
		sum[1] += waiting[i];
		avgWait[i] = waiting[i] / wCount[i];
		if(wCount[i] == 0)
			avgWait[i] = 0;
	}
	avg[0] = sum[0] / tJobs;
	avg[1] = sum[1] / tJobs;
}

void printTableHorz(char P1, char P2, char P3)
{
	int length[8] = {9, 14, 12, 10, 16, 17, 14, 22};
	
	cout<<endl<<P1;
	for(int i = 0; i < 8; i++)
	{
		for(int x = 0; x < length[i]; x++)
			cout<<HORZ;
		if(i != 7)
			cout<<P2;
		else
			cout<<P3;
	}
}

void printTable(float avgWait[], float wCount[], float avg[], float sum[], int tJobs, int turnAround[], int finish[], float arrive[], int waiting[], float burst[], float priority[])
{
	cout<<endl<<"Table: ";
	calculate(avgWait, wCount, avg, sum, tJobs, turnAround, finish, arrive, waiting, burst);
	printTableHorz(TL, TM, TR);
	cout<<endl<<VERT<<"         "<<VERT<<" Arrival Time "<<VERT<<" Burst Time "<<VERT<<" Priority "<<VERT<<" Finishing Time "<<VERT<<" Turnaround Time "<<VERT<<" Waiting Time "<<VERT<<" Average Waiting Time "<<VERT;
	for(int i = 0; i < tJobs; i++)
	{
		printTableHorz(VR, VH, VL);
		cout<<left;
		cout<<endl<<VERT<<" P"<<setw(7)<<i<<VERT<<" "<<setw(13)<<arrive[i]<<VERT<<" "<<setw(11)<<burst[i]<<VERT<<" "<<setw(9)<<priority[i]<<VERT<<" "<<setw(15)<<finish[i]<<VERT<<" "<<setw(16)<<turnAround[i]<<VERT<<" "<<setw(13)<<waiting[i]<<VERT<<setprecision(5)<<" "<<setw(21)<<avgWait[i]<<VERT;
	}
	printTableHorz(VR, VH, VL);
	cout<<endl<<VERT<<" Total   "<<VERT<<setw(15)<<right<<VERT<<setw(13)<<VERT<<setw(11)<<VERT<<setw(17)<<VERT<<" "<<setw(16)<<left<<sum[0]<<VERT<<" "<<setw(13)<<sum[1]<<VERT<<setw(23)<<right<<VERT;
	printTableHorz(VR, VH, VL);
	cout<<endl<<VERT<<setprecision(5)<<" Average "<<VERT<<setw(15)<<VERT<<setw(13)<<VERT<<setw(11)<<VERT<<setw(17)<<VERT<<" "<<setw(16)<<left<<avg[0]<<VERT<<" "<<setw(13)<<avg[1]<<VERT<<setw(23)<<right<<VERT;	
	printTableHorz(BL, BM, BR);
}

