#include<iostream>
#include<cstdio>

using namespace std;

using I=int;

I main(){
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    if(n==-1){return 0;}
    printf("1 %i 1",n-1);
    for(I i=1;i<n;i++)printf(" %i",i+1);
    printf("\n");
    fflush(stdout);
    I u;cin>>u;
    if(u==-1){return 0;}
    I l=1,r=n-1;
    while(l<r){
      I m=l+(r-l+1)/2;
      printf("1 %i 1",m-l);
      for(I i=l;i<m;i++)printf(" %i",i+1);
      printf("\n");
      fflush(stdout);
      I a;cin>>a;
      if(a==-1){return 0;}
      if(a==u)r=m-1;
      else l=m;
    }
    printf("1 %i %i",n-1,l+1);
    for(I i=0;i<n;i++)if(i!=l)printf(" %i",i+1);
    printf("\n");
    fflush(stdout);
    I res;cin>>res;
    if(res==-1){return 0;}
    printf("-1 %i\n",res);
  }
  return 0;
}