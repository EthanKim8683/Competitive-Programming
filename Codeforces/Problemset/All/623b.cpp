#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1000000;
const Lli MAX=1e18;
I a_arr[N];
set<I>facs;
Lli csts1[N],csts2[N];
void add1(I a){
  for(I i=2;i*i<=a;i++)if(a%i==0){
    facs.insert(i);
    while(a%i==0)a/=i;
  }
  if(a>1)facs.insert(a);
}
void add2(I a){
  add1(a+1),add1(a-1),add1(a);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;Lli a,b;cin>>n>>a>>b;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  add2(a_arr[0]),add2(a_arr[n-1]);
  Lli res=MAX;
  for(auto i:facs){
    fill_n(csts1,n,MAX);
    fill_n(csts2,n,MAX);
    Lli cst=0;
    for(I j=0;j<n;j++){
      I a=a_arr[j];
      if(a%i==0)cst+=0;
      else if((a+1)%i==0)cst+=b;
      else if((a-1)%i==0)cst+=b;
      else break;
      csts1[j]=cst;
    }
    cst=0;
    for(I j=n-1;j>=0;j--){
      I a=a_arr[j];
      if(a%i==0)cst+=0;
      else if((a+1)%i==0)cst+=b;
      else if((a-1)%i==0)cst+=b;
      else break;
      csts2[j]=cst;
    }
    Lli pre=0;
    for(I j=0;j<n;j++){
      Lli cst1=csts1[j]-(Lli)(j+1)*a;
      Lli cst2=csts2[j]+(Lli)j*a;
      res=min(res,pre+cst2);
      res=min(res,cst1+(Lli)n*a);
      pre=min(pre,cst1);
    }
  }
  printf("%lli\n",res);
}
/*
the maximum number of possible prime gcd's for any prefix is log(A)

this is because there are at most log(A) prime factors of a[0] and successive
a[i] can only remove them

thus, we can find the maximum pairing of prefix and suffix (including cost in
between) with equal gcd
*/