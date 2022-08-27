#include<iostream>
#include<cstdio>

using namespace std;

using I=int;
using Lli=long long int;

const I N=1e5;

I c_arr[N],a_arr[N],b_arr[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>c_arr[i];
    for(I i=0;i<n;i++){I a;cin>>a,a_arr[i]=a-1;}
    for(I i=0;i<n;i++){I b;cin>>b,b_arr[i]=b-1;}
    I d=-1,e=-1;
    Lli sum=0,res=0;
    for(I i=n-1;i>=1;i--){
      I a=a_arr[i],b=b_arr[i],c=c_arr[i];
      if(d==-1||e==-1)sum=c-1;
      else sum=max((Lli)c-1,sum+d+c-1-e);
      sum+=2;
      if(a==b){
        d=e=-1;
        res=max(res,sum);
      }else{
        d=min(a,b),e=max(a,b);
        res=max(res,sum+e-d);
      }
    }
    printf("%lli\n",res);
  }
  return 0;
}