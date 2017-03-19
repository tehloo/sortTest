/*
 * SortThings.cpp
 *
 *  Created on: 2017. 3. 18.
 *      Author: tehlo_000
 */

#include <iostream>
#include <vector>
#include <list>
#include <stdlib.h>
#include <ctime>

using namespace std;

#define MAX_NUMBERS_SIZE 10

void fill_numbers(vector<int>& vec) {
	srand(time(NULL));
	for (int i = 0; i < MAX_NUMBERS_SIZE; i++) {
		vec.push_back(rand() % MAX_NUMBERS_SIZE);
		cout << " " << vec[i];
//		if (i % 10 == 9) cout << endl;
	}

	cout << endl << " size of numbers is " << vec.size() << endl;
}

void fill_numbers(int* array, int size) {
	srand(time(NULL));
	for (int i = 0; i < size; i++) {
		array[i] = (rand() % MAX_NUMBERS_SIZE);
		cout << " " << array[i];
//		if (i % 10 == 9) cout << endl;
	}

	cout << endl << " size of numbers is " << size << endl;
}

void fill_numbers(list<int>& list, int size) {
	srand(time(NULL));
	for (int i = 0; i < size; i++) {
		int value = (rand() % MAX_NUMBERS_SIZE);
		list.push_back(value);
		cout << " " << list.back();
//		if (i % 10 == 9) cout << endl;
	}

	cout << endl << " size of numbers is " << size << endl;
}


void bubble_sort_numbers(vector<int>& vec) {
	time_t begin = time(NULL);
	for (vector<int>::iterator it_left = vec.begin(); it_left < vec.end(); it_left++) {
		for (vector<int>::iterator it_right = it_left + 1; it_right < vec.end(); it_right++) {
			if (*it_left < *it_right) {
				int temp = *it_left;
				*it_left = *it_right;
				*it_right = temp;
			}
		}
	}
	cout << " elapsed clock = " << difftime(time(NULL), begin) << endl;
}

void show_numbers(vector<int>& vec) {
	for (vector<int>::iterator it = vec.begin(); it < vec.end(); it++) {
		cout << " " << *it;
//		if ((it - vec.begin()) % 10 == 9) cout << endl;
	}
}

/*
 * merge sort with vector makes me confused. ~_~
 */

void merge_both(vector<int>& vec, vector<int>& helper
				, vector<int>::iterator it_lower
				, vector<int>::iterator it_middle
				, vector<int>::iterator it_higher) {
	int lower = it_lower - vec.begin();
	int middle = it_middle - vec.begin();
	int high = it_higher - vec.begin();
	for(vector<int>::iterator it = helper.begin() + lower;
			it <= helper.begin() + high; it++) {
		int index = it - helper.begin();
		*it = vec[it - helper.begin()];
	}

	vector<int>::iterator it_h_left = helper.begin();
	vector<int>::iterator it_h_right = helper.begin() + middle;
	vector<int>::iterator it = it_lower;

	while (it_h_left <= helper.begin() + middle
			&& it_h_right <= helper.begin() + high) {
		if (*it_h_left < *it_h_right) {
			*it = *it_h_right;
			it_h_right++;
		} else if (*it_h_left >= *it_h_right) {
			*it = *it_h_left;
			it_h_left++;
		}
	}

	int remain = middle - (it_h_left - helper.begin());
	for(vector<int>::iterator it_r = vec.end() - remain - 1;
			it_r < vec.end(); it_r++) {
		*it_r = *it_h_left;
		it_h_left++;
	}
}

void merge_sort(vector<int>& vec, vector<int>& helper
				, vector<int>::iterator it_lower
				, vector<int>::iterator it_higher) {
	if (it_lower < it_higher) {
		int lower = it_lower - vec.begin();
		int higher = it_higher - vec.begin();
		vector<int>::iterator it_middle = ((lower + higher) / 2) + vec.begin();
		merge_sort(vec, helper, it_lower, it_middle);
		merge_sort(vec, helper, it_middle+1, it_higher);
		merge_both(vec, helper, it_lower, it_middle, it_higher);
	}
}

void merge_sort(vector<int>& vec) {
	vector<int> helper = vector<int>(vec.size());
	vector<int>::iterator it_lower = vec.begin();
	vector<int>::iterator it_higher = vec.end() - 1;

	merge_sort(vec, helper, it_lower, it_higher);
}

