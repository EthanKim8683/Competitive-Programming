#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;

const I N=2e5;

vector<I>adjs[N];
vector<I>tops;
I viss[N];
I invs[N];
I cnts[N];
I res;

void dfs1(I a){
  if(viss[a])return;
  viss[a]=1;
  for(auto b:adjs[a])dfs1(b);
  tops.push_back(a);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)adjs[i].clear();
    tops.clear();
    for(I i=0;i<n;i++){
      I k;cin>>k;
      for(I j=0;j<k;j++){
        I a;cin>>a;
        adjs[a-1].push_back(i);
      }
    }
    fill_n(viss,n,0);
    for(I i=0;i<n;i++)dfs1(i);
    reverse(tops.begin(),tops.end());
    for(I i=0;i<n;i++)invs[tops[i]]=i;
    I vld=1;
    for(I i=0;i<n;i++)for(auto j:adjs[i])
      vld&=invs[j]>invs[i];
    if(!vld){printf("-1\n");continue;}
    res=0;
    fill_n(cnts,n,1);
    for(auto a:tops){
      res=max(res,cnts[a]);
      for(auto b:adjs[a])
        cnts[b]=max(cnts[b],cnts[a]+(b<a));
    }
    printf("%i\n",res);
  }
  return 0;
}