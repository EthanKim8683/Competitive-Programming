#include<iostream>
#include<cstdio>
#include<unordered_map>
#include<vector>

using namespace std;

using I=int;

const I N=1e5;

unordered_map<I,I>cnvs;
I revs[2*N];
vector<I>adjs[2*N];
I degs[2*N];
vector<I>ress;

I qry(I i){
  I res;
  auto it=cnvs.find(i);
  if(it==cnvs.end()){
    cnvs.insert({i,res=cnvs.size()});
    revs[res]=i;
  }
  else res=it->second;
  return res;
}

void dfs(I a,I p=-1){
  ress.push_back(a);
  for(auto b:adjs[a])if(b!=p)dfs(b,a);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I a,b;cin>>a>>b;
    a=qry(a),b=qry(b);
    adjs[a].push_back(b);
    adjs[b].push_back(a);
    degs[a]++,degs[b]++;
  }
  for(I i=0;i<cnvs.size();i++)
    if(degs[i]==1){dfs(i);break;}
  for(auto i:ress)printf("%i ",revs[i]);
  return 0;
}