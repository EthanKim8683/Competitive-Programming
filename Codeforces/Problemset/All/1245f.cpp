#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I LOGR=30;
vector<I>lows,upps;
Lli dp[LOGR+1][2][2][2][2];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    fill(&dp[0][0][0][0][0],&dp[0][0][0][0][0]+(LOGR+1)*2*2*2*2,0);
    I l,r;cin>>l>>r;
    lows.clear(),upps.clear();
    for(I t=l;t;t>>=1)lows.push_back(t&1);
    for(I t=r;t;t>>=1)upps.push_back(t&1);
    while(lows.size()<upps.size())lows.push_back(0);
    reverse(lows.begin(),lows.end());
    reverse(upps.begin(),upps.end());
    I n=upps.size();
    dp[0][1][1][1][1]=1;
    for(I i=0;i<n;i++)for(I j=0;j<2;j++)for(I k=0;k<2;k++)for(I l=0;l<2;l++)for(I m=0;m<2;m++){
      I low=lows[i],upp=upps[i];
      for(I t=0;t<2;t++){
        if(j==1&&t<low)continue;
        if(k==1&&t>upp)continue;
        for(I u=0;u<2;u++){
          if(l==1&&u<low)continue;
          if(m==1&&u>upp)continue;
          if(t&u)continue;
          dp[i+1][j==1&&t==low][k==1&&t==upp][l==1&&u==low][m==1&&u==upp]+=dp[i][j][k][l][m];
        }
      }
    }
    Lli res=0;
    for(I i=0;i<2;i++)for(I j=0;j<2;j++)for(I k=0;k<2;k++)for(I l=0;l<2;l++)res+=dp[n][i][j][k][l];
    printf("%lli\n",res);
  }
}
/*
if a & b != 0, a + b != a ^ b, since any bit shared by a and b will not be
carried

to find the number of pairs (a, b) such that a & b = 0 and l <= a <= r and
l <= b <= r, we can use digit dynamic programming
*/