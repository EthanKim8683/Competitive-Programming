#include<iostream>
#include<cstdio>
 
using namespace std;
 
using I=int;
using Lli=long long int;
 
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m,k;cin>>n>>m>>k;
    Lli t=(Lli)n*(n-1)/2;
    if(m<n-1||m>t){printf("NO\n");continue;}
    I l=m==t?1:2;
    if(n==1)l=0;
    if(n==2)l=1;
    if(l<k-1)printf("YES\n");
    else printf("NO\n");
  }
  return 0;
}