#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//获取一个随机题目
//toDo：添加括号，算式合法性
string getQues(int maxNum, int len) {
    string symbols[] = {"+", "-", "*", "/"};
    string ques = "";
    int index = 0;
    while(index < len) {
        if(index % 2) {
            int ranSym = rand()%5;
            string symbol = symbols[ranSym];
            ques.append(symbol);
        }
        else {
            int ranNum = rand()%(maxNum+1);
            string num = to_string(ranNum);
            ques.append(num);
        }
        index++;
    }
    
    return ques;
}

//初始化题库
void initQues() {

    return;
}

//计算问题
int cal(string ques) {
    int ans;
    vector<int> OPND;
    vector<char> OPTR;

    return ans;
}

int main() {
    srand((unsigned)time(NULL));
    initQues();
    int i;
    cin>>i;
    while(i--) {
        cout<<getQues(10, 5)<<endl;
    }

    return 0;
}