#include <iostream>
#include <iomanip>
#include <cmath>
#include <windows.h>

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

void printTableSJF( float avg[], float sum[], int tJobs, Process P[])
{
	cout<<endl<<"Table: ";
	printTableHorz(TL, TM, TR);
	cout<<endl<<VERT<<"         "<<VERT<<" Arrival Time "<<VERT<<" Burst Time "<<VERT<<" Priority "<<VERT<<" Finishing Time "<<VERT<<" Turnaround Time "<<VERT<<" Waiting Time "<<VERT;
	for(int i = 0; i < tJobs; i++)
	{
		printTableHorz(VR, VH, VL);
		cout<<left;
		cout<<endl<<VERT<<" P"<<setw(7)<<P[i].getName()<<VERT<<" "<<setw(13)<<P[i].getArrival()<<VERT<<" "<<setw(11)<<P[i].getBurst()<<VERT<<" "<<setw(9)<<"-"<<VERT<<" "<<setw(15)<<P[i].getCompletion()<<VERT<<" "<<setw(16)<<P[i].getTurnaround()<<VERT<<" "<<setw(13)<<P[i].getWaiting()<<VERT;
	}
	printTableHorz(VR, VH, VL);
	cout<<endl<<VERT<<" Total   "<<VERT<<setw(15)<<right<<VERT<<setw(13)<<VERT<<setw(11)<<VERT<<setw(17)<<VERT<<" "<<setw(16)<<left<<sum[0]<<VERT<<" "<<setw(13)<<sum[1]<<VERT;
	printTableHorz(VR, VH, VL);
	cout<<endl<<VERT<<" Average "<<VERT<<setw(15)<<right<<VERT<<setw(13)<<VERT<<setw(11)<<VERT<<setw(17)<<VERT<<" "<<setw(16)<<left<<avg[0]<<VERT<<" "<<setw(13)<<avg[1]<<right<<VERT;
	printTableHorz(BL, BM, BR);
}