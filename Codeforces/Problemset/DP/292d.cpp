#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=500;
const I M=1e4;
pair<I,I>edgs[M];
I pars1[M+1][N],pars2[M+1][N],pars3[N];
I cnt;
I fnd1(I i,I j){
  return pars1[i][j]<0?j:pars1[i][j]=fnd1(i,pars1[i][j]);
}
void uni1(I i,I a,I b){
  if((a=fnd1(i,a))==(b=fnd1(i,b)))return;
  if(pars1[i][a]>pars1[i][b])swap(a,b);
  pars1[i][a]+=pars1[i][b],pars1[i][b]=a;
}
I fnd2(I i,I j){
  return pars2[i][j]<0?j:pars2[i][j]=fnd2(i,pars2[i][j]);
}
void uni2(I i,I a,I b){
  if((a=fnd2(i,a))==(b=fnd2(i,b)))return;
  if(pars2[i][a]>pars2[i][b])swap(a,b);
  pars2[i][a]+=pars2[i][b],pars2[i][b]=a;
}
I fnd3(I i){
  return pars3[i]<0?i:pars3[i]=fnd3(pars3[i]);
}
void uni3(I a,I b){
  if((a=fnd3(a))==(b=fnd3(b)))return;
  if(pars3[a]>pars3[b])swap(a,b);
  pars3[a]+=pars3[b],pars3[b]=a,cnt--;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I x,y;cin>>x>>y,x--,y--;
    edgs[i]={x,y};
  }
  fill_n(pars1[0],n,-1);
  for(I i=0;i<m;i++){
    copy_n(pars1[i],n,pars1[i+1]);
    auto[x,y]=edgs[i];
    uni1(i+1,x,y);
  }
  fill_n(pars2[m],n,-1);
  for(I i=m;i>0;i--){
    copy_n(pars2[i],n,pars2[i-1]);
    auto[x,y]=edgs[i-1];
    uni2(i-1,x,y);
  }
  I k;cin>>k;
  while(k--){
    I l,r;cin>>l>>r,l--,r--;
    fill_n(pars3,n,-1),cnt=n;
    for(I i=0;i<n;i++)uni3(i,fnd1(l,i));
    for(I i=0;i<n;i++)uni3(i,fnd2(r+1,i));
    printf("%i\n",cnt);
  }
}