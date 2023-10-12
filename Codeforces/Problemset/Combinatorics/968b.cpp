#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lf=long double;
const I N=1e6;
I prms[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>prms[i];
  I cnt=0;
  for(I i=0;i<n;i++)cnt+=prms[i]==i+1;
  Lf pev=n*pow((Lf)(n-2)/n,3*n),aev=n*pow((Lf)(n-2)/n,7*n+1);
  printf("%s\n",n==5||abs(cnt-pev)<abs(cnt-aev)?"Petr":"Um_nik");
}
/*
by linearity of expectation, the expected number of unchanged elements is equal
to the probability of a single element being unchanged summed up for all
elements

the probability of a single element being unchanged after x operations is
((n - 2) / n) ^ x, where (n - 2) / n is the probability of a single element
being unchanged after 1 operation

this means, the expected number of unchanged elements for Petr's method is
n * ((n - 2) / n) ^ (3 * n) and Alex's method, n * ((n - 2) / n) ^ (7 * n + 1)
*/