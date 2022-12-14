#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using S=string;
const I N=4000;
I cnts[9*N+1];
I sum;
I a;
I fnd(I x){
  if(a==0){
    if(x==0)return sum;
    return cnts[0];
  }
  I l=0,r=9*N;
  while(l<=r){
    I m=l+(r-l)/2;
    I val=m*x;
    if(val==a)return cnts[m];
    if(val>a)r=m-1;
    if(val<a)l=m+1;
  }
  return 0;
}
I main(){
  cin>>a;
  S s;cin>>s;
  I n=s.size();
  for(I i=0;i<n;i++){
    I cur=0;
    for(I j=i;j<n;j++){
      cur+=s[j]-'0';
      cnts[cur]++;
    }
  }
  sum=accumulate(cnts,cnts+9*n+1,0);
  Lli res=0;
  for(I i=0;i<n;i++){
    I cur=0;
    for(I j=i;j<n;j++){
      cur+=s[j]-'0';
      res+=fnd(cur);
    }
  }
  printf("%lli\n",res);
}