#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using S=string;
const I A=10000;
const I B=30;
const I N=1e9;
map<pair<I,I>,I>dp;
Lli n;
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x=min(x,n);y;y>>=1,x=min(x*x,n))if(y&1)res=min(res*x,n);
  return res;
}
I dfs(I t,I a,I b){
  if(dp.find({a,b})!=dp.end())return dp[{a,b}];
  if(mpw(a,b)>=n)return dp[{a,b}]=-1;
  I res1=b!=1||dfs(t,a+1,b+1)!=-1?dfs(!t,a+1,b):(t+n-a)%2;
  I res2=a!=1||dfs(t,a+1,b+1)!=-1?dfs(!t,a,b+1):2;
  if(res1==t||res2==t)return dp[{a,b}]=t;
  if(res1==2||res2==2)return dp[{a,b}]=2;
  if(res1==-1||res2==-1)return dp[{a,b}]=!t;
  if(res1==!t||res2==!t)return dp[{a,b}]=!t;
  return dp[{a,b}]=2;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I a,b;cin>>a>>b>>n;
  printf("%s\n",(S[]){"Masha","Stas","Missing"}[dfs(0,a,b)].c_str());
}