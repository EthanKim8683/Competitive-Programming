#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;

const I N=100;
const I MAX=1e9;

I dp[N+1][2];
I pars[N+1][2];

void add(I i,I j,I k,I c){
  if(dp[i][k]+c>=dp[i+1][j])return;
  dp[i+1][j]=dp[i][k]+c,pars[i+1][j]=k;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    S s;cin>>s;
    for(I i=0;i<=n;i++)for(I j=0;j<2;j++)dp[i][j]=MAX;
    dp[0][0]=dp[0][1]=0;
    for(I i=0;i<n;i++){
      if(s[i]=='?'){
        add(i,0,0,1);
        add(i,0,1,0);
        add(i,1,0,0);
        add(i,1,1,1);
      }else if(s[i]=='R'){
        add(i,0,0,1);
        add(i,0,1,0);
      }else if(s[i]=='B'){
        add(i,1,0,0);
        add(i,1,1,1);
      }
    }
    S res="";
    I j=dp[n][1]<dp[n][0];
    for(I i=n;i>0;i--){
      res=(j?"B":"R")+res;
      j=pars[i][j];
    }
    printf("%s\n",res.c_str());
  }
}