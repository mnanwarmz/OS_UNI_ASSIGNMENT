#include <iostream>
#include <algorithm>
#include "Process.cpp"

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

void bubbleSort(Process arr[], int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++)

		for (j = 0; j < n - i - 1; j++)
			if (arr[j].getPriority() > arr[j + 1].getPriority())
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
}