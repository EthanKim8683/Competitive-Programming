#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=2e5;

I a_arr[N];
multiset<I>rems;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    rems.clear();
    for(I i=0;i<n;i++)rems.insert(a_arr[i]);
    Lli res=0;
    printf("%i ",rems.count(0));
    for(I i=0;i<n;i++){
      auto it=rems.upper_bound(i);
      if(it==rems.begin())res=-1;
      if(res==-1){printf("-1 ");continue;}
      it--,res+=i-*it,rems.erase(it);
      printf("%lli ",res+rems.count(i+1));
    }
    printf("\n");
  }
}