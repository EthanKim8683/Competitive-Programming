#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
const Lli MOD=1e9+7;
vector<I>adjs[N];
Lli dp[N];
I cnts[N];
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
Lli inv(Lli x){
  return mpw(x,MOD-2);
}
void mul(I a,Lli fac){
  fac%=MOD;
  if(fac==0){
    cnts[a]++;
  }else{
    (dp[a]*=fac)%=MOD;
  }
}
void div(I a,Lli fac){
  fac%=MOD;
  if(fac==0){
    cnts[a]--;
  }else{
    (dp[a]*=inv(fac))%=MOD;
  }
}
Lli get(I a){
  if(cnts[a]>0){
    return 0;
  }else{
    return dp[a];
  }
}
void dfs1(I a){
  dp[a]=1;
  for(auto b:adjs[a]){
    dfs1(b);
    mul(a,get(b)+1);
  }
}
void dfs2(I a){
  for(auto b:adjs[a]){
    Lli fac=get(b)+1;
    div(a,fac);
    mul(b,get(a)+1);
    mul(a,fac);
    dfs2(b);
  }
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=1;i<n;i++){
    I p;cin>>p,p--;
    adjs[p].push_back(i);
  }
  dfs1(0),dfs2(0);
  for(I i=0;i<n;i++)printf("%lli ",get(i));
}
/*
the number of ways to solve for any node a's subtree is equal to the product of
the number of ways to solve each of its children plus one, since we can either
leave one bad road to the parent of a, or improve the road and allow the
children to determine the placement of their own bad roads
*/