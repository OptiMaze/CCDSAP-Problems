#include<bits/stdc++.h>
using namespace std;

#define fi first
#define se second

const int maxn = 1e5+1;

vector<int> g[maxn];
bool vis[maxn];
int in[maxn],low[maxn];
int Time;
set<pair<int,int> > Bridges;

void dfs(int cur,int par){
    vis[cur]=true;
    in[cur]=low[cur]=Time++;
    for(auto it:g[cur]){
        if(it==par) continue;
        if(vis[it]){
            low[cur]=min(low[cur],in[it]);
        }   
        else{
            dfs(it,cur);
            low[cur]=min(low[cur],low[it]);
            if(in[cur]<low[it]){
                int a=cur,b=it;
                if(a>b) swap(a,b);
                Bridges.insert(make_pair(a,b));
            }
        }
    }

}

void find_Bridges(int root){
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
        int t;
        cin>>t;
        for(int test=1;test<=t;test++){
        int n,m;
        cin>>n>>m;
        for(int i=1;i<=n;i++){
            g[i].clear();
            vis[i]=false;
        }
        Bridges.clear();
        while(m--){
            int x,y;
            cin>>x>>y;
            g[x].push_back(y);
            g[y].push_back(x);
        }
        for(int i=1;i<=n;i++){
            if(vis[i]==false){
                find_Bridges(i);
            }
        }
        cout<<"Caso #"<<test<<endl;
        if(Bridges.empty()){
            cout<<"Sin bloqueos"<<endl;
        }
        else{
            cout<<Bridges.size()<<endl;
            for(auto it:Bridges){
                pair <int,int> ans = it;
                cout<<ans.fi<<" "<<ans.se<<endl;
            }
        }
    }
    return 0;
}
