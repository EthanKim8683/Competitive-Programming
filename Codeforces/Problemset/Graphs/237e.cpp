#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using B=bool;

const I N=128;
const I MAX=1e9;
 
I adjs[N][N];
I viss[N];
I x;
I t=1;
 
I dfs(I a,I cur=MAX){
  if(a==x-1)return cur;
  if(viss[a]>=t)return 0;
  viss[a]=t;
  for(I b=0;b<x;b++)if(adjs[a][b]){
    I res=dfs(b,min(cur,adjs[a][b]));
    if(!res)continue;
    adjs[a][b]-=res,adjs[b][a]+=res;
    return res;
  }
  return 0;
}
 
I ffa(){
  I res=0,cur;
  while(cur=dfs(0))res+=cur,t++;
  return res;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  S t;cin>>t;
  I n;cin>>n;
  x=n+28;
  for(auto c:t)adjs[n+1+c-'a'][n+27]++;
  for(I i=0;i<n;i++){
    S s;I a;cin>>s>>a;
    adjs[0][i+1]=a;
    for(auto c:s)adjs[i+1][n+1+c-'a']++;
  }
  if(ffa()!=t.size())printf("-1\n"),exit(0);
  I res=0;
  for(I i=0;i<n;i++)res+=adjs[i+1][0]*(i+1);
  printf("%i\n",res);
}