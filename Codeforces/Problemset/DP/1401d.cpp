#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=1e5;
const Lli MOD=1e9+7;

vector<I>adjs[N];
vector<Lli>facs;
vector<Lli>edgs;
I n;

I dfs(I a,I p=-1){
  Lli cnt=1;
  for(auto b:adjs[a])if(b!=p)cnt+=dfs(b,a);
  if(a)edgs.push_back(cnt*(n-cnt));
  return cnt;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    cin>>n;
    for(I i=0;i<n;i++)adjs[i].clear();
    edgs.clear();
    for(I i=0;i<n-1;i++){
      I u,v;cin>>u>>v,u--,v--;
      adjs[u].push_back(v);
      adjs[v].push_back(u);
    }
    I m;cin>>m;
    facs.resize(m);
    for(I i=0;i<m;i++)cin>>facs[i];
    dfs(0);
    while(facs.size()<n-1)facs.push_back(1);
    sort(facs.begin(),facs.end());
    sort(edgs.begin(),edgs.end());
    while(facs.size()>n-1){
      Lli a=facs.back();facs.pop_back();
      Lli b=facs.back();facs.pop_back();
      facs.push_back(a*b%MOD);
    }
    Lli res=0;
    for(I i=0;i<n-1;i++)(res+=facs[i]*edgs[i])%=MOD;
    printf("%lli\n",res);
  }
}