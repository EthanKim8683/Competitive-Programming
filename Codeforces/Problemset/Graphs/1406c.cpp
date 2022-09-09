#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;

const I N=1e5;

vector<I>adjs[N];
I sizs[N];
I n;

I dfs1(I a,I p=-1){
  I siz=1;
  for(auto b:adjs[a]){
    if(b==p)continue;
    siz+=dfs1(b,a);
  }
  return sizs[a]=siz;
}

I dfs2(I a,I p=-1){
  for(auto b:adjs[a]){
    if(b==p)continue;
    if(sizs[b]*2>n)
      return dfs2(b,a);
  }
  return a;
}

I dfs3(I a,I p=-1){
  for(auto b:adjs[a]){
    if(b==p)continue;
    if(sizs[b]*2>=n)
      return dfs3(b,a);
  }
  return a;
}

I dfs4(I a,I p=-1){
  for(auto b:adjs[a]){
    if(b==p)continue;
    return dfs4(b,a);
  }
  return a;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    cin>>n;
    for(I i=0;i<n;i++)adjs[i].clear();
    for(I i=0;i<n-1;i++){
      I x,y;cin>>x>>y,x--,y--;
      adjs[x].push_back(y);
      adjs[y].push_back(x);
    }
    dfs1(0);
    I a=dfs2(0);
    dfs1(a);
    I b=dfs3(a);
    if(a==b){
      I c=0,d=adjs[0][0];
      printf("%i %i\n",c+1,d+1);
      printf("%i %i\n",c+1,d+1);
      continue;
    }
    if(sizs[a]<sizs[b])swap(a,b);
    I c=dfs4(b,a),d=adjs[c][0];
    printf("%i %i\n",c+1,d+1);
    printf("%i %i\n",c+1,a+1);
  }
  return 0;
}