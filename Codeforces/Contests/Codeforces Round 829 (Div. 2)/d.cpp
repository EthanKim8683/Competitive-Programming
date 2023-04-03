#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=500000;
const I X=500000;

I a_arr[N];
I dp[X+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,x;cin>>n>>x;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)dp[a_arr[i]]++;
  for(I i=2;i<=x;i++){
    if(dp[i-1]%i)printf("No\n"),exit(0);
    dp[i]+=dp[i-1]/i;
  }
  printf("Yes\n");
}