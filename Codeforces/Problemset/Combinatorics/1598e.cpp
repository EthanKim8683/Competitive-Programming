#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=1000;
const I M=1000;
B locs[N][M];
Lli cons[M+N+1];
Lli res=0;
I n,m;
void upd(I t){
  res-=cons[t+M],cons[t+M]=0;
  I pre=0;
  for(I x=0;x<n;x++){
    I y=x-t;
    if(y>=0&&y<m){
      locs[x][y]?pre=0:pre++;
      cons[t+M]+=pre;
    }
    y++;
    if(y>=0&&y<m){
      locs[x][y]?pre=0:pre++;
      cons[t+M]+=max(pre-1,0);
    }
  }
  res+=cons[t+M];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I q;cin>>n>>m>>q;
  for(I i=1-m;i<=n;i++)upd(i);
  while(q--){
    I x,y;cin>>x>>y,x--,y--;
    locs[x][y]^=1;
    upd(x-y),upd(x+1-y);
    printf("%lli\n",res);
  }
}
/*
for any (x, y),
- the number of staircases ending at (x, y) from the left is equal to the
  number of staircases ending at (x, y - 1) from the top
- the number of staircases ending at (x, y) from the top is equal to the
  number of staircases ending at (x - 1, y) from the left

we can update relevant diagonals on each update
*/