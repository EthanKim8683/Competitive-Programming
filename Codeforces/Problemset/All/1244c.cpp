#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
tuple<Lli,Lli,Lli>gcd(Lli a,Lli b){
  if(b==0)return{a,1,0};
  auto[res,x,y]=gcd(b,a%b);
  return{res,y,x-a/b*y};
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  Lli n,p,w,d;cin>>n>>p>>w>>d;
  if(p==0)printf("0 0 %lli\n",n),exit(0);
  auto[g,x,y]=gcd(d,w);
  if(p%g)printf("-1"),exit(0);
  Lli t=w/g,m=(p/g%t*x%t+t)%t,k=(p-m*d)/w,l=n-m-k;
  if(k<0||l<0)printf("-1\n"),exit(0);
  printf("%lli %lli %lli\n",k,m,l);
}