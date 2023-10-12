#include<bits/stdc++.h>
using namespace std;
using I=int;
map<I,I>cacs;
I ask(I i,I j,I k){
  printf("? %i %i %i\n",i+1,j+1,k+1),fflush(stdout);
  I res;cin>>res;
  if(res==-1)exit(0);
  return res;
}
I asc(I i,I j,I k){
  if(i>j)swap(i,j);
  if(j>k)swap(j,k);
  if(i>j)swap(i,j);
  return cacs[i*16+j*4+k];
}
void ans(I i,I j){
  printf("! %i %i\n",i+1,j+1),fflush(stdout);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    tuple<I,I,I,I>pre={0,0,1,2};
    for(I i=0;i<4;i++)for(I j=i+1;j<4;j++)for(I k=j+1;k<4;k++)cacs[i*16+j*4+k]=ask(i,j,k);
    for(I i=0;i<4;i++)for(I j=i+1;j<4;j++)if(i!=j){
      I a=-1,b=-1,c=-1;
      for(I k=0;k<4;k++)if(k!=i&&k!=j){
        c=k;
        if(a==-1){a=asc(i,j,k);continue;}
        if(b==-1){b=asc(i,j,k);continue;}
      }
      if(a==b)pre=max(pre,{a,i,j,c});
    }
    for(I i=4;i<n;i++){
      auto[tot,a,b,c]=pre;
      pre=max(max(pre,{ask(a,i,c),a,i,c}),{ask(i,b,c),i,b,c});
    }
    auto[tot,a,b,c]=pre;
    ans(a,b);
  }
}