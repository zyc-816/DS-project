#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
using namespace std;

//获取函数运行时间
double getFuncTime(void (*p)(vector<int>), vector<int>nums) {
    clock_t start = clock();
    p(nums);
    clock_t end = clock();
    double dur = static_cast<double>(end - start)/CLOCKS_PER_SEC;
    return dur;
}

//保存排序结构到对应文件
void saveData(string funcName, vector<int> nums) {
    ofstream data(funcName + ".txt");
    for(auto num : nums) {
        data<<num;
    }
    return;
}

//选择排序
void selectionSort(vector<int> nums) {
    int n = nums.size();
    for(int i = 0; i < n-1; i++) {
        int j = i; //最小元素下标
        for(int k = i+1; k < n; k++) {
            if(nums[k] < nums[j]) {
                j = k;
            }
        }
        swap(nums[i], nums[j]);
    }

    saveData(__func__, nums);
    return;
}

//冒泡排序
void bubbleSort(vector<int> nums) {
    int n = nums.size();
    for(int i = n-1; i>0; i++) {
        bool flag = false;
        for(int j = 0; j < i; j++) {
            if(nums[j] > nums[j+1]) {
                swap(nums[j], nums[j+1]);
                flag = true;
            }
        }
        if(!flag) break; //若未发生交换则排序完成
    }

    saveData(__func__, nums);
    return;
}

//插入排序
void insertionSort(vector<int> nums) {
    int n = nums.size();
    for(int i = 1; i < n; i++) {
        int base = nums[i];
        int j = i - 1;
        while(j >= 0 && nums[j] > base) {
            nums[j+1] = nums[j];
            j--;
        }
        nums[j+1] = base;
    }

    saveData(__func__, nums);
    return;
}

int main() {
    srand((unsigned int)time(nullptr));
    vector<int> nums;
    int n;
    while(1) {
        cout<<"请输入要生成的数字个数：";
        cin>>n;
        if(n > 20000) break;
        else {
            cout<<"数量太少，请重新输入20000以上的数"<<endl;
        }
    }
    //随机生成n个数
    for(int i=0; i<n; i++) {
        int num = rand();
        nums.push_back(num);
    }


    return 0;
}