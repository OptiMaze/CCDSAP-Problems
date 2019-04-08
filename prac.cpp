#include<bits/stdc++.h>
using namespace std;

const int maxn = 1e5+1;

vector<int> g[maxn];
bool vis[maxn];
int in[maxn],low[maxn];
int Time;
set<int> AP;

void dfs(int cur,int par){
    vis[cur]=true;
    in[cur]=low[cur]=Time++;
    int child=0;
    for(auto it:g[cur]){
        if(it==par) continue;
        if(vis[it]){
            low[cur]=min(low[cur],in[it]);
        }   
        else{
            dfs(it,cur);
            child++;
            low[cur]=min(low[cur],low[it]);
            if(par!=-1&&in[cur]<=low[it]){
                AP.insert(cur);
            }
        }
    }
    if(par==-1&&child>1){
        AP.insert(cur);
    }
}

void find_AP(int root){
    Time = 1;
    dfs(root,-1);
}

int main(){

    #ifndef ONLINE_JUDGE
    // for getting input from input.txt
    freopen("input.txt", "r", stdin);
    // for writing output to output.txt
    freopen("output.txt", "w", stdout);
    #endif

    while(1){
        int n,m;
        cin>>n>>m;
        if(n==0&&m==0) break;
        for(int i=1;i<=n;i++){
            g[i].clear();
            vis[i]=false;
        }
        AP.clear();
        while(m--){
            int x,y;
            cin>>x>>y;
            g[x].push_back(y);
            g[y].push_back(x);
        }
        for(int i=1;i<=n;i++){
            if(vis[i]==false){
                find_AP(i);
            }
        }
        cout<<AP.size()<<endl;
    }
    return 0;
}