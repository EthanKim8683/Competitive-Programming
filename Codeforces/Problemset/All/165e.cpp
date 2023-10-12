#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1e6;
I a_arr[N];
I upps[1<<22];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&upps[0],&upps[0]+(1<<22),-1);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)upps[a_arr[i]]=a_arr[i];
  for(I i=0;i<(1<<22);i++)for(I j=0;j<22;j++)if(~i>>j&1)upps[i|1<<j]=max(upps[i|1<<j],upps[i]);
  for(I i=0;i<n;i++)printf("%i ",upps[a_arr[i]^((1<<22)-1)]);
}