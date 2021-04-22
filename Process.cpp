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
		completion - arrival;
	}
	int getWaiting()
	{
		return waiting;
	}
};
