#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  Lli n;cin>>n;
  if(n>=14)printf("%lli\n",49*n-247),exit(0);
  if(n>=10)printf("%lli\n",(-n*n*n+36*n*n-137*n+234)/6),exit(0);
  if(n>=9)printf("%lli\n",(-n*n*n+30*n*n-164*n+369)/3),exit(0);
  if(n>=6)printf("%lli\n",3*n*n-6*n+11),exit(0);
  printf("%lli\n",(n*n*n+6*n*n+11*n+6)/6);
}