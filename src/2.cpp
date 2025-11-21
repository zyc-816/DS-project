#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <stack>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

//节点类
class Node {
public:
    enum class NodeType {
        opt,
        val,
    };
    double val;
    char opt;
    NodeType type;
    Node* l;
    Node* r;
    Node(double _val) {
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
        this->_ans = setAns();
    }
    ~Eq() {
        delTree(this->_root);
    }
    //中序遍历获得算式
    string getQues() {
        return midOrder(this->_root);
    }

    double getAns() {
        return this->_ans;
    }

    //获取后缀表达式（测试用）
    string getRpn() {
        stack<Node*> st1;
        stack<Node*> st2;
        Node* cur = this->_root;
        st1.push(cur);
        while(!st1.empty()) {
            cur = st1.top();
            st1.pop();
            st2.push(cur);
            if(cur->l) st1.push(cur->l);
            if(cur->r) st1.push(cur->r);
        }

        string rpn = "";
        while(!st2.empty()) {
            Node* temp = st2.top();
            st2.pop();
            if(temp->type == Node::NodeType::opt) rpn += temp->opt;
            else rpn.append(to_string((int)temp->val));
        }
        return rpn;
    }
    
private:
    int _deep;
    Node* _root;
    double _ans;
    int getNum(int maxNum = 10) {
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
            double num = getNum();
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
        if(root->l == nullptr && root->r == nullptr) return doubleToString(root->val);
        if(root->type == Node::NodeType::opt) {
            string str = "";
            if(root->l->type == Node::NodeType::opt) {
                char op1 = root->opt;
                char op2 = root->l->opt;
                if(op1 == '+' || op1 == '-') {
                    str += midOrder(root->l);
                } else {
                    if(op2 == '+' || op2 == '-') {
                        str = str + '(' + midOrder(root->l) + ')';
                    }
                    else str += midOrder(root->l);
                }
            } else {
                str += midOrder(root->l);
            }
            str += root->opt;
            if(root->r->type == Node::NodeType::opt) {
                char op1 = root->opt;
                char op2 = root->r->opt;
                if(op1 == '+') {
                    str += midOrder(root->r);
                } else {
                    if(op2 == '+' || op2 == '-') {
                        str = str + '(' + midOrder(root->r) + ')';
                    } else {
                        str += midOrder(root->r);
                    }
                }
            } else {
                str += midOrder(root->r);
            }
            return str;
        }
        return "";
    }

    //从操作数栈中获取前两个数
    void getTwo(double& a, double& b, stack<double>& OPND) {
        b = OPND.top();
        OPND.pop();
        a = OPND.top();
        OPND.pop();
        return;
    }

    //处理过程中的基本算式
    bool Cal(double a, double b, char optr, double& ans) {
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

    //后序遍历得到后缀表达式并计算
    double setAns() {
        stack<Node*> st1;
        stack<Node*> st2;
        Node* cur = this->_root;
        st1.push(cur);
        while(!st1.empty()) {
            cur = st1.top();
            st1.pop();
            st2.push(cur);
            if(cur->l) st1.push(cur->l);
            if(cur->r) st1.push(cur->r);
        }

        stack<double> OPND;
        while(!st2.empty()) {
            Node* temp = st2.top();
            st2.pop();
            if(temp->type == Node::NodeType::val) {
                OPND.push(temp->val);
            } else if(temp->type == Node::NodeType::opt) {
                double a, b;
                double t;
                getTwo(a, b, OPND);
                if(!Cal(a, b, temp->opt, t)) {
                    initTree(this->_deep, this->_root);
                    this->_ans = this->setAns();
                    return this->_ans;
                }
                OPND.push(t);
            }
        }
        return OPND.top();
    }

    //将浮点数转为字符串
    string doubleToString(double val) {
        stringstream stream; 
        stream << fixed << setprecision(1) << val;
        return stream.str();
    }
};

struct Ques {
    string ques;
    double ans;
};

//初始化题库
void initQues(int count = 50, int deep = 3) {
    ofstream qus("Questions.txt");
    qus<<setiosflags(ios::fixed)<<setprecision(1);
    for(int i=0; i<count; i++) {
        Eq eq(deep);
        qus<<eq.getQues()<<"="<<eq.getAns()<<endl;
    }
    qus.close();
    return;
}

//读取题库
void readQues(vector<Ques>& questions) {
    ifstream qus("Questions.txt");
    string line;
    while(getline(qus, line)) {
        Ques q;
        int pos = line.find('=');
        q.ques = line.substr(0, pos+1);
        string s_ans = line.substr(pos+1, line.length() - pos - 1);
        q.ans = stod(s_ans);
        questions.push_back(q);
    }
    qus.close();
    return;
}

bool fileExist(string filename) {
    ifstream file(filename);
    return file.good(); //返回文件是否存在
}

void getHis(int& hisScore) {
    if(!fileExist("history.txt")) {
        ofstream file("history.txt");
        file<<0;
        file.close();
    }
    ifstream his("history.txt");
    his>>hisScore;
    return;
}

bool getInsturction(string mes) {
    char flag = 'Y';
    cout<<mes<<"(y/n) ";
    cin>>flag;
    cin.get();
    if(flag == 'N' || flag == 'n') {
        return false;
    }
    else if(flag == 'Y' || flag == 'y') {
        return true;
    }
    else {
        cout<<"输入错误"<<endl;
        return getInsturction(mes);
    }
}

void saveScore(int curScore, int hisScore) {
    if(curScore > hisScore) {
        ofstream his("history.txt");
        his<<curScore;
        cout<<"有进步，加油！"<<endl;
    } else {
        cout<<"还要继续努力哦~"<<endl;
    }
    
    return;
}

int main() {
    srand((unsigned)time(NULL)); //设置随机数种子
    cout<<setiosflags(ios::fixed)<<setprecision(1); //设置精度
    int hisScore = 0;
    int curScore = 0;
    getHis(hisScore);
    int n = 0;
    cout<<"请选择题库大小：";
    cin>>n;
    initQues(n);
    vector<Ques> questions;
    readQues(questions);

    cout<<"历史最高分："<<hisScore<<endl;
    cout<<"当前得分："<<curScore<<endl;
    while(1) {
        if(getInsturction("是否继续答题？(答案请保留一位小数)")) {
            int id = rand()%questions.size();
            Ques q = questions[id];
            cout<<q.ques<<" ";
            double ans;
            cin>>ans;
            if(ans == q.ans) {
                curScore++;
                cout<<"答对了！加1分(当前得分："<<curScore<<")"<<endl;
            } else {
                cout<<"答错了！(当前得分："<<curScore<<")"<<endl;
            }
        } else {
            break;
        }
    }

    saveScore(curScore, hisScore);
    
    return 0;
}