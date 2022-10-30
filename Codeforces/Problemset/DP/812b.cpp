#include<bits/stdc++.h>

using namespace std;

using I=int;
using C=char;
using B=bool;

const I N=15;
const I M=100;
const I MAX=1e9;

C cels[N][M+3];
I movs[N][2];
I dp[1<<N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>cels[i];
  I l=n;
  for(I i=n-1;i>=0;i--){
    I low=m+1,upp=0;
    B vis=0;
    for(I j=0;j<m+2;j++)if(cels[i][j]=='1'){
      low=min(low,j);
      upp=max(upp,j);
      vis=1;
    }
    movs[i][0]=low;
    movs[i][1]=upp;
    if(vis)l=min(l,i+1);
  }
  I res=MAX;
  for(I i=0;i<(1<<n);i++){
    I cur=n-l,pos=0;
    for(I j=n-1;j>=l-1;j--){
      I k=i>>j&1;
      I mov=movs[j][k];
      if(k){
        cur+=pos-0+mov-0;
        pos=mov;
      }else{
        cur+=m+1-pos+m+1-mov;
        pos=mov;
      }
    }
    res=min(res,cur);
  }
  printf("%i\n",res);
}