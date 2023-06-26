#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I LOGN=40;
const I LOGT=40;
Lli dp[LOGN+1][LOGT+2][2];
vector<I>dgts;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  Lli n,t;cin>>n>>t,n++;
  if(__builtin_popcountll(t)!=1)printf("0"),exit(0);
  I log=__builtin_ctzll(t);
  for(Lli i=n;i;i>>=1)dgts.push_back(i&1);
  reverse(dgts.begin(),dgts.end());
  I m=dgts.size();
  dp[0][0][1]=1;
  for(I i=0;i<m;i++)for(I j=0;j<=log+1;j++){
    if(dgts[i]==0)dp[i+1][j][1]+=dp[i][j][1];
    if(dgts[i]==1)dp[i+1][j][0]+=dp[i][j][1];
    dp[i+1][j][0]+=dp[i][j][0];
    if(j+1<=log+1){
      if(dgts[i]==1)dp[i+1][j+1][1]+=dp[i][j][1];
      dp[i+1][j+1][0]+=dp[i][j][0];
    }
  }
  printf("%lli\n",dp[m][log+1][0]+dp[m][log+1][1]-(t==1));
}