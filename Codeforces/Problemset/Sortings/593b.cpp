#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=100000;
pair<I,I>lins[N];
I inds1[N],inds2[N];
I x1,x2;
B cmp1(I a,I b){
  auto[k1,b1]=lins[a];auto[k2,b2]=lins[b];
  Lli y1=(Lli)k1*x1+b1,y2=(Lli)k2*x1+b2;
  return y1==y2?k1<k2:y1<y2;
}
B cmp2(I a,I b){
  auto[k1,b1]=lins[a];auto[k2,b2]=lins[b];
  Lli y1=(Lli)k1*x2+b1,y2=(Lli)k2*x2+b2;
  return y1==y2?k1>k2:y1<y2;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  cin>>x1>>x2;
  for(I i=0;i<n;i++){
    I k,b;cin>>k>>b;
    lins[i]={k,b};
  }
  iota(inds1,inds1+n,0);
  iota(inds2,inds2+n,0);
  sort(inds1,inds1+n,cmp1);
  sort(inds2,inds2+n,cmp2);
  for(I i=0;i<n;i++)if(inds1[i]!=inds2[i])printf("YES"),exit(0);
  printf("NO");
}