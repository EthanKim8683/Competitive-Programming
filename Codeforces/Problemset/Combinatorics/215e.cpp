#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=64;
Lli dp1[N+1][N+1][2];
Lli dp2[N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  Lli l,r;cin>>l>>r;
  auto dif=[&](Lli x,I b,I k,I t)->pair<I,I>{
    Lli y=0,z=0;
    for(I i=(b-1)%k;i<N;i+=k){
      y|=x&(1ll<<i);
      if(i<b)z|=(Lli)t<<i;
    }
    return{z!=y?__builtin_clzll(z^y):N,z<=y};
  };
  auto cnt=[&](Lli x){
    Lli res=0;
    for(I i=1;i<=N;i++){
      if((1ll<<(i-1))>x)break;
      fill_n(dp2,i,0);
      for(I j=1;j<i;j++)if(i%j==0){
        fill(&dp1[0][0][0],&dp1[0][0][0]+(N+1)*(N+1)*2,0);
        auto[a,b]=dif(x,i,j,1);
        dp1[1][a][b]=1;
        for(I k=1;k<j;k++)for(I l=0;l<=N;l++)for(I m=0;m<2;m++)for(I n=0;n<2;n++){
          auto[a,b]=min(dif(x,i-k,j,n),{l,m});
          dp1[k+1][a][b]+=dp1[k][l][m];
        }
        for(I k=0;k<=N;k++)dp2[j]+=dp1[j][k][1];
      }
      for(I j=1;j<i;j++)if(i%j==0)for(I k=j*2;k<i;k+=j)dp2[k]-=dp2[j];
      for(I j=1;j<i;j++)if(i%j==0)res+=dp2[j];
    }
    return res;
  };
  printf("%lli\n",cnt(r)-cnt(l-1));
}
/*
for an upper bound x, we can count for all periods k in [1, n] the number of
binary strings s less than or equal to x

the answer is the number of binary strings less than or equal to r minus the
number of binary strings less than or equal to l - 1

to count the number of valid binary strings for period k, we only need to
check the validity of the first k characters, where the first of the k
characters to result in a bit different from x (if any) is strictly less that
the corresponding bit in x

this can be found using dynamic programming
*/