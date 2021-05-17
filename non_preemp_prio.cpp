#include <iostream>
#include <algorithm>
#include <iterator>
#include <iomanip>


using namespace std;
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

bool exists(int x, int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (x == arr[i])
			return true;
		else
			return false;
	}
	return false;
}

int key_value(int x, int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (x == arr[i])
			return i;
		else
			return 0;
	}
	return 0;
}

void gantt_chart(Process *P, int length)
{
	int arrSize = sizeof(P) / sizeof(P[0]);
	int completions[arrSize];
	int midPoints[arrSize];

	for (int i = 0; i < arrSize; i++)
	{
		if (P[i].getCompletion())
			completions[i] = P[i].getCompletion();
	}
	for (int i = 0; i < arrSize; i++)
	{
		if (P[i].getCompletion())
			midPoints[i] = P[i].getCompletion() / 2;
	}

	// Top Part
	for (int i = 0; i < length; i++)
	{
		if (i == 0 || exists(i, completions, arrSize))
			cout << "+";
		else
			cout << "-";
	}
	cout << endl;
	for (int i = 0; i < length; i++)
	{
		if (i == 0 || exists(i, completions, arrSize))
			cout << "|";
		else if (exists(i, midPoints, arrSize))
			cout << "P" << key_value(i, midPoints, arrSize);
		else
			cout << " ";
	}
	cout << endl;
	for (int i = 0; i < length; i++)
	{
		if (i == 0 || exists(i, completions, arrSize))
			cout << "+";
		else
			cout << "-";
	}
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

void bubbleSort(Process arr[], int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++)

		for (j = 0; j < n - i - 1; j++)
			if (arr[j].getPriority() > arr[j + 1].getPriority())
				swap(&arr[j], &arr[j + 1]);
}

void process_name(int i ){
	cout<<"Process"<<i+1;
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
		cout << "Priority of Process " << i + 1 << " :";
		cin >> priority;
		P[i].setPriority(priority);
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
		totalWaiting = P[i].getWaiting();
	}
	avgTurnaround = totalTurnaround / size;
	avgWaiting = totalWaiting / size;

	cout << endl;
	cout << "No. of Process :" << size << endl;
	cout << "Total Turnaround Time :" << totalTurnaround << endl;
	cout << "Average Turnaround Time :" << avgTurnaround << endl;
	cout << "Total Waiting Time :" << totalWaiting << endl;
	cout << "Average Waiting Time :" << avgWaiting << endl;

	cout << "|"
		 << "Process" << setw(10) << "|" << setw(10) << "Burst Time" << setw(10) << "|" << setw(10) << "Arrival Time" << setw(10) << "|" << setw(10) << "Priority" << setw(10) << "|" << setw(10) << "Turnaround Time" << setw(10) << "|" << setw(10) << "Waiting Time" << setw(10) << "   |" << setw(10) << "Completion Time"
		 << "   |  " << endl;
	for (int i = 0; i < size; i++)
	{

		cout << "|"
			 <<"Process"<<i+1<< setw(10) << "" << setw(10) << P[i].getBurst() << setw(10) << "\t" << setw(10) << P[i].getArrival() << setw(10) << "\t" << setw(10) << P[i].getPriority() << setw(10) << "\t" << setw(10) << P[i].getTurnaround() << setw(10) << "\t" << setw(10) << P[i].getWaiting() << setw(5) <<"\t" << setw(10) << P[i].getCompletion()
			 << "   |   " << endl;
	}

	// gantt_chart(P, size);
}