#include<iostream>
#include<cstdio>

using namespace std;

using I=int;
using Lli=long long int;

const I N=100;
const I H=1000;
const Lli MOD=1e9+7;

I h_arr[N];
Lli dp[2][H+1][H+1+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin>>n;
  for(I i=0;i<n;i++)
    cin>>h_arr[i];
  I low=H;
  if(n%2==0)low=0;
  else for(I i=0;i<n;i++)
    low=min(low,h_arr[i]);
  for(I i=0;i<=low;i++)
    dp[0%2][i][i]=1;
  for(I i=1;i<n;i++){
    I a=i%2,b=(i-1)%2;
    for(I j=0;j<=low;j++){
      for(I k=j;k<=h_arr[i-1];k++){
        // for(I l=0;j+l<=h_arr[i]&&k+l<=h_arr[i-1];l++)
        //   dp[a][j][j+l]+=dp[b][j][k];
        (dp[a][j][j+0]+=dp[b][j][k])%=MOD;
        (dp[a][j][j+min(h_arr[i]-j,h_arr[i-1]-k)+1]-=dp[b][j][k])%=MOD;
      }
      for(I k=j+1;k<=h_arr[i];k++)
        (dp[a][j][k]+=dp[a][j][k-1])%=MOD;
    }
    fill(&dp[b][0][0],&dp[b][0][0]+sizeof(dp[b])/sizeof(Lli),0);
  }
  Lli res=0;
  for(I i=0;i<=low;i++)
    for(I j=i;j<=h_arr[n-1];j++)
      (res+=dp[(n-1)%2][i][j])%=MOD;
  printf("%i\n",res+(res<0)*MOD);
  return 0;
}