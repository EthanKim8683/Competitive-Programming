#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=17;
const I POWN=1<<N;
I a_arr[POWN];
I vals[N+1][POWN];
I n;
void bld(){
  for(I i=n-1;i>=0;i--){
    for(I j=0;j<1<<i;j++){
      I a=vals[i+1][j<<1],b=vals[i+1][j<<1|1];
      if((n+i)%2==1)vals[i][j]=a|b;
      if((n+i)%2==0)vals[i][j]=a^b;
    }
  }
}
void upd(I i,I val){
  vals[n][i]=val;
  for(I j=n-1;j>=0;j--){
    I a=vals[j+1][i],b=vals[j+1][i^1];
    i>>=1;
    if((n+j)%2==1)vals[j][i]=a|b;
    if((n+j)%2==0)vals[j][i]=a^b;
  }
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I m;cin>>n>>m;
  for(I i=0;i<(1<<n);i++)cin>>a_arr[i];
  copy_n(a_arr,1<<n,vals[n]);
  bld();
  while(m--){
    I p,b;cin>>p>>b,p--;
    upd(p,b);
    printf("%i\n",vals[0][0]);
  }
}