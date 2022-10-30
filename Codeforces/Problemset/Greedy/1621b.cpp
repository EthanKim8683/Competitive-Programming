#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=1e5;

tuple<I,I,I>segs[N];

I cst(I a,I b,I c){
  I res=get<2>(segs[a])+get<2>(segs[b]);
  if(c!=-1)res=min(res,get<2>(segs[c]));
  return res;
}

void cmb(I&x,I i){
  if(x==-1||get<2>(segs[i])<get<2>(segs[x]))x=i;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++){
      I l,r,c;cin>>l>>r>>c;
      segs[i]={l,r,c};
    }
    I x=0,y=0,z=0;
    printf("%i\n",cst(x,y,z));
    for(I i=1;i<n;i++){
      auto[l,r,c]=segs[i];
      I a=get<0>(segs[x]),b=get<1>(segs[y]);
      if(l==a&&r==b)cmb(x,i),cmb(y,i),cmb(z,i);
      if(l >a&&r==b)cmb(y,i);
      if(l==a&&r <b)cmb(x,i);
      if(l <a&&r==b)x=z=i,cmb(y,i);
      if(l==a&&r >b)y=z=i,cmb(x,i);
      if(l <a&&r >b)x=y=z=i;
      if(l <a&&r <b)x=i,z=-1;
      if(l >a&&r >b)y=i,z=-1;
      if(l >a&&r <b);
      printf("%i\n",cst(x,y,z));
    }
  }
}