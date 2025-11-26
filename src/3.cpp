#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
using namespace std;

class Vertex {
public:
    string name; //课程名称
    vector<Vertex*> pre; //前置要求
    Vertex(string n, vector<Vertex*> p) {
        this->name = n;
        this->pre = p;
    }
};

class GraphAdjList {
public:
    unordered_map<Vertex*, vector<Vertex*>> adjList;
    unordered_map<Vertex*, int> in;
    GraphAdjList(vector<Vertex*> vets) {
        for(auto vet : vets) {
            addVertex(vet);
        }
        for(auto vet : vets) {
            addEdge(vet);
        }
    }
    ~GraphAdjList() {
        for(auto v : adjList) {
            delete v.first;
        }
    }
private:
    void addVertex(Vertex* vet) {
        if(adjList.count(vet)) return;
        adjList[vet] = vector<Vertex*>();
        in[vet] = 0;
        return;
    }
    void addEdge(Vertex* vet) {
        for(auto e : vet->pre) {
            if(adjList.count(e) == 0) return;
            adjList[e].push_back(vet);
            in[vet]++;
        }
        return;
    }
    void delVertex(Vertex* vet) {
        if(adjList.count(vet)) {
            //删除以vet为尾的边
            for(auto v : adjList[vet]) {
                if(in.count(v)) {
                    in[v]--;
                }
            }
            //删除以vet为头的边
            for(auto v : adjList) {
                int len = v.second.size();
                for(int i = 0; i < len; i++) {
                    if(v.second[i] == vet) {
                        v.second.erase(v.second.begin() + i);
                    }
                }
            }
            //删除vet
            adjList.erase(vet);
            in.erase(vet);
            delete vet;
        } else return;
    }
};

Vertex* findVetByName(string name, vector<Vertex*> vets) {
    for(auto vet : vets) {
        if(vet->name == name) return vet;
    }
    return NULL;
}

int main() {
    int n = 0;
    vector<Vertex*> vets;
    cout<<"请输入课程总数：";
    cin>>n;
    for(int i = 1; i <= n; i++) {
        string name;
        vector<Vertex*> pre;
        cout<<"请输入课程"<<i<<"名称：";
        cin>>name;
        Vertex* temp = new Vertex(name, pre);
        vets.push_back(temp);
    }
    for(auto vet : vets) {
        int n;
        cout<<"请输入"<<vet->name<<"的前置课程数量：";
        cin>>n;
        if(n > vets.size() - 1) {
            cout<<"前置课程数量超过上限"<<endl;
            return -1;
        }
        for(int i = 1; i <= n; i++) {
            string preName;
            cout<<"请输入"<<vet->name<<"的前置课程"<<i<<"名称："<<endl;
            cin>>preName;
            Vertex* pre = findVetByName(preName, vets);
            if(pre) vet->pre.push_back(pre);
            else {
                cout<<"前置课程不存在或名称有误"<<endl;
                i--;
            }
        }
    }

    GraphAdjList graph(vets);

    return 0;
}