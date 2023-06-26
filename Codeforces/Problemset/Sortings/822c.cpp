#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
const I L=2e5;
const I R=2e5;
const Lli MAX=1e18;
I durs[N],csts[N];
vector<I>lows[L+1],upps[R+1];
Lli pres[L+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill_n(pres,L+1,MAX);
  I n,x;cin>>n>>x;
  for(I i=0;i<n;i++){
    I l,r,cst;cin>>l>>r>>cst;
    lows[l].push_back(i);
    upps[r].push_back(i);
    durs[i]=r-l+1,csts[i]=cst;
  }
  Lli res=MAX;
  for(I i=1;i<=L;i++){
    for(auto j:lows[i]){
      I dur=durs[j],cst=csts[j];
      if(x>=dur)res=min(res,cst+pres[x-dur]);
    }
    for(auto j:upps[i]){
      I dur=durs[j],cst=csts[j];
      pres[dur]=min(pres[dur],(Lli)cst);
    }
  }
  printf("%lli\n",res==MAX?-1:res);
}