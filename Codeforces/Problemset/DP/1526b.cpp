#include<iostream>
#include<cstdio>

using namespace std;

using I=int;
using B=bool;

const I X=11;
const I Y=111;
const I Z=X*Y-X-Y;

B dp[Z+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  dp[0]=1;
  for(I i=0;i<=Z;i++){
    if(i+X<=Z)dp[i+X]|=dp[i];
    if(i+Y<=Z)dp[i+Y]|=dp[i];
  }
  while(t--){
    I x;cin>>x;
    if(x>Z)printf("YES\n");
    else printf("%s\n",dp[x]?"YES":"NO");
  }
  return 0;
}