#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <time.h> 
#include <cstdlib>


using namespace std;

int SetSize=10; //Size of element
int Set[10] = {}; //Size of element
//int *Set;
int FirstSet[10] = {}; //Size of element
int SecondSet[10] = {}; //Size of element

int max = 50; //maximum number
int min = 1; //minimum number

int generate_random_set_yes(); //random generate number with garanteed solution
int generate_random_set(); //random generate number without garanteed solution
bool dynamic_programming(int set[], int n, int sum);
int best_fit();

int main()
{
	while (generate_random_set_yes() == 99)//eliminate possibility of having sum that is odd
	{
		while (Set[10] == 0)
		{
			generate_random_set_yes();
		}		
	}

	cout << "The element in set are" << endl;

	for (int j = 0; j < SetSize; j++)
	{
		cout << Set[j] << endl;
	}

	best_fit();
	return 0;
}

int generate_random_set_yes()
{
	int total = 0;
	srand(time(NULL));
	for (int i = 0; i < SetSize - 1; i++) //reserve 1 number for second set
	{

		int result = rand() % (max - min + 1) + min; //generate random between max and min
		//cout << result << endl;
		Set[i] = result;
		total = total + result;
	}
	if (total % 2 == 1)
	{
		return 99;//eliminate possibility of having sum that is odd		
	}
	int half = total / 2;
	int arrcounter = 0;
	int firstsum = 0, secondsum = 0;

	//one by one insert an element into the first array until the sum exceed the half of total sum
	while (half > 0)
	{
		FirstSet[arrcounter] = Set[arrcounter];
		half = half - Set[arrcounter];
		firstsum = firstsum + Set[arrcounter];
		arrcounter++;
	}

	//insert the remaining into the second array and calculate the sum
	int secondcounter = 0;
	while (arrcounter < SetSize-1)
	{
		SecondSet[secondcounter] = Set[arrcounter];
		secondsum = secondsum + Set[arrcounter];
		arrcounter++;
		secondcounter++;
	}

	//calculate the difference between sum of first array and second array
	//put the diffenrence into the second array

	if (arrcounter == SetSize)
	{		
		SecondSet[secondcounter] = firstsum - secondsum;
	}
	int index = 0;
	for (int i = 0; i < SetSize; i++)
	{
		if (FirstSet[i] != 0)
		{
			Set[i] = FirstSet[i];
			index++;
		}
		else
		{
			break;
		}
	}

	for (int j = 0; j < SetSize; j++)
	{
		if (SecondSet[j] != 0)
		{
			Set[index] = SecondSet[j];
			index++;			
		}
		else
		{
			break;
		}
	}
	
	Set[SetSize-1] = firstsum - secondsum;

	return 0;
}

int generate_random_set()
{
	int total = 0;
	srand(time(NULL));
	cout << "not guarantee solution" << endl;
	for (int i = 0; i < SetSize; i++)
	{

		int result = rand() % (max - min + 1) + min; //generate random between max and min
		cout << result << endl;
		Set[i] = result;
		total = total + result;
	}
	if (total % 2 == 1)//eliminate possibility of having sum that is odd
	{
		return 99;
	}
	return 0;
}

bool dynamic_programming(int set[], int n, int sum)
{
	// Base Cases
	if (sum == 0)
		return true;
	if (n == 0 && sum != 0)
		return false;

	// If last element is greater than sum, then ignore it
	if (set[n - 1] > sum)
		return dynamic_programming(set, n - 1, sum);

	/* else, check if sum can be obtained by any of the following
	(a) including the last element
	(b) excluding the last element   */
	return dynamic_programming(set, n - 1, sum) || dynamic_programming(set, n - 1, sum - set[n - 1]);

	//http://www.geeksforgeeks.org/dynamic-programming-subset-sum-problem/
}

int best_fit()
{
	int solution[10];//change size
	int totalsum = 0, half = 0, diff = 0, index = 0;;

	for (int i = 0; i < SetSize; i++)
	{
		totalsum = totalsum + Set[i];
	}

	half = totalsum / 2;
	cout << "The target is " << half << endl;

	int temp;

	for (int i = 0; i < SetSize; i++)
	{
		for (int j = 0; j < SetSize - 1; j++)
		{
			if (Set[j] < Set[j + 1])
			{
				//we need to swap
				temp = Set[j];
				Set[j] = Set[j + 1];
				Set[j + 1] = temp;
			}
		}
	}
	
	for (int k = 0; k < SetSize; k++)
	{
		if (half - Set[k] > -1)
		{
			half = half - Set[k];
			solution[index] = Set[k];
			index++;
		}		
	}

	cout << "Solution is:" << endl;
	for (int i = 0; i < SetSize; i++)
	{
		if (solution[i] > -1)//eliminate empty array element
		{
			cout << solution[i] << endl;
		}
	}

	return 0;
}