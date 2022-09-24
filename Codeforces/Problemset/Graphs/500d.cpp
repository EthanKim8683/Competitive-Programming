#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

using I=int;
using Lli=long long int;
using Ld=long double;

const I N=1e5;

vector<pair<I,I>>adjs[N];
I l_arr[N-1];
I sizs1[N],sizs2[N];
Lli dp1[N],dp2[N];
Lli pats[N-1];
I n;

void dfs1(I a,I p=-1){
  for(auto[b,i]:adjs[a])if(b!=p){
    dfs1(b,a);
    sizs1[a]+=sizs1[b]+1;
    pats[i]=(Lli)(sizs1[b]+1)*(n-(sizs1[b]+1));
  }
  sizs2[a]=n-(sizs1[a]+1);
}

void dfs2(I a,I p=-1){
  for(auto[b,i]:adjs[a])if(b!=p){
    dfs2(b,a);
    dp1[a]+=dp1[b];
    dp1[a]+=(sizs1[b]+1)*l_arr[i];
  }
}

void dfs3(I a,I p=-1){
  for(auto[b,i]:adjs[a])if(b!=p){
    dp2[b]+=dp2[a];
    dp2[b]+=dp1[a]-(dp1[b]+(sizs1[b]+1)*l_arr[i]);
    dp2[b]+=sizs2[b]*l_arr[i];
    dfs3(b,a);
  }
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  for(I i=0;i<n-1;i++){
    I a,b,l;cin>>a>>b>>l,a--,b--;
    adjs[a].push_back({b,i});
    adjs[b].push_back({a,i});
    l_arr[i]=l;
  }
  dfs1(0),dfs2(0),dfs3(0);
  Ld ev=0;
  for(I i=0;i<n;i++)ev+=dp1[i]+dp2[i];
  ev*=(n-2)*3;
  I q;cin>>q;
  while(q--){
    I r,w;cin>>r>>w,r--;
    ev-=pats[r]*2*(n-2)*3*(l_arr[r]-w);
    l_arr[r]=w;
    printf("%.10Lf\n",ev/((Lli)n*(n-1)*(n-2)));
  }
  return 0;
}