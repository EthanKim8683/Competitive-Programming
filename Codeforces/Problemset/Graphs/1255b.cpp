#include<iostream>
#include<cstdio>
#include<numeric>
#include<algorithm>
#include<vector>

using namespace std;

using I=int;
using B=bool;

const I N=1000;

I a_arr[N];
I inds[N];

B cmp(I a,I b){
  return a_arr[a]<a_arr[b];
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    if(n<=2||m<n){printf("-1\n");continue;}
    iota(inds,inds+n,0);
    sort(inds,inds+n);
    I a=inds[0],b=inds[1];
    printf("%i\n",accumulate(a_arr,a_arr+n,0)*2+(m-n)*(a_arr[a]+a_arr[b]));
    for(I i=0;i<n;i++)printf("%i %i\n",i+1,(i+1)%n+1);
    for(I i=n;i<m;i++)printf("%i %i\n",a+1,b+1);
  }
  return 0;
}