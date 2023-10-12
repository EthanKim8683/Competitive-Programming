#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using C=char;
const I N=500;
const I M=500;
C mats[M][N+1];
Lli dp[N+1][N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;Lli mod;cin>>n>>m>>mod;
  for(I i=0;i<n;i++)cin>>mats[i];
  for(I i=0;i<m;i++){
    I cnt=0;
    for(I j=0;j<n;j++)cnt+=mats[i][j]=='1';
    if(cnt!=2)printf("0"),exit(0);
  }
  I cnt1=0,cnt2=0;
  for(I i=0;i<n;i++){
    I cnt=2;
    for(I j=0;j<m;j++)cnt-=mats[j][i]=='1';
    if(cnt<0)printf("0"),exit(0);
    if(cnt==1)cnt1++;
    if(cnt==2)cnt2++;
  }
  dp[cnt2][cnt1]=1;
  for(I i=cnt2;i>=0;i--)for(I j=n-i;j>=0;j--){
    if(i>=2)(dp[i-2][j+2]+=i*(i-1)/2%mod*dp[i][j])%=mod;
    if(i>=1&&j>=1)(dp[i-1][j]+=i*j%mod*dp[i][j])%=mod;
    if(j>=2)(dp[i][j-2]+=j*(j-1)/2%mod*dp[i][j])%=mod;
  }
  printf("%lli\n",dp[0][0]);
}
/*
we can simplify the problem as the number of (n - m) by n matrices whose sum
along each column equal the remaining number of ones as per the corresponding
column in the provided m by n matrix (in addition to the sum along each row
being 2)

we can find said number of matrices by keeping track of the number of columns
awaiting either 1 or 2 ones after i rows using dynamic programming
*/