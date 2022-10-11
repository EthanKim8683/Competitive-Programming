#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=500;
const I M=500;

I grds[N][M];
multiset<I>vals;
I scrs[N];
I m;

I scr(I i){
  I res=0;
  for(I j=0;j<m;j++)if(grds[i][j]){
    I k=j;
    while(j<m&&grds[i][j])j++;
    res=max(res,j-k);
  }
  return res;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,q;cin>>n>>m>>q;
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)cin>>grds[i][j];
  for(I i=0;i<n;i++)vals.insert(scrs[i]=scr(i));
  while(q--){
    I i,j;cin>>i>>j,i--,j--;
    vals.erase(vals.find(scrs[i]));
    grds[i][j]^=1;
    vals.insert(scrs[i]=scr(i));
    printf("%i\n",*vals.rbegin());
  }
}