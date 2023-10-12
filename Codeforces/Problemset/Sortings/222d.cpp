#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1e5;
I a_arr[N];
I b_arr[N];
multiset<I>rems1,rems2;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,x;cin>>n>>x;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)cin>>b_arr[i];
  for(I i=0;i<n;i++)rems1.insert(a_arr[i]),rems2.insert(b_arr[i]);
  I res=0;
  while(rems1.size()){
    auto it1=prev(rems1.end()),it2=rems2.lower_bound(x-*it1);
    if(it2==rems2.end())break;
    rems1.erase(it1),rems2.erase(it2),res++;
  }
  printf("1 %i\n",res);
}