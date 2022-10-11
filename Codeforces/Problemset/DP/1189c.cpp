#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=1e5;
const I LOGN=17;

I sums[N][LOGN];
I cans[N][LOGN];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>sums[i][0];
  for(I i=1;i<LOGN;i++)for(I j=0;j+(1<<(i-1))<n;j++){
    I k=j+(1<<(i-1)),sum=sums[j][i-1]+sums[k][i-1];
    cans[j][i]=sum/10+cans[j][i-1]+cans[k][i-1];
    sums[j][i]=sum%10;
  }
  I q;cin>>q;
  while(q--){
    I l,r;cin>>l>>r;
    printf("%i\n",cans[l-1][31-__builtin_clz(r-l+1)]);
  }
}