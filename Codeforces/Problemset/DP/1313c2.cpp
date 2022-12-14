#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=500000;
const I MAX=1e9;
I m_arr[N];
vector<pair<Lli,Lli>>stks;
Lli lows[N],upps[N];
I ress[N];
Lli val=0;
void add(Lli i,Lli a){
  auto[j,b]=stks.back();
  val+=abs(i-j)*a;
  stks.push_back({i,a});
}
void rem(){
  auto[i,a]=stks.back();
  stks.pop_back();
  auto[j,b]=stks.back();
  val-=abs(i-j)*a;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>m_arr[i];
  val=0;
  stks.clear(),stks.push_back({-1,-1});
  for(I i=0;i<n;i++){
    I m=m_arr[i];
    while(stks.back().second>=m)rem();
    add(i,m);
    lows[i]=val;
  }
  val=0;
  stks.clear(),stks.push_back({n,-1});
  for(I i=n-1;i>=0;i--){
    I m=m_arr[i];
    while(stks.back().second>=m)rem();
    add(i,m);
    upps[i]=val;
  }
  pair<Lli,I>res={-1,-1};
  for(I i=0;i<n;i++){
    I m=m_arr[i];
    res=max(res,{lows[i]+upps[i]-m,i});
  }
  auto[sum,j]=res;
  I cur=MAX;
  for(I i=j;i<n;i++){
    cur=min(cur,m_arr[i]);
    ress[i]=cur;
  }
  cur=MAX;
  for(I i=j;i>=0;i--){
    cur=min(cur,m_arr[i]);
    ress[i]=cur;
  }
  for(I i=0;i<n;i++)printf("%i ",ress[i]);
}