#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=300000;
I a_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  Lli tot=0,res=0;
  for(I i=0;i<n;i++){
    Lli a=a_arr[i];
    Lli cur=min(a/2,tot-res*3);
    res+=(a-2*cur)/3+cur;
    tot+=a;
  }
  printf("%lli\n",res);
}