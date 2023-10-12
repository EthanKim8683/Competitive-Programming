#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=100;
I a_arr[N];
vector<I>lens;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  Lli res=0;
  for(I i=0;i<n;i++)res|=a_arr[i];
  I l=0;
  for(I r=0;r<n;r++)if(a_arr[r]!=a_arr[l]){
    if(l>0&&a_arr[l]==0)res*=r-l+1;
    l=r;
  }
  printf("%lli\n",res);
}