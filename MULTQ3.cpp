#include<bits/stdc++.h>
using namespace std;

const int maxn = 1e6;

struct node{
    int a,b,c;
};

node seg[maxn];
int lazy[maxn];

void add(int n0,int n1,int n2){
    seg[n0].a=seg[n1].a+seg[n2].a;
    seg[n0].b=seg[n1].b+seg[n2].b;
    seg[n0].c=seg[n1].c+seg[n2].c;
}

void fix(int nod){
    int temp=seg[nod].c;
    seg[nod].c=seg[nod].b;
    seg[nod].b=seg[nod].a;
    seg[nod].a=temp;
}

void propogate(int nod,int l,int r){
    if(lazy[nod]){
        int val=lazy[nod]%3;
        if(val==1){
            fix(nod);
        }
        else if(val==2){
            fix(nod);
            fix(nod);
        }
        if(l!=r){
            lazy[2*nod+1]+=lazy[nod];
            lazy[2*nod+2]+=lazy[nod];
        }
        lazy[nod]=0;
    }
}

void upd(int nod,int l,int r,int ql,int qr){
    propogate(nod,l,r);
    if(r<ql||l>qr) return ;
    if(l>=ql&&r<=qr){
        fix(nod);
        if(l!=r){
            lazy[2*nod+1]+=1;
            lazy[2*nod+2]+=1;
        }
        return ;
    }
    upd(2*nod+1,l,(l+r)/2,ql,qr);
    upd(2*nod+2,(l+r)/2+1,r,ql,qr);
    add(nod,2*nod+1,2*nod+2);
}   

int query(int nod,int l,int r,int ql,int qr){
    propogate(nod,l,r);
    if(l>qr||r<ql) return 0;
    if(l>=ql&&r<=qr){
        return seg[nod].c;
    }
    return query(2*nod+1,l,(l+r)/2,ql,qr)+query(2*nod+2,(l+r)/2+1,r,ql,qr);
}

void divide(int node,int l,int r){
    if(l>r) return ;
    if(l==r){
        seg[node].c=1;
        seg[node].b=0;
        seg[node].a=0;
        return ;
    }
    int mid=(l+r)/2;
    divide(2*node+1,l,mid);
    divide(2*node+2,mid+1,r);
    add(node,2*node+1,2*node+2);
}

int main(){

    #ifndef ONLINE_JUDGE
    // for getting input from input.txt
    freopen("input.txt", "r", stdin);
    // for writing output to output.txt
    freopen("output.txt", "w", stdout);
    #endif

    int n,q;
    cin>>n>>q;
    divide(0,0,n-1);
    while(q--){
        int ty,l,r;
        cin>>ty>>l>>r;
        if(ty==0){
            upd(0,0,n-1,l,r);
        }
        else{
            cout<<query(0,0,n-1,l,r)<<endl;
        }
    }
    return 0;
}
