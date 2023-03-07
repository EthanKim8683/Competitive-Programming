#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=300000;
const I LOGN=19;
I a_arr[N];
I ancs[N][LOGN];
void bld(I i){
  for(I j=1;j<LOGN;j++)ancs[i][j]=ancs[ancs[i][j-1]][j-1];
}
I fnd(I i,I a){
  if(max(-a_arr[i],0)<a)return i;
  for(I j=LOGN-1;j>=0;j--){
    I k=ancs[i][j];
    if(max(-a_arr[k],0)>=a)i=k;
  }
  return ancs[i][0];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i+1];
  for(I i=1;i<n+1;i++){
    I a=a_arr[i];
    if(a>0)ancs[i][0]=fnd(i-1,1),bld(i);
    if(a<0)ancs[i][0]=fnd(max(fnd(i-1,-a)-1,0),-a),bld(i);
    printf("%i\n",a_arr[fnd(i,1)]);
  }
}