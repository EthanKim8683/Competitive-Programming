#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=5000;
const I LOGA=13;
const I MAX=1e9;
I a_arr[N];
I dp[N+1][1<<LOGA];
void cmb(I&a,I b){
  a=min(a,b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<=n;i++)for(I j=0;j<(1<<LOGA);j++)dp[i][j]=MAX;
    for(I i=0;i<(1<<LOGA);i++)dp[0][i]=!!i;
    for(I i=0;i<n;i++){
      for(I j=0;j<(1<<LOGA);j++)cmb(dp[i+1][j],dp[i][a_arr[i]^j]+!!j);
      for(I j=0;j<(1<<LOGA);j++)cmb(dp[i+1][0],dp[i][j]+1);
    }
    printf("%i\n",*min_element(dp[n],dp[n]+(1<<LOGA)));
  }
}