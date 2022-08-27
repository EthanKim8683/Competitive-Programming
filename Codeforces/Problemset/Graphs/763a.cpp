#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;
const I LOGN=17;
const I MAX=1e9;
const I MIN=-1e9;

vector<I>adjs[N];
I c_arr[N];
I els[N],ers[N];
I sprs[2][N][LOGN];
I ps[N];
I t=0;
I res=-1;
I n;

void bld(){
  for(I i=1;i<LOGN;i++)for(I j=0;j+(1<<(i-1))<n;j++){
    sprs[0][j][i]=min(sprs[0][j][i-1],sprs[0][j+(1<<(i-1))][i-1]);
    sprs[1][j][i]=max(sprs[1][j][i-1],sprs[1][j+(1<<(i-1))][i-1]);
  }
}

B qry(I a){
  I l=els[a],r=ers[a];
  I dis=31-__builtin_clz(r-l);
  I x=min(sprs[0][l][dis],sprs[0][r-(1<<dis)][dis]);
  I y=max(sprs[1][l][dis],sprs[1][r-(1<<dis)][dis]);
  return x==y;
}

void dfs1(I a,I p=-1){
  sprs[0][t][0]=sprs[1][t][0]=c_arr[a];
  els[a]=t++;
  for(auto b:adjs[a])
    if(b!=p)dfs1(b,a);
  ers[a]=t;
}

B chk(I a,I p=-1){
  for(auto b:adjs[a]){
    if(b==p)continue;
    if(!qry(b))return false;
  }
  return true;
}

B mat(I a,I b){
  return c_arr[a]==c_arr[b]&&qry(b);
}

void dfs2(I a,I p=-1){
  I c=0;
  for(auto b:adjs[a])
    if(b!=p)c+=!mat(a,b);
  if(c>1)return;
  for(auto b:adjs[a]){
    if(b==p)continue;
    if(c-!mat(a,b)!=0)continue;
    if(chk(b,a))res=b+1;
    if(c_arr[a]==c_arr[b])dfs2(b,a);
  }
}

I main(){
  fill(&sprs[0][0][0],&sprs[0][0][0]+sizeof(sprs[0])/sizeof(I),MAX);
  fill(&sprs[1][0][0],&sprs[1][0][0]+sizeof(sprs[1])/sizeof(I),MIN);
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  for(I i=0;i<n-1;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs[u].push_back(v);
    adjs[v].push_back(u);
  }
  for(I i=0;i<n;i++)cin>>c_arr[i];
  dfs1(0);
  bld();
  if(chk(0))res=1;
  dfs2(0);
  if(res==-1)printf("NO\n");
  else printf("YES\n%i\n",res);
  return 0;
}