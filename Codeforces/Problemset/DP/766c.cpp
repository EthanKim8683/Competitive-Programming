#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using Lli=long long int;
using B=bool;

const I N=1e3;
const I X=26;
const Lli MOD=1e9+7;
const I MAX=1e9;

I a_arr[X];
Lli dp1[N+1];
I dp2[N+1];
I ps[X][N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  S s;cin>>s;
  fill_n(dp2,n+1,MAX);
  for(I i=0;i<X;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)ps[s[i]-'a'][i+1]=1;
  for(I i=0;i<X;i++)for(I j=0;j<n;j++)ps[i][j+1]+=ps[i][j];
  dp1[0]=1,dp2[0]=0;
  I res=0;
  for(I i=0;i<n;i++)for(I j=1;i+j<=n;j++){
    I upp=MAX;
    for(I k=0;k<X;k++)if(ps[k][i+j]-ps[k][i])upp=min(upp,a_arr[k]);
    if(upp<j)break;
    (dp1[i+j]+=dp1[i])%=MOD;
    dp2[i+j]=min(dp2[i+j],dp2[i]+1);
    if(dp1[i])res=max(res,j);
  }
  printf("%lli\n",dp1[n]);
  printf("%i\n",res);
  printf("%i\n",dp2[n]);
}