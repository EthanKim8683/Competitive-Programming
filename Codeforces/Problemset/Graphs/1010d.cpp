#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using B=bool;

const I N=1e6;

vector<I>adjs[N];
I vals[N];
I typs[N];
B inps[N];
B infs[N];

I dfs1(I a){
  if(typs[a]==0){
    return vals[a];
  }
  if(typs[a]==1){
    I b=adjs[a][0],c=adjs[a][1];
    I x=dfs1(b),y=dfs1(c);
    infs[b]=(!x&y)!=(x&y);
    infs[c]=(x&!y)!=(x&y);
    return x&y;
  }
  if(typs[a]==2){
    I b=adjs[a][0],c=adjs[a][1];
    I x=dfs1(b),y=dfs1(c);
    infs[b]=(!x|y)!=(x|y);
    infs[c]=(x|!y)!=(x|y);
    return x|y;
  }
  if(typs[a]==3){
    I b=adjs[a][0],c=adjs[a][1];
    I x=dfs1(b),y=dfs1(c);
    infs[b]=(!x^y)!=(x^y);
    infs[c]=(x^!y)!=(x^y);
    return x^y;
  }
  if(typs[a]==4){
    I b=adjs[a][0];
    I x=dfs1(adjs[a][0]);
    infs[b]=(!!x)!=(!x);
    return !x;
  }
  return 0;
}

void dfs2(I a,B inf){
  infs[a]&=inf;
  if(typs[a]==0)return;
  dfs2(adjs[a][0],infs[a]);
  if(typs[a]==4)return;
  dfs2(adjs[a][1],infs[a]);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    S s;cin>>s;
    if(s=="IN"){
      I a;cin>>a;
      vals[i]=a;
      inps[i]=1;
      typs[i]=0;
    }
    if(s=="AND"){
      I a,b;cin>>a>>b;
      adjs[i].push_back(a-1);
      adjs[i].push_back(b-1);
      typs[i]=1;
    }
    if(s=="OR"){
      I a,b;cin>>a>>b;
      adjs[i].push_back(a-1);
      adjs[i].push_back(b-1);
      typs[i]=2;
    }
    if(s=="XOR"){
      I a,b;cin>>a>>b;
      adjs[i].push_back(a-1);
      adjs[i].push_back(b-1);
      typs[i]=3;
    }
    if(s=="NOT"){
      I a;cin>>a;
      adjs[i].push_back(a-1);
      typs[i]=4;
    }
  }
  I res=dfs1(0);
  infs[0]=1;
  dfs2(0,1);
  for(I i=0;i<n;i++)if(inps[i])
    printf("%i",infs[i]^res);
}