#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=100;
I a_arr[N];
multiset<I>vals;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    vals.clear();
    for(I i=0;i<n;i++)vals.insert(a_arr[i]);
    for(I i=0;i<n;i++){
      if(!vals.count(i))break;
      printf("%i ",i);
      vals.erase(vals.find(i));
    }
    for(auto i:vals)printf("%i ",i);
    printf("\n");
  }
}