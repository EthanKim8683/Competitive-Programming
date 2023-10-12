#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=2e5;
const I A=1e9;
I b_arr[N];
set<I>curs;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>b_arr[i];
    curs.clear();
    curs.insert(b_arr[0]);
    auto it=curs.begin();
    B vld=1;
    for(I i=1;i<n;i++){
      I b=b_arr[i];
      curs.insert(b);
      if(b>b_arr[i-1])it++;
      if(b<b_arr[i-1])it--;
      vld&=*it==b;
    }
    printf("%s\n",vld?"YES":"NO");
  }
}