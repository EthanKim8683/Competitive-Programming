#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
using I128=__int128;
const I N=100000;
const Lli MAX=1e18;
I inds[N];
pair<I,I>vecs[N];
I hlf(pair<I,I>a){
  auto[x,y]=a;
  return y==0?x>0:y>0;
}
B cmp1(I a,I b){
  auto[x1,y1]=vecs[a];auto[x2,y2]=vecs[b];
  I hlf1=hlf(vecs[a]),hlf2=hlf(vecs[b]);
  return hlf1==hlf2?x1*y2>x2*y1:hlf1<hlf2;
}
B cmp2(pair<Lli,Lli>a,pair<Lli,Lli>b){
  auto[x1,y1]=a;auto[x2,y2]=b;
  return(I128)x1*y2>(I128)x2*y1;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I x,y;cin>>x>>y;
    vecs[i]={x,y};
  }
  iota(inds,inds+n,0);
  sort(inds,inds+n,cmp1);
  pair<pair<Lli,Lli>,I>res={{-MAX,1},0};
  for(I i=0;i<n;i++){
    auto[x1,y1]=vecs[inds[i]];
    auto[x2,y2]=vecs[inds[(i+1)%n]];
    Lli num=x1*x2+y1*y2;
    Lli den=x1*x1+y1*y1;
    if(num<0)den=-den;
    num*=num;
    den*=x2*x2+y2*y2;
    if(den<0)num=-num,den=-den;
    pair<Lli,Lli>cur={num,den};
    if(cmp2(cur,res.first))res={cur,i};
  }
  auto[dot,i]=res;
  printf("%i %i",inds[i]+1,inds[(i+1)%n]+1);
}
/*
if we sort the vectors radially, we can compare the dot products of all
adjacent pairs

to be as precise as possible, we store the squares of the numerator and
denominator of each dot product, since the square-root operation required to
divide the magnitudes of either vector may affect precision

we also must preserve the sign of the numerator prior to squaring, since
negative and positive dot products would otherwise appear the same
*/