#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=5000;

vector<I>adjs[N];
I dp1[N];
B dp2[N];
set<pair<I,I>>ress;
I n;

void dfs1(I a,I p=-1){
  dp1[a]=1;
  for(auto b:adjs[a])if(b!=p){
    dfs1(b,a);
    dp1[a]+=dp1[b];
  }
}

void dfs2(I a,I p=-1){
  fill_n(dp2,n,0);
  dp2[0]=dp2[n-dp1[a]]=1;
  for(auto b:adjs[a])if(b!=p){
    I sum=dp1[b];
    for(I i=n-sum-1;i>=0;i--)dp2[i+sum]|=dp2[i];
  }
  for(I i=1;i<n-1;i++)if(dp2[i])
    ress.insert({i,n-i-1});
  for(auto b:adjs[a])if(b!=p)dfs2(b,a);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  for(I i=0;i<n-1;i++){
    I x,y;cin>>x>>y,x--,y--;
    adjs[x].push_back(y);
    adjs[y].push_back(x);
  }
  dfs1(0),dfs2(0);
  printf("%i\n",ress.size());
  for(auto[a,b]:ress)printf("%i %i\n",a,b);
}