#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;

B viss1[N];
B viss2[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    fill_n(viss1,n,false),fill_n(viss2,n,false);
    I c=n;
    for(I i=0;i<n;i++){
      I k;cin>>k;
      for(I j=0;j<k;j++){
        I g;cin>>g,g--;
        if(viss1[i]||viss2[g])continue;
        viss1[i]=viss2[g]=true;
        c--;
      }
    }
    if(c==0){printf("OPTIMAL\n");continue;}
    printf("IMPROVE\n");
    I p,k;
    for(I i=0;i<n;i++){
      if(!viss1[i])p=i;
      if(!viss2[i])k=i;
    }
    printf("%i %i\n",p+1,k+1);
  }
  return 0;
}