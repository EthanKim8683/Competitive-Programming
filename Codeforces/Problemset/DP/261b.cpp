#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lf=long double;
using Lli=long long int;
const I N=50;
const I P=50;
I a_arr[N];
Lli dp[N+1][N+1][P+1];
Lf bins[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  I p;cin>>p;
  if(p>=accumulate(a_arr,a_arr+n,0))printf("%i\n",n),exit(0);
  for(I i=0;i<n;i++){
    bins[i]=1;
    for(I j=1;j<=i;j++)bins[i]*=n-j;
    for(I j=1;j<=i;j++)bins[i]/=j;
  }
  Lf res=0;
  for(I i=0;i<n;i++){
    fill(&dp[0][0][0],&dp[0][0][0]+(N+1)*(N+1)*(P+1),0);
    dp[0][0][0]=1;
    for(I j=0;j<n;j++)for(I k=0;k<=j;k++)for(I l=0;l<=p;l++){
      I a=a_arr[j];
      if(j!=i&&l+a<=p)dp[j+1][k+1][l+a]+=dp[j][k][l];
      dp[j+1][k][l]+=dp[j][k][l];
    }
    I a=a_arr[i];
    for(I j=p;j>=max(p-a+1,0);j--)for(I k=0;k<n;k++)res+=(Lf)k*dp[n][k][j]/bins[k];
  }
  printf("%.10Lf\n",res/n);
}