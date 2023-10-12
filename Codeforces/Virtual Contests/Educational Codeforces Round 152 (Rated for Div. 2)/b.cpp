#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=3e5;
I a_arr[N];
I inds[N];
I k;
B cmp(I a,I b){
  I x=(a_arr[a]-1)%k+1,y=(a_arr[b]-1)%k+1;
  return x==y?a<b:x>y;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n>>k;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    iota(inds,inds+n,0);
    sort(inds,inds+n,cmp);
    for(I i=0;i<n;i++)printf("%i ",inds[i]+1);
    printf("\n");
  }
}