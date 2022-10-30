#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=1e5;
const I LOGN=17;

I a_arr[N];
I n;

I bld(I x,I y){
  return x+(1<<y);
}

I fnd(I x){
  I l=0,r=LOGN;
  while(l<r){
    I m=l+(r-l+1)/2;
    if(bld(x,m)<n)l=m;
    else r=m-1;
  }
  return l;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  I res=0;
  for(I i=0;i<n-1;i++){
    res+=a_arr[i];
    a_arr[bld(i,fnd(i))]+=a_arr[i];
    a_arr[i]=0;
    printf("%i\n",res);
  }
}