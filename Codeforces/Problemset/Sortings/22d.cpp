#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=1000;
pair<I,I>segs[N];
B nlds[N];
vector<I>ress;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I l,r;cin>>l>>r;
    if(l>r)swap(l,r);
    segs[i]={r,l};
  }
  sort(segs,segs+n);
  for(I i=0;i<n;i++){
    if(nlds[i])continue;
    auto[r1,l1]=segs[i];
    for(I j=0;j<n;j++){
      auto[r2,l2]=segs[j];
      if(l2>r1||r2<r1)continue;
      nlds[j]=1;
    }
    ress.push_back(r1);
  }
  printf("%i\n",ress.size());
  for(auto i:ress)printf("%i ",i);
}