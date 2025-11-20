#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <stack>
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

//运算符优先级比较
bool compare(char chr, char top) {
    if(top == '(') return true;
    int pri_1 = 0;
    int pri_2 = 0;
    if(chr == '*' || chr == '/') pri_1 = 1;
    if(top == '*' || top == '/') pri_2 = 1;
    return pri_1 > pri_2;
}

//从操作数栈中获取前两个数
void getTwo(int& a, int& b, stack<int>& OPND) {
    a = OPND.top();
    OPND.pop();
    b = OPND.top();
    OPND.pop();
    return;
}

//处理过程中的基本算式
bool baseCal(int a, int b, char optr, int& ans) {
    if(optr == '+') ans = a + b;
    else if(optr == '-') ans = a - b;
    else if(optr == '*') ans = a * b;
    else if(optr == '/') {
        if(b == 0) {
            return false;
        }
        else ans = a / b;
    }

    return true;
}

//计算问题
bool calEq(string ques, int& ans) {
    stack<int> OPND; //操作数栈
    stack<char> OPTR; //操作符栈

    //转化为后缀表达式
    string rpn = "";
    int len = ques.length();
    for(int i=0; i<len; i++) {
        char chr = ques[i];
        if(isSym(chr) || chr == '(' || chr == ')') {
            if(chr == ')') {
                while(OPTR.top() != '(') {
                    rpn.push_back(OPTR.top());
                    OPTR.pop();
                }
                OPTR.pop();
            }
            else if(OPTR.empty() || compare(chr, OPTR.top())) {
                OPTR.push(chr);
            }
            else {
                while(!compare(chr, OPTR.top())) {
                    rpn.push_back(OPTR.top());
                    OPTR.pop();
                }
                OPTR.push(chr);
            }
        }
        else if(isNum(chr)) {
            rpn.push_back(chr);

            //以空格隔开数字，便于处理
            if(i+1 < len 
                && (isSym(ques[i+1]) || chr == '(' || chr == ')')) {
                rpn.push_back(' ');
            }
        }
    }

    //后缀表达式求值
    int rpnLen = rpn.length();
    for(int i=0; i<rpnLen; i++) {
        char chr = rpn[i];
        if(isSym(chr)) {
            int a, b;
            int temp;
            getTwo(a, b, OPND);
            if(!baseCal(a, b, chr, temp)) return false;
            else OPND.push(temp);
        }
        else if(isNum(chr)) { //以空格分隔，获取操作数
            
            OPND.push(chr);
        }
    }
    ans = OPND.top();

    return true;
}

int main() {
    srand((unsigned)time(NULL));
    initQues();
    int i;
    cin>>i;
    while(i--) {
        int ans;
        string eq = getQues(10, 5, 1);
        calEq(eq, ans);
        cout<<eq<<" = "<<ans<<endl;
    }

    return 0;
}