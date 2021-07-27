
#include <iostream>
#include<vector>
#include<time.h>

using namespace std;

int SearchMinNonNeg(vector<int>&arr)
{
	int ptr = 0;

	// Check if 1 is present in array or not
	for (int i = 0; i < arr.size(); i++)
	{
		if (arr[i] == 1)
		{
			ptr = 1;
			break;
		}
	}

	// If 1 is not present
	if (ptr == 0)
	{
		return 1;
	}

	// Changing negative values and values > size of vector to 1
	for (int i = 0; i < arr.size(); i++)
	{
		if (arr.at(i) <= 0 || arr.at(i) > arr.size())
		{
			arr.at(i) = 1;
		}
	}

	// Updating indices according to values
	for (int i = 0; i < arr.size(); i++)
	{
		arr.at((arr.at(i) - 1) % arr.size()) += arr.size();
	}
		
	// Finding which index has value less than n
	for (int i = 0; i < arr.size(); i++)
	{
		if (arr.at(i) <= arr.size())
		{
			return i + 1;
		}
	}

	// If array has values from 1 to n
	return (arr.size() + 1);
}


void Display(const vector<int>& arr)// display vector
{
	
	for (int i = 0; i < arr.size(); i++)
	{
		cout << arr.at(i) << " ";
	}
	cout << endl;

}

//Input
int Random(const int& minN, const int& maxN)// create random value for elements
{
	return  ((rand() % (maxN - minN + 1)) + minN);
}

int main()
{
	srand(time(NULL));
	//int value = 0;
	int numberOfElement = 0;

	cout << "Enter number of elements: ";
	cin >> numberOfElement;

	if (numberOfElement < 0)
	{
		numberOfElement = 1;
	}
	vector<int>arr(numberOfElement);

	int min = 0;
	int max = 0;
	cout << "Enter range of value: "<<endl;
	cout << "min: ";
	cin >> min;
	cout << "max: ";
	cin >> max;

	if (max < min)
	{
		int temp = max;
		max = min;
		min = temp;
	} 

	for (int i = 0; i < numberOfElement; i++)
	{
		arr.at(i) = Random(min, max);
	}

	cout << "List: ";
	Display(arr);
	int output = SearchMinNonNeg(arr);

	cout <<"The smallest positive number which is not belong to array: " << output;

	return 0;
	
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
