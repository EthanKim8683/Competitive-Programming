#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=2e5;
I s_arr[N];
I inds[N];
I ress[N];
B cmp(I a,I b){
  return s_arr[a]<s_arr[b];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>s_arr[i];
    iota(inds,inds+n,0);
    sort(inds,inds+n,cmp);
    for(I i=0;i<n-1;i++)ress[inds[i]]=s_arr[inds[i]]-s_arr[inds[n-1]];
    ress[inds[n-1]]=s_arr[inds[n-1]]-s_arr[inds[n-2]];
    for(I i=0;i<n;i++)printf("%i ",ress[i]);
    printf("\n");
  }
}