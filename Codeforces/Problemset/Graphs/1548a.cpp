#include<iostream>
#include<cstdio>
#include<set>

using namespace std;

using I=int;
using B=bool;

const I N=2e5;

set<I>adjs[N];
B kils[N];
I cnt;

void upd(I a){
  B k=adjs[a].upper_bound(a)!=adjs[a].end();
  if(kils[a]==k)return;
  kils[a]=k;
  cnt+=k?-1:1;
}

void add(I a,I b){
  adjs[a].insert(b);
  adjs[b].insert(a);
  upd(a),upd(b);
}

void rem(I a,I b){
  adjs[a].erase(b);
  adjs[b].erase(a);
  upd(a),upd(b);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  cnt=n;
  for(I i=0;i<m;i++){I u,v;cin>>u>>v,add(u-1,v-1);}
  I q;cin>>q;
  while(q--){
    I t;cin>>t;
    if(t==1){I u,v;cin>>u>>v,add(u-1,v-1);}
    if(t==2){I u,v;cin>>u>>v,rem(u-1,v-1);}
    if(t==3){printf("%i\n",cnt);}
  }
  return 0;
}