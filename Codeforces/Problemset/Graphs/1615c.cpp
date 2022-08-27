#include<iostream>
#include<cstdio>

using namespace std;

using I=int;
using S=string;

const I MAX=1e9;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    S a;cin>>a;
    S b;cin>>b;
    I sam=0,dif=0;
    I o1=0,o2=0,z1=0,z2=0;
    for(I i=0;i<n;i++){
      if(a[i]==b[i]){
        o1+=a[i]=='1',z1+=a[i]=='0';
        sam++;
      }
      if(a[i]!=b[i]){
        o2+=a[i]=='1',z2+=a[i]=='0';
        dif++;
      }
    }
    I res=MAX;
    if(sam%2==1&&o1-z1==1)res=min(res,sam);
    if(dif%2==0&&o2-z2==0)res=min(res,dif);
    if(res==MAX)printf("-1\n");
    else printf("%i\n",res);
  }
  return 0;
}