#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=5000;
const I MAX=1e9;
I a_arr[N];
map<I,I>pres;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  pres[0]=0;
  for(I i=0;i<n;i++){
    I a=a_arr[i],tot=a;
    for(I j=1;j<=k;j++,tot+=a)pres[tot]=pres.find(tot)!=pres.end()?min(pres[tot],j):j;
  }
  I q;cin>>q;
  while(q--){
    I x;cin>>x;
    I res=x==0?0:MAX;
    for(I i=0;i<n;i++){
      I a=a_arr[i],tot=a;
      for(I j=1;j<=k;j++,tot+=a)if(pres.find(x-tot)!=pres.end())res=min(res,j+pres[x-tot]);
    }
    printf("%i\n",res>k?-1:res);
  }
}