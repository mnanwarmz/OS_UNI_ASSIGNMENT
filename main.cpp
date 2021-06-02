#include	<iostream>
#include	<algorithm>
#include 	<iterator>
#include 	<iomanip>
#include 	<queue>
#include	"Process.cpp"
#include	"table.cpp"

using namespace std;

int getNoOfProcesses()
{
	int size;
	int completion = 0;

	cout << "How many processes would you like: \n";
	do
	{
		cin >> size;
		if (size < 3 || size > 10)
		{
			cout << "Invalid size.\n";
			cout << "Please enter a new value.\n";
		}
	} while (size < 3 || size > 10);
	return size;
}

void swap(Process *xp, Process *yp)
{
	Process temp = *xp;
	*xp = *yp;
	*yp = temp;
}


void bubbleSortArrival(Process arr[], int n,int ea)
{
	int i, j;
	for (i = ea; i < n - 1; i++)

		for (j = ea; j < n - i - 1; j++)
			if (arr[j].getArrival() > arr[j + 1].getArrival())
				swap(&arr[j], &arr[j + 1]);
}

void bubbleSortPriority(Process arr[], int n, int completion, int ea)
{
	int i, j;
	for (i = ea; i < n - 1; i++)

		for (j = ea; j < n - i - 1; j++)
		{
			if(arr[j].getArrival() <= completion)
				if (arr[j].getPriority() > arr[j + 1].getPriority())
					swap(&arr[j], &arr[j + 1]);
		}
}

void bubbleSortBurst(Process arr[], int n, int completion, int ea)
{
	int i, j;
	for (i = ea; i < n - 1; i++)

		for (j = ea; j < n - i - 1; j++)
		{
			if(arr[j].getArrival() <= completion)
				if (arr[j].getBurst() > arr[j + 1].getBurst())
					swap(&arr[j], &arr[j + 1]);
		}
}


int main()
{
	int size;
	int arrival;
	int priority;
	int burst;
	int completion = 0;
	int algoType;
	int quantum;
	float totalTurnaround = 0;
	float totalWaiting = 0;
	float avgTurnaround = 0;
	float avgWaiting = 0;

	cout<<"What type of algorithm would you like to use?"<<endl<<endl;
	cout<<"1.Non-Preemptive SJF"<<endl;
	cout<<"2.Non-Preemptive Priority"<<endl;
	cout<<"3.Round Robin"<<endl;
	cin>>algoType;
	size = getNoOfProcesses();
	Process P[size];

	// Setting details for each processes
		cout << "Define the details of each processes" << endl;
		for (int i = 0; i < size; i++)
		{
			cout << "Arrival Time of Process " << i + 1 << " :";
			cin >> arrival;
			P[i].setArrival(arrival);
			cout << "Burst Time of Process " << i + 1 << " :";
			cin >> burst;
			P[i].setBurst(burst);
			if(algoType == 2)
			{
				cout << "Priority of Process " << i + 1 << " :";
				cin >> priority;
				P[i].setPriority(priority);
			}
			P[i].setName(i);
		}

		if(algoType == 3)
		{
			cout<< "Enter Quantum"<<endl;
			cin>>quantum;
		}

		for(size_t i = 0; i < size; i++)
		{
			bubbleSortArrival(P, size,i);
			// cout<<"ProcessA " <<P[i].getName()<<" ";
			bubbleSortPriority(P,size,completion,i);
			// cout<<"ProcessP " <<P[i].getName()<<endl;
			completion += P[i].getBurst();
			// cout<<" "<<completion<<endl;
			P[i].setCompletion(completion);
			if(!(P[i + 1].getArrival() <= completion))
				break;
		}


	for(int i = 0;i < size;i++)
	{
		totalTurnaround	+= P[i].getTurnaround();
		totalWaiting += P[i].getWaiting();
	}

	avgTurnaround = totalTurnaround / size;
	avgWaiting = totalWaiting / size;

	cout << endl;
	cout << "No. of Process :" << size << endl;
	cout << "Total Turnaround Time :" << totalTurnaround << endl;
	cout << "Average Turnaround Time :" << avgTurnaround << endl;
	cout << "Total Waiting Time :" << totalWaiting << endl;
	cout << "Average Waiting Time :" << avgWaiting << endl;

	int name[size];
	int time[size];

	for (size_t i = 0; i < size; i++)
	{
		name[i] = P[i].getName();
		time[i] = P[i].getCompletion();
	}

	float avg[2] = {avgTurnaround,avgWaiting};
	float total[2] = {totalTurnaround,totalWaiting};
		printTable(avg,total,size,P);
	printGanttChart(size,name,time);

}