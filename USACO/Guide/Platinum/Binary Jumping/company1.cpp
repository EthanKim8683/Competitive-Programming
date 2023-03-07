#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=2e5;
const I LOGN=18;
vector<I>adjs[N];
I ancs[N][LOGN];
I deps[N];
void dfs(I a,I p,I d=0){
  deps[a]=d;
  ancs[a][0]=p;
  for(I i=1;i<LOGN;i++)ancs[a][i]=ancs[ancs[a][i-1]][i-1];
  for(auto b:adjs[a])dfs(b,a,d+1);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,q;cin>>n>>q;
  for(I i=1;i<n;i++){
    I e;cin>>e,e--;
    adjs[e].push_back(i);
  }
  dfs(0,0);
  while(q--){
    I x,k;cin>>x>>k,x--;
    if(k>deps[x]){printf("-1\n");continue;}
    for(I i=0;i<LOGN;i++)if(k>>i&1)x=ancs[x][i];
    printf("%i\n",x+1);
  }
}