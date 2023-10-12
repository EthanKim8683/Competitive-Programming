#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I M=1e6;
const I LOGM=20;
I h_arr[2],a_arr[2],x_arr[2],y_arr[2];
I diss[M];
pair<I,I>lins[2];
tuple<I,I,I>gcd(I a,I b){
  if(b==0)return{a,1,0};
  auto[g,x,y]=gcd(b,a%b);
  return{g,y,x-y*(a/b)};
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I m;cin>>m;
  for(I i=0;i<2;i++){
    cin>>h_arr[i]>>a_arr[i];
    cin>>x_arr[i]>>y_arr[i];
  }
  for(I i=0;i<2;i++){
    I j=h_arr[i],cnt1=0,cnt2=1;
    for(;j!=a_arr[i];j=((Lli)x_arr[i]*j+y_arr[i])%m){
      if(cnt1>m)printf("-1"),exit(0);
      cnt1++;
    }
    j=((Lli)x_arr[i]*j+y_arr[i])%m;
    for(;j!=a_arr[i];j=((Lli)x_arr[i]*j+y_arr[i])%m){
      if(cnt2>m){cnt2=0;break;}
      cnt2++;
    }
    lins[i]={cnt1,cnt2};
  }
  auto[a,c]=lins[0];
  auto[b,d]=lins[1];
  auto[g,x,y]=gcd(c,d);
  Lli equ=b-a;
  if(equ%g)printf("-1"),exit(0);
  Lli res=(Lli)equ/g*x*c+a,fac=(Lli)c/g*d;
  if(fac!=0){
    while(max(a,b)>res)res+=fac;
    while(max(a,b)<=res-fac)res-=fac;
  }else{
    if(max(a,b)>res)printf("-1"),exit(0);
  }
  printf("%lli\n",res);
}