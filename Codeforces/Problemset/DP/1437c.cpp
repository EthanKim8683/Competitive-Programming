#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=200;
const I T=N;
const I MAX=1e9;

I t_arr[N];
I dp[N+1][2*T+1];

void cmb(I&a,I b){
  a=min(a,b);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I q;cin>>q;
  while(q--){
    I n;cin>>n;
    for(I i=0;i<=n;i++)for(I j=0;j<=2*T;j++)dp[i][j]=MAX;
    for(I i=0;i<n;i++){I t;cin>>t,t_arr[i]=t-1;}
    sort(t_arr,t_arr+n);
    dp[0][0]=0;
    for(I i=0;i<n;i++)for(I j=0;j<2*T;j++){
      cmb(dp[i+1][j+1],dp[i][j]+abs(t_arr[i]-j));
      cmb(dp[i][j+1],dp[i][j]);
    }
    printf("%i\n",*min_element(dp[n],dp[n]+2*T+1));
  }
}