#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=15;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  printf("%lli\n",(Lli[]){1,0,18,0,1800,0,670320,0,734832000,0,890786230,0,695720788,0,150347555,0}[n-1]);
}
/*
we know that the sum of bin(n, i) for all i in [0, n] is bin(2 * n, n)
 
this means that there are at most bin(30, 15) states to consider (the answer
is always 0 if n is even)
*/