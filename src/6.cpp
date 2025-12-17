#include <iostream>
#include <algorithm>
#include <queue>
#include <string>
#include <vector>
using namespace std;

struct edge {
    int v, w;
};
struct node {
    int dis, u;

    bool operator >(const node& n) const {
        return dis > n.dis;
    }
};

vector<string> citys = {
    "西宁", "兰州", "西安", "成都",
    "昆明", "贵阳", "柳州", "南宁",
    "株洲", "广州", "深圳", "南昌",
    "福州", "上海", "徐州", "郑州",
    "北京", "天津", "武汉",
};

vector<vector<edge>> e = {
    //0. 西宁
    {
        {1, 236},
    },
    //1. 兰州
    {
        {0, 236},
        {2, 676},
    },
    //2. 西安
    {
        {1, 676},
        {3, 842},
        {15, 511},
    },
    //3. 成都
    {
        {2, 842},
        {4, 1100},
        {5, 967},
    },
    //4. 昆明
    {
        {3, 1100},
        {5, 639},
    },
    //5. 贵阳
    {
        {3, 967},
        {4, 639},
        {8, 902},
        {6, 607},
    },
    //6. 柳州
    {
        {5, 607},
        {7, 255},
        {8, 679},
    },
    //7. 南宁
    {
        {6, 255},
    },
    //8. 株洲
    {
        {5, 902},
        {6, 679},
        {18, 409},
        {11,367},
    },
    //9. 广州
    {
        {8, 679},
        {10, 140},
    },
    //10. 深圳
    {
        {9, 140},
    },
    //11. 南昌
    {
        {8, 367},
        {12, 622},
        {13, 825},
    },
    //12. 福州
    {
        {11, 622},
    },
    //13. 上海
    {
        {11, 825},
        {14, 651},
    },
    //14. 徐州
    {
        {13, 651},
        {15, 349},
        {17, 674},
    },
    //15. 郑州
    {
        {2, 511},
        {16, 695},
        {14, 349},
        {18, 534},
    },
    //16. 北京
    {
        {15, 695},
        {17, 137},
    },
    //17. 天津
    {
        {16, 137},
        {14, 674},
    },
    //18. 武汉
    {
        {15, 534},
        {8, 409},
    },
};

int findEdgeByName(string name) {
    for(int i=0; i<citys.size(); i++) {
        if(citys[i] == name) return i;
    }
    return -1;
}

int dijstra(string start, string end, vector<int>& path) {
    int st = findEdgeByName(start);
    int ed = findEdgeByName(end);
    if(st == -1 || ed == -1) return -1;
    int n = e.size();
    vector<int> dis(n, 0x3f3f3f3f);
    vector<bool> vis(n, false);
    vector<int> prev(n, -1);
    priority_queue<node, vector<node>, greater<node>> q;
    dis[st] = 0;
    q.push({0, st});
    while(!q.empty()) {
        int u = q.top().u;
        q.pop();
        if(vis[u]) continue;
        vis[u] = true;
        for(auto ver : e[u]) {
            int v = ver.v;
            int w = ver.w;
            if(dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                prev[v] = u;
                q.push({dis[v], v});
            }
        }
    }

    for(int i = ed; i != -1; i = prev[i]) {
        path.push_back(i);
    }
    reverse(path.begin(), path.end());
    if(path.empty()) return -1;
    else return dis[ed];
}

int main() {
    string start, end;
    vector<int> path;
    cout<<"包含的城市有：\n";
    for(int i=0; i<citys.size(); i++) {
        cout<<i<<". "<<citys[i]<<endl;
    }
    cout<<"请输入起点和终点（以空格隔开）："<<endl;
    cin>>start;
    cin>>end;
    int dis = dijstra(start, end, path);
    if(dis != -1) {
        cout<<start<<"到"<<end<<"的最短路径为："<<endl;
        cout<<citys[path[0]];
        for(int i=1; i<path.size(); i++) {
            cout<<"->"<<citys[path[i]];
        }
        cout<<endl;
        cout<<"最短路径长度为："<<dis<<endl;
    } else {
        cout<<"路径不存在"<<endl;
    }

    return 0;
}