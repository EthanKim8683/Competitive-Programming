#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=1e6;

I dp[N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  dp[0]=1;
  for(I i=0;i<N;i++){
    if(i+2020<=N)dp[i+2020]+=dp[i];
    if(i+2021<=N)dp[i+2021]+=dp[i];
  }
  while(t--){
    I n;cin>>n;
    printf("%s\n",dp[n]?"YES":"NO");
  }
}