#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;
const I A=1e5;

I a_arr[N];
B viss[A+1];
I dp[N];
I cnt=0;

void add(I i){
  if(viss[i])return;
  viss[i]=1,cnt++;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=n-1;i>=0;i--){
    add(a_arr[i]);
    dp[i]=cnt;
  }
  while(m--){
    I l;cin>>l;
    printf("%i\n",dp[l-1]);
  }
}