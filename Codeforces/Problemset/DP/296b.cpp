#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using C=char;
using Lli=long long int;
const I N=1e5;
const Lli MOD=1e9+7;
Lli dp[N+1][2][2];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  S s;cin>>s;
  S w;cin>>w;
  dp[0][0][0]=1;
  for(I i=0;i<n;i++){
    C a=s[i],b=w[i];
    if(a=='?'&&b=='?'){
      for(I c=0;c<2;c++)for(I d=0;d<2;d++)for(I e=0;e<=9;e++)for(I f=0;f<=9;f++)(dp[i+1][c||(e<f)][d||(e>f)]+=dp[i][c][d])%=MOD;
    }
    if(a=='?'&&b!='?'){
      I f=b-'0';
      for(I c=0;c<2;c++)for(I d=0;d<2;d++)for(I e=0;e<=9;e++)(dp[i+1][c||(e<f)][d||(e>f)]+=dp[i][c][d])%=MOD;
    }
    if(a!='?'&&b=='?'){
      I e=a-'0';
      for(I c=0;c<2;c++)for(I d=0;d<2;d++)for(I f=0;f<=9;f++)(dp[i+1][c||(e<f)][d||(e>f)]+=dp[i][c][d])%=MOD;
    }
    if(a!='?'&&b!='?'){
      I e=a-'0',f=b-'0';
      for(I c=0;c<2;c++)for(I d=0;d<2;d++)(dp[i+1][c||(e<f)][d||(e>f)]+=dp[i][c][d])%=MOD;
    }
  }
  printf("%lli\n",dp[n][1][1]);
}