#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=1e5;
pair<I,I>pnts[N];
B viss[N];
pair<I,I>cen;
I n;
pair<I,I>sub(pair<I,I>a,pair<I,I>b){
  auto[x1,y1]=a;auto[x2,y2]=b;
  x1-=x2,y1-=y2;
  if(x1<0)x1=-x1,y1=-y1;
  return{x1,y1};
}
auto cmp=[](pair<I,I>a,pair<I,I>b)->B{
  auto[x1,y1]=sub(a,cen);auto[x2,y2]=sub(b,cen);
  if(x1==0)return 0;
  if(x2==0)return 1;
  return(Lli)y1*x2<(Lli)y2*x1;
};
map<pair<I,I>,vector<I>,decltype(cmp)>rels(cmp);
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  if(n<=4)printf("YES\n"),exit(0);
  for(I i=0;i<n;i++){
    I x,y;cin>>x>>y;
    pnts[i]={x,y};
  }
  B fnd=0;
  for(I i=0,cnt=0;i<n&&!fnd&&cnt<3;i++)if(!viss[i]){
    rels.clear(),cen=pnts[i],cnt++;
    for(I j=0;j<n;j++)if(!viss[j]&&i!=j)rels[pnts[j]].push_back(j);
    for(auto&[rel,pnts]:rels)if(pnts.size()>1||rels.size()==1){
      for(auto j:pnts)viss[j]=1;
      viss[i]=1,fnd=1;break;
    }
    if(rels.size()==0)viss[i]=1,fnd=1;
  }
  fnd=0;
  for(I i=0,cnt=0;i<n&&!fnd&&cnt<3;i++)if(!viss[i]){
    rels.clear(),cen=pnts[i],cnt++;
    for(I j=0;j<n;j++)if(!viss[j]&&i!=j)rels[pnts[j]].push_back(j);
    for(auto&[rel,pnts]:rels)if(pnts.size()>1||rels.size()==1){
      for(auto j:pnts)viss[j]=1;
      viss[i]=1,fnd=1;break;
    }
    if(rels.size()==0)viss[i]=1,fnd=1;
  }
  B res=1;
  for(I i=0;i<n;i++)res&=viss[i];
  printf("%s\n",res?"YES":"NO");
}