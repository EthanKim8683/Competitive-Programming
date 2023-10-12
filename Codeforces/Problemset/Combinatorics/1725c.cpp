#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=3e5;
const I M=3e5;
const Lli MOD=998244353;
Lli facs[M+1];
I d_arr[N];
Lli ps[N];
set<Lli>viss;
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
Lli inv(Lli x){
  return mpw(x,MOD-2);
}
Lli bin(I n,I k){
  return facs[n]*inv(facs[k]*facs[n-k])%MOD;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  facs[0]=1;
  for(I i=1;i<=M;i++)facs[i]=facs[i-1]*i%MOD;
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>d_arr[i];
  copy_n(d_arr,n,ps);
  for(I i=0;i+1<n;i++)ps[i+1]+=ps[i];
  I cnt=0;
  if(ps[n-1]%2==0){
    Lli hlf=ps[n-1]/2;
    for(I i=0;i<n;i++){
      cnt+=viss.find(ps[i]%hlf)!=viss.end();
      viss.insert(ps[i]%hlf);
    }
  }
  Lli res=0;
  for(I i=0;i<=cnt;i++){
    Lli cur=bin(cnt,i);
    (cur*=bin(m,i))%=MOD;
    (cur*=facs[i])%=MOD;
    (cur*=mpw((Lli)(m-i)*(m-i-1),cnt-i))%=MOD;
    (cur*=mpw(m-i,n-2*cnt))%=MOD;
    (res+=cur)%=MOD;
  }
  printf("%lli\n",res);
}
/*
if two arcs (each may consist of multiple arcs themselves) conjoined at a
vertex have length sum equal to half the total circumference of the mirror,
the endpoints of the arcs form a right triangle 

this is because, if we draw two different lines spanning the diameter of the
mirror, we will always get a rectangle and, by having an arc half the total
circumference of the mirror, two vertices form one such line, and the third
forms half the second

using this observation, we can effectively look at just pairs of vertices on
opposite ends of the mirror

if a pair is both one color, no other vertex can be that color (since they
would form a triangle with the pair)

this means we can count the number colorings for each number of pairs such that
both vertices in each pair are one color
*/