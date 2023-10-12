#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lf=long double;
const I K=1000;
const I P=1000;
const I D=10000;
Lf dp[D+1][K+1];
vector<I>prbs;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I k,q;cin>>k>>q;
  dp[0][0]=1;
  for(I i=0;i<D;i++)for(I j=0;j<=k;j++){
    dp[i+1][j+1]+=(Lf)(k-j)/k*dp[i][j];
    dp[i+1][j]+=(Lf)j/k*dp[i][j];
  }
  for(I i=0;i<=D;i++)prbs.push_back(dp[i][k]*2000);
  while(q--){
    I p;cin>>p;
    printf("%i\n",lower_bound(prbs.begin(),prbs.end(),p)-prbs.begin());
  }
}