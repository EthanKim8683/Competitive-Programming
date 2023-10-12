#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
const I M=20;
const I MAX=1e9;
I cnts[M][M];
I trns[M][1<<M];
I dp[1<<M];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  S s;cin>>s;
  for(I i=0;i+1<n;i++){
    I a=s[i]-'a',b=s[i+1]-'a';
    if(a!=b)cnts[a][b]++,cnts[b][a]++;
  }
  for(I i=0;i<m;i++){
    for(I j=0;j<m;j++)if(j!=i)trns[i][0]-=cnts[i][j];
    for(I j=0;j+1<(1<<m);j++){
      trns[i][j+1]=trns[i][j];
      for(I k=j^(j+1);k;k-=k&-k){
        I l=__builtin_ctz(k&-k);
        if(l!=i)trns[i][j+1]+=2*cnts[i][l]*(1-2*(j>>l&1));
      }
    }
  }
  fill_n(dp,1<<m,MAX),dp[0]=0;
  for(I i=0;i<(1<<m);i++)for(I j=0;j<m;j++)if(~i>>j&1)dp[i|1<<j]=min(dp[i|1<<j],dp[i]+__builtin_popcount(i)*trns[j][i]);
  printf("%i\n",dp[(1<<m)-1]);
}