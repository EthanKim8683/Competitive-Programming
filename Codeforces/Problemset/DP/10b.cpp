#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I K=99;
const I MAX=1e9;

B viss[K][K];
I ps1[K+1];
I ps2[K][K+1];
I k;

B chk(I x,I yl,I yr){
  if(x<0||x>=k)return 0;
  if(yl<0||yl>=k)return 0;
  if(yr<0||yr>=k)return 0;
  if(ps2[x][yr+1]-ps2[x][yl])return 0;
  return 1;
}

I cst(I x,I yl,I yr){
  return abs(x-k/2)*(yr-yl+1)+ps1[yr+1]-ps1[yl];
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n>>k;
  for(I i=0;i<k;i++)ps1[i+1]=abs(i-k/2);
  for(I i=0;i<k;i++)ps1[i+1]+=ps1[i];
  for(I i=0;i<n;i++){
    I m;cin>>m;
    I res=MAX,x,y;
    for(I j=0;j<k;j++)for(I l=0;l<k;l++){
      if(!chk(j,l,l+m-1))continue;
      I cur=cst(j,l,l+m-1);
      if(cur>res)continue;
      if(cur<res){res=cur,x=j,y=l;continue;}
      if(j>x)continue;
      if(j<x){res=cur,x=j,y=l;continue;}
      if(l>y)continue;
      if(l<y){res=cur,x=j,y=l;continue;}
    }
    if(res==MAX){printf("-1\n");continue;}
    for(I j=y;j<y+m;j++)viss[x][j]=1;
    for(I j=0;j<k;j++)ps2[x][j+1]=ps2[x][j]+viss[x][j];
    printf("%i %i %i\n",x+1,y+1,y+m);
  }
}