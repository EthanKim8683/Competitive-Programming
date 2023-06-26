#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=2000;
I a_arr[N];
I stds[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  copy_n(a_arr,n,stds);
  sort(stds,stds+n);
  for(I i=0;i<n;i++)printf("%i ",n-(upper_bound(stds,stds+n,a_arr[i])-stds)+1);
}