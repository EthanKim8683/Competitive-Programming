#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using Lli=long long int;
using B=bool;

const I N=3e5;
const Lli MOD=998244353;

B viss[N];
B cols[N];
vector<I>adjs[N];
I cnts[N][2];

B dfs(I a,B c){
  viss[a]=1,cols[a]=c;
  cnts[a][c]=1,cnts[a][!c]=0;
  B res=1;
  for(auto b:adjs[a]){
    if(viss[b]){res&=cols[b]==!c;continue;}
    res&=dfs(b,!c);
    cnts[a][0]+=cnts[b][0],cnts[a][1]+=cnts[b][1];
  }
  return res;
}

Lli pow(Lli x,I y){
  Lli res=1;
  while(y){
    if(y&1)(res*=x)%=MOD;
    (x*=x)%=MOD,y>>=1;
  }
  return res;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    fill_n(viss,n,0);
    for(I i=0;i<n;i++)adjs[i].clear();
    for(I i=0;i<m;i++){
      I u,v;cin>>u>>v,u--,v--;
      adjs[u].push_back(v);
      adjs[v].push_back(u);
    }
    B vld=1;
    Lli res=1;
    for(I i=0;i<n&&vld;i++){
      if(viss[i])continue;
      vld&=dfs(i,cols[i]);
      (res*=pow(2,cnts[i][0])+pow(2,cnts[i][1]))%=MOD;
    }
    if(!vld)res=0;
    printf("%lli\n",res);
  }
  return 0;
}