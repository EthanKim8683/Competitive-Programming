#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=1e5;
pair<I,I>pcws[N];
vector<pair<I,I>>cpss;
Lli lows[N+1],upps[N+1],slps[N+1];
B cmp(pair<I,I>a,pair<I,I>b){
  auto[x1,y1]=a;auto[x2,y2]=b;
  return((Lli)x1*y2<(Lli)x2*y1)^(y1<0)^(y2<0);
}
B equ(pair<I,I>a,pair<I,I>b){
  auto[x1,y1]=a;auto[x2,y2]=b;
  return(Lli)x1*y2==(Lli)x2*y1;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I k,b;cin>>k>>b;
    pcws[i]={k,b};
    if(k!=0)cpss.push_back({-b,k});
  }
  sort(cpss.begin(),cpss.end(),cmp);
  cpss.erase(unique(cpss.begin(),cpss.end(),equ),cpss.end());
  for(I i=0;i<n;i++){
    auto[k,b]=pcws[i];
    if(k<0)lows[lower_bound(cpss.begin(),cpss.end(),pair<I,I>{-b,k},cmp)-cpss.begin()]+=k;
    if(k>0)upps[lower_bound(cpss.begin(),cpss.end(),pair<I,I>{-b,k},cmp)-cpss.begin()+1]+=k;
  }
  for(I i=cpss.size();i>0;i--)lows[i-1]+=lows[i];
  for(I i=0;i<cpss.size();i++)upps[i+1]+=upps[i];
  for(I i=0;i<=cpss.size();i++)slps[i]=lows[i]+upps[i];
  I res=0;
  for(I i=0;i<cpss.size();i++){
    auto[b,k]=cpss[i];
    if(k==0)continue;
    res+=slps[i]!=slps[i+1];
  }
  printf("%i\n",res);
}