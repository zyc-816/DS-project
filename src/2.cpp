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
    int val;
    char opt;
    NodeType type;
    Node* l;
    Node* r;
    Node(int _val) {
        this->type = NodeType::val;
        this->l = nullptr;
        this->r = nullptr;
        this->val = _val;
        this->opt = '\0';
    }
    Node(char _opt) {
        this->type = NodeType::opt;
        this->l = nullptr;
        this->r = nullptr;
        this->opt = _opt;
        this->val = '0';
    }   
};

//算式类
class Eq {
public:
    Eq(int deep) {
        this->_deep = deep;
        initTree(deep, this->_root);
    }
    ~Eq() {
        delTree(this->_root);
    }
    //中序遍历获得算式
    string getQues() {
        return midOrder(this->_root);
    }
    //后序遍历得到后缀表达式并计算
    string getAns();
private:
    int _deep;
    Node* _root;
    int getNum(int maxNum = 100) {
        int ranNum = rand()%(maxNum+1);
        return ranNum;
    }
    char getSymbol() {
        char symbols[] = {'+', '-', '*', '/'};
        int ranSym = rand()%4;
        return symbols[ranSym];
    }
    void initTree(int deep, Node*& root) {
        if(deep == 1) {
            int num = getNum();
            root = new Node(num);
            return;
        }
        else {
            char chr = getSymbol();
            root = new Node(chr);
            initTree(deep-1, root->l);
            initTree(deep-1, root->r);
        }
    }
    void delTree(Node* root) {
        if(!root) return;
        if(root->l) delTree(root->l);
        if(root->r) delTree(root->r);
        delete root;
        return;
    }

    string midOrder(Node* root) {
        if(root->l == nullptr && root->r == nullptr) return to_string(root->val);
        if(root->type == Node::NodeType::opt) {
            return midOrder(root->l) + root->opt + midOrder(root->r);
        }
        return "";
    }
};

//获取一个随机题目
//toDo：去除多余括号，算式合法性

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
        Eq eq(4);
        cout<<eq.getQues()<<endl;
    }

    return 0;
}