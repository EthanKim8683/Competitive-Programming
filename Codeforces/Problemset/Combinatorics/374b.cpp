#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using S=string;
const I N=100000;
I pars[N];
I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}
void uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
}
I siz(I i){
  return-pars[fnd(i)];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  S a;cin>>a;
  I n=a.size();
  fill_n(pars,n,-1);
  for(I i=0;i+1<n;i++)if(a[i]+a[i+1]-2*'0'==9)uni(i,i+1);
  Lli res=1;
  for(I i=0;i<n;i++)if(fnd(i)==i){
    I cur=siz(i);
    if(cur>1&&cur%2==1)res*=cur/2+1;
  }
  printf("%lli\n",res);
}
/*
we must utilize the maximum number of pairs possible

however, if a range such that each adjacent pair has sum equal to 9 is of odd
length, 1 digit will be left over

the number of ways to select pairs is equal to the number of selections of
that 1 digit
*/