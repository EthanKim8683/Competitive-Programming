#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=2000;
const I MAX=1e9;

I a_arr[N];

I gcd(I a,I b){
  return b?gcd(b,a%b):a;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  I x=-1,y=MAX;
  for(I i=0;i<n;i++){
    I val=a_arr[i];
    if(val==1&&0<y)x=i+0,y=0;
    for(I j=1;i+j<n;j++){
      val=gcd(val,a_arr[i+j]);
      if(val==1&&j<y)x=i+j,y=j;
    }
  }
  if(y==MAX)printf("-1\n"),exit(0);
  I cnt=0;
  for(I i=0;i<n;i++)if(i!=x)cnt+=a_arr[i]!=1;
  printf("%i\n",y+cnt);
}