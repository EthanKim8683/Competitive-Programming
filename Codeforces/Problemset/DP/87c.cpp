#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const I MAX=1e9;
vector<I>facs[2*N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=2;i<=2*n;i++)for(I j=i;j<=2*n;j+=i)facs[j].push_back(i);
  for(I i=1;i<=n;i++){
    for(auto j:facs[2*i]){
      Lli rem=i-(Lli)j*(j+1)/2;
      if(rem<0||rem%j)continue;
      I k=rem/j;
      // transition from [k+1,k+j]
    }
  }
}
/*
n * ((n + 1) / 2 + x) = m
n * (n + 1) / 2 + n * x = m
n * x = m - n * (n + 1) / 2
if m % n == 0 and m >= n * (n + 1) / 2:
  can transition

factor combinations at max F = 128
N * F

Need to figure out game stuff
*/