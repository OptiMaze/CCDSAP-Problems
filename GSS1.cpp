#include<bits/stdc++.h>
using namespace std;

#define sync ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define ll long long
const ll maxn = 5e6+1;

struct node{
    ll sum,pre,suf,mxsub;
};

node lol={0,INT_MIN,INT_MIN,LONG_LONG_MIN};

node seg[maxn]; 

void merge(ll lel,ll l,ll r){
    seg[lel].mxsub=max(seg[l].mxsub,max(seg[r].mxsub,seg[l].suf+seg[r].pre));
    seg[lel].sum=seg[l].sum+seg[r].sum;
    seg[lel].pre=max(seg[l].pre,seg[l].sum+seg[r].pre);
    seg[lel].suf=max(seg[r].suf,seg[r].sum+seg[l].suf);
}

node Merge(node a,node b){
    node c;
    c.sum=a.sum+b.sum;
    c.mxsub=max(a.mxsub,max(b.mxsub,a.suf+b.pre));
    c.pre=max(a.pre,a.sum+b.pre);
    c.suf=max(b.suf,b.sum+a.suf);
    return c;
}

void upd(ll node,ll l,ll r,ll idx,ll val){
    if(l>idx||r<idx) return ;
    if(l==r){
        seg[node].sum=seg[node].pre=seg[node].suf=seg[node].mxsub=val;
        return ;
    }
    upd(2*node+1,l,(l+r)/2,idx,val);
    upd(2*node+2,(l+r)/2+1,r,idx,val);
    merge(node,2*node+1,2*node+2);
}

node query(ll nod,ll l,ll r,ll ql,ll qr){
    if(l>qr||r<ql) return lol;
    if(l>=ql&&r<=qr) return seg[nod];
    node a=query(2*nod+1,l,(l+r)/2,ql,qr);
    node b=query(2*nod+2,(l+r)/2+1,r,ql,qr);
    node c=Merge(a,b);
    return c;
}

int main(){
    sync
    #ifndef ONLINE_JUDGE
    // for getting input from input.txt
    freopen("input.txt", "r", stdin);
    // for writing output to output.txt
    freopen("output.txt", "w", stdout);
    #endif

        ll n;
        cin>>n;
        for(ll i=0;i<n;i++){
            ll x;
            cin>>x;
           upd(0,0,n-1,i,x);
        }
        ll q;
        cin>>q;
        while(q--){
            ll l,r;
            cin>>l>>r;
           cout<<query(0,0,n-1,l-1,r-1).mxsub<<endl;
        }
        return 0;
}
