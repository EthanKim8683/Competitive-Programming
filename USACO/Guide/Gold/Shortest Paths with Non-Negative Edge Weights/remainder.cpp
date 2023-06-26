#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=50;
const I A=50;
const I MAX=A+1;
I a_arr[N];
I b_arr[N];
I dp1[A+1][A+1];
B dp2[N][A+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp1[0][0],&dp1[0][0]+(A+1)*(A+1),MAX);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)cin>>b_arr[i];
  for(I i=0;i<=A;i++){
    dp1[i][i]=-1;
    for(I j=i;j>=1;j--)for(I k=0;k<=i;k++)if(dp1[i%j][k]!=MAX)dp1[i][k]=j;
  }
  for(I i=0;i<n;i++)dp2[i][a_arr[i]]=1;
  Lli res=0;
  while(1){
    I k=-1;
    for(I i=0;i<n;i++){
      I l=MAX;
      for(I j=0;j<=A;j++)if(dp2[i][j])l=min(l,dp1[j][b_arr[i]]);
      k=max(k,l);
    }
    if(k==MAX)printf("-1\n"),exit(0);
    if(k==-1)break;
    res|=1ll<<k;
    for(I i=0;i<n;i++)for(I j=0;j<=A;j++)if(dp2[i][j])dp2[i][j%k]|=1;
  }
  printf("%lli\n",res);
}