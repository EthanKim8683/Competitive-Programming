#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
I a_arr[N];
I b_arr[N];
Lli facs[2*N+1];
Lli cnts[2*N+1];
map<I,map<I,I>>vals;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)cin>>b_arr[i];
  Lli m;cin>>m;
  facs[0]=1;
  for(I i=1;i<=2*n;i++){
    I cnt=0,fac=i;
    while(fac%2==0)cnt++,fac/=2;
    facs[i]=facs[i-1]*fac%m;
    cnts[i]=cnts[i-1]+cnt;
  }
  for(I i=0;i<n;i++)vals[a_arr[i]][i]++;
  for(I i=0;i<n;i++)vals[b_arr[i]][i]++;
  Lli fac=1,cnt=0;
  for(auto[fst,secs]:vals){
    I tot=0,div=0;
    for(auto[sec,cnt]:secs){
      tot+=cnt;
      div+=cnt==2;
    }
    (fac*=facs[tot])%=m;
    cnt+=cnts[tot];
    cnt-=div;
  }
  for(I i=0;i<cnt;i++)(fac*=2)%=m;
  printf("%lli\n",fac);
}