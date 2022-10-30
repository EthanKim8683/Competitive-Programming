#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=100;
const I A=2000;

I a_arr[N];
I dp1[N+1][N*A+1];
I dp2[N+1][N*A+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  dp1[0][0]=dp2[n][0]=1;
  for(I i=0;i<n;i++)for(I j=0;j<=n*A;j++){
    if(!dp1[i][j])continue;
    I a=a_arr[i];
    dp1[i+1][j+a]=1;
    dp1[i+1][j]=1;
  }
  for(I i=n;i>0;i--)for(I j=0;j<=n*A;j++){
    if(!dp2[i][j])continue;
    I a=a_arr[i-1];
    dp2[i-1][j+a]=1;
    dp2[i-1][j]=1;
  }
  I sum=accumulate(a_arr,a_arr+n,0);
  if(sum%2||!dp1[n][sum/2])printf("0\n"),exit(0);
  for(I i=0;i<n;i++){
    I cur=sum-a_arr[i];
    if(cur%2)printf("1\n%i\n",i+1),exit(0);
    B vld=1;
    for(I j=0;j<=cur/2;j++)vld&=!(dp1[i][j]&&dp2[i+1][cur/2-j]);
    if(vld)printf("1\n%i\n",i+1),exit(0);
  }
  printf("-1\n");
}