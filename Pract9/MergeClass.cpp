#include <iostream>
#include <vector>
#include <functional>
#include <thread>
using namespace std;
class MergeClass
{
private:
    void Merge(vector<int>& array, vector<int>& left, vector<int>& right) {
        int l = 0;
        int r = 0;
        int a = 0;
        while (l < left.size() && r < right.size()) {
            if (left[l] <= right[r]) array[a++] = left[l++];
            else array[a++] = right[r++];
        }

        while (l < left.size()) {
            array[a++] = left[l++];
        }
        while (r < right.size()) {
            array[a++] = right[r++];
        }
    }
    
public:
    void Sort(vector<int>& array) {
        if (array.size() <= 1) return;

        double center = array.size() / 2;
        vector<int> left(array.begin(), array.begin() + center);
        vector<int> right(array.begin() + center, array.end());

        function<void()> leftSort = [&left, this]() {
            Sort(left);
        };
        thread goSortLeft(leftSort);

        function<void()> rightSort = [&right, this]() {
            Sort(right);
        };
        thread goSortRight(rightSort);
        goSortLeft.join();
        goSortRight.join();
        Merge(array, left, right);
    }
};