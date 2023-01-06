#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=200000;
const I A=2.5e6;
I a_arr[N];
I inds[N];
pair<I,I>difs[A+1];
B cmp(I a,I b){
  return a_arr[a]<a_arr[b];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill_n(difs,A+1,pair<I,I>{-1,-1});
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  iota(inds,inds+n,0);
  sort(inds,inds+n,cmp);
  for(I i=0;i<n;i++){
    for(I j=i+1;j<n;j++){
      auto[k,l]=difs[a_arr[inds[j]]-a_arr[inds[i]]];
      if(k!=-1){
        printf("YES\n");
        printf("%i %i %i %i\n",inds[i]+1,inds[l]+1,inds[j]+1,inds[k]+1);
        exit(0);
      }
    }
    for(I j=0;j<i;j++)difs[a_arr[inds[i]]-a_arr[inds[j]]]={j,i};
  }
  printf("NO\n");
}