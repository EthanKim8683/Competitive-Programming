#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<map>
#include<vector>

using namespace std;

using I=int;
using S=string;
using C=char;
using B=bool;

const I N=200;

map<S,I>cpss;
vector<I>adjs[N];
B viss[N];
I dep=1,res=1;

void fix(C& c){
  if(c>='A'&&c<='Z')c+='a'-'A';
}

void fix(S& s){
  for(auto& c:s)fix(c);
}

I tod(S s){
  auto it=cpss.find(s);
  if(it!=cpss.end())return it->second;
  I res=cpss.size();
  cpss.insert({s,res});
  return res;
}

void dfs(I a){
  if(viss[a])return;
  viss[a]=true;
  res=max(res,dep);
  dep++;
  for(auto b:adjs[a])dfs(b);
  dep--;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  cpss.insert({"polycarp",0});
  for(I i=0;i<n;i++){
    S a,r,b;
    cin>>a>>r>>b;
    fix(a),fix(b);
    adjs[tod(b)].push_back(tod(a));
  }
  dfs(0);
  printf("%i\n",res);
  return 0;
}