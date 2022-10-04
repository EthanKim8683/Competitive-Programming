#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using B=bool;

const I N=1e3;
const I M=1e3;

S pols[N];
S enes[M];
set<S>vals;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>pols[i];
  for(I i=0;i<m;i++)cin>>enes[i];
  for(I i=0;i<n;i++)vals.insert(pols[i]);
  for(I i=0;i<m;i++)vals.insert(enes[i]);
  sort(pols,pols+n);
  sort(enes,enes+m);
  I cnt1=0,cnt2=0,cnt3=0;
  for(auto i:vals){
    B vis1=binary_search(pols,pols+n,i);
    B vis2=binary_search(enes,enes+m,i);
    if(vis1&&vis2)cnt1++;
    else if(vis1)cnt2++;
    else if(vis2)cnt3++;
  }
  if(cnt2>cnt3)printf("YES\n"),exit(0);
  if(cnt3>cnt2)printf("NO\n"),exit(0);
  printf("%s\n",cnt1%2?"YES":"NO");
}