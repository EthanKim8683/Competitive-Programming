#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=100;
I a_arr[N];
I inds[N];
B cmp(I a,I b){
  return a_arr[a]<a_arr[b];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,p;cin>>n>>p;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    iota(inds,inds+n,0);
    sort(inds,inds+n,cmp);
    // if(a_arr[inds[0]]!=0)
  }
}