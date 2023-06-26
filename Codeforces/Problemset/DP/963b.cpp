#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=2e5;
vector<I>adjs[N];
B cols[N];
vector<I>ress;
B dfs1(I a,I p=-1){
  B res=adjs[a].size()%2;
  for(auto b:adjs[a])if(b!=p)res^=!dfs1(b,a);
  return cols[a]=res;
}
void dfs2(I a,I p=-1){
  for(auto b:adjs[a])if(b!=p&&cols[b]==0)dfs2(b,a);
  ress.push_back(a);
  for(auto b:adjs[a])if(b!=p&&cols[b]==1)dfs2(b,a);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I p;cin>>p,p--;
    if(p<0)continue;
    adjs[p].push_back(i);
    adjs[i].push_back(p);
  }
  if(dfs1(0))printf("NO\n"),exit(0);
  dfs2(0);
  printf("YES\n");
  for(auto i:ress)printf("%i\n",i+1);
}