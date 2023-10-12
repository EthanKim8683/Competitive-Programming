#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using I128=__int128;
const I N=1e6;
const Lli BAS=(1ll<<31)-1;
const Lli MOD=(1ll<<61)-1;
vector<I>adjs[N];
Lli pows[N];
map<Lli,I>pres;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  pows[0]=1;
  for(I i=1;i<N;i++)pows[i]=(I128)pows[i-1]*BAS%MOD;
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I v,u;cin>>v>>u,v--,u--;
    adjs[v].push_back(u);
    adjs[u].push_back(v);
  }
  Lli res=0;
  for(I i=0;i<n;i++){
    Lli hsh=0;
    for(auto j:adjs[i])(hsh+=pows[j])%=MOD;
    res+=pres[hsh]+pres[(hsh+pows[i])%MOD];
    pres[hsh]++,pres[(hsh+pows[i])%MOD]++;
  }
  printf("%lli\n",res);
}
/*
a pair of profiles i, j are doubles if both profiles cover the same set of
profiles disregarding i and j

we can check this using hashing
*/