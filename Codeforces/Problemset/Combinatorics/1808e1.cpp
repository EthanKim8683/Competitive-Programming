#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=100;
const I K=30;
Lli dp[N+1][K][4];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;Lli m;cin>>n>>k>>m;
  Lli res=0;
  for(I s=0;s<k;s++){
    fill(&dp[0][0][0],&dp[0][0][0]+(N+1)*K*4,0);
    dp[0][0][0]=1;
    for(I i=0;i<n;i++)for(I x=0;x<k;x++)for(I y=0;y<k;y++)for(I j=0;j<2;j++)(dp[i+1][(x+y)%k][j|(y==s)]+=dp[i][x][j])%=m;
    (res+=dp[n][2*s%k][1])%=m;
  }
  if(k%2==0){
    for(I s=0;s<k/2;s++){
      I t=s+k/2;
      fill(&dp[0][0][0],&dp[0][0][0]+(N+1)*K*4,0);
      dp[0][0][0]=1;
      for(I i=0;i<n;i++)for(I x=0;x<k;x++)for(I y=0;y<k;y++)for(I j=0;j<4;j++)(dp[i+1][(x+y)%k][j|(y==s)<<1|(y==t)]+=dp[i][x][j])%=m;
      (res-=dp[n][2*s%k][3])%=m;
    }
  }
  printf("%lli\n",(res+m)%m);
}
/*
a number is lucky if there exists x - y[i] = 0 (mod k), where x is the sum
modulo k of y[j] such that j != i for all j in [0, n) and any i also in [0, n)

in addition, if x - y[i] = 0 (mod k), there can only exist a y[j] such that
the inequality still holds true if y[i] - y[j] = k / 2 (mod k) if k is even,
since y[j] = (x + (y[i] - y[j])) - y[i] + (y[i] - y[j]) = 0 (mod k)

for each digit s, we can count the number of numbers such that x - y[i] = 0
(mod k) for some i such that y[i] = s

then, if k is even, for each pair of digits (s, t) such that s - t = k / 2
(mod k), we can discount the number of numbers such that x - y[i] = 0 (mod k)
and x - y[j] = 0 (mod k) for some (i, j) such that y[i] = s and y[j] = t
*/