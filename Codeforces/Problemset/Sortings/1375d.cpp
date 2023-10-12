#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=1000;
I a_arr[N];
I tmps[N];
vector<I>ress;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    ress.clear();
    while(1){
      copy_n(a_arr,n,tmps);
      sort(tmps,tmps+n);
      I x=0;
      for(I j=0;j<n;j++){
        if(tmps[j]>x)break;
        if(tmps[j]==x)x++;
      }
      if(x==n){
        B fnd=0;
        for(I j=0;j<n;j++){
          if(a_arr[j]==j)continue;
          a_arr[j]=x;
          ress.push_back(j);
          fnd=1;
          break;
        }
        if(!fnd)break;
      }else{
        a_arr[x]=x;
        ress.push_back(x);
      }
    }
    printf("%i\n",ress.size());
    for(auto i:ress)printf("%i ",i+1);
    printf("\n");
  }
}