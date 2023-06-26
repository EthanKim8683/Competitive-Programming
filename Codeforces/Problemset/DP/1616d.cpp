#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=50000;
const I MIN=-1e9;
I a_arr[N];
Lli ps[N+1];
vector<Lli>cpss;
I segs1[2*(N+1)],segs2[2*(N+2)];
I pres[N+1];
I n;
I cps(Lli x){
  return lower_bound(cpss.begin(),cpss.end(),x)-cpss.begin();
}
void upd1(I i,I val){
  for(segs1[i+=cpss.size()]=val;i>>=1;)segs1[i]=max(segs1[i<<1],segs1[i<<1|1]);
}
void upd2(I i,I val){
  i+=n+2;
  for(segs2[i]=max(segs2[i],val);i>>=1;)segs2[i]=max(segs2[i<<1],segs2[i<<1|1]);
}
I qry1(I l,I r){
  I res=0;
  for(l+=cpss.size(),r+=cpss.size();l<r;l>>=1,r>>=1){
    if(l&1)res=max(res,segs1[l++]);
    if(r&1)res=max(res,segs1[--r]);
  }
  return res;
}
I qry2(I l,I r){
  I res=MIN;
  for(l+=n+2,r+=n+2;l<r;l>>=1,r>>=1){
    if(l&1)res=max(res,segs2[l++]);
    if(r&1)res=max(res,segs2[--r]);
  }
  return res;
}
I qry2(I i){
  return segs2[i+n+2];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    I x;cin>>x;
    for(I i=0;i<n;i++)ps[i+1]=ps[i]+a_arr[i]-x;
    cpss.clear();
    for(I i=0;i<=n;i++)cpss.push_back(ps[i]);
    sort(cpss.begin(),cpss.end());
    cpss.erase(unique(cpss.begin(),cpss.end()),cpss.end());
    fill_n(segs1,2*cpss.size(),0);
    fill_n(segs2,2*(n+2),MIN);
    for(I i=0;i<=n;i++){
      pres[i]=qry1(cps(ps[i])+1,cpss.size());
      if(i-1>=0)upd1(cps(ps[i-1]),i);
    }
    for(I i=0;i<n;i++)pres[i+1]=max(pres[i+1],pres[i]);
    upd2(0,n),upd2(1,n-1),upd2(2,n-2);
    for(I i=0;i<n;i++)upd2(i+1,qry2(pres[i],i)-1),upd2(i+2,qry2(pres[i],i)-2);
    printf("%i\n",max(qry2(pres[n],n),qry2(n)));
  }
}