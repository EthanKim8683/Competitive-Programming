#include<iostream>
#include<cstdio>
#include<algorithm>
#include<set>

using namespace std;

using I=int;
using B=bool;

const I N=1e3;

I pars[N];
multiset<I>sizs;

I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}

void uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
}

B con(I a,I b){
  return fnd(a)==fnd(b);
}

I siz(I i){
  return -pars[fnd(i)];
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,d;cin>>n>>d;
  fill_n(pars,n,-1);
  for(I i=0;i<n;i++)sizs.insert(-1);
  I cnt=1;
  for(I i=0;i<d;i++){
    I x,y;cin>>x>>y,x--,y--;
    if(con(x,y))cnt++;
    else{
      sizs.erase(sizs.find(-siz(x)));
      sizs.erase(sizs.find(-siz(y)));
      uni(x,y);
      sizs.insert(-siz(x));
    }
    I res=0;
    auto it=sizs.begin();
    for(I i=0;i<cnt&&it!=sizs.end();i++,it++)
      res+=*it;
    printf("%i\n",-res-1);
  }
  return 0;
}