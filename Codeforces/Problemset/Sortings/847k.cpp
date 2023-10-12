#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
const I N=300;
pair<I,I>trps[N];
map<S,I>cpss;
map<pair<I,I>,I>csts;
vector<I>vals;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,a,b,k,f;cin>>n>>a>>b>>k>>f;
  for(I i=0;i<n;i++){
    S sta,fin;cin>>sta>>fin;
    if(cpss.find(sta)==cpss.end())cpss[sta]=cpss.size();
    if(cpss.find(fin)==cpss.end())cpss[fin]=cpss.size();
    trps[i]={cpss[sta],cpss[fin]};
  }
  I pre=-1;
  for(I i=0;i<n;i++){
    auto[x,y]=trps[i];
    I cst=x==pre?b:a;
    pre=y;
    if(x>y)swap(x,y);
    csts[{x,y}]+=cst;
  }
  for(auto[rou,cst]:csts)vals.push_back(-cst);
  sort(vals.begin(),vals.end());
  I res=0;
  for(I i=0;i<vals.size();i++)res+=i<k?min(-vals[i],f):-vals[i];
  printf("%i\n",res);
}