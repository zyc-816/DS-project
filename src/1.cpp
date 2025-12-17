#include <iostream>
#include <cctype>
#include <vector>
#include <string>
#define MAX_LENGTH 85
using namespace std;

void getArticle(char article[], vector<int>& lines, int N) {
    int line = 0;
    int index = 0;
    while(line < N) {
        char chr = '\0';
        cin.get(chr);
        if(chr == '\n') {
            lines[line++] = index;
        }
        else {
            article[index++] = chr;
        }
    }
    article[index] = '\0';

    return;
}

void countArticle(const char article[], 
int &letterCnt, int &numCnt, int &spaceCnt, int &totalCnt, int N) {
    int index = 0;
    letterCnt = numCnt = spaceCnt = totalCnt = 0; //初始化计数
    while(article[index] != '\0') {
        char chr = article[index];
        if(isalpha(chr)) letterCnt++;
        else if(isdigit(chr)) numCnt++;
        else if(chr == ' ') spaceCnt++;
        index++;
    }
    totalCnt = letterCnt + numCnt; //总字数为字母数加数字数

    return;
}

void printArticle(const char article[], const vector<int>& lines, int N) {
    int index = 0;
    int line = 0;
    while(article[index] != '\0') {
        if(lines[line] != 0 && index == lines[line]) {
            cout<<endl;
            line++;
        }
        cout<<article[index++];
    }
    cout<<endl;

    return;
}

int findStr(string str, const char article[], int& cnt) {
    int i = 0;
    int j = 0;
    int len = str.length();
    cnt = 0;
    while(article[i] != '\0') {
        if(article[i] == str[j]) {
            i++;
            j++;
        }
        else {
            i = i - j + 1;
            j = 0;
        }
        if(j >= len) {
            cnt++;
            i = i - j + 1;
            j = 0;
        }
    }

    return cnt;
}

bool delStr(string str, char article[], vector<int>& lines) {
    int i = 0;
    int j = 0;
    int len = str.length();
    int pos = -1;
    while(article[i] != '\0') {
        if(article[i] == str[j]) {
            i++;
            j++;
        }
        else {
            i = i - j + 1;
            j = 0;
        }
        if(j >= len) {
            pos = i - j;
            break;
        }
    }

    if(pos == -1) return false;
    
    //修改行表
    int line = 0; //pos所在行
    int sumLine = 0; // 到pos所在行为止总字符数（含pos所在行）
    for(line=0; pos>=sumLine; line++) {
        sumLine += lines[line];
    }
    line--;

    int delt = sumLine - pos; //pos所在行减去的长度
    //之后每行都要减去delt
    for(int i=line; i<lines.size(); i++) {
        lines[i] -= delt;
    }
    //若删去子串有部分在下一行，则下一行行表应减去剩下的部分
    int left = len - delt; //剩余需要删除的长度
    int l = line+1; //待处理行标
    while(left > 0) {
        int length = lines[l] - lines[l-1]; //当前行长度
        if(length >= left) {
            for(int i=l; i<lines.size(); i++) {
                lines[i] -= left;
            }
            left = 0;
        } else {
            for(int i=l; i<lines.size(); i++) {
                lines[i] -= length;
            }
            left -= length;
        }
        l++;
    }

    //删除子串
    int index = pos;
    while(article[index + len] != '\0') {
        article[index] = article[index + len];
        index++;
    }
    article[index] = '\0';
    
    return true;
}

int main() {
    int N = 0;
    int letterCnt = 0;
    int numCnt = 0;
    int spaceCnt = 0;
    int totalCnt = 0;

    cout<<"请输入文章行数：";
    cin>>N;
    cin.get();
    char article[N * MAX_LENGTH + 5];
    vector<int> lines(N);
    cout<<"请输入文章内容："<<endl;
    getArticle(article, lines, N);
    countArticle(article, letterCnt, numCnt, spaceCnt, totalCnt, N);
    cout<<"文章内容为："<<endl;
    printArticle(article, lines, N);
    cout<<"全部字母数："<<letterCnt<<endl;
    cout<<"数字个数："<<numCnt<<endl;
    cout<<"空格个数："<<spaceCnt<<endl;
    cout<<"文章总字数："<<totalCnt<<endl;

    while(1) {
        cout<<"请选择操作：\n"
        <<"0. 退出\n"
        <<"1. 统计字符串出现次数\n"
        <<"2. 删除字符串\n"
        <<"3. 输出文章内容及统计信息\n";
        int ins;
        cin>>ins;
        switch(ins) {
            case 0: {
                return 0;
                break;
            }
            case 1: {
                string str;
                cout<<"请输入需要统计的字符串："<<endl;
                cin>>str;
                int strCnt = 0;
                findStr(str, article, strCnt);
                cout<<"字符串出现次数为："<<strCnt<<endl;
                break;
            }
            case 2: {
                string str;
                cout<<"请输入需要删除的字符串："<<endl;
                cin>>str;
                if(delStr(str, article, lines)) {
                    cout<<"删除成功！"<<endl;
                    cout<<"删除后文章内容为："<<endl;
                    printArticle(article, lines, N);
                }
                else cout<<"未找到目标字符串！"<<endl;
                break;
            }
            case 3: {
                countArticle(article, letterCnt, numCnt, spaceCnt, totalCnt, N);
                cout<<"文章内容为："<<endl;
                printArticle(article, lines, N);
                cout<<"全部字母数："<<letterCnt<<endl;
                cout<<"数字个数："<<numCnt<<endl;
                cout<<"空格个数："<<spaceCnt<<endl;
                cout<<"文章总字数："<<totalCnt<<endl;
                break;
            }
            default: {
                cout<<"输入错误，请重新输入\n";
                break;
            }
        }
    }

    return 0;
}