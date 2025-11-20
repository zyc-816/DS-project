#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <stack>
using namespace std;

//节点类
class Node {
public:
    enum class NodeType {
        opt,
        val,
    };
    Node() {
        this->_l = nullptr;
        this->_r = nullptr;
        this->_opt = '\0';
        this->_val = '0';
    }

    Node(NodeType type, int val) {
        this->_type = type;
        this->_l = nullptr;
        this->_r = nullptr;
        this->_val = val;
    }
    Node(NodeType type, char opt) {
        this->_type = type;
        this->_l = nullptr;
        this->_r = nullptr;
        this->_opt = opt;
    }
    ~Node() {}
    void setL(Node* node) {
        this->_l = node;
    }
    void setR(Node* node) {
        this->_r = node;
    }
    Node* getL() {
        return this->_l;
    }
    Node* getR() {
        return this->_r;
    }
    void setVal(int val) {
        this->_val = val;
    }
    int getVal() {
        return this->_val;
    }
    void setOpt(char opt) {
        this->_opt = opt;
    }
    char getOpt() {
        return this->_opt;
    }

private:
    int _val;
    char _opt;
    NodeType _type;
    Node* _l;
    Node* _r;
};

//算式类
class Eq {
public:
    Eq(int deep) {
        this->_deep = deep;
        this->_root = initTree(deep);
    }

    string getQues();
    string getAns();
private:
    int _deep;
    Node _root;
    Node initTree(int deep) {

    }

};

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