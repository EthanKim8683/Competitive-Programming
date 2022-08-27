#include<iostream>
#include<cstdio>
#include<vector>
#include<tuple>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;
using Lli=long long int;
using Llu=long long unsigned;

const I N=20;
const I M=20;

Llu cels[N][M];
vector<tuple<I,I,Llu>>viss1;
vector<tuple<I,I,Llu>>viss2;
I len=1;
Llu val=0;
I n,m;
I len1,len2;

B bnd(I i,I j){
  return i>=0&&i<n&&j>=0&&j<m;
}

void dfs1(I i,I j){
  if(!bnd(i,j))return;
  if(len==len1){
    viss1.push_back({i,j,val^cels[i][j]});
    return;
  }
  val^=cels[i][j];
  len++;
  dfs1(i+1,j);
  dfs1(i,j+1);
  val^=cels[i][j];
  len--;
}

void dfs2(I i,I j){
  if(!bnd(i,j))return;
  if(len==len2){
    viss2.push_back({i,j,val});
    return;
  }
  val^=cels[i][j];
  len++;
  dfs2(i-1,j);
  dfs2(i,j-1);
  val^=cels[i][j];
  len--;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  Llu k;cin>>n>>m>>k;
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)
    cin>>cels[i][j];
  I tot=n+m;
  len1=tot-tot/2;
  len2=tot/2;
  dfs1(0,0);
  dfs2(n-1,m-1);
  sort(viss1.begin(),viss1.end());
  sort(viss2.begin(),viss2.end());
  Lli res=0;
  for(auto[i,j,val]:viss1){
    val^=k;
    auto low=lower_bound(viss2.begin(), viss2.end(),tuple<I,I,Llu>{i,j,val});
    auto upp=upper_bound(viss2.begin(), viss2.end(),tuple<I,I,Llu>{i,j,val});
    res+=upp-low;
  }
  printf("%lli\n",res);
  return 0;
}