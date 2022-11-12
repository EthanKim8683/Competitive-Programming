#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using B=bool;

const I N=2e5;
const I MAX=1e9;

I dp[N-3][1<<4];

B chk(I x){
  if(x==0b0101)return 1;
  if(x==0b0011)return 1;
  return 0;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    S s;cin>>s;
    S a;cin>>a;
    for(auto&i:s)i-='(';
    for(auto&i:a)i-='0';
    for(I i=0;i<n-3;i++)for(I j=0;j<(1<<4);j++)dp[i][j]=MAX;
    for(I i=0;i<(1<<4);i++){
      if(a[0]&&!chk(i))continue;
      I cst=0;
      for(I j=0;j<4;j++)cst+=(i>>(3-j)&1)!=s[j];
      dp[0][i]=cst;
    }
    for(I i=0;i+1<n-3;i++)for(I j=0;j<(1<<4);j++){
      I c=s[i+4],x=(j<<1|c)&0b1111,y=(j<<1|!c)&0b1111;
      if(!a[i+1]||chk(x))dp[i+1][x]=min(dp[i+1][x],dp[i][j]);
      if(!a[i+1]||chk(y))dp[i+1][y]=min(dp[i+1][y],dp[i][j]+1);
    }
    I res=*min_element(dp[n-4],dp[n-4]+(1<<4));
    printf("%i\n",res==MAX?-1:res);
  }
}