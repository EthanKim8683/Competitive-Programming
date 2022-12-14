#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using Lli=long long int;
const I N=100000;
Lli dp[N+1+1][2][2];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  S s;cin>>s;
  S t;cin>>t;
  dp[0][0][0]=1;
  for(I i=0;i<=n;i++)for(I j=0;j<2;j++)for(I k=0;k<2;k++){
    I x=i-j,y=i-k;
    if(x<0||y<0)continue;
    I a=x>=n?-1:s[x]-'a',b=y>=n?-1:t[y]-'a';
    for(I l=0;l<26;l++){
      I z=j+(l!=a),w=k+(l!=b);
      if(z>1||w>1)continue;
      dp[i+1][z][w]+=dp[i][j][k];
    }
  }
  printf("%lli\n",dp[n+1][1][1]);
}