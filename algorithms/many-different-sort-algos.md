Code below show many different sorts in cpp
credit: unknown
```cpp
#include "SortingLibrary.h"

void swap(int list[], int firstIndex, int secondIndex) {
	int temporary = list[firstIndex];
	list[firstIndex] = list[secondIndex];
	list[secondIndex] = temporary;
}

int* bubbleSort(int list[], int len, int(*compare)(int, int), int& comparisonCount) {

	bool swapped = false;
	do {

		swapped = false;
		//4,3,1,5
		//3,1,4,5
		//1,3,4,5
		for (int i = 1; i < len; i++) {
			if (compare(list[i - 1], list[i]) > 0) {
				swap(list, i - 1, i);
				swapped = true;
			}
		}

	} while (swapped);

	return list;
}

int* selectionSort(int list[], int len, int(*compare)(int, int), int& comparisonCount) {
	
	return list;
}

int* insertionSort(int list[], int len, int(*compare)(int, int), int& comparisonCount) {

	return list;
}
int* quickSort(int list[], int len, int(*compare)(int, int), int& comparisonCount) {

	return list;
}

int* mergeSort(int list[], int len, int(*compare)(int, int), int& comparisonCount) {


	return list;
}
```