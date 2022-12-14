#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=5000;
const I M=5000;
const Lli MIN=-1e18;
I a_arr[N];
I b_arr[M];
I dp1[N];
I dp2[N+1],dp3[N+1];
Lli dp4[N+1][N+1];
I m;
I cnt(I a){
  Lli res=0;
  for(I i=0;i<m;i++){
    I b=b_arr[i];
    while(a%b==0)res--,a/=b;
  }
  for(I i=2;i*i<=a;i++)
    while(a%i==0)res++,a/=i;
  return res+(a>1);
}
void cmb(Lli&a,Lli b){
  a=max(a,b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp4[0][0],&dp4[0][0]+N*(N+1),MIN);
  I n;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<m;i++)cin>>b_arr[i];
  dp1[0]=a_arr[0];
  for(I i=1;i<n;i++)dp1[i]=gcd(a_arr[i],dp1[i-1]);
  dp2[n]=0;
  for(I i=0;i<n;i++)dp2[i]=cnt(a_arr[i]);
  dp3[n]=0;
  for(I i=0;i<n;i++)dp3[i]=cnt(dp1[i]);
  dp4[n][n]=0;
  for(I i=n-1;i>=0;i--)for(I j=0;j<=n;j++){
    cmb(dp4[i][i],dp4[i+1][j]+dp2[i]-dp3[i]);
    cmb(dp4[i][j],dp4[i+1][j]+dp2[i]-dp3[j]);
  }
  printf("%lli\n",*max_element(dp4[0],dp4[0]+n+1));
}