#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  printf("%lli\n",((Lli)1<<(n+1))-2);
}