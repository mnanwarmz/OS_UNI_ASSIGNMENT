#include	<iostream>
#include	<algorithm>
#include 	<iterator>
#include 	<iomanip>
#include 	<queue>
#include	"Process.cpp"
#include	"table.cpp"

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

void printTableHorz(char P1, char P2, char P3)
{
	int length[8] = {9, 14, 12, 10, 16, 17, 14};

	cout<<endl<<P1;
	for(int i = 0; i < 7; i++)
	{
		for(int x = 0; x < length[i]; x++)
			cout<<HORZ;
		if(i != 6)
			cout<<P2;
		else
			cout<<P3;
	}
}

void printTable( float avg[], float sum[], int tJobs, Process P[])
{
	cout<<endl<<"Table: ";
	printTableHorz(TL, TM, TR);
	cout<<endl<<VERT<<"         "<<VERT<<" Arrival Time "<<VERT<<" Burst Time "<<VERT<<" Priority "<<VERT<<" Finishing Time "<<VERT<<" Turnaround Time "<<VERT<<" Waiting Time "<<VERT;
	for(int i = 0; i < tJobs; i++)
	{
		printTableHorz(VR, VH, VL);
		cout<<left;
		cout<<endl<<VERT<<" P"<<setw(7)<<P[i].getName()<<VERT<<" "<<setw(13)<<P[i].getArrival()<<VERT<<" "<<setw(11)<<P[i].getBurst()<<VERT<<" "<<setw(9)<<P[i].getPriority()<<VERT<<" "<<setw(15)<<P[i].getCompletion()<<VERT<<" "<<setw(16)<<P[i].getTurnaround()<<VERT<<" "<<setw(13)<<P[i].getWaiting()<<VERT;
	}
	printTableHorz(VR, VH, VL);
	cout<<endl<<VERT<<" Total   "<<VERT<<setw(15)<<right<<VERT<<setw(13)<<VERT<<setw(11)<<VERT<<setw(17)<<VERT<<" "<<setw(16)<<left<<sum[0]<<VERT<<" "<<setw(13)<<sum[1]<<VERT;
	printTableHorz(VR, VH, VL);
	cout<<endl<<VERT<<" Average "<<VERT<<setw(15)<<right<<VERT<<setw(13)<<VERT<<setw(11)<<VERT<<setw(17)<<VERT<<" "<<setw(16)<<left<<avg[0]<<VERT<<" "<<setw(13)<<avg[1]<<right<<VERT;
	printTableHorz(BL, BM, BR);
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
		P[i].setName(i);
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

	// return 0;
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