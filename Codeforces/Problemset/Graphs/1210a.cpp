#include<iostream>
#include<cstdio>

using namespace std;

using I=int;
using B=bool;

const I N=7;
const I M=N*(N-1)/2;

pair<I,I>edgs[M];
I dots[N];
B viss[6][6];
I res=0;
I n,m;

void chk(){
  fill(&viss[0][0],&viss[0][0]+sizeof(viss)/sizeof(B),0);
  I cnt=0;
  for(I i=0;i<m;i++){
    auto[a,b]=edgs[i];
    a=dots[a],b=dots[b];
    if(a>b)swap(a,b);
    if(viss[a][b])continue;
    viss[a][b]=true;
    cnt++;
  }
  res=max(res,cnt);
}

void dfs(I d){
  if(d==n){chk();return;}
  for(I i=0;i<6;i++)dots[d]=i,dfs(d+1);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n>>m;
  for(I i=0;i<m;i++){I a,b;cin>>a>>b;edgs[i]={a-1,b-1};}
  dfs(0);
  printf("%i\n",res);
  return 0;
}