#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;
using B=bool;

const I N=2e5;
const I P=2e5;
const Lli MOD=1e9+7;

I a_arr[N];
Lli dp[P+1];
set<I>viss;

B dfs(I a){
  if(a<1)return 0;
  B res=viss.count(a);
  if((a-1)%2==0)res|=dfs((a-1)/2);
  if(a%4==0)res|=dfs(a/4);
  return res;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,p;cin>>n>>p;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  sort(a_arr,a_arr+n);
  for(I i=0;i<n;i++){
    I a=a_arr[i];
    if(!dfs(a))dp[32-__builtin_clz(a)]++;
    viss.insert(a);
  }
  for(I i=0;i<p;i++){
    if(i+1<=p)(dp[i+1]+=dp[i])%=MOD;
    if(i+2<=p)(dp[i+2]+=dp[i])%=MOD;
  }
  Lli res=0;
  for(I i=0;i<=p;i++)(res+=dp[i])%=MOD;
  printf("%lli\n",res);
}