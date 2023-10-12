#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
const I K=20;
const I MIN=-1e9;
I dp[1<<K][K];
void cmb(I&a,I b){
  a=max(a,b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+(1<<K)*K,MIN);
  S s;cin>>s;
  I n=s.size();
  for(I i=0;i<n;i++){
    I msk=0;
    for(I j=0;i+j<n;j++){
      I c=s[i+j]-'a';
      if(msk>>c&1)break;
      msk|=1<<c;
      if(j+1<=K-1)cmb(dp[msk][j+1],i);
    }
  }
  for(I i=0;i<(1<<K);i++)for(I j=1;j<=K-1;j++)for(I k=0;k<K;k++)if(~i>>k&1)cmb(dp[i|1<<k][j],dp[i][j]);
  I res=0;
  for(I i=0;i<n;i++){
    I msk=0;
    for(I j=0;j<=i;j++){
      I c=s[i-j]-'a';
      if(msk>>c&1)break;
      msk|=1<<c;
      cmb(res,j+1);
      for(I k=1;k<=K-1;k++)if(dp[msk^((1<<K)-1)][k]>i)cmb(res,j+1+k);
    }
  }
  printf("%i\n",res);
}
/*
for each dividing index and suffix ending at said index of length [1, 20], we
can look for a substring that does not overlap with the suffix

we can do this using bitmask dynamic programming, where we store the latest
substring for each bitmask of included letters

however, since queries just using this would take at most 2 ^ 20 operations
each, we can enable bits that aren't included so that simply inverting the
query input bitmask finds the answer above

but since a bitmask with fewer unique letters but appears later in the string
may override a bitmask with more unique letters that appears earlier, we
must also separate bitmasks by quantity of unique letters
*/