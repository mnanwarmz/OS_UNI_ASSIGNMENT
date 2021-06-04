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
	int ganttSize;
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
	queue<Process> PQ;

	// Setting details for each processes
		cout << "Define the details of each processes" << endl;
		for (int i = 0; i < size; i++)
		{
			cout << "Arrival Time of Process " << i + 1 << " :";
			cin >> arrival;
			P[i].setArrival(arrival);
			cout << "Burst Time of Process " << i + 1 << " :";
			cin >> burst;
			if(algoType == 3)
				P[i].setOriginalBurst(burst);
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

		if(algoType != 3)
		{
			for(size_t i = 0; i < size; i++)
			{
				bubbleSortArrival(P, size,i);
				bubbleSortPriority(P,size,completion,i);
				completion += P[i].getBurst();
				P[i].setCompletion(completion);
				if(!(P[i + 1].getArrival() <= completion))
					break;
			}
		}

			queue<Process> PV;
		if(algoType == 3)
		{
			Process temp_array[size];
			bubbleSortArrival(P,size,0);
			completion = 0;
			int j = 0;
			do
			{
				for(int i = j; i < size ;i++)
				{
					if(P[i].getArrival() <= completion)
					{
						PQ.push(P[i]);
						j++;
					}
				}
				Process front = PQ.front();
				if(front.getBurst() > quantum)
				{
					front.setBurst(front.getBurst() - quantum);
					completion += quantum;
					PQ.push(front);
				}
				else
				{
					completion += front.getBurst();
					front.setBurst(front.getBurst() - front.getBurst());
					front.setCompletion(completion);
					cout<<front.getName()<<": "<<front.getCompletion()<< " > "
						<<completion<<endl;
					temp_array[front.getName()] = front;
				}
				PV.push(front);
				PQ.pop();
				// cout<<completion<<endl;
			}while(!PQ.empty());
			for(int i = 0; i < size;i++)
			{
				P[i] = temp_array[i];
				P[i].setBurst(P[i].getOriginalBurst());
			}
			ganttSize = PV.size();
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

	int name[ganttSize];
	int time[ganttSize];

	if(algoType != 3)
	{
		for (size_t i = 0; i < size; i++)
		{
			name[i] = P[i].getName();
			time[i] = P[i].getCompletion();
		}
	}
	else
	{
		int i = 0;
		while(!(PV.empty()))
		{
			Process front = PV.front();
			name[i] = front.getName();
			time[i] = front.getCompletion();
			PV.pop();
		}
	}

	float avg[2] = {avgTurnaround,avgWaiting};
	float total[2] = {totalTurnaround,totalWaiting};

		printTable(avg,total,size,P);
		printGanttChart(ganttSize,name,time);

}