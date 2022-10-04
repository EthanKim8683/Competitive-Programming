#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lf=long double;

const I N=1000;

I a_arr[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,l;cin>>n>>l;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  sort(a_arr,a_arr+n);
  Lf res=0;
  for(I i=0;i+1<n;i++){
    I a=a_arr[i],b=a_arr[i+1];
    res=max(res,(Lf)(b-a)/2);
  }
  res=max(res,(Lf)a_arr[0]);
  res=max(res,(Lf)l-a_arr[n-1]);
  printf("%.10Lf\n",res);
}