#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using B=bool;
const I N=1e6;
const I K=N;
const I MAX=1e9;
I dp[K][3];
void cmb(I&a,I b){
  a=min(a,b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,k;cin>>n>>k;
    S s;cin>>s;
    for(I i=0;i<n;i++)s[i]-='0';
    I all=accumulate(s.begin(),s.end(),0);
    for(I i=0;i<k;i++)for(I j=0;j<3;j++)dp[i][j]=all;
    for(I i=0;i<n;i++){
      I j=i%k,x=s[i];
      I a=dp[j][0],b=dp[j][1],c=dp[j][2];
      dp[j][0]=dp[j][1]=dp[j][2]=MAX;
      a-=x,b-=x,c-=x;
      cmb(dp[j][0],a+x);
      cmb(dp[j][1],a+!x);
      cmb(dp[j][1],b+!x);
      cmb(dp[j][2],b+x);
      cmb(dp[j][2],c+x);
    }
    I res=MAX;
    for(I i=0;i<k;i++)for(I j=0;j<3;j++)cmb(res,dp[i][j]);
    printf("%i\n",res);
  }
}