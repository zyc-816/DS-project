#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

//记录排序函数信息
struct FUNC {
    double runTime;
    string name;
};

//FUNC 比较函数
bool cmp(FUNC a, FUNC b) {
    return a.runTime < b.runTime;
}

//获取函数运行时间
double getFuncTime(void (*p)(vector<int>&), vector<int>nums) {
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
        data<<num<<" ";
    }
    return;
}

//选择排序
void selectionSort(vector<int>& nums) {
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
void bubbleSort(vector<int>& nums) {
    int n = nums.size();
    for(int i = n-1; i>0; i--) {
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
void insertionSort(vector<int>& nums) {
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

//快速排序

//选择base
int selectBase(vector<int>& nums, int l, int r) {
    int m = (l+r) / 2;
    if((nums[l] < nums[m] && nums[m] < nums[r]) 
    || (nums[r] < nums[m] && nums[m] < nums[l])) {
        return m;
    } else if((nums[m] < nums[l] && nums[l] < nums[r])
    || (nums[r] < nums[l] && nums[l] < nums[m])) {
        return l;
    } else return r;
}

//哨兵分划
int partition(vector<int>& nums, int left, int right) {
    int i = left;
    int j = right;
    int base = selectBase(nums, left, right);
    swap(nums[left], nums[base]);
    while(i < j) {
        while(i < j && nums[j] >= nums[left]) {
            j--;
        }
        while(i < j && nums[i] <= nums[left]) {
            i++;
        }
        swap(nums[i], nums[j]);
    }
    swap(nums[i], nums[left]);
    return i;
}

//排序
void _quickSort(vector<int>& nums, int left, int right) {
    //尾递归优化
    while(left < right) {
        int pivot = partition(nums, left, right);
        //右子串短
        if(pivot - left > right - pivot) {
            _quickSort(nums, pivot+1, right);
            right = pivot - 1;
        } else {
            _quickSort(nums, left, pivot-1);
            left = pivot + 1;
        }
    }
    return;
}

//统一参数，便于调用
void quickSort(vector<int>& nums) {
    int n = nums.size();
    _quickSort(nums, 0, n-1);
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

    //调用各排序方法
    vector<void (*)(vector<int>&)> func = {
        selectionSort,
        bubbleSort,
        insertionSort,
        quickSort,
    };
    vector<FUNC> funcs = {
        {0, "选择排序"},
        {0, "冒泡排序"},
        {0, "插入排序"},
        {0, "快速排序"},
    };
    for(int i=0; i<func.size(); i++) {
        double time = getFuncTime(func[i], nums);
        funcs[i].runTime = time;
    }
    sort(funcs.begin(), funcs.end(), cmp);

    //输出结果
    cout<<"各排序算法耗时为："<<endl;
    for(int i=0; i<func.size(); i++) {
        cout<<funcs[i].name<<": "<<funcs[i].runTime<<endl;
    }
    cout<<"最快的两种排序方法为："<<funcs[0].name<<"、"<<funcs[1].name<<endl;

    return 0;
}