#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=300000;
const I MAX=1e9;
I c_arr[N];
I inds[N];
B cmp(I a,I b){
  return c_arr[a]<c_arr[b];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,x1,x2;cin>>n>>x1>>x2;
  for(I i=0;i<n;i++)cin>>c_arr[i];
  iota(inds,inds+n,0);
  sort(inds,inds+n,cmp);
  I pre1=MAX,pre2=MAX;
  for(I i=1;i<=n;i++){
    if((x1+i-1)/i<=c_arr[inds[n-i]])pre1=min(pre1,i);
    if((x2+i-1)/i<=c_arr[inds[n-i]])pre2=min(pre2,i);
  }
  I suf1=MAX,suf2=MAX;
  for(I i=1;i<=n-pre1;i++)if((x2+i-1)/i<=c_arr[inds[n-pre1-i]])suf1=min(suf1,i);
  for(I i=1;i<=n-pre2;i++)if((x1+i-1)/i<=c_arr[inds[n-pre2-i]])suf2=min(suf2,i);
  if(suf1!=MAX){
    printf("Yes\n");
    printf("%i %i\n",pre1,suf1);
    for(I i=0;i<pre1;i++)printf("%i ",inds[n-1-i]+1);
    printf("\n");
    for(I i=0;i<suf1;i++)printf("%i ",inds[n-1-pre1-i]+1);
    printf("\n");
    exit(0);
  }
  if(suf2!=MAX){
    printf("Yes\n");
    printf("%i %i\n",suf2,pre2);
    for(I i=0;i<suf2;i++)printf("%i ",inds[n-1-pre2-i]+1);
    printf("\n");
    for(I i=0;i<pre2;i++)printf("%i ",inds[n-1-i]+1);
    printf("\n");
    exit(0);
  }
  printf("No\n");
}