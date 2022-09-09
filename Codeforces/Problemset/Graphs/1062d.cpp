#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

using I=int;
using B=bool;
using Lli=long long int;

const I N=100000;
const I M=3867004;

vector<pair<I,I>>adjs[N+N+1];
vector<I>stks;
B viss1[N+N+1],viss2[M];
vector<I>euls;
I ind=0;

void add(I i,I j){
  i+=N,j+=N;
  adjs[i].push_back({j,ind});
  adjs[j].push_back({i,ind});
  ind++;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=2;i<=n;i++)for(I j=2*i;j<=n;j+=i)
    add(i,j),add(-i,j),add(i,-j),add(-i,-j);
  Lli res=0;
  for(I i=-n;i<=n;i++){
    if(abs(i)<2||viss1[i+N])continue;
    stks.push_back(i+N);
    while(stks.size()){
      I a=stks.back();
      viss1[a]=1;
      B fnd=0;
      while(adjs[a].size()){
        auto[b,j]=adjs[a].back();adjs[a].pop_back();
        if(!viss2[j]){stks.push_back(b),fnd=viss2[j]=1;break;}
      }
      if(!fnd)euls.push_back(a),stks.pop_back();
    }
    Lli cur=0;
    for(I j=0;j+1<euls.size();j++){
      I a=abs(euls[j]-N),b=abs(euls[j+1]-N);
      cur+=a<b?b/a:a/b;
    }
    res=max(res,cur);
    euls.clear();
  }
  printf("%lli\n",res);
  return 0;
}