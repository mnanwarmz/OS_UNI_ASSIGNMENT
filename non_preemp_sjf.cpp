#include <iostream>
#include <algorithm>

#include "utility.cpp"

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
class Process
{
private:
	int burst;
	int arrival;
	int priority;
	int turnaround;
	int completion;
	int waiting;

public:
	void setArrival(int arrival)
	{
		this->arrival = arrival;
	}
	void setBurst(int burst)
	{
		this->burst = burst;
	}
	void setPriority(int priority)
	{
		this->priority = priority;
	}
	void setCompletion(int completion)
	{
		this->completion = completion;
	}
	void setWaiting(int waiting)
	{
		this->waiting = waiting;
	}
	int getArrival()
	{
		return arrival;
	}
	int getBurst()
	{
		return burst;
	}
	int getPriority()
	{
		return priority;
	}
	int getCompletion()
	{
		return completion;
	}
	int getTurnaround()
	{
		turnaround = completion - arrival;
		return turnaround;
	}
	int getWaiting()
	{
		return waiting;
	}
};

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

// A function to implement bubble sort
void bubbleSort(Process arr[], int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++)

		for (j = 0; j < n - i - 1; j++)
			if (arr[j].getBurst() > arr[j + 1].getBurst())
				swap(&arr[j], &arr[j + 1]);
}

int main()
{
	int size;
	int arrival;
	int priority;
	int burst;
	int completion = 0;
	float totalTurnaround = 0;
	float totalWaiting = 0;
	float avgTurnaround = 0;
	float avgWaiting = 0;

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
	}
	P[0].setArrival(0);
	bubbleSort(P, size);

	for (size_t i = 0; i < size; i++)
	{
		completion += P[i].getBurst();
		P[i].setCompletion(completion);
		totalTurnaround += P[i].getTurnaround();
		if (P[i].getArrival() == 0)
			P[i].setWaiting(0);
		else
			P[i].setWaiting(P[i - 1].getCompletion());
		totalWaiting += P[i].getWaiting();
		totalTurnaround += P[i].getTurnaround();
	}
	avgWaiting = totalWaiting / size;
	avgTurnaround = totalTurnaround / size;

	printGanttChart(size,)
}