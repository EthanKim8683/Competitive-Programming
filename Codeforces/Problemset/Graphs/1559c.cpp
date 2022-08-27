#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=1e4;

I a_arr[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    B res=false;
    I end=-1;
    for(I i=0;i<=n;i++){
      I a=0,b=1;
      if(i>=0)a=a_arr[i-1];
      if(i<n)b=a_arr[i];
      if(a==0&&b==1)end=i;
    }
    if(end==-1){printf("-1\n");continue;}
    for(I i=0;i<end;i++)printf("%i ",i+1);
    printf("%i ",n+1);
    for(I i=end;i<n;i++)printf("%i ",i+1);
    printf("\n");
  }
  return 0;
}