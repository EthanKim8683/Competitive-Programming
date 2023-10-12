#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using Lf=long double;
using B=bool;
const I N=200000;
const I A=10000;
const I ITR=100;
I a_arr[N];
I n;
pair<Lf,Lf>dis(Lf x){
  Lf pre1=0,pre2=0,ext1,ext2,acc=0;
  for(I i=0;i<n;i++){
    acc+=a_arr[i]-x;
    if(i==0){
      ext1=acc-pre1;
      ext2=acc-pre2;
    }else{
      ext1=max(ext1,acc-pre1);
      ext2=min(ext2,acc-pre2);
    }
    pre1=min(pre1,acc);
    pre2=max(pre2,acc);
  }
  return{ext1,-ext2};
}
B chk(Lf x){
  auto[ext1,ext2]=dis(x);
  return ext1<=ext2;
}
Lf fnd(){
  Lf l=-A,r=A;
  for(I i=0;i<ITR;i++){
    Lf m=(l+r)/2;
    chk(m)?r=m:l=m;
  }
  return l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  auto[ext1,ext2]=dis(fnd());
  printf("%.15Lf\n",max(ext1,ext2));
}