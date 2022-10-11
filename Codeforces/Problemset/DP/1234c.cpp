#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;

const I N=2e5;

I dp[N+1][1<<2];
I cels[N];
I trns[1<<2][1<<2]{
  {0b00,0b00,0b00,0b00},
  {0b01,0b00,0b01,0b10},
  {0b10,0b10,0b00,0b01},
  {0b11,0b10,0b01,0b11}
};

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I q;cin>>q;
  while(q--){
    I n;cin>>n;
    S a;cin>>a;
    S b;cin>>b;
    for(I i=0;i<n;i++){
      I x=a[i]>'2',y=b[i]>'2';
      cels[i]=x<<1|y<<0;
    }
    for(I i=0;i<=n;i++)for(I j=0;j<(1<<2);j++)dp[i][j]=0;
    dp[0][1<<1|0<<0]=1;
    for(I i=0;i<n;i++)for(I j=0;j<(1<<2);j++)
      dp[i+1][trns[j][cels[i]]]|=dp[i][j];
    printf("%s\n",dp[n][0b01]||dp[n][0b11]?"YES":"NO");
  }
}