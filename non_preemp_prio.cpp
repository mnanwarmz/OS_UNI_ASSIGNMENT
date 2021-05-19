#include <iostream>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include<windows.h>
#include<cmath>

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

bool exists(int x, int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (x == arr[i])
			return true;
	}
	return false;
}

int key_value(int x, int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (x == arr[i])
			return i;
	}
	return 0;
}
// void table (int size[], int burst[], int arrival[], int completion[],int priotity[], float totalTurnaround[],float totalWaiting[])
//  {
// 	cout<<endl<<"Results";
// 	printTableHorz(TL, TM, TR);
// 	cout<<endl<<VERT<<"			"<<VERT<<"PROCES"<<VERT<<"BURST TIME"<<VERT<<"ARRIVAL TIME"<<VERT<<"PRIORITY"<<VERT<<"TURNAROUND TIME"<<VERT<<"WAITING TIME"<<VERT<<"COMPLETION TIME";
// 	for (int i = 0; i < size; i++)
// 	{
// 		printTableHorz(VR, VH, VL);
// 		cout<<left;
// 		cout<<endl<<VERT<<" P"<<setw(7)<<i<<VERT<<" "<<setw(13)<<burst[i]<<VERT<<" "<<setw(11)<<arrival[i]<<VERT<<" "<<setw(9)<<priority[i]<<VERT<<" "<<setw(15)<<totalTurnaround[i]<<VERT<<" "<<setw(16)<<[i]<<VERT<<" "<<setw(13)<<totalWaiting[i]<<VERT<<setprecision(5)<<" "<<setw(21)<<completion[i]<<VERT;
// 	}


// }
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
// void gantt_chart(Process *P, int length)
// {
// 	int arrSize = sizeof(P) / sizeof(P[0]);
// 	int completions[arrSize];
// 	int midPoints[arrSize];

// 	for (int i = 0; i < arrSize; i++)
// 	{
// 		if (P[i].getCompletion())
// 			completions[i] = P[i].getCompletion();
// 	}
// 	for (int i = 0; i < arrSize; i++)
// 	{
// 		if (P[i].getCompletion())
// 			midPoints[i] = P[i].getCompletion() / 2;
// 	}

// 	// Top Part
// 	for (int i = 0; i < length; i++)
// 	{
// 		if (i == 0 || exists(i, completions, arrSize))
// 			cout << "+";
// 		else
// 			cout << "-";
// 	}
// 	cout << endl;
// 	for (int i = 0; i < length; i++)
// 	{
// 		if (i == 0 || exists(i, completions, arrSize))
// 			cout << "|";
// 		else if (exists(i, midPoints, arrSize))
// 			cout << "P" << key_value(i, midPoints, arrSize);
// 		else
// 			cout << " ";
// 	}
// 	cout << endl;
// 	for (int i = 0; i < length; i++)
// 	{
// 		if (i == 0 || exists(i, completions, arrSize))
// 			cout << "+";
// 		else
// 			cout << "-";
// 	}
// }
void printGanttChart( int completions[],int midPoints[],int length)
{
	cout<<endl<<endl<<"Gantt Chart: "<<endl;
	cout<<TL;
	for(int i = 0; i < midPoints; i++)
	{
<<<<<<< HEAD
		for(int x = 0; x < 6; x++)
			cout<<HORZ;
		if(i+1 != midPoints)
			cout<<TM;
=======
		if (i == 0 || exists(i, completions, arrSize))
			cout << "+";
		cout << "-";
>>>>>>> b706d4f6cdf523e2a3ddbe7a51f35802a1b8211f
	}
	cout<<TR<<endl;
	for(int i = 0; i < midPoints; i++)
	{
		cout<<VERT;
		if(length[i] != -1)
			cout<<"  P"<<midPoints[i]<<"  ";
		else
			cout<<"  XX  ";
	}
	cout<<VERT<<endl<<BL;
	for(int i = 0; i < midPoints; i++)
	{
		for(int x = 0; x < 6; x++)
			cout<<HORZ;
		if(i+1 != midPoints)
			cout<<BM;
	}
	cout<<BR;
	cout<<endl<<"0";
	for(int i = 0; i < midPoints; i++)
			cout<<setw(7)<<completions[i];
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

void process_name(int i)
{
	cout << "Process" << i + 1;
}
int main()
{
		//rezie the window
	HWND console = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);
	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 1100, 500, TRUE);

	int size;
	int arrival;
	int priority;
	int burst;
	int completion = 0;
	float totalTurnaround = 0;
	float totalWaiting = 0;
	float avgTurnaround = 0;
	float avgWaiting = 0;
	// void table (int size[], int burst[], int arrival[], int completion[],int priotity[], float totalTurnaround[],float totalWaiting[]);
	void printGanttChart(int length, int completions[],int midPoints[]);

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
		 << " Process" << setw(10) << "|" << setw(10) << " Burst Time" << setw(10) << "|" << setw(10) << " Arrival Time" << setw(10) << "|" << setw(10) << " Priority" << setw(10) << "|" << setw(10) << " Turnaround Time" << setw(10) << "|" << setw(20) << "Waiting Time" << setw(10) << "   |" << setw(15) << " Completion Time"
		 << "   |  " << endl;
	for (int i = 0; i < size; i++)
	{

		cout << "|"
<<<<<<< HEAD
			 <<" Process"<<i+1<< setw(10) << "" << setw(10) << P[i].getBurst() << setw(10) << "\t" << setw(10) << P[i].getArrival() << setw(10) << "\t" << setw(10) << P[i].getPriority() << setw(10) << "\t" << setw(10) << P[i].getTurnaround() << setw(10) << "\t" << setw(10) << P[i].getWaiting() << setw(10) <<"\t" << setw(15) << P[i].getCompletion()
			 << "" << endl;
=======
			 << "Process" << i + 1 << setw(10) << "|" << setw(5) << P[i].getBurst() << setw(5) << "|" << setw(5) << P[i].getArrival() << setw(5) << "|" << setw(5) << P[i].getPriority() << setw(5) << "   |   " << setw(5) << P[i].getTurnaround() << setw(5) << "   |   " << setw(5) << P[i].getWaiting() << setw(5) << "	|	" << setw(5) << P[i].getCompletion()
			 << "   |  " << endl;
>>>>>>> b706d4f6cdf523e2a3ddbe7a51f35802a1b8211f
	}
	printGanttChart(length,completions,midPoints);

<<<<<<< HEAD
=======
	gantt_chart(P, completion);
>>>>>>> b706d4f6cdf523e2a3ddbe7a51f35802a1b8211f
}