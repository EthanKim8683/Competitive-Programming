#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lf=long double;
using Lli=long long int;
const I N=1e5;
const I X=1e7;
const I Y=1e7;
pair<I,I>pnts[2*(N+2)];
vector<tuple<I,I,I>>ques;
pair<I,I>adjs[2*N];
I pars[N];
vector<pair<I,I>>ress;
I x=0;
I fnd(I i){
  return pars[i]<0?i:fnd(pars[i]);
}
B uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return 0;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
  return 1;
}
Lli crs(I a,I b,I c){
  auto[x1,y1]=pnts[a];auto[x2,y2]=pnts[b];auto[x3,y3]=pnts[c];
  return(Lli)(x2-x1)*(y3-y2)-(Lli)(x3-x2)*(y2-y1);
}
Lf evl(I i){
  auto[x1,y1]=pnts[2*i];auto[x2,y2]=pnts[2*i+1];
  if(x1==x2)return y1;
  return(Lf)(x-x1)/(x2-x1)*(y2-y1)+y1;
}
pair<I,I>wlk(I i,I j,I k,I top){
  if(top==-1)return{-1,-1};
  I pre1=-1,pre2=-1;
  for(I l=top;l!=-1;l=adjs[l].first){
    if(pre1/2==j)break;
    if(pre1!=-1&&crs(i,pre1,l)<0)break;
    if(uni(i/2,l/2))ress.push_back({i,l});
    pre1=l;
  }
  for(I l=top;l!=-1;l=adjs[l].second){
    if(pre2/2==k)break;
    if(pre2!=-1&&crs(i,pre2,l)>0)break;
    if(uni(i/2,l/2))ress.push_back({i,l});
    pre2=l;
  }
  return{pre1,pre2};
}
B cmp(I a,I b){
  Lf y1=evl(a),y2=evl(b);
  return y1==y2?a<b:y1<y2;
}
map<I,I,decltype(cmp)*>divs(cmp);
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  fill_n(pars,n,-1);
  fill_n(adjs,2*n,pair<I,I>{-1,-1});
  for(I i=0;i<n;i++){
    I x1,y1,x2,y2;cin>>x1>>y1>>x2>>y2;
    if(x1==x2&&y1>y2)swap(y1,y2);
    if(x1>x2)swap(x1,x2),swap(y1,y2);
    pnts[2*i]={x1,y1};
    pnts[2*i+1]={x2,y2};
    ques.push_back({-x1,-y1,2*i});
    ques.push_back({-x2,-y2,2*i+1});
  }
  pnts[2*n]={-X-1,-Y-1};
  pnts[2*n+1]={X+1,-Y-1};
  pnts[2*n+2]={-X-1,Y+1};
  pnts[2*n+3]={X+1,Y+1};
  divs.insert({n,-1});
  divs.insert({n+1,-1});
  sort(ques.begin(),ques.end());
  while(ques.size()){
    auto[x1,y1,i]=ques.back();ques.pop_back();
    x=-x1;
    if(i%2==0){
      auto upp2=divs.lower_bound(i/2),low2=prev(upp2);
      auto[a,b]=wlk(i,low2->first,upp2->first,upp2->second);
      upp2->second=i;
      adjs[i]={a,b};
      divs.insert({i/2,i});
    }
    if(i%2==1){
      auto upp1=divs.find(i/2),low1=prev(upp1);
      auto[a,b]=wlk(i,low1->first,upp1->first,upp1->second);
      auto low2=upp1,upp2=next(low2);
      auto[c,d]=wlk(i,low2->first,upp2->first,upp2->second);
      upp2->second=i;
      adjs[i]={a,d};
      divs.erase(i/2);
    }
  }
  for(auto[a,b]:ress){
    auto[x1,y1]=pnts[a];auto[x2,y2]=pnts[b];
    printf("%i %i %i %i\n",x1,y1,x2,y2);
  }
}