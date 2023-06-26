#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using Lf=long double;
const I N=100000;
Lli ares[N];
vector<Lli>cpss;
Lli segs[2*N];
I n;
void upd(I i,Lli val){
  i+=cpss.size();
  for(segs[i]=max(segs[i],val);i>>=1;)segs[i]=max(segs[i<<1],segs[i<<1|1]);
}
Lli qry(I l,I r){
  Lli res=0;
  for(l+=cpss.size(),r+=cpss.size();l<r;l>>=1,r>>=1){
    if(l&1)res=max(res,segs[l++]);
    if(r&1)res=max(res,segs[--r]);
  }
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  for(I i=0;i<n;i++){
    I r,h;cin>>r>>h;
    ares[i]=(Lli)r*r*h;
    cpss.push_back(ares[i]);
  }
  sort(cpss.begin(),cpss.end());
  cpss.erase(unique(cpss.begin(),cpss.end()),cpss.end());
  for(I i=0;i<n;i++){
    I j=lower_bound(cpss.begin(),cpss.end(),ares[i])-cpss.begin();
    upd(j,qry(0,j)+ares[i]);
  }
  Lf res=qry(0,cpss.size());
  printf("%.9Lf\n",res*3.14159265359L);
}