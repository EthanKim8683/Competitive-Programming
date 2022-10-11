#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;

const I N=5e5;
const I MIN=-1e9;

I dp[26][26];

void cmb(I&a,I b){
  a=max(a,b);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+26*26,MIN);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    S s;cin>>s;
    I a=s.front()-'a',b=s.back()-'a';
    for(I j=0;j<26;j++)if(dp[j][a]!=MIN)cmb(dp[j][b],dp[j][a]+s.size());
    cmb(dp[a][b],s.size());
  }
  I res=MIN;
  for(I i=0;i<26;i++)res=max(res,dp[i][i]);
  printf("%i\n",res==MIN?0:res);
}