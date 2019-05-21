#include<bits/stdc++.h>
using namespace std;


#define fi first 
#define se second
#define mp make_pair
#define forn(i,n) for(ll i=0;i<n;i++)

typedef long long ll;

const ll maxn = 1e5+1;

vector<pair<ll,ll> > g[maxn];

ll dijkstra(ll source,ll n){
    priority_queue<pair<ll,pair<ll,ll> >,vector<pair<ll,pair<ll,ll> > >,
    greater<pair<ll,pair<ll,ll> > > > pq;
    vector<ll> dist(n,LONG_LONG_MAX);
    vector<ll> last(n,LONG_LONG_MAX);
    vector<bool> vis(n,false);
    dist[source] = 0;
    ll span = 0;
    pq.push(mp(0,mp(0,0)));
    while(!pq.empty()){
        auto val = pq.top();
        pq.pop();
        if(vis[val.se.se]) continue;
        vis[val.se.se] = true;
        span+=val.se.fi;
        for(auto it:g[val.se.se]){
            if(dist[it.se]>val.fi+it.fi){
                dist[it.se] = val.fi+it.fi;
                last[it.se] = it.fi;
                pq.push(mp(dist[it.se],mp(last[it.se],it.se)));
            }
            else if(dist[it.se]==val.fi+it.fi){
                if(it.fi<last[it.se]){
                    pq.push(mp(dist[it.se],mp(it.fi,it.se)));
                    last[it.se] = it.fi;
                }
            }
        }
    }
    return span;
}

int main(){

    #ifndef ONLINE_JUDGE
    // for getting input from input.txt
    freopen("input.txt", "r", stdin);
    // for writing output to output.txt
    freopen("output.txt", "w", stdout);
    #endif

    ll t;
    cin>>t;
    while(t--){
        ll n,m;
        cin>>n>>m;
        forn(i,n) g[i].clear();
        while(m--){
            ll u,v,w;
            cin>>u>>v>>w;
            g[u].push_back(make_pair(w,v));
            g[v].push_back(make_pair(w,u));
        }
        ll one = dijkstra(0,n);
        vector<bool> vis(n,false);
        set<pair<ll,ll> > pq;
        pq.insert(mp(0,0));
        ll two = 0;
        ll viss = 0;
        while(!pq.empty()){
            auto val = *pq.begin();
            pq.erase(pq.begin());
            if(vis[val.se]) continue;
            vis[val.se] = true;
            viss++;
            two += val.fi;
            for(auto it:g[val.se]){
                if(vis[it.se]==true) continue;
                pq.insert(it);
            }
        }
        if(viss!=n){
            cout<<"NO";
        }
        else{
            one==two? cout<<"YES":cout<<"NO";

        }
        cout<<endl;
        // forn(i,n) g[i].clear();
    }
    return 0;

}
