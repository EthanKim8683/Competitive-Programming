#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=2000;
pair<I,I>crds[N];
vector<pair<I,I>>curs;
I hlf(pair<I,I>a){
  auto[x,y]=a;
  return x==0?y<0:x<0;
}
pair<I,I>sub(pair<I,I>a,pair<I,I>b){
  auto[x1,y1]=a;auto[x2,y2]=b;
  return{x1-x2,y1-y2};
}
pair<I,I>neg(pair<I,I>a){
  auto[x,y]=a;
  return{-x,-y};
}
Lli crs(pair<I,I>a,pair<I,I>b){
  auto[x1,y1]=a;auto[x2,y2]=b;
  return(Lli)x1*y2-(Lli)y1*x2;
}
B cmp(pair<I,I>a,pair<I,I>b){
  I h1=hlf(a),h2=hlf(b);
  return h1!=h2?h1<h2:crs(a,b)<0;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I x,y;cin>>x>>y;
    crds[i]={x,y};
  }
  Lli res=0;
  for(I i=0;i<n;i++){
    curs.clear();
    for(I j=0;j<n;j++)if(crds[i]!=crds[j])curs.push_back(sub(crds[j],crds[i]));
    sort(curs.begin(),curs.end(),cmp);
    for(auto low:curs){
      pair<I,I>upp=neg(low);
      if(cmp(upp,low))swap(upp,low);
      res+=lower_bound(curs.begin(),curs.end(),low,cmp)-curs.begin();
      res+=lower_bound(curs.begin(),curs.end(),upp,cmp)-upper_bound(curs.begin(),curs.end(),low,cmp);
      res+=curs.end()-upper_bound(curs.begin(),curs.end(),upp,cmp);
    }
  }
  printf("%lli\n",res/6);
}