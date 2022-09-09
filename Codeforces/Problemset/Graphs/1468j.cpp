#include<iostream>
#include<cstdio>
#include<tuple>
#include<algorithm>
#include<vector>

using namespace std;

using I=int;
using B=bool;
using Lli=long long int;

const I N=2e5;
const I MAX=1e9;

vector<tuple<I,I,I>>lows;
vector<tuple<I,I,I>>upps;
I pars[N];

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

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m,k;cin>>n>>m>>k;
    fill_n(pars,n,-1);
    lows.clear(),upps.clear();
    I dis=MAX;
    for(I i=0;i<m;i++){
      I x,y,s;cin>>x>>y>>s,x--,y--;
      if(s>k)upps.push_back({s,x,y}),dis=min(dis,s-k);
      else lows.push_back({s,x,y}),dis=min(dis,k-s);
    }
    B gre=0;
    Lli res=0;
    sort(upps.begin(),upps.end());
    for(auto[s,i,j]:lows)uni(i,j);
    for(auto[s,i,j]:upps)if(uni(i,j))res+=s-k,gre=1;
    if(!gre)res+=dis;
    printf("%lli\n",res);
  }
  return 0;
}