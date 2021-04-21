#include <iostream>

using namespace std;

class Process
{
private:
	int burst;
	int arrival;
	int priority;
	int turnaround;
	int completion;

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
	int getArrival(int arrival)
	{
		return arrival;
	}
	int getBurst(int burst)
	{
		return burst;
	}
	int getPriority(int priority)
	{
		return priority;
	}
	int getTurnaround()
	{
	}
};
int getNoOfProcesses()
{
	int size;

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

int main()
{
	int size;
	int arrival;
	int priority;
	int burst;

	size = getNoOfProcesses();
	Process P[size];

	// Setting details for each processes
	cout << "Define the details of each processes" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << "Arrival Time of Process " << i + 1 << endl;
		cin >> arrival;
		P[i].setArrival(arrival);
		cout << "Burst Time of Process " << i + 1 << endl;
		cin >> burst;
		P[i].setBurst(burst);
		cout << "Priority of Process " << i + 1 << endl;
		cin >> priority;
		P[i].setPriority(priority);
	}
	for (int i = 0; i < size; i++)
	{
	}

	P[0].setArrival(0);
}