void quick_sort(vector<int>& vec, int i_begin, int i_end) {
	if (i_begin >= i_end) return;
	vector<int>::iterator it_pivot = vec.begin() + i_begin;
	vector<int>::iterator it = vec.begin() + i_begin;
	vector<int>::iterator it_vs = vec.begin() + i_begin + 1;
	int mid = *it_pivot;

	while(it_vs - vec.begin() < i_end) {
		if (mid > *it_vs) {
			it++;
			int temp = *it;
			*it = *it_vs;
			*it_vs = temp;
		}
		it_vs++;
	}

	*it_pivot = *it;
	*it = mid;

	quick_sort(vec, i_begin, (it - vec.begin() - 1));
	quick_sort(vec, (it - vec.begin() - 1), i_end);
}

vector<int>::iterator binary_search(vector<int>& vec, int target, int i_begin, int i_end) {
	if (i_begin >= i_end)
		return vec.end();
	vector<int>::iterator mid = vec.begin() + (i_end + i_begin) / 2;

	if (*mid == target)
		return mid;

	if (*mid < target) {
		return binary_search(vec, target, i_begin, mid - vec.begin() - 1);
	}

	return binary_search(vec, target, mid - vec.begin() + 1, i_end);

}

void merge(int* array, int* helper, int i_begin, int i_mid, int i_end) {
	for (int i = i_begin; i <= i_end; i++) {
		helper[i] = array[i];
	}

	int i_left = i_begin;
	int i_right = i_mid + 1;
	int i = i_begin;

	while (i_left <= i_mid && i_right <= i_end) {
		if (helper[i_left] < helper[i_right]) {
			array[i] = helper[i_right];
			i++;
			i_right++;
		} else {
			array[i] = helper[i_left];
			i++;
			i_left++;
		}
	}

	while (i_left <= i_mid) {
		array[i] = helper[i_left];
		i++;
		i_left++;
	}
}

void merge_sort(int* array, int* helper, int i_begin, int i_end) {
	if (i_begin >= i_end)
		return;
	int i_mid = (i_begin + i_end) / 2;
	merge_sort(array, helper, i_begin, i_mid);
	merge_sort(array, helper, i_mid + 1, i_end);
	merge(array, helper, i_begin, i_mid, i_end);
}

void merge_sort(int* array, int size) {
	int helper[size] = {0,};

	merge_sort(array, helper, 0, size - 1);
}

void show_numbers(int* array, int size) {
	int i = 0;
	while (i < size) {
		cout << array[i++] << " ";
	}
}

/*
void quick_sort(int* array, int begin, int end) {
	int pivot = begin;
	int pivot_val = array[begin];
	for (int i = begin + 1; i <= end; i++) {
		if (array[i])
	}
}

void quick_sort(int* array, int size) {
	quick_sort(array, 0, size - 1);
}

*/

void quick_sort(list<int>& li
				, list<int>::iterator it_begin
				, list<int>::iterator it_end) {
	if (it_begin == it_end)
		return;

	list<int>::iterator pivot = it_begin;
	list<int>::iterator it = it_begin++;

	while (it != it_end) {
		if (*pivot < *it) {
			li.insert(it_begin, *it);
			list<int>::iterator it_erase = it;
			it++;
			li.erase(it_erase);
		}
	}

	list<int>::iterator pre_pivot = pivot;
	list<int>::iterator post_pivot = pivot;

	quick_sort(li, it_begin, pre_pivot--);
	quick_sort(li, post_pivot++, it_end);
}

void quick_sort(list<int>& list) {
	quick_sort(list, list.begin(), list.end()--);
}

void show_number(list<int>& li) {
	list<int>::iterator it = li.begin();
	while (it != li.end()) {
		cout << *it << " ";
		it++;
	}
}



//#define USE_VECTOR

int main()
{
#ifdef USE_VECTOR
	vector<int> vec = vector<int>();


	fill_numbers(vec);
	bubble_sort_numbers(vec);

//	merge_sort(vec);
//	quick_sort(vec, 0, vec.size() - 1);
	show_numbers(vec);
	cout << endl;
	vector<int>::iterator it = binary_search(vec, 4, 0, vec.size());
	if (it == vec.end()) cout << "can not find it";
	else cout << "target is in " << (int)(it - vec.begin());
#else
	int array[MAX_NUMBERS_SIZE] = {0,};
	int length = sizeof(array) / sizeof(int);
	fill_numbers(array, length);
	//merge_sort(array, length);
//	quick_sort(array, length);
	show_numbers(array, length);

	list<int> li = list<int>();
	fill_numbers(li, MAX_NUMBERS_SIZE);
	quick_sort(li);
//	show_number(li);


#endif
}


