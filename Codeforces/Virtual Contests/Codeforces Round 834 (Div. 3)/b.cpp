#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I M=50;
I b_arr[M];
I fnd(I x){
  I l=1,r=2*M;
  while(l<=r){
    I m=l+(r-l)/2;
    I val=m*(m+1)/2;
    if(val==x)return m;
    if(val<x)l=m+1;
    if(val>x)r=m-1;
  }
  return -1;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I m,s;cin>>m>>s;
    for(I i=0;i<m;i++)cin>>b_arr[i];
    I x=fnd(accumulate(b_arr,b_arr+m,0)+s);
    if(x==-1){printf("NO\n");continue;}
    if(m>=x){printf("NO\n");continue;}
    if(*max_element(b_arr,b_arr+m)>x){printf("NO\n");continue;}
    printf("YES\n");
  }
}