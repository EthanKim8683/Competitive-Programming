#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=100;
I a_arr[N];
I b_arr[N];
I inds[N];
B cmp(I a,I b){
  return a_arr[a]<a_arr[b];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,k;cin>>n>>k;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<n;i++)cin>>b_arr[i];
    iota(inds,inds+n,0);
    sort(inds,inds+n,cmp);
    for(I i=0;i<n;i++){
      I j=inds[i],a=a_arr[j],b=b_arr[j];
      if(a>k)break;
      k+=b;
    }
    printf("%i\n",k);
  }
}