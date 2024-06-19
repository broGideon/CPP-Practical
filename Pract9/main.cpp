#include <iostream>
#include <fcntl.h>
#include <Windows.h>
#include <string>
#include "MergeClass.cpp"
#include <vector>

using namespace std;
int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);

    vector<int> array;
    for (int i = 1; i <= 10; i++) {
        wcout << L"Введите " << i << L" элемент массива" << endl;
        int value;
        wcin >> value; 
        array.push_back(value);
    }

    MergeClass sortClass;
    function<void()> sorting = [&array, &sortClass]() { sortClass.Sort(array); };
    thread goSort(sorting);
    goSort.join();

    for (int i : array) {
        wcout << L"Ячейка массива равна: " << i << endl;
    }
}