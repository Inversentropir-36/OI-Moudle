#include <bits/stdc++.h>
using namespace std;

long long n,p,a,b,m,x,y,ans;

inline int read() {
	char c=getchar();
	while(!isdigit(c)) {
		c=getchar();
	}
	int x=0;
	while(isdigit(c)) {
		x=x*10+c-'0';
		c=getchar();
	}
	return x;
}

struct node{
	long long l,r,w,f;
}tree[1000000*4+1];

inline void build(long long k,long long ll,long long rr) {
	tree[k].l=ll,tree[k].r=rr;
	if(tree[k].l==tree[k].r) {
		tree[k].w=read();
		return;
	}
	int m=(ll+rr)/2;
	build(k*2,ll,m);
	build(k*2+1,m+1,rr);
	tree[k].w=tree[k*2].w+tree[k*2+1].w;
}

inline void down(long long k) {
	tree[k*2].f+=tree[k].f;
	tree[k*2+1].f+=tree[k].f;
	tree[k*2].w+=tree[k].f*(tree[k*2].r-tree[k*2].l+1);
	tree[k*2+1].w+=tree[k].f*(tree[k*2+1].r-tree[k*2+1].l+1);
	tree[k].f=0;
}
inline void ask_interval(long long k) {
	if(tree[k].l>=a&&tree[k].r<=b) {
		ans+=tree[k].w;
		return;
	}
	if(tree[k].f) down(k);
	int m=(tree[k].l+tree[k].r)/2;
	if(a<=m) ask_interval(k*2);
	if(b>m) ask_interval(k*2+1);
}

void add(long long k)
{
    if(tree[k].l>=a&&tree[k].r<=b)
    {
        tree[k].w+=(tree[k].r-tree[k].l+1)*x;
        tree[k].f+=x;
        return;
    }
    if(tree[k].f) down(k);
    int m=(tree[k].l+tree[k].r)/2;
    if(a<=m) add(k*2);
    if(b>m) add(k*2+1);
    tree[k].w=tree[k*2].w+tree[k*2+1].w;
}
int main(){
	int n=read(),m=read();
	build(1,1,n);
	for(int i=1; i<=m; i++) {
		int op=read();
		ans=0;
		if(op==1) {
			a=read();b=read();x=read();
			add(1);
		} else if(op==2) {
			a=read();b=read();
			ask_interval(1);
			cout<<ans<<endl;
		}
	}
}
