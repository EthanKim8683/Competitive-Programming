#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=2e5;
const I M=1e5;
I cols[N];
I lsts[M+1];
queue<I>diss[M+1];
I sizs[M+1];
I k;
I res=1;
void add(I i,I v){
  diss[i].push(v);
  sizs[i]+=v;
  if(sizs[i]>k){
    sizs[i]-=diss[i].front();
    diss[i].pop();
  }
  res=max(res,(I)diss[i].size()+1);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m>>k;
  for(I i=0;i<n;i++)cin>>cols[i];
  fill_n(lsts,m+1,-1);
  for(I i=0;i<n;i++){
    I col=cols[i];
    I j=lsts[col];
    if(j!=-1)add(col,i-j-1);
    lsts[col]=i;
  }
  printf("%i\n",res);
}