#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=2e5;

vector<I>adjs[N];
I s_arr[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,k;cin>>n>>k;
    for(I i=0;i<n;i++)adjs[i].clear();
    for(I i=1;i<n;i++){
      I p;cin>>p;
      adjs[p-1].push_back(i);
    }
    for(I i=0;i<n;i++)cin>>s_arr[i];
  }
}