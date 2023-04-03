#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=5000;
const I A=5000;
const I MAX=1e9;
const I MIN=-MAX;
I a_arr[N];
I lows[A+1],upps[A+1];
I dp1[N][N],dp2[N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  fill_n(lows,A+1,MAX),fill_n(upps,A+1,MIN);
  for(I i=0;i<n;i++){
    I a=a_arr[i];
    lows[a]=min(lows[a],i),upps[a]=max(upps[a],i);
  }
  for(I i=0;i<=A;i++){
    I low=lows[i],upp=upps[i];
    if(low!=MAX&&upp!=MIN)dp1[low][upp]=i;
  }
  for(I i=2;i<n;i++)for(I j=0;j+i<n;j++)dp1[j][j+i]^=dp1[j][j+i-1]^dp1[j+1][j+i]^dp1[j+1][j+i-1];
  for(I i=0;i<n;i++){
    I low=MAX,upp=MIN;
    for(I j=i;j<n;j++){
      I a=a_arr[j];
      low=min(low,lows[a]),upp=max(upp,upps[a]);
      if(low==i&&upp==j)dp2[j+1]=max(dp2[j+1],dp2[i]+dp1[i][j]);
    }
    dp2[i+1]=max(dp2[i+1],dp2[i]);
  }
  printf("%i\n",dp2[n]);
}