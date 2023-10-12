#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=100000;
const I W=100000;
const I H=100000;
const I T=100000;
const I D=T;
tuple<I,I,I>dans[N];
vector<I>hors[2*D+1];
vector<I>vers[2*D+1];
vector<I>cmbs;
pair<I,I>ress[N];
B cmp(I a,I b){
  return get<1>(dans[a])<get<1>(dans[b]);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,w,h;cin>>n>>w>>h;
  for(I i=0;i<n;i++){
    I g,p,t;cin>>g>>p>>t;
    dans[i]={g,p,t};
    if(g==1)vers[W+p-t].push_back(i);
    if(g==2)hors[H+p-t].push_back(i);
  }
  for(I i=-D;i<=D;i++){
    sort(vers[i+D].begin(),vers[i+D].end(),cmp);
    sort(hors[i+D].begin(),hors[i+D].end(),cmp);
    reverse(vers[i+D].begin(),vers[i+D].end());
    cmbs.clear();
    for(auto j:vers[i+D])cmbs.push_back(j);
    for(auto j:hors[i+D])cmbs.push_back(j);
    reverse(vers[i+D].begin(),vers[i+D].end());
    reverse(hors[i+D].begin(),hors[i+D].end());
    for(auto j:vers[i+D]){
      auto[g,p,t]=dans[j];
      I k=cmbs.back();cmbs.pop_back();
      ress[k]={p,h};
    }
    for(auto j:hors[i+D]){
      auto[g,p,t]=dans[j];
      I k=cmbs.back();cmbs.pop_back();
      ress[k]={w,p};
    }
  }
  for(I i=0;i<n;i++){
    auto[x,y]=ress[i];
    printf("%i %i\n",x,y);
  }
}