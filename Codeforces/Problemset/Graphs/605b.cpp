#include<iostream>
#include<cstdio>
#include<algorithm>
#include<tuple>
#include<set>

using namespace std;

using I=int;
using B=bool;

const I N=100000;
const I M=100000;

tuple<I,I,I>edgs[M];
pair<I,I>ress[M];
I pars[N];
set<pair<I,I>>viss;

I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}

B uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return 0;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
  return 1;
}

B add(I i,I a,I b){
  if(a>b)swap(a,b);
  if(a==b||viss.find({a,b})!=viss.end())return 0;
  viss.insert({a,b});
  ress[i]={a,b};
  return 1;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  fill_n(pars,n,-1);
  for(I i=0;i<m;i++){
    I a,b;cin>>a>>b;
    edgs[i]={a,-b,i};
  }
  sort(edgs,edgs+m);
  I cur=1,x=0,y=0;
  B res=1;
  for(I i=0;i<m;i++){
    auto[a,b,j]=edgs[i];
    if(b)add(j,cur-1,cur),cur++;
    else while(x<cur&&y<cur&&!add(j,x,y))
      y++,x+=y/cur,y%=cur;
    res&=x<cur&&y<cur;
  }
  for(I i=0;i<m;i++){
    auto[a,b,j]=edgs[i];
    auto[k,l]=ress[j];
    res&=uni(k,l)==-b;
  }
  if(!res){printf("-1\n");return 0;}
  for(I i=0;i<m;i++){
    auto[a,b]=ress[i];
    printf("%i %i\n",a+1,b+1);
  }
  return 0;
}