#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  Lli n;cin>>n;
  Lli m=1+(n-1)*3;
  printf("%lli\n",m*(m+1)/2+3*n*(n-1)/2);
}