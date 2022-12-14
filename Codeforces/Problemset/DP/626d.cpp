#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using Lf=long double;
const I N=2000;
const I A=5000;
I a_arr[N];
I dp1[A+1];
Lli dp2[2+1][2*A+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  sort(a_arr,a_arr+n);
  for(I i=0;i<n;i++)for(I j=i+1;j<n;j++)dp1[a_arr[j]-a_arr[i]]++;
  dp2[0][0]=1;
  for(I i=0;i<2;i++)for(I j=0;j<=2*A;j++)for(I k=0;k<=A&&j+k<=2*A;k++)dp2[i+1][j+k]+=dp2[i][j]*dp1[k];
  Lf res=0;
  for(I i=0;i<=2*A;i++)for(I j=i+1;j<=A;j++)res+=dp2[2][i]*dp1[j];
  for(I i=0;i<3;i++)res/=n*(n-1)/2;
  printf("%.10Lf\n",res);
}