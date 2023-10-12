#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=20;
map<I,I>cnts1;
vector<pair<I,I>>cnts2;
Lli facs[N+1];
Lli bin(I n,I k){
  if(n<0||k<0||n-k<0)return 0;
  return facs[n]/(facs[k]*facs[n-k]);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  facs[0]=1;
  for(I i=1;i<=N;i++)facs[i]=facs[i-1]*i;
  I t;cin>>t;
  while(t--){
    Lli k;cin>>k;
    cnts1.clear();
    I n=2;
    for(;k;k/=n,n++)cnts1[k%n]++;
    n--;
    cnts2.assign(cnts1.rbegin(),cnts1.rend());
    Lli res=0;
    for(auto&[r1,cnt1]:cnts2){
      if(r1==0)continue;
      cnt1--;
      Lli cur=1;
      I pre=n-1,rem=0;
      for(auto[r2,cnt2]:cnts2){
        r2=max(r2,1);
        rem+=pre-r2;
        cur*=bin(rem,cnt2);
        pre=r2,rem-=cnt2;
      }
      res+=cur;
      cnt1++;
    }
    printf("%lli\n",res-1);
  }
}
/*
we can simplify the problem to assigning indistinguishable remainders to
divisors such that all divisors are strictly greater than its assigned
remainder and the final divisor has a non-zero remainder

to do this, we can first fix the final divisor to any non-zero remainder, then
count the number of ways to assign the remaining remainders

this can be done by processing the remainders from greatest to least, choosing
from the (invariant) number of available divisors each time
*/