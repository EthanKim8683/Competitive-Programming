#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=100;
const I M=20;
const Lli MAX=8e18;
I x_arr[N];
I k_arr[N];
I msks[N];
vector<I>slvs[M];
Lli dp[1<<M];
I inds[N];
B cmp(I a,I b){
  return k_arr[a]<k_arr[b];
}
void cmb(Lli&a,Lli b){
  a=min(a,b);
}
I fsz(I i){
  return i&1?__builtin_ctz(~i&(i<<1)):0;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,b;cin>>n>>m>>b;
  for(I i=0;i<n;i++){
    I x,k,m;cin>>x>>k>>m;
    x_arr[i]=x,k_arr[i]=k;
    for(I j=0;j<m;j++){
      I p;cin>>p,p--;
      msks[i]|=1<<p,slvs[p].push_back(i);
    }
  }
  iota(inds,inds+n,0);
  sort(inds,inds+n,cmp);
  Lli res=MAX;
  for(I i=0;i<n;i++){
    fill_n(dp,1<<m,MAX),dp[0]=0;
    for(I j=0;j<(1<<m)-1;j++)if(dp[j]!=MAX)for(auto k:slvs[fsz(j)])if(k_arr[k]<=k_arr[inds[i]])cmb(dp[j|msks[k]],dp[j]+x_arr[k]);
    res=min(res,dp[(1<<m)-1]+(Lli)k_arr[inds[i]]*b);
  }
  printf("%lli\n",res==MAX?-1:res);
}