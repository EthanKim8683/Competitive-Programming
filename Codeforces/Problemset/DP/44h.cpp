#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using Lli=long long int;

const I N=50;

Lli dp[N][10];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  S s;cin>>s;
  I n=s.size();
  fill_n(dp[0],10,1);
  for(I i=0;i+1<n;i++)for(I j=0;j<10;j++){
    I c=s[i+1]-'0'+j;
    if(c%2){
      dp[i+1][c/2+0]+=dp[i][j];
      dp[i+1][c/2+1]+=dp[i][j];
    }else{
      dp[i+1][c/2]+=dp[i][j];
    }
  }
  Lli res=accumulate(dp[n-1],dp[n-1]+10,(Lli)0);
  I j=s[0]-'0',rem=1;
  for(I i=0;i+1<n;i++){
    I c=s[i+1]-'0'+j;
    if(c%2){
      if(c/2+0==s[i+1]-'0'){j=c/2+0;continue;}
      if(c/2+1==s[i+1]-'0'){j=c/2+1;continue;}
    }else{
      if(c/2==s[i+1]-'0'){j=c/2;continue;}
    }
    rem=0;
  }
  printf("%lli\n",res-rem);
}