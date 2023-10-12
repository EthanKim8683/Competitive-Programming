#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=2e5;
I w_arr[N];
vector<I>adjs[N];
queue<I>ques;
I degs[N];
B viss[N];
Lli res=0;
void add(I i){
  if(viss[i]||--degs[i]>1)return;
  viss[i]=1,ques.push(i);
}
Lli dfs1(I a,I p=-1){
  Lli res=0;
  for(auto b:adjs[a])if(b!=p)res=max(res,dfs1(b,a));
  return res+w_arr[a];
}
B dfs2(I a,I p=-1){
  if(!viss[a])return 1;
  for(auto b:adjs[a])if(b!=p&&dfs2(b,a)){
    viss[a]=0,res+=w_arr[a];
    return 1;
  }
  return 0;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>w_arr[i];
  for(I i=0;i<m;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs[u].push_back(v);
    adjs[v].push_back(u);
    degs[u]++,degs[v]++;
  }
  I s;cin>>s,s--;
  for(I i=0;i<n;i++)if(degs[i]<=1)add(i);
  while(ques.size()){
    I a=ques.front();ques.pop();
    for(auto b:adjs[a])add(b);
  }
  B all=1;
  for(I i=0;i<n;i++)all&=viss[i];
  if(all){
    printf("%lli\n",dfs1(s));
  }else{
    for(I i=0;i<n;i++)if(!viss[i])res+=w_arr[i];
    dfs2(s);
    Lli add=0;
    for(I i=0;i<n;i++)if(!viss[i])for(auto b:adjs[i])if(viss[b])add=max(add,dfs1(b,i));
    printf("%lli\n",res+add);
  }
}