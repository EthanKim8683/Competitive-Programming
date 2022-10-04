#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;

const I MAX=1e9;
const I MIN=-1e9;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  S a;cin>>a;
  S b;cin>>b;
  sort(a.begin(),a.end());
  sort(b.begin(),b.end());
  I res1=MAX,res2=MIN;
  for(I i=0;i<n;i++){
    I cur1=0,cur2=0;
    for(I j=0;j<n;j++){
      cur1+=b[(j+i)%n]<a[j];
      cur2+=b[(j+i)%n]>a[j];
    }
    res1=min(res1,cur1);
    res2=max(res2,cur2);
  }
  printf("%i\n",res1);
  printf("%i\n",res2);
}