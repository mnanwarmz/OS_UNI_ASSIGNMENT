#include <iostream>

class Process
{
	private:
		int name;
		int burst;
		int arrival;
		int priority;
		int completion;
		int waiting;
		int turnaround;
	public:
		int	getBurst()
		{
			return burst;
		}
		int	getArrival()
		{
			return arrival;
		}
		int	getPriority()
		{
			return priority;
		}
		int	getName()
		{
			return name;
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
			waiting = turnaround - burst;
			return waiting;
		}
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
		void setName(int name)
		{
			this->name = name;
		}
};

