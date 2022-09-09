#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=2e5;

I t_arr[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I q;cin>>q;
  while(q--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>t_arr[i];
    I lst=t_arr[n-1],len=1,lon=1;
    for(I i=0;i<n;i++){
      I t=t_arr[i];
      len+=t==lst;
      lon=max(lon,len);
      lst=t;
    }
    if(len>=n){
      printf("1\n");
      for(I i=0;i<n;i++)printf("1 ");
    }else if(n%2){
      if(lon>=2){
        printf("2\n");
        B use=0;
        I lst=t_arr[n-1],cur=0;
        for(I i=0;i<n;i++){
          I t=t_arr[i];
          if(t==lst&&!use)use=1;
          else cur^=1;
          printf("%i ",cur+1);
          lst=t;
        }
      }else{
        printf("3\n");
        for(I i=0;i<n-1;i++)printf("%i ",i%2+1);
        printf("3");
      }
    }else{
      printf("2\n");
      for(I i=0;i<n;i++)printf("%i ",i%2+1);
    }
    printf("\n");
  }
  return 0;
}