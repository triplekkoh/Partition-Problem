#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>
using namespace std;

//Partition Problem is the task of deciding whether a given multiset S of positive integers
//can be partitioned into two subsets S1 and S2 
//such that the sum of the numbers in S1 equals the sum of the numbers in S2
//
//This program generate two types of set:
//1. Random Generated Yes Solution
//2. Random Generated No Solution
//
//This program provides two types of search:
//
//1. Exhaustive Search
//Exhaustive Search (Brute Force) would examine all possible combination 
//which sums up to the solution of partition problem
//
//2. Greedy Search
//Greedy Search would examine absolute difference between the sums of numbers is S1 ans S2 
//|sum(S1) - sum(S2)| needs to be minimum.
//

int total = 100;// change value (total is the target value. example: if 10 elemenets sums up become 100, this value should be 50 )
int total_no = 0;
int Size = 20;  // change value
int minNumb = 1;
int maxNumb = total / 2;
int set[20];    // change value
int set_no[20]; // change value

vector<int> combination;
vector<int> position;
vector<int> sortArray;
vector<int> setA;
vector<int> setB;

int random_generate_yes();
int random_generate_no();
bool print(int set[], const vector<int>& v, const vector<int>& p, int total);
bool exhaustive(int set[], int k, int n, int offset, int total);
void sort_array(int set[]);
int greedy(int set[], int k, int n);

