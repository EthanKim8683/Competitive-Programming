#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=100000;
const I Y=1e6;
const Lli MAX=1e18;
tuple<I,I,I,I>rcts[N];
vector<pair<I,I>>ques;
pair<I,I>pnts[4*N+2];
map<I,I>curs;
pair<Lli,I>trns[2][4*N+2];
vector<pair<I,I>>ress;
I dis(I a,I b){
  auto[x1,y1]=pnts[a];auto[x2,y2]=pnts[b];
  return abs(x1-x2)+abs(y1-y2);
}
void mov(I x1,I y1){
  if(ress.size()){
    auto[x2,y2]=ress.back();
    if(x1!=0&&x2!=0)ress.pop_back(),x1+=x2;
    if(y1!=0&&y2!=0)ress.pop_back(),y1+=y2;
  }
  if(x1==0&&y1==0)return;
  ress.push_back({x1,y1});
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&trns[0][0],&trns[0][0]+2*(4*N+2),pair<Lli,I>{MAX,-1});
  I x,y;cin>>x>>y;
  I n;cin>>n;
  I c=4*n+0,d=4*n+1;
  pnts[c]={0,0},pnts[d]={x,y};
  I low=-Y,upp=Y;
  for(I i=0;i<n;i++){
    I x1,y1,x2,y2;cin>>x1>>y1>>x2>>y2;
    if(x1>x2)swap(x1,x2);
    if(y1>y2)swap(y1,y2);
    rcts[i]={x1,y1,x2,y2};
    I j=4*i+0,k=4*i+1,l=4*i+2,m=4*i+3;
    pnts[j]={x1-1,y1-1},pnts[k]={x1-1,y2+1};
    pnts[l]={x2+1,y1-1},pnts[m]={x2+1,y2+1};
    if(x1<=x&&x<=x2){
      if(y1>y)upp=min(upp,y1-1);
      if(y2<y)low=max(low,y2+1);
    }
  }
  for(I i=0;i<n;i++){
    auto[x1,y1,x2,y2]=rcts[i];
    if(x1<x)ques.push_back({-(x1-1),i});
  }
  sort(ques.begin(),ques.end());
  curs.insert({0,c});
  trns[0][c]={0,-1};
  while(ques.size()){
    auto[t,i]=ques.back();ques.pop_back();
    auto[x1,y1,x2,y2]=rcts[i];
    auto low=curs.lower_bound(y1-1);
    auto upp=curs.upper_bound(y2+1);
    I k=4*i+0,l=4*i+1;
    for(auto it=low;it!=upp;it=curs.erase(it)){
      auto[y3,j]=*it;
      trns[0][k]=min(trns[0][k],{trns[0][j].first+dis(j,k),j});
      trns[0][l]=min(trns[0][l],{trns[0][j].first+dis(j,l),j});
    }
    if(trns[0][k].first!=MAX)curs.insert({y1-1,k});
    if(trns[0][l].first!=MAX)curs.insert({y2+1,l});
  }
  for(auto[y1,i]:curs)if(low<=y1&&y1<=upp){
    trns[0][d]=min(trns[0][d],{trns[0][i].first+dis(d,i),i});
  }
  curs.clear();
  for(I i=0;i<n;i++){
    auto[x1,y1,x2,y2]=rcts[i];
    if(x2<x)ques.push_back({x2+1,i});
  }
  sort(ques.begin(),ques.end());
  curs.insert({y,d});
  trns[1][d]={0,-1};
  while(ques.size()){
    auto[t,i]=ques.back();ques.pop_back();
    auto[x1,y1,x2,y2]=rcts[i];
    auto low=curs.lower_bound(y1-1);
    auto upp=curs.upper_bound(y2+1);
    I k=4*i+2,l=4*i+3;
    for(auto it=low;it!=upp;it=curs.erase(it)){
      auto[y3,j]=*it;
      trns[1][k]=min(trns[1][k],{trns[1][j].first+dis(j,k),j});
      trns[1][l]=min(trns[1][l],{trns[1][j].first+dis(j,l),j});
    }
    if(trns[1][k].first!=MAX)curs.insert({y1-1,k});
    if(trns[1][l].first!=MAX)curs.insert({y2+1,l});
  }
  for(auto[y1,i]:curs){
    trns[1][c]=min(trns[1][c],{trns[1][i].first+dis(c,i),i});
  }
  for(I i=0;i<n;i++){
    I j=4*i+0,k=4*i+1,l=4*i+2,m=4*i+3;
    trns[0][l]={trns[0][j].first+dis(l,j),j};
    trns[0][m]={trns[0][k].first+dis(m,k),k};
    trns[1][j]={trns[1][l].first+dis(j,l),l};
    trns[1][k]={trns[1][m].first+dis(k,m),m};
  }
  pair<Lli,I>res={MAX,-1};
  for(I i=0;i<4*n+2;i++){
    res=min(res,{trns[0][i].first+trns[1][i].first,i});
  }
  auto[tot,i]=res;
  for(I j=i;j!=c;){
    auto[cur,k]=trns[0][j];
    auto[x1,y1]=pnts[j];auto[x2,y2]=pnts[k];
    mov(0,y1-y2),mov(x1-x2,0),j=k;
  }
  reverse(ress.begin(),ress.end());
  for(I j=i;j!=d;){
    auto[cur,k]=trns[1][j];
    auto[x1,y1]=pnts[j];auto[x2,y2]=pnts[k];
    mov(0,y2-y1),mov(x2-x1,0),j=k;
  }
  printf("%lli\n",tot);
  printf("%i\n",ress.size());
  for(auto[x,y]:ress)printf("%i %i\n",x,y);
}