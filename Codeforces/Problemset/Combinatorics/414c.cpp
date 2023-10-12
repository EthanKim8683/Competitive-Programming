#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=20;
I a_arr[1<<N];
Lli invs[N];
Lli equs[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<(1<<n);i++)cin>>a_arr[i];
  I m;cin>>m;
  for(I i=0;i<n;i++)for(I j=0;j<(1<<n);j+=2<<i){
    sort(a_arr+j,a_arr+j+(1<<i)),sort(a_arr+j+(1<<i),a_arr+j+(2<<i));
    for(I k=0;k<(1<<i);k++){
      auto beg=a_arr+j+(1<<i),end=a_arr+j+(2<<i);
      invs[i]+=lower_bound(beg,end,a_arr[j+k])-beg;
      equs[i]+=upper_bound(beg,end,a_arr[j+k])-lower_bound(beg,end,a_arr[j+k]);
    }
  }
  Lli res=accumulate(invs,invs+n,0ll);
  while(m--){
    I q;cin>>q;
    for(I i=0;i<q;i++)res-=invs[i],invs[i]=(1ll<<(i+n-1))-invs[i]-equs[i],res+=invs[i];
    printf("%lli\n",res);
  }
}
/*
if we swap two subarrays of size n with i inversions between them initially,
the resulting number of inversions will be n * n - i

meaning, for all q, we can swap adjacent subarrays of size 2 ^ i for all i in
[0, q), resulting in (2 ^ i) * (2 ^ i) * (2 ^ (n - i - 1)) - invs[i] - equs[i]
inversions afterwards, where invs[i] is the prior number of inversions and
equs[i] is the number of equal pairs
*/