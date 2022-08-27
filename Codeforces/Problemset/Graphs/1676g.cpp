#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using S=string;

const I N=4000;

vector<I>adjs[N];
S s;
I bps[N+1],wps[N+1];
I tb[N],te[N];
I ti=0;

void dfs(I a){
  bps[ti+1]+=s[a]=='B';
  wps[ti+1]+=s[a]=='W';
  tb[a]=ti++;
  for(auto b:adjs[a])dfs(b);
  te[a]=ti;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    fill_n(bps,n+1,0),fill_n(wps,n+1,0);
    ti=0;
    for(I i=0;i<n;i++)adjs[i].clear();
    for(I i=1;i<n;i++){
      I a;cin>>a,a--;
      adjs[a].push_back(i);
    }
    cin>>s;
    dfs(0);
    for(I i=0;i<n;i++)
      bps[i+1]+=bps[i],wps[i+1]+=wps[i];
    I res=0;
    for(I i=0;i<n;i++){
      I e=te[i],b=tb[i];
      res+=bps[e]-bps[b]==wps[e]-wps[b];
    }
    printf("%i\n",res);
  }
  return 0;
}