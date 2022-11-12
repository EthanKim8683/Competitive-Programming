#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using Lli=long long int;
using C=char;

const I N=1e5;
const Lli MAX=1e18;

I a_arr[N];
Lli dp[N+1][4];

void cmb(Lli&a,Lli b){
  a=min(a,b);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+(N+1)*4,MAX);
  I n;cin>>n;
  S s;cin>>s;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  dp[0][0]=0;
  for(I i=0;i<n;i++){
    C c=s[i];I a=a_arr[i];
    if(c=='h')cmb(dp[i+1][1],dp[i][0]);
    if(c=='a')cmb(dp[i+1][2],dp[i][1]);
    if(c=='r')cmb(dp[i+1][3],dp[i][2]);
    if(c=='h')cmb(dp[i+1][0],dp[i][0]+a);
    else cmb(dp[i+1][0],dp[i][0]);
    if(c=='a')cmb(dp[i+1][1],dp[i][1]+a);
    else cmb(dp[i+1][1],dp[i][1]);
    if(c=='r')cmb(dp[i+1][2],dp[i][2]+a);
    else cmb(dp[i+1][2],dp[i][2]);
    if(c=='d')cmb(dp[i+1][3],dp[i][3]+a);
    else cmb(dp[i+1][3],dp[i][3]);
  }
  printf("%lli\n",*min_element(dp[n],dp[n]+4));
}