#include<bits/stdc++.h>
using namespace std;
using I=int;
const I Q=3e5;
const I LOGK=20;
const I FIXK=1<<LOGK;
tuple<I,I,I>ords[Q];
vector<I>cpss;
I sizs[2*FIXK];
I vals[2*FIXK],dels[2*FIXK];
void app(I i,I val){
  vals[i]=sizs[i]*val;
  if(i<FIXK)dels[i]=val;
}
void psh(I i){
  for(I j=LOGK-1;j>0;j--){
    I k=(i+FIXK)>>j;
    if(dels[k]!=-1)app(k<<1,dels[k]),app(k<<1|1,dels[k]),dels[k]=-1;
  }
}
void pll(I i){
  for(i+=FIXK;i>>=1;){
    vals[i]=vals[i<<1]+vals[i<<1|1];
    if(dels[i]!=-1)vals[i]=sizs[i]*dels[i];
  }
}
void asn(I i,I val){
  vals[i+FIXK]=sizs[i+FIXK]*val;
}
void bld(){
  for(I i=FIXK-1;i>0;i--)vals[i]=vals[i<<1]+vals[i<<1|1];
}
void upd(I l,I r,I val){
  psh(l),psh(r-1);
  for(I i=l+FIXK,j=r+FIXK;i<j;i>>=1,j>>=1){
    if(i&1)app(i++,val);
    if(j&1)app(--j,val);
  }
  pll(l),pll(r-1);
}
I qry(I l,I r){
  psh(l),psh(r-1);
  I res=0;
  for(I i=l+FIXK,j=r+FIXK;i<j;i>>=1,j>>=1){
    if(i&1)res+=vals[i++];
    if(j&1)res+=vals[--j];
  }
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  I q;cin>>q;
  for(I i=0;i<q;i++){
    I l,r,k;cin>>l>>r>>k,l--;
    ords[i]={l,r,k};
    cpss.push_back(l);
    cpss.push_back(r);
  }
  cpss.push_back(0),cpss.push_back(n);
  sort(cpss.begin(),cpss.end());
  cpss.erase(unique(cpss.begin(),cpss.end()),cpss.end());
  for(I i=0;i+1<cpss.size();i++)sizs[i+FIXK]=cpss[i+1]-cpss[i];
  for(I i=FIXK-1;i>0;i--)sizs[i]=sizs[i<<1]+sizs[i<<1|1];
  for(I i=0;i+1<cpss.size();i++)asn(i,1);
  bld();
  fill_n(dels,2*FIXK,-1);
  for(I i=0;i<q;i++){
    auto[l,r,k]=ords[i];
    l=lower_bound(cpss.begin(),cpss.end(),l)-cpss.begin();
    r=lower_bound(cpss.begin(),cpss.end(),r)-cpss.begin();
    if(k==1)upd(l,r,0);
    if(k==2)upd(l,r,1);
    printf("%i\n",qry(0,FIXK));
  }
}
/*
range paint range query where we initially solve for the size of each
segment answers queries neatly
*/