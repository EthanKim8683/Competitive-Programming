#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using C=char;
const I N=1e5;
pair<I,I>bmbs[N];
vector<tuple<I,I,C>>ress;
B cmp(pair<I,I>a,pair<I,I>b){
  auto[x1,y1]=a;auto[x2,y2]=b;
  x1=abs(x1),x2=abs(x2),y1=abs(y1),y2=abs(y2);
  return x1==x2?y1<y2:x1<x2;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I x,y;cin>>x>>y;
    bmbs[i]={x,y};
  }
  sort(bmbs,bmbs+n,cmp);
  for(I i=0;i<n;i++){
    auto[x,y]=bmbs[i];
    if(x>0)ress.push_back({1,abs(x),'R'});
    if(x<0)ress.push_back({1,abs(x),'L'});
    if(y>0)ress.push_back({1,abs(y),'U'});
    if(y<0)ress.push_back({1,abs(y),'D'});
    ress.push_back({2,-1,-1});
    if(y>0)ress.push_back({1,abs(y),'D'});
    if(y<0)ress.push_back({1,abs(y),'U'});
    if(x>0)ress.push_back({1,abs(x),'L'});
    if(x<0)ress.push_back({1,abs(x),'R'});
    ress.push_back({3,-1,-1});
  }
  printf("%i\n",ress.size());
  for(auto[t,k,d]:ress){
    if(t==1)printf("%i %i %c\n",t,k,d);
    if(t==2)printf("%i\n",t);
    if(t==3)printf("%i\n",t);
  }
}