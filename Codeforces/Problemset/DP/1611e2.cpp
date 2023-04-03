#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=2e5;
const I K=N;
const I MAX=1e9;
I x_arr[K];
vector<I>adjs[N];
I diss[N];
I dfs(I a,I p=-1,I d=0){
  I res=0;B inv=0;
  for(auto b:adjs[a])if(b!=p){
    I cur=dfs(b,a,d+1);
    cur==-1?inv=1:res+=cur;
    diss[a]=min(diss[a],diss[b]+1);
  }
  if(diss[a]<=d)return 1;
  if(inv)return-1;
  return res?:-1;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,k;cin>>n>>k;
    for(I i=0;i<k;i++){I x;cin>>x,x_arr[i]=x-1;}
    for(I i=0;i<n;i++)adjs[i].clear();
    for(I i=0;i<n-1;i++){
      I u,v;cin>>u>>v,u--,v--;
      adjs[u].push_back(v);
      adjs[v].push_back(u);
    }
    fill_n(diss,n,MAX);
    for(I i=0;i<k;i++)diss[x_arr[i]]=0;
    printf("%i\n",dfs(0));
  }
}