#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=3e5;
const I A=1.5e7;
I eras[A+1];
I a_arr[N];
I cnts[A+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  iota(eras,eras+A+1,0);
  for(I i=2;i*i<=A;i++)if(eras[i]==i)for(I j=i*i;j<=A;j+=i)eras[j]=min(eras[j],i);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++){
    I a=a_arr[i],lst=-1,pow=1;
    while(a>1){
      I cur=eras[a];
      if(cur!=lst)pow=1;
      a/=cur,pow*=cur,lst=cur;
      cnts[pow]++;
    }
  }
  I res=n;
  for(I i=0;i<=A;i++){
    I dif=n-cnts[i];
    if(dif==0)continue;
    res=min(res,dif);
  }
  printf("%i\n",res==n?-1:res);
}