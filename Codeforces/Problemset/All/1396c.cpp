#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e6;
const Lli MAX=1e18;
I a_arr[N];
Lli dp[N+1][2];
void cmb(Lli&a,Lli b){
  a=min(a,b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+(N+1)*2,MAX);
  I n;Lli r1,r2,r3,d;cin>>n>>r1>>r2>>r3>>d;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  dp[0][0]=(n-1)*d;
  for(I i=0;i<n-1;i++){
    I a=a_arr[i],b=a_arr[i+1];
    cmb(dp[i+2][0],dp[i][0]+min(r2,a*min(r1,r3)+min(r1,r2))+min(r2,b*min(r1,r3)+min(r1,r2))+2*min(min(r1,r2),r3)+2*d);
    cmb(dp[i+2][1],dp[i][1]+min(r2,a*min(r1,r3)+min(r1,r2))+min(r2,b*min(r1,r3)+min(r1,r2))+2*min(min(r1,r2),r3)+2*d);
    cmb(dp[i+1][1],dp[i][0]+min(r2,a*min(r1,r3)+min(r1,r2))+min(min(r1,r2),r3)+(n-1-i)*d);
    cmb(dp[i+1][0],dp[i][0]+a*min(r1,r3)+r3);
    cmb(dp[i+1][0],dp[i][0]+min(r2,a*min(r1,r3)+min(r1,r2))+min(min(r1,r2),r3)+2*d);
    cmb(dp[i+1][1],dp[i][1]+a*min(r1,r3)+r3);
    cmb(dp[i+1][1],dp[i][1]+min(r2,a*min(r1,r3)+min(r1,r2))+min(min(r1,r2),r3));
  }
  I a=a_arr[n-1];
  cmb(dp[n][0],dp[n-1][0]+a*min(r1,r3)+r3);
  cmb(dp[n][0],dp[n-1][0]+min(r2,a*min(r1,r3)+min(r1,r2))+min(min(r1,r2),r3)+2*d);
  cmb(dp[n][1],dp[n-1][1]+a*min(r1,r3)+r3);
  cmb(dp[n][1],dp[n-1][1]+min(r2,a*min(r1,r3)+min(r1,r2))+min(min(r1,r2),r3)+2*d);
  printf("%lli\n",min(dp[n][0],dp[n][1]));
}
/*
we can simplify the guns as following:
- the pistol kills one normal monster and can damage the boss
- the laser gun kills all normal monsters and damages the boss
- the AWP kills one normal monster and can kill the boss

initially, (n - 1) * d time is used by default to move between levels

for each boss that is damaged but not killed, we can:
- keep a minimum such level and return after the final level, costing
  (n - 1 - i) * d time
- add 2 * d and visit another level before returning
- or a mix of either

for the final level, it is optimal to add 2 * d time if its boss is damaged
but not killed
*/