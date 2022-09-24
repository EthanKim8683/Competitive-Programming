#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using B=bool;

const I N=200;
const I MAX=1e9;

B dp[5];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    S s;cin>>s;
    B res=0;
    fill_n(dp,5,0);
    for(I i=0;i<n;i++){
      if(i>=0&&s.substr(i-0,i)=="")dp[0]=1;
      if(i>=1&&s.substr(i-1,i)=="2")dp[1]=1;
      if(i>=2&&s.substr(i-2,i)=="20")dp[2]=1;
      if(i>=3&&s.substr(i-3,i)=="202")dp[3]=1;
      if(i>=4&&s.substr(i-4,i)=="2020")dp[4]=1;
      if(i<=n-0&&s.substr(i,i+0)=="")res|=dp[4];
      if(i<=n-1&&s.substr(i,i+1)=="0")res|=dp[3];
      if(i<=n-2&&s.substr(i,i+2)=="20")res|=dp[2];
      if(i<=n-3&&s.substr(i,i+3)=="020")res|=dp[1];
      if(i<=n-4&&s.substr(i,i+4)=="2020")res|=dp[0];
    }
    printf("%s\n",res?"YES":"NO");
  }
}