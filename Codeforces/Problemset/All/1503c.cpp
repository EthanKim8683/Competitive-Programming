#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const Lli MAX=1e18;
pair<I,I>cits[N];
vector<I>cpss;
Lli segs[2][4*N];
I cps(I x){
  return lower_bound(cpss.begin(),cpss.end(),x)-cpss.begin();
}
void upd(I t,I i,Lli val){
  i+=cpss.size();
  for(segs[t][i]=min(segs[t][i],val);i>>=1;)segs[t][i]=min(segs[t][i<<1],segs[t][i<<1|1]);
}
Lli qry(I t,I l,I r){
  Lli res=MAX;
  for(l+=cpss.size(),r+=cpss.size();l<r;l>>=1,r>>=1){
    if(l&1)res=min(res,segs[t][l++]);
    if(r&1)res=min(res,segs[t][--r]);
  }
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&segs[0][0],&segs[0][0]+2*(4*N),MAX);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I a,c;cin>>a>>c;
    cits[i]={a,c};
    cpss.push_back(a);
    cpss.push_back(a+c);
  }
  sort(cpss.begin(),cpss.end());
  cpss.erase(unique(cpss.begin(),cpss.end()),cpss.end());
  sort(cits,cits+n);
  auto[a,c]=cits[0];
  upd(0,cps(a+c),-(a+c)),upd(1,cps(a+c),0);
  Lli res;
  for(I i=1;i<n;i++){
    auto[a,c]=cits[i];
    res=min(qry(0,0,cps(a))+a,qry(1,cps(a),cpss.size()));
    upd(0,cps(a+c),res-(a+c)),upd(1,cps(a+c),res);
  }
  for(I i=0;i<n;i++){
    auto[a,c]=cits[i];
    res+=c;
  }
  printf("%lli\n",res);
}