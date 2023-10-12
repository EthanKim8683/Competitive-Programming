#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
Lli mpw(Lli x,Lli y,Lli m){
  Lli res=1;
  for(x%=m;y;y>>=1,(x*=x)%=m)if(y&1)(res*=x)%=m;
  return res;
}
Lli inv(Lli x,Lli m){
  return mpw(x,m-2,m);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  if(n==4)printf("YES\n1\n3\n2\n4"),exit(0);
  for(I i=2;i<n;i++)if(n%i==0)printf("NO\n"),exit(0);
  printf("YES\n1\n");
  for(I i=2;i<n;i++)printf("%lli\n",i*inv(i-1,n)%n);
  if(n>1)printf("%lli",n);
}
/*
if n is composite, factors of n will cause the prefix product sequence to
reach 0 before a[n - 1] = n

to construct a solution, we must prove the following:

inv(i - 1) will always produce a unique number, since for any i, j such that
j = inv(i), i = inv(j)

therefore, i * inv(i - 1) must also always produce a unique number since
  i * inv(i - 1)
= (i - 1) * inv(i - 1) + inv(i - 1)
= 1 + inv(i - 1)
*/