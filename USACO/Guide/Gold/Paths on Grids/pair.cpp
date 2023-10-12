#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using B=bool;
using Lli=long long int;
const I N=2000;
const Lli MOD=1e9+7;
B dp1[N+1][N+1];
Lli dp2[N+1][N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    S s;cin>>s;
    S t;cin>>t;
    S x="",y="";
    for(auto c:s)if(c!='1')x+=c;
    for(auto c:t)if(c!='1')y+=c;
    for(I i=0;i<=x.size();i++)for(I j=0;j<=y.size();j++)dp1[i][j]=dp2[i][j]=0;
    dp1[0][0]=1;
    for(I i=0;i<=x.size();i++)for(I j=0;j<=y.size();j++){
      if(i<x.size()){
        if(x[i]=='+')(dp2[i+1][j]+=dp1[i][j]+dp2[i][j])%=MOD;
        if(x[i]=='0')dp1[i+1][j]|=1;
        if(x[i]>='2')dp1[i+1][j]|=dp1[i][j],(dp2[i+1][j]+=dp2[i][j])%=MOD;
      }
      if(j<y.size()){
        if(y[j]=='+')(dp2[i][j+1]+=dp1[i][j]+dp2[i][j])%=MOD;
        if(y[j]=='0')dp1[i][j+1]|=1;
        if(y[j]>='2')dp1[i][j+1]|=dp1[i][j],(dp2[i][j+1]+=dp2[i][j])%=MOD;
      }
      if(i<x.size()&&j<y.size()){
        if(x[i]=='+'&&y[j]=='+')(dp2[i+1][j+1]-=dp1[i][j]+dp2[i][j])%=MOD;
        if(x[i]>='2'&&y[j]>='2')(dp2[i+1][j+1]-=dp2[i][j])%=MOD;
      }
    }
    printf("%lli\n",(dp1[x.size()][y.size()]+dp2[x.size()][y.size()]+MOD)%MOD);
  }
}