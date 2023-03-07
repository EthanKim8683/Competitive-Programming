#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=100000;
const I MAX=1e9;
vector<I>adjs[N];
I sizs[N],tops[N],pars[N],inds[N],invs[N];
I segs[2*N];
I ind=0;
I n;
void upd(I i,I x){
  for(segs[i+=n]=x;i>1;i>>=1)segs[i>>1]=min(segs[i],segs[i^1]);
}
void tog(I i){
  i=inds[i];
  segs[i+n]==MAX?upd(i,i):upd(i,MAX);
}
I qry(I l,I r){
  I res=MAX;
  for(l+=n,r+=n;l<r;l>>=1,r>>=1){
    if(l&1)res=min(res,segs[l++]);
    if(r&1)res=min(res,segs[--r]);
  }
  return res;
}
void dfs1(I a,I p=-1){
  sizs[a]=1;
  pars[a]=p;
  for(auto&b:adjs[a])if(b!=p){
    dfs1(b,a);
    sizs[a]+=sizs[b];
    if(sizs[b]>sizs[adjs[a][0]])swap(b,adjs[a][0]);
  }
}
void dfs2(I a,I p=-1){
  inds[a]=ind++;
  invs[inds[a]]=a;
  for(auto b:adjs[a])if(b!=p){
    tops[b]=b==adjs[a][0]?tops[a]:b;
    dfs2(b,a);
  }
}
I pat(I a){
  I res=MAX;
  for(;tops[a]!=0;a=pars[tops[a]])res=min(res,qry(inds[tops[a]],inds[a]+1));
  res=min(res,qry(inds[0],inds[a]+1));
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I q;cin>>n>>q;
  for(I i=0;i<n-1;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  dfs1(0,0),dfs2(0);
  fill_n(segs,2*n,MAX);
  while(q--){
    I t;cin>>t;
    if(t==0){
      I i;cin>>i,i--;
      tog(i);
    }
    if(t==1){
      I v;cin>>v,v--;
      I res=pat(v);
      printf("%i\n",res==MAX?-1:invs[res]+1);
    }
  }
}