#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=5e5;
const I A=1e7;
I eras[A+1];
I a_arr[N];
set<I>facs;
I ress1[N],ress2[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  iota(eras,eras+A+1,0);
  for(I i=2;i*i<=A;i++)if(eras[i]==i)for(I j=i*i;j<=A;j+=i)eras[j]=min(eras[j],i);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  fill_n(ress1,n,-1);
  fill_n(ress2,n,-1);
  for(I i=0;i<n;i++){
    I a=a_arr[i];
    facs.clear();
    I t=a;
    while(t!=1){
      I fac=eras[t];
      facs.insert(fac);
      t/=fac;
    }
    if(facs.size()<2)continue;
    auto it=facs.begin();
    ress1[i]=ress2[i]=1;
    for(I j=0;it!=facs.end();it++,j++){
      if(j%2==0)ress1[i]*=*it;
      if(j%2==1)ress2[i]*=*it;
    }
  }
  for(I i=0;i<n;i++)printf("%i ",ress1[i]);
  printf("\n");
  for(I i=0;i<n;i++)printf("%i ",ress2[i]);
  printf("\n");
}