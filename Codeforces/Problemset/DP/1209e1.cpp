#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=4;
const I M=100;
I a_arr[N][M];
I upps[M];
I inds[M];
B cmp(I a,I b){
  return upps[a]>upps[b];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    for(I i=0;i<n;i++)for(I j=0;j<m;j++)cin>>a_arr[i][j];
    fill_n(upps,m,0);
    for(I i=0;i<m;i++)for(I j=0;j<n;j++)upps[i]=max(upps[i],a_arr[j][i]);
    iota(inds,inds+m,0);
    sort(inds,inds+m,cmp);
    I upp=1;
    for(I i=0;i<min(n,m);i++)upp*=n;
    I res=0;
    for(I i=0;i<upp;i++){
      I cur=0;
      for(I j=0;j<n;j++){
        I val=0;
        for(I k=0,fac=1;k<min(n,m);k++,fac*=n)val=max(val,a_arr[(j+i/fac%n)%n][inds[k]]);
        cur+=val;
      }
      res=max(res,cur);
    }
    printf("%i\n",res);
  }
}