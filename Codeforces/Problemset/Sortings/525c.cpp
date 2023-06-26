#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
I l_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>l_arr[i];
  sort(l_arr,l_arr+n);
  Lli pre=0,res=0;
  for(I i=n-2;i>=0;i--)if(l_arr[i+1]-l_arr[i]<=1){
    if(pre)res+=(Lli)l_arr[i]*pre,pre=0;
    else pre=l_arr[i];
    i--;
  }
  printf("%lli\n",res);
}