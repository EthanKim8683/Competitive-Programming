#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
const I M=1000;
I a_arr[N];
I dp1[M];
Lli dp2[M];
I m;
I mpw(I x,Lli y){
  I res=1;
  for(x%=m;y;y>>=1,(x*=x)%=m)if(y&1)(res*=x)%=m;
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  sort(a_arr,a_arr+n);
  for(I i=0;i<n;i++){
    I a=a_arr[i]%m;
    for(I j=0;j<m;j++)dp2[(a-j+m)%m]+=dp1[j];
    dp1[a]++;
  }
  I res=1;
  for(I i=0;i<m;i++)(res*=mpw(i,dp2[i]))%=m;
  printf("%i\n",res);
}