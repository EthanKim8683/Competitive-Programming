#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

using I=int;

const I N=5000;

vector<I>adjs[N];
I dep=0;

I dfs(I a,I r){
  if(dep==3)return a==r;
  I res=0;
  dep++;
  for(auto b:adjs[a])res+=dfs(b,r);
  dep--;
  return res;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){I f;cin>>f,adjs[f-1].push_back(i);}
  I res=0;
  for(I i=0;i<n;i++)res+=dfs(i,i);
  if(res>0)printf("YES\n");
  else printf("NO\n");
  return 0;
}