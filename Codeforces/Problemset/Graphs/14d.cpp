#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=200;

vector<pair<I,I>>adjs[N];
B viss[N];
I r,rd;

void dfs(I a,I j,I p=-1,I d=0){
  viss[a]=1;
  if(d>=rd)r=a,rd=d;
  for(auto[b,k]:adjs[a])if(k!=j&&b!=p)dfs(b,j,a,d+1);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n-1;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[a].push_back({b,i});
    adjs[b].push_back({a,i});
  }
  I res=0;
  for(I i=0;i<n-1;i++){
    fill_n(viss,n,0);
    I tot=1;
    rd=0;
    for(I j=0;j<n;j++)if(!viss[j]){dfs(j,i),dfs(r,i);break;}
    tot*=rd;
    rd=0;
    for(I j=0;j<n;j++)if(!viss[j]){dfs(j,i),dfs(r,i);break;}
    tot*=rd;
    res=max(res,tot);
  }
  printf("%i\n",res);
  return 0;
}