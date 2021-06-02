#ifndef UTILITY_H
#define UTILITY_H

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

void calculate(float avgWait[], float wCount[], float avg[], float sum[], int tJobs, int turnAround[], int finish[], float arrive[], int waiting[], float burst[])
{
	for(int i = 0; i < tJobs; i++)
	{
		turnAround[i] = finish[i] - arrive[i];
		sum[0] += turnAround[i];
		waiting[i] = turnAround[i] - burst[i];
		sum[1] += waiting[i];
		avgWait[i] = waiting[i] / wCount[i];
		if(wCount[i] == 0)
			avgWait[i] = 0;
	}
	avg[0] = sum[0] / tJobs;
	avg[1] = sum[1] / tJobs;
}

void printTable(float avgWait[], float wCount[], float avg[], float sum[], int tJobs, int turnAround[], int finish[], float arrive[], int waiting[], float burst[], float priority[])
{
	cout<<endl<<"Table: ";
	calculate(avgWait, wCount, avg, sum, tJobs, turnAround, finish, arrive, waiting, burst);
	printTableHorz(TL, TM, TR);
	cout<<endl<<VERT<<"         "<<VERT<<" Arrival Time "<<VERT<<" Burst Time "<<VERT<<" Priority "<<VERT<<" Finishing Time "<<VERT<<" Turnaround Time "<<VERT<<" Waiting Time "<<VERT<<" Average Waiting Time "<<VERT;
	for(int i = 0; i < tJobs; i++)
	{
		printTableHorz(VR, VH, VL);
		cout<<left;
		cout<<endl<<VERT<<" P"<<setw(7)<<i<<VERT<<" "<<setw(13)<<arrive[i]<<VERT<<" "<<setw(11)<<burst[i]<<VERT<<" "<<setw(9)<<priority[i]<<VERT<<" "<<setw(15)<<finish[i]<<VERT<<" "<<setw(16)<<turnAround[i]<<VERT<<" "<<setw(13)<<waiting[i]<<VERT<<setprecision(5)<<" "<<setw(21)<<avgWait[i]<<VERT;
	}
	printTableHorz(VR, VH, VL);
	cout<<endl<<VERT<<" Total   "<<VERT<<setw(15)<<right<<VERT<<setw(13)<<VERT<<setw(11)<<VERT<<setw(17)<<VERT<<" "<<setw(16)<<left<<sum[0]<<VERT<<" "<<setw(13)<<sum[1]<<VERT<<setw(23)<<right<<VERT;
	printTableHorz(VR, VH, VL);
	cout<<endl<<VERT<<setprecision(5)<<" Average "<<VERT<<setw(15)<<VERT<<setw(13)<<VERT<<setw(11)<<VERT<<setw(17)<<VERT<<" "<<setw(16)<<left<<avg[0]<<VERT<<" "<<setw(13)<<avg[1]<<VERT<<setw(23)<<right<<VERT;
	printTableHorz(BL, BM, BR);
}
#endif