int main() {
	clock_t start;
	double duration;
	int option;
	int difference;
	do {

		//reset vector/array
		combination.clear();
		position.clear();
		fill_n(set, Size, 0);
		fill_n(set_no, Size, 0);
		total_no = 0;

		//check if total size is odd number then break.
		if (Size % 2) {
			cout << "There is no solution for Odd number size." << endl << endl;
			break;
		}

		cout << "Exhaustive Search and Greedy Search: " << endl;
		cout << "1. Generate Confirm Yes Solution" << endl;
		cout << "2. Generate Confirm No Solution" << endl;
		cout << "3. Exit" << endl;
		cout << "Your option: ";
		cin >> option;

		if (option == 1) { // Confirm Yes Solution
			system("CLS");

			//Exhaustive Search
			cout << "Exhaustive Search:" << endl;
			random_generate_yes();
			start = clock(); 
			if (!exhaustive(set, (Size / 2), Size, 0, total)) {
				cout << "There is no solution. Could not find solution." << endl;
			}
			duration = (clock() - start) / (double)CLOCKS_PER_SEC;
			cout << "Exhaustive search duration is: " << duration << endl << endl;
			duration = 0;

			//Greedy Search
			cout << "Greedy Search:" << endl;
			cout << "Sorted Random YES: " << endl;
			sort_array(set);
			cout << endl;
			start = clock();
			difference = greedy(set, (Size / 2), Size);
			cout << "Set A: [ ";
			for (int i = 0; i < setA.size(); i++) {
				cout << setA[i] << " ";
			}
			cout << "]" << endl;
			cout << "Set B: [ ";
			for (int i = 0; i < setB.size(); i++) {
				cout << setB[i] << " ";
			}
			cout << " ]" << endl;
			cout << "Difference: " << difference << endl;
			duration = (clock() - start) / (double)CLOCKS_PER_SEC;
			cout << "Greedy search duration is: " << duration << endl << endl;
			duration = 0;

		}
		else if (option == 2) { // Confirm No Solution Search
			system("CLS");

			//Exhaustive Search
			cout << "Exhaustive Search:" << endl;
			random_generate_no();
			start = clock();
			if (!exhaustive(set_no, (Size / 2), Size, 0, total_no)) {
				cout << "There is no solution. Could not find solution." << endl;
			}
			duration = (clock() - start) / (double)CLOCKS_PER_SEC;
			cout << "Exhaustive search duration is: " << duration << endl << endl;
			duration = 0;

			//Greedy Search
			cout << "Greedy Search:" << endl;
			cout << "Sorted Random NO: " << endl;
			sort_array(set_no);
			cout << endl;
			start = clock();
			difference = greedy(set_no, (Size / 2), Size);
			cout << "Set A: [ ";
			for (int i = 0; i < setA.size(); i++) {
				cout << setA[i] << " ";
			}
			cout << "]" << endl;

			cout << "Set B: [ ";
			for (int i = 0; i < setB.size(); i++) {
				cout << setB[i] << " ";
			}
			cout << " ]" << endl;
			cout << "Difference: " << difference << endl;
			duration = (clock() - start) / (double)CLOCKS_PER_SEC;
			cout << "Greedy search duration is: " << duration << endl << endl;
			duration = 0;
		}
	} while (option != 3);
	return 0;
}
int random_generate_yes() {

	srand((unsigned int)time(NULL));

	//confirm YES solution generate
	//generate random numbers for first half set
	do {
		int left_total = total;
		for (int i = 0; i < (Size/2)-1; i++) {
			int randnum = rand() % (maxNumb - minNumb + 1) + minNumb;
			set[i] = randnum;
			left_total -= set[i];
		}
		set[(Size/2)-1] = left_total;
	} while (set[(Size / 2) - 1] < 1);

	//generate random numbers for second half set
	do {
		int right_total = total;
		for (int i = (Size/2); i < (Size/2) + ((Size/2) -1); i++) {

			int randnum = rand() % (maxNumb - minNumb + 1) + minNumb;
			set[i] = randnum;
			right_total -= set[i];
		}
		set[(Size / 2) + ((Size / 2) - 1)] = right_total;
	} while (set[(Size / 2) + ((Size / 2) - 1)] < 1);

	//random swap
	for (int k = 0; k < Size; k++) {
		int random = rand() % Size;
		if (random != k) {
			int temp = set[k];
			set[k] = set[random];
			set[random] = temp;
		}
	}

	//display all elemenets for random YES 
	cout << "Random YES: " << endl;
	for (int j = 0; j < Size; j++) {
		cout << "set[" << j << "]: " << set[j] << endl;
	}

	return 0;
}
int random_generate_no() {

	srand((unsigned int)time(NULL));
	int left_total;
	int right_total;
	int total_up;
	int totalsum;

	//confirm NO solution generate
	do {
		total_up = 0;
		//generate random numbers for first half set
		do {
			left_total = total;
			for (int i = 0; i < (Size / 2); i++) {

				int randnum = rand() % (maxNumb - minNumb + 1) + minNumb;
				set_no[i] = randnum;
				left_total -= set_no[i];
			}
		} while (left_total == 0);
		//generate random numbers for second half set
		do {
			right_total = total;
			for (int i = (Size / 2); i < Size; i++) {

				int randnum = rand() % (maxNumb - minNumb + 1) + minNumb;
				set_no[i] = randnum;
				right_total -= set_no[i];
			}
		} while (right_total == 0);
		total_up = (total * 2) - left_total - right_total;
		totalsum = 0;
		for (int z = 0; z < Size; z++) {
			totalsum += set_no[z];
		}
	} while ((total_up == 0) || (totalsum % 2 == 0));
	total_no = totalsum; //get all total from random generate no set 
	//display all elements for random NO
	cout << endl << "Random NO: " << endl;
	for (int j = 0; j < Size; j++) {
		cout << "set[" << j << "]: " << set_no[j] << endl;
	}

	return 0;
}
bool print(int sets[], const vector<int>& v, const vector<int>& p, int total) {
	static int count = 0;
	int totalsum = 0;

	//total up all the elements in combination vector
	for (int i = 0; i < v.size(); i++) {
		totalsum += v[i];
	}
	++count;

	//check if the total sum is the sum of the half of all elements
	if (totalsum == total) {
		int temp_total = 0;

		//loop and find all the sum of the other half of all elements
		for (int z = 0; z < v.size(); z++) {
			for (int m = 0; m < (v.size() * 2); m++) {
				if (p[z] == m) {
					temp_total += sets[m];
					break;
				}
			}
		}

		//if another half also sums up equally then the solution is confirm
		if (temp_total == total) {
			cout << endl;
			cout << "combination no." << count << ": [";
			for (int i = 0; i < v.size(); ++i) {
				cout << v[i] << "(" << p[i] + 1 << ") ";
			}
			cout << "] :" << totalsum << endl;
			count = 0;
			return true;
		}
		else {
			count = 0;
			return false;
		}
	}
	else {
		count - 0;
		return false;
	}
	
}
bool exhaustive(int sets[], int k, int n, int offset, int total) {
	bool check;
	//check if k is zero
	if (k == 0) {
		if (print(sets, combination, position, total)) {
			return true;
		}
		else {
			return false;
		}
	}
	for (int i = offset; i <= n - k; i++) {
		combination.push_back(sets[i]);
		position.push_back(i);
	    check = exhaustive(sets, k - 1, n, i + 1, total);
		if (check) {
			break;
		}
		combination.pop_back();
		position.pop_back();
	}
	if (check) {
		return true;
	}
}
void sort_array(int set[]) {
	for (int i = 0; i < Size; i++) {
		sortArray.push_back(set[i]);
	}
	sort(sortArray.begin(), sortArray.end());
	int z = 0; // vector index
	for (int i = (Size - 1); i >= 0; i--) {
		set[i] = sortArray[z];
		z++;
	}
	//display all elemenets for random YES 
	for (int j = 0; j < Size; j++) {
	cout << "set[" << j << "]: " << set[j] << endl;
	}
	sortArray.clear();
}
int greedy(int set[], int k, int n) {
	setA.clear();
	setB.clear();
	setA.push_back(set[0]);
	setB.push_back(set[1]);
	int totalA = set[0];
	int totalB = set[1];
	int diff = 0;
	for (int i = 2; i < n; i++) {
		if (totalA < totalB) {
			totalA += set[i];
			setA.push_back(set[i]);
		}
		else if (totalA > totalB) {
			totalB += set[i];
			setB.push_back(set[i]);
		}
		else {
			totalA += set[i];
			setA.push_back(set[i]);
		}
	}
	if (totalA > totalB) {
		diff = totalA - totalB;
	}
	else if (totalA < totalB) {
		diff = totalB - totalA;
	}
	else {
		diff = totalA - totalB;
	}
	return diff;
}