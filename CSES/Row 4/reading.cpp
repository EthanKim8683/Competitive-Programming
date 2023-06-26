#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
I t_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>t_arr[i];
  Lli upp=*max_element(t_arr,t_arr+n),tot=accumulate(t_arr,t_arr+n,0ll);
  printf("%lli\n",max(upp,tot/2)+max(upp,tot-tot/2));
}