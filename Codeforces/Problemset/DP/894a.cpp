#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;

I dp[3+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  S s;cin>>s;
  dp[0]=1;
  for(auto c:s){
    if(c=='A')dp[2]+=dp[1];
    if(c=='Q')dp[1]+=dp[0],dp[3]+=dp[2];
  }
  printf("%i\n",dp[3]);
}