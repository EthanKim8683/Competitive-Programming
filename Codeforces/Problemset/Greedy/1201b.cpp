#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=1e5;

Lli a_arr[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  Lli sum=accumulate(a_arr,a_arr+n,(Lli)0);
  Lli upp=*max_element(a_arr,a_arr+n);
  printf("%s\n",sum%2||upp>sum-upp?"NO":"YES");
}