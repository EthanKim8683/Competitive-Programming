#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=2e5;

I x_arr[N];
Lli ps[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,a,b;cin>>n>>a>>b;
    for(I i=0;i<n;i++)cin>>x_arr[i];
    ps[n-1]=0;
    for(I i=n-1;i>0;i--)ps[i-1]=ps[i]+(Lli)(x_arr[i]-x_arr[i-1])*(n-i);
    Lli res=(Lli)(ps[0]+(Lli)x_arr[0]*n)*b;
    for(I i=0;i<n;i++)res=min(res,(Lli)(b+a)*x_arr[i]+ps[i]*b);
    printf("%lli\n",res);
  }
}