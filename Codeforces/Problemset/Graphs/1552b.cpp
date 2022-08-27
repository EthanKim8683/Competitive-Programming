#include<iostream>
#include<cstdio>

using namespace std;

using I=int;
using B=bool;
struct Ath{I r1,r2,r3,r4,r5;};

const I N=50000;
const I MAX=1e9;

Ath aths[N];

B cmp(Ath a,Ath b){
  I c=0;
  c+=a.r1<b.r1;
  c+=a.r2<b.r2;
  c+=a.r3<b.r3;
  c+=a.r4<b.r4;
  c+=a.r5<b.r5;
  return c>=3;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)
      cin>>aths[i].r1>>aths[i].r2>>aths[i].r3>>aths[i].r4>>aths[i].r5;
    Ath cur=aths[0];
    I res=1;
    for(I i=1;i<n;i++){
      Ath ath=aths[i];
      if(cmp(ath,cur))cur=ath,res=i+1;
    }
    for(I i=0;i<n;i++)
      if(cmp(aths[i],cur)){res=-1;break;}
    printf("%i\n",res);
  }
  return 0;
}