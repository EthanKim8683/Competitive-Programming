#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=2e5;
const Lli MOD=998244353;
I a_arr[N];
vector<I>cpss;
vector<I>outs[N],incs[N];
B viss[N];
vector<I>tops;
void dfs1(I a){
  if(viss[a])return;
  viss[a]=1;
  for(auto b:outs[a])dfs1(b);
  tops.push_back(a);
}
void dfs2(I a){
  viss[a]=1;
  for(auto b:incs[a])if(!viss[b])dfs2(b);
}
Lli mpw(Lli x,I y){
  Lli res=1;
  for(;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)cpss.push_back(a_arr[i]);
  sort(cpss.begin(),cpss.end());
  cpss.erase(unique(cpss.begin(),cpss.end()),cpss.end());
  for(I i=0;i<n;i++)a_arr[i]=lower_bound(cpss.begin(),cpss.end(),a_arr[i])-cpss.begin();
  for(I i=0;i+1<n;i++){
    I a=a_arr[i],b=a_arr[i+1];
    if(a==b)continue;
    outs[a].push_back(b);
    incs[b].push_back(a);
  }
  for(I i=0;i<cpss.size();i++)dfs1(i);
  reverse(tops.begin(),tops.end());
  fill_n(viss,cpss.size(),0);
  I cnt=0;
  for(auto i:tops)if(!viss[i])dfs2(i),cnt++;
  printf("%lli\n",mpw(2,cnt-1));
}