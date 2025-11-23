#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

struct Node {
    int val;
    char chr;
    Node* l;
    Node* r;
    Node(int _val = 0, char _chr = '\0', Node* _l = nullptr, Node* _r = nullptr) 
    : val(_val), chr(_chr), l(_l), r(_r) {}
};

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

bool fileExist(string filename) {
    ifstream file(filename);
    return file.good(); //返回文件是否存在
}

void initData(int& n, string& chars, vector<int>& vals) {
    if(fileExist("./data.txt")) {
        if(getInsturction("是否重新初始化字符集？")) {
            cout<<"请输入字符集大小：";
            cin>>n;
            if(n == 0) {
                cout<<"字符集大小不能为0"<<endl;
                initData(n, chars, vals);
                return;
            }
            ofstream data("./data.txt");
            data<<n<<endl;
            cout<<"请输入"<<n<<"个字符："<<endl;
            cin.get();
            getline(cin, chars);
            data<<chars<<endl;
            cout<<"请输入"<<n<<"个权值："<<endl;
            for(int i=0; i<n; i++) {
                int v;
                cin>>v;
                vals.push_back(v);
                data<<v<<" ";
            }
            data.close();
        } else {
            ifstream data("./data.txt");
            data>>n;
            data.get();
            getline(data, chars);
            for(int i=0; i<n; i++) {
                int t;
                data>>t;
                vals.push_back(t);
            }
            data.close();
        }
    } else {
        cout<<"请输入字符集大小：";
        cin>>n;
        ofstream data("./data.txt");
        data<<n<<endl;
        cout<<"请输入"<<n<<"个字符："<<endl;
        cin.get();
        getline(cin, chars);
        data<<chars<<endl;
        cout<<"请输入"<<n<<"个权值："<<endl;
        for(int i=0; i<n; i++) {
            int v;
            cin>>v;
            vals.push_back(v);
            data<<v<<" ";
        }
        data.close();
    }
}

bool cmp(Node* a, Node* b) {
    return a->val < b->val;
}

class huffTree {
public:
    huffTree(string _chars, vector<int> vals, int n) {
        _n = n;
        chars = _chars;
        for(int i=0; i<n; i++) {
            Node* newNode = new Node(vals[i], chars[i], nullptr, nullptr);
            nodes.push_back(newNode);
        }
        sort(nodes.begin(), nodes.end(), cmp);
        buildTree(this->root);
        vector<int> path;
        if(n == 1) {
            vector<int> temp(1, 0);
            huffCode[this->root->chr] = temp;
        }
        else getHuffCode(this->root, path);
    }
    ~huffTree() {
        delTree(this->root);
    }

    void printCode() {
        for(auto chr : chars) {
            cout<<chr<<": ";
            for(auto num : huffCode[chr]) {
                cout<<num;
            }
            cout<<endl;
        }
    }

    void enCode(string str) {
        vector<int> res;
        for(auto chr : str) {
            if(huffCode.count(chr) == 0) {
                cout<<"error: 含有字符集以外的字符"<<endl;
                return;
            } else {
                for(auto n : huffCode[chr]) {
                    res.push_back(n);
                }
            }
        }
        cout<<"编码结果为：";
        for(auto n : res) {
            cout<<n;
        }
        cout<<endl;
        return;
    }

    void deCode(string nums) {
        Node* r = this->root;
        string res = "";
        for(auto chr : nums) {
            int num;
            if(chr == '1') num = 1;
            else if(chr == '0') num = 0;
            else {
                cout<<"error: 编码格式错误"<<endl;
                return;
            }
            if(!r->l && !r->r) {
                res += r->chr;
                r = this->root;
            }
            if(num == 0) r = r->l;
            if(num == 1) r = r->r;
        }
        cout<<"译码结果为："<<res<<endl;
        return;
    }
    
private:
    int _n;
    Node* root;
    string chars;
    vector<Node*> nodes;
    map<char, vector<int>> huffCode;
    void buildTree(Node*& root) {
        while(nodes.size() > 1) {
            Node* newNode = new Node();
            newNode->l = nodes[0];
            newNode->r = nodes[1];
            newNode->val = nodes[0]->val + nodes[1]->val;
            nodes.erase(nodes.begin(), nodes.begin()+2);
            nodes.push_back(newNode);
            stable_sort(nodes.begin(), nodes.end(), cmp);
        }
        root = nodes[0];
        return;
    }

    void delTree(Node* root) {
        if(!root) return;
        delTree(root->l);
        delTree(root->r);
        delete root;
        return;
    }

    void getHuffCode(Node* root, vector<int> curPath) {
        if(!root) return;
        if(!root->l && !root->r) huffCode[root->chr] = curPath;
        curPath.push_back(0);
        getHuffCode(root->l, curPath);
        curPath.pop_back();
        curPath.push_back(1);
        getHuffCode(root->r, curPath);
        curPath.pop_back();
        return;
    }
};

int main() {
    int n = 0; //字符数
    string chars; //字符
    vector<int> vals; //权值
    initData(n, chars, vals); //初始化权值文件
    huffTree huff(chars, vals, n);
    while(1) {
        int ins;
        cout<<"请选择功能：\n"
        <<"0. 退出\n"
        <<"1. 显示哈夫曼编码\n"
        <<"2. 编码\n"
        <<"3. 译码\n";
        cin>>ins;
        switch(ins) {
            case 0: {
                return 0;
                break;
            }
            case 1: {
                huff.printCode();
                break;
            }
            case 2: {
                string str;
                cout<<"请输入原始字符串："<<endl;
                cin.get();
                getline(cin, str);
                huff.enCode(str);
                break;
            }
            case 3: {
                string nums;
                cout<<"请输入哈夫曼编码串："<<endl;
                cin>>nums;
                huff.deCode(nums);
                break;
            } 
        }
    }
    return 0;
}