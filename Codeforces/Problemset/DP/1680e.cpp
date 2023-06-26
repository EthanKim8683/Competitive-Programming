#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
const I N=2e5;
const I MAX=1e9;
I dp[N+1][1<<2];
void cmb(I&a,I b){
  a=min(a,b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    S s1;cin>>s1;
    S s2;cin>>s2;
    for(I i=0;i<=n;i++)for(I j=0;j<(1<<2);j++)dp[i][j]=MAX;
    I j=0;
    dp[0][0b00]=0;
    for(I i=0;i<n;i++){
      if(s1[i]!='*'&&s2[i]!='*'){
        cmb(dp[i+1][0b00],dp[i][0b00]);
        cmb(dp[i+1][0b01],dp[i][0b01]+1);
        cmb(dp[i+1][0b10],dp[i][0b01]+2);
        cmb(dp[i+1][0b01],dp[i][0b10]+2);
        cmb(dp[i+1][0b10],dp[i][0b10]+1);
      }
      if(s1[i]=='*'&&s2[i]!='*'){
        cmb(dp[i+1][0b01],dp[i][0b00]);
        cmb(dp[i+1][0b10],dp[i][0b00]+1);
        cmb(dp[i+1][0b01],dp[i][0b01]+1);
        cmb(dp[i+1][0b10],dp[i][0b01]+2);
        cmb(dp[i+1][0b01],dp[i][0b10]+2);
        cmb(dp[i+1][0b10],dp[i][0b10]+2);
        j=i;
      }
      if(s1[i]!='*'&&s2[i]=='*'){
        cmb(dp[i+1][0b01],dp[i][0b00]+1);
        cmb(dp[i+1][0b10],dp[i][0b00]);
        cmb(dp[i+1][0b01],dp[i][0b01]+2);
        cmb(dp[i+1][0b10],dp[i][0b01]+2);
        cmb(dp[i+1][0b01],dp[i][0b10]+2);
        cmb(dp[i+1][0b10],dp[i][0b10]+1);
        j=i;
      }
      if(s1[i]=='*'&&s2[i]=='*'){
        cmb(dp[i+1][0b01],dp[i][0b00]+1);
        cmb(dp[i+1][0b10],dp[i][0b00]+1);
        cmb(dp[i+1][0b01],dp[i][0b01]+2);
        cmb(dp[i+1][0b10],dp[i][0b01]+2);
        cmb(dp[i+1][0b01],dp[i][0b10]+2);
        cmb(dp[i+1][0b10],dp[i][0b10]+2);
        j=i;
      }
    }
    printf("%i\n",min(dp[j+1][0b10],dp[j+1][0b01]));
  }
}