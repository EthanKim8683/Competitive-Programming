#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I Q=1e5;
const I D=9;

I a_arr[Q];
I lims[]={0,0,19,23,119,199,299,95,559,143};
B dp[D+1][559+1];

B cons(I i,I d){
  for(;i;i/=10)if(i%10==d)return 1;
  return 0;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  for(I i=1;i<=D;i++){
    for(I j=0;j<=lims[i];j++)dp[i][j]=cons(j,i);
    for(I j=0;j<=lims[i];j++)for(I k=0;k<=lims[i];k++)
      if(j+k<=lims[i])dp[i][j+k]|=dp[i][j]&&dp[i][k];
  }
  while(t--){
    I q,d;cin>>q>>d;
    while(q--){
      I a;cin>>a;
      printf("%s\n",a>lims[d]||dp[d][a]?"YES":"NO");
    }
  }
}