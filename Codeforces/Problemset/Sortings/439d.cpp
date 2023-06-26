#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const I M=1e5;
const Lli MAX=1e18;
I a_arr[N];
I b_arr[M];
Lli ps1[N+1],ps2[M+1];
I n,m;
Lli sum1(I x){
  I i=upper_bound(a_arr,a_arr+n,x)-a_arr;
  return(Lli)x*i-(ps1[i]-ps1[0]);
}
Lli sum2(I x){
  I i=lower_bound(b_arr,b_arr+m,x)-b_arr;
  return(ps2[m]-ps2[i])-(Lli)x*(m-i);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n>>m;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<m;i++)cin>>b_arr[i];
  sort(a_arr,a_arr+n);
  sort(b_arr,b_arr+m);
  for(I i=0;i<n;i++)ps1[i+1]=ps1[i]+a_arr[i];
  for(I i=0;i<m;i++)ps2[i+1]=ps2[i]+b_arr[i];
  Lli res=MAX;
  for(I i=0;i<n;i++)res=min(res,sum1(a_arr[i])+sum2(a_arr[i]));
  for(I i=0;i<m;i++)res=min(res,sum1(b_arr[i])+sum2(b_arr[i]));
  printf("%lli\n",res);
}