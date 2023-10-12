#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1e5;
const I MAX=2e9;
I a_arr[N];
set<I>curs;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    I pre=MAX;
    curs.clear();
    for(I i=0;i<n;i++){
      I a=a_arr[i];
      if(a>=pre)continue;
      curs.insert(i),pre=a;
    }
    for(I i=0;i<m;i++){
      I k,d;cin>>k>>d,k--;
      I a=a_arr[*prev(curs.upper_bound(k))];
      a_arr[k]-=d;
      if(a_arr[k]<a){
        auto it=curs.lower_bound(k);
        while(it!=curs.end()){
          if(a_arr[*it]<a_arr[k])break;
          it=curs.erase(it);
        }
        curs.insert(k);
      }
      printf("%i ",curs.size());
    }
    printf("\n");
  }
}