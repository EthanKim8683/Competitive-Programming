#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=2e5;

vector<I>adjs[N];
I deps[N];
I n,k;
I x;
I cnt;

I dfs(I a,I d=0){
}

B chk(I v){
  x=v,cnt=0;
  dfs(0);
  return cnt<=k;
}

I fnd(){
  I l=1,r=n;
  while(l<r){
    I m=l+(r-l)/2;
    chk(m)?r=m:l=m+1;
  }
  return l;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    cin>>n>>k;
    for(I i=0;i<n;i++)adjs[i].clear();
    for(I i=1;i<n;i++){
      I p;cin>>p,p--;
      adjs[p].push_back(i);
    }
    printf("%i\n",fnd());
  }
}