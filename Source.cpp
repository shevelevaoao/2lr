#include <iostream>
#include <chrono>
#include <Windows.h>

using namespace std;

double averageTime = 0.0;

void merge(float* array, int left, int middle, int right) {
	int subArrayOne = middle - left + 1;
	int subArrayTwo = right - middle;
	int* leftArray = new int[subArrayOne];
	int* rightArray = new int[subArrayTwo];
	for (int i = 0; i < subArrayOne; ++i) {
		leftArray[i] = array[left + i];
	}
	for (int i = 0; i < subArrayTwo; ++i) {
		rightArray[i] = array[middle + 1 + i];
	}
	int indexOfSubArrayOne = 0;
	int indexOfSubArrayTwo = 0;
	int indexOfMergedArray = left;
	while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
		if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
			array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
			indexOfSubArrayOne++;
		}
		else {
			array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
			indexOfSubArrayTwo++;
		}
		indexOfMergedArray++;
	}
	while (indexOfSubArrayOne < subArrayOne) {
		array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}
	while (indexOfSubArrayTwo < subArrayTwo) {
		array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}
	delete[] leftArray;
	delete[] rightArray;
}

void mergeSortRecursive(float* array, int left, int right) {
	if (left >= right) {
		return;
	}
	int middle = left + (right - left) / 2;
	mergeSortRecursive(array, left, middle);
	mergeSortRecursive(array, middle + 1, right);
	merge(array, left, middle, right);
}

void mergeSort(float* array, int size) {
	mergeSortRecursive(array, 0, size - 1);
}


struct Snail {
	float x = 0.0;
	float y = 0.0;
	int length = 0;
	float* paths = new float[length]();
	bool isConfused = false;
	//float temp;

	void detectConfusion()
	{
		auto begin = chrono::high_resolution_clock::now();
		mergeSort(paths, length);
		auto end = chrono::high_resolution_clock::now();
		chrono::duration<double, milli> spent = end - begin;
		averageTime += spent.count();
		if (paths[0] == paths[1]) {
			isConfused = true;
		}
	}
};

float lengthOfParth(float x1, float y1, float x2, float y2) {
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

int main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int snailCount;

	cout << "Введите количество улиток: ";
	cin >> snailCount;
	Snail* snails = new Snail[snailCount];
	cout << "Для каждой улитки введите стартовую позицию (X, Y через пробел) в см (верхний левый угол - 0.0 0.0)" << endl;
	for (int i = 0; i < snailCount; i++) {
		snails[i].length = snailCount - 1;
		cout << "Улитка " << i + 1 << " (X, Y): ";
		cin >> snails[i].x;
		cin >> snails[i].y;
	}
	float shortestPath = 141422;//самое большое возможное расстояние
	float temp = 0.0;
	int l = 0;
	for (int i = 0; i < snailCount; i++) {
		for (int j = 0; j < snailCount; j++) {
			if (i != j) {
				temp = lengthOfParth(snails[i].x, snails[i].y, snails[j].x, snails[j].y);
				snails[i].paths[l] = temp;
				if (temp < shortestPath) {
					shortestPath = temp;
				}
				l++;
			}
		}
		snails[i].detectConfusion();
		l = 0;
	}
	int k = 0;
	for (int i = 0; i < snailCount; i++) {
		if (snails[i].isConfused) {
			cout << "Улитка " << i << " в замешательстве" << endl;
			k++;
		}
	}
	cout << "Среднее время сортировки: " << averageTime / snailCount << " мс" << endl;
	if (k != snailCount)
		cout << "Кратчайшее время: " << shortestPath / 2 << " с" << endl;
	system("pause");
	return 0;
}