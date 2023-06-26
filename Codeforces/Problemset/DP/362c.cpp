#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=5000;
I prms[N];
I fens[N+1];
I invs1[N+1][N],invs2[N+1][N];
map<I,I>ress;
I n;
void upd(I i,I val){
  for(;i<=n;i+=i&-i)fens[i]+=val;
}
I qry(I i){
  I res=0;
  for(;i>0;i-=i&-i)res+=fens[i];
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  for(I i=0;i<n;i++)cin>>prms[i];
  I tot=0;
  for(I i=0;i<n;i++){
    for(I j=0;j<n;j++)invs1[i][j]=qry(n)-qry(j+1);
    tot+=qry(n)-qry(prms[i]+1);
    upd(prms[i]+1,1);
  }
  for(I i=0;i<n;i++)invs1[n][i]=qry(n)-qry(i+1);
  fill_n(fens,n+1,0);
  for(I i=n;i>0;i--){
    for(I j=0;j<n;j++)invs2[i][j]=qry(j)-qry(0);
    upd(prms[i-1]+1,1);
  }
  for(I i=0;i<n;i++)invs2[0][i]=qry(i)-qry(0);
  for(I i=0;i<n;i++)for(I j=i+1;j<n;j++){
    I a=prms[i],b=prms[j];
    I cur=tot;
    cur-=invs1[i][a]+invs2[i][a];
    cur-=invs1[j][b]+invs2[j][b];
    cur+=invs1[j][a]+invs2[j][a];
    cur+=invs1[i][b]+invs2[i][b];
    ress[cur]++;
  }
  auto[swp,cnt]=*ress.begin();
  printf("%i %i\n",swp,cnt);
}