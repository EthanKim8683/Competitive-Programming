#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lf=long double;
using Lli=long long int;
using B=bool;
const I N=1e3;
Lli bin(I n,I k){
  if(n<0||k<0||n-k<0)return 0;
  Lli res=1;
  for(I i=n-k+1;i<=n;i++)res*=i;
  for(I i=1;i<=k;i++)res/=i;
  return res;
}
I main(){
  I n;Lf p;cin>>n>>p;
  I l=0,r=n;
  while(l<r){
    I m=l+(r-l)/2;
    bin(n-m,2)*bin(m,1)+2*bin(n-m,1)*bin(m,2)+2*bin(n-m,0)*bin(m,3)>=ceil(2*p*bin(n,3))?r=m:l=m+1;
  }
  printf("%i\n",l);
}
/*
the probability a map Johnny has studied is played can be considered as the
combination of 4 cases:
- Johnny has studied 0 of the initial 3 selected maps:
  - Regardless of which player chooses which map, Johnny has studied none of
    the maps: 0
- Johnny has studied 1 of the initial 3 selected maps:
  - The opponent discards the same map as Johnny: (1 / 3) * (1 / 2)
  - The opponent discards the map Johnny has studied: (1 / 3) * (0 / 1)
  - The opponent discards the remaining map: (1 / 3) * (1 / 1)
- Johnny has studied 2 of the initial 3 selected maps:
  - The opponent discards the same map as Johnny: (1 / 3) * (2 / 2)
  - The opponent discards either of the remaining maps: (2 / 3) * (1 / 1)
- Johnny has studied 3 of the initial 3 selected maps:
  - Regardless of which player chooses which map, Johnny has studied all of
    the maps: 1

The number of maps Johnny has studied can be used to determine the probability
of each of these 4 cases occurring, the weighed sum of which we can binary
search on to find the answer
*/