#include<iostream>
#include<cstdio>
#include<numeric>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=2e5;

I r_arr[N];
I c_arr[N];
I inds[N];

B cmp(I a,I b){
  return r_arr[a]<r_arr[b];
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++){I r;cin>>r,r_arr[i]=r-1;}
    for(I i=0;i<n;i++){I c;cin>>c,c_arr[i]=c-1;}
    iota(inds,inds+n,0);
    sort(inds,inds+n,cmp);
    I r1=0,c1=0;
    I res=0;
    for(I i=0;i<n;i++){
      I j=inds[i];
      I r=r_arr[j],c=c_arr[j];
      I r2=r-c,c2=c;
      res+=r2/2-r1/2;
      res+=r1%2==0&&r2-r1==0?c2-c1:0;
      r1=r2,c1=c2;
    }
    printf("%i\n",res);
  }
  return 0;
}