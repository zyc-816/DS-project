#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//获取一个随机题目
//toDo：去除多余括号，算式合法性
string getSymbol() {
    string symbols[] = {"+", "-", "*", "/"};
    int ranSym = rand()%4;
    return symbols[ranSym];
}

string getNum(int maxNum) {
    int ranNum = rand()%(maxNum+1);
    return to_string(ranNum);
}

bool isSym(char chr) {
    char sym[] = {'+', '-', '*', '/'};
    for(int i=0; i<4; i++) {
        if(chr == sym[i]) return true;
    }
    return false;
}

bool isNum(char chr) {
    return chr >= '0' && chr <='9';
}

string getQues(int maxNum, int len, int parNum) {
    
    string ques = "";
    int index = 0;
    if(len % 2 == 0) len++;
    while(index < len) {
        if(index % 2) {
            string symbol = getSymbol();
            ques.append(symbol);
        }
        else {
            string num = getNum(maxNum);
            ques.append(num);
        }
        index++;
    }

    //插入括号
    while(parNum--) {
        int l = 0;
        int r = 0;
        while(l == r) {
            l = rand()%len;
            r = rand()%len;
            if(l == r) continue;
            l = min(l, r);
            r = max(l, r);
            //保证括号位置合理?
            while(l != 0 && !isSym(ques[l-1])) l--;
            while(r != len && isNum(ques[r])) r++;
            ques.insert(l, "(");
            ques.insert(r+1, ")");
            len += 2;
        }
    }
    return ques;
}

//初始化题库
void initQues() {

    return;
}

//计算问题
bool cal(string ques, int ans) {
    vector<int> OPND;
    vector<char> OPTR;

    return true;
}

int main() {
    srand((unsigned)time(NULL));
    initQues();
    int i;
    cin>>i;
    while(i--) {
        cout<<getQues(10, 5, 1)<<endl;
    }

    return 0;
}