#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=2e5;
const I K=N;
I a_arr[K];
vector<I>adjs[N];
B uses[N];
B viss[N];
void dfs(I a,I p=-1){
  for(auto b:adjs[a])if(b!=p){
    dfs(b,a);
    uses[a]|=uses[b];
    viss[a]|=viss[b];
  }
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,k;cin>>n>>k;
    I x,y;cin>>x>>y,x--,y--;
    for(I i=0;i<k;i++){I a;cin>>a,a_arr[i]=a-1;}
    for(I i=0;i<n;i++)adjs[i].clear();
    for(I i=0;i<n-1;i++){
      I v,u;cin>>v>>u,v--,u--;
      adjs[v].push_back(u);
      adjs[u].push_back(v);
    }
    fill_n(uses,n,0);
    fill_n(viss,n,0);
    uses[x]=uses[y]=1;
    for(I i=0;i<k;i++)uses[a_arr[i]]=1;
    viss[y]=1;
    dfs(x);
    I res=0;
    for(I i=0;i<n;i++){
      if(i==x)continue;
      if(viss[i]){res+=1;continue;}
      if(uses[i]){res+=2;continue;}
    }
    printf("%i\n",res);
  }
}