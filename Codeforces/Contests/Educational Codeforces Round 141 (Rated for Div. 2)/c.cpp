#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=5e5;
I a_arr[N];
I inds[N];
B viss[N];
B cmp(I a,I b){
  return a_arr[a]<a_arr[b];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    iota(inds,inds+n,0);
    sort(inds,inds+n,cmp);
    fill_n(viss,n,0);
    I res=0,sum=0;
    if(a_arr[0]<=m)res=1;
    for(I i=1;i<n;i++){
      I a=a_arr[i],cur=sum;
      I j=inds[i-1],b=a_arr[j];
      viss[i]?cur+=b:cur+=a;
      if(cur<=m)res=max(res,i+1);
      viss[j]=1,sum+=b;
    }
    sum=0;
    for(I i=0;i<n;i++){
      if(sum<=m)res=max(res,i);
      sum+=a_arr[inds[i]];
    }
    printf("%i\n",n+1-res);
  }
}