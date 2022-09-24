#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=2e5;
const Lli MIN=-1e18;

I a_arr[N];
vector<I>adjs[N];
Lli dp[N][2];

void dfs(I a){
  Lli eve1=0,odd1=a_arr[a];
  Lli eve3=0,odd3=MIN;
  for(auto b:adjs[a]){
    dfs(b);
    Lli eve2=eve1;
    eve2=max(eve2,odd1+dp[b][0]);
    eve2=max(eve2,eve1+dp[b][1]);
    Lli odd2=odd1;
    odd2=max(odd2,eve1+dp[b][0]);
    odd2=max(odd2,odd1+dp[b][1]);
    Lli eve4=eve3;
    eve4=max(eve4,odd3+dp[b][0]);
    eve4=max(eve4,eve3+dp[b][1]);
    Lli odd4=odd3;
    odd4=max(odd4,eve3+dp[b][0]);
    odd4=max(odd4,odd3+dp[b][1]);
    eve1=eve2,odd1=odd2;
    eve3=eve4,odd3=odd4;
  }
  dp[a][0]=odd1;
  dp[a][1]=eve3;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  I p,a;cin>>p>>a;
  a_arr[0]=a;
  for(I i=1;i<n;i++){
    I p,a;cin>>p>>a;
    adjs[p-1].push_back(i);
    a_arr[i]=a;
  }
  dfs(0);
  printf("%lli\n",dp[0][0]);
}