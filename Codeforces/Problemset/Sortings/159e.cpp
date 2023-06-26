#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=1e5;
const Lli MIN=-1e18;
pair<I,I>cubs[N];
vector<I>cpss;
vector<Lli>ps[N];
pair<Lli,I>pres[N];
I inds[N];
vector<I>mems[N];
B cmp1(I a,I b){
  return cubs[a].second>cubs[b].second;
}
B cmp2(I a,I b){
  return ps[a].size()>ps[b].size();
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I c,s;cin>>c>>s;
    cubs[i]={c,s};
    cpss.push_back(c);
  }
  sort(cpss.begin(),cpss.end());
  cpss.erase(unique(cpss.begin(),cpss.end()),cpss.end());
  for(I i=0;i<n;i++){
    auto[c,s]=cubs[i];
    c=lower_bound(cpss.begin(),cpss.end(),c)-cpss.begin();
    mems[c].push_back(i);
  }
  for(I i=0;i<cpss.size();i++){
    sort(mems[i].begin(),mems[i].end(),cmp1);
    ps[i].push_back(cubs[mems[i].front()].second);
    for(I j=0;j+1<mems[i].size();j++)ps[i].push_back(ps[i][j]+cubs[mems[i][j+1]].second);
  }
  iota(inds,inds+cpss.size(),0);
  sort(inds,inds+cpss.size(),cmp2);
  tuple<Lli,I,I,I,I>res={MIN,-1,-1,-1,-1};
  fill_n(pres,n,pair<Lli,I>{MIN,-1});
  for(I i=0;i<cpss.size();i++){
    I j=inds[i];
    for(I k=0;k<ps[j].size();k++){
      if(k-1>=0)res=max(res,{ps[j][k]+pres[k-1].first,j,pres[k-1].second,k,k-1});
      res=max(res,{ps[j][k]+pres[k].first,j,pres[k].second,k,k});
      if(k+1<n)res=max(res,{ps[j][k]+pres[k+1].first,pres[k+1].second,j,k+1,k});
    }
    for(I k=0;k<ps[j].size();k++)pres[k]=max(pres[k],{ps[j][k],j});
  }
  auto[hgt,x,y,z,w]=res;z++,w++;
  printf("%lli\n",hgt);
  printf("%i\n",z+w);
  for(I i=0;i<z+w;i++)printf("%i ",mems[i%2?y:x][i/2]+1);
}