#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using Lli=long long int;
const I M=200000;
I ps[M+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  S a;cin>>a;
  S b;cin>>b;
  I n=a.size(),m=b.size();
  for(I i=0;i<m;i++)ps[i+1]=ps[i]+b[i]-'0';
  Lli res=0;
  for(I i=0;i<n;i++){
    I j=m-(n-i)+1;
    if(a[i]=='0')res+=ps[j]-ps[i];
    if(a[i]=='1')res+=(j-i)-(ps[j]-ps[i]);
  }
  printf("%lli\n",res);
}
/*
each digit in a pairs with a range of digits in b

if a[i] is 0, b[j] must be 1 to contribute to the sum, so we count the number
of j in i's range such that b[j] = 1

likewise, if a[i] is 1, b[j] must be 0 to contribute to the sum
*/