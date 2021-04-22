#include <iostream>
#include <algorithm>
#include <iterator>

#include "Process.cpp"

using namespace std;

bool exists(int x, int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (x == arr[i])
			return true;
		else
			return false;
	}
}

void gantt_chart(Process P[], int length)
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
			cout << " ";
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