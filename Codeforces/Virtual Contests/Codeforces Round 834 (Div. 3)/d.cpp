#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I X=32;
const I Y=12;
const I Z=9;
Lli fivs[X+1];
Lli twos[Y+1];
Lli tens[Z+1];
Lli m;
B chk(Lli x,I y){
  return x*tens[y]<=m;
}
I fnd(Lli x){
  I l=0,r=Z;
  while(l<r){
    I m=l+(r-l+1)/2;
    chk(x,m)?l=m:r=m-1;
  }
  return l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fivs[0]=1;
  for(I i=1;i<=X;i++)fivs[i]=fivs[i-1]*5;
  twos[0]=1;
  for(I i=1;i<=Y;i++)twos[i]=twos[i-1]*2;
  tens[0]=1;
  for(I i=1;i<=Z;i++)tens[i]=tens[i-1]*10;
  I t;cin>>t;
  while(t--){
    I n;cin>>n>>m;
    I x=n;
    while(x%10==0)x/=10;
    I two=0,fiv=0;
    for(I i=x;i%2==0;i/=2)two++;
    for(I i=x;i%5==0;i/=5)fiv++;
    pair<I,Lli>res={0,1};
    for(I i=0;i<=two;i++)for(I j=0;j<=fiv;j++){
      Lli cur=fivs[i]*twos[j];
      if(cur>m)continue;
      I k=fnd(cur),l=i+j+k;
      cur*=tens[k];
      cur*=m/cur;
      res=max(res,{l,cur});
    }
    printf("%lli\n",n*res.second);
  }
}