#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const I A=70;
const I P=19;
const Lli MOD=1e9+7;
I a_arr[N];
I cnts[A];
Lli dp[2][1<<P];
I prms[P],eras[A+1];
Lli pows[N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill_n(eras,A+1,-1);
  for(I i=2,j=0;i<=A;i++)if(eras[i]==-1){
    for(I k=i*i;k<=A;k+=i)if(eras[k]==-1)eras[k]=j;
    eras[i]=j,prms[j++]=i;
  }
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)cnts[a_arr[i]-1]++;
  pows[0]=1;
  for(I i=1;i<=n;i++)pows[i]=pows[i-1]*2%MOD;
  dp[0][0]=1;
  for(I i=0;i<A;i++){
    I cnt=cnts[i];
    if(cnt){
      I msk=0;
      for(I k=i+1;k>1;k/=prms[eras[k]])msk^=1<<eras[k];
      for(I j=0;j<(1<<P);j++){
        (dp[(i+1)%2][j^msk]+=dp[i%2][j]*pows[cnt-1])%=MOD;
        (dp[(i+1)%2][j]+=dp[i%2][j]*pows[cnt-1])%=MOD;
        dp[i%2][j]=0;
      }
    }else{
      for(I j=0;j<(1<<P);j++){
        (dp[(i+1)%2][j]+=dp[i%2][j])%=MOD;
        dp[i%2][j]=0;
      }
    }
  }
  printf("%lli\n",(dp[A%2][0]-1+MOD)%MOD);
}