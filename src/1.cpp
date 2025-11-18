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

void countArticle(char article[], 
int &letterCnt, int &numCnt, int &spaceCnt, int &totalCnt, int N) {
    int index = 0;
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

void printArticle(char article[], const vector<int>& lines, int N) {
    int index = 0;
    int line = 0;
    while(article[index] != '\0') {
        if(index == lines[line]) {
            cout<<endl;
            line++;
        }
        cout<<article[index++];
    }
    cout<<endl;

    return;
}

bool getInsturction(string mes) {
    char flag = 'N';
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

int findStr(string str, char article[], int& cnt) {
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
    getArticle(article, lines, N);
    countArticle(article, letterCnt, numCnt, spaceCnt, totalCnt, N);
    printArticle(article, lines, N);
    cout<<"全部字母数："<<letterCnt<<endl;
    cout<<"数字个数："<<numCnt<<endl;
    cout<<"空格个数："<<spaceCnt<<endl;
    cout<<"文章总字数："<<totalCnt<<endl;

    if(getInsturction("是否需要统计字符串出现次数？")) {
        string str;
        cout<<"请输入需要统计的字符串："<<endl;
        cin>>str;
        int strCnt = 0;
        findStr(str, article, strCnt);
        cout<<"字符串出现次数为："<<strCnt<<endl;
    }


    

    return 0;
}