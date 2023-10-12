#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=2e5;
const I L=5e5;
const I LOGN=18;
const I MAX=1e9;
pair<I,I>rngs[N];
I ancs[N][LOGN];
pair<I,I>segs[2*(L+1)];
void upd(I i,pair<I,I>val){
  i+=L+1;
  for(segs[i]=min(segs[i],val);i>>=1;)segs[i]=min(segs[i<<1],segs[i<<1|1]);
}
pair<I,I>qry(I l,I r){
  pair<I,I>res={MAX,-1};
  for(l+=L+1,r+=L+1;l<r;l>>=1,r>>=1){
    if(l&1)res=min(res,segs[l++]);
    if(r&1)res=min(res,segs[--r]);
  }
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++){
    I l,r;cin>>l>>r;
    rngs[i]={l,r};
  }
  sort(rngs,rngs+n);
  fill_n(segs,2*(L+1),pair<I,I>{MAX,-1});
  for(I i=0;i<n;i++){
    auto[l,r]=rngs[i];
    I j=qry(l,r+1).second;
    ancs[i][0]=j==-1?i:j;
    upd(r,{l,i});
  }
  for(I i=1;i<LOGN;i++)for(I j=0;j<n;j++)ancs[j][i]=ancs[ancs[j][i-1]][i-1];
  while(m--){
    I x,y;cin>>x>>y;
    I j=qry(y,L+1).second;
    if(j==-1){printf("-1\n");continue;}
    I res=1;
    if(rngs[j].first>x){
      for(I i=LOGN-1;i>=0;i--){
        I k=ancs[j][i];
        if(rngs[k].first>x)j=k,res+=1<<i;
      }
      j=ancs[j][0],res++;
    }
    printf("%i\n",rngs[j].first>x?-1:res);
  }
}