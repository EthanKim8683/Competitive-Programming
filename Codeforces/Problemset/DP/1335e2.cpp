#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=2e5;
const I A=200;

I a_arr[N];
vector<I>inds[A];
I cnts[A];
I cur=0;

I upd(I i){
  if(++cnts[i]>cnts[cur])cur=i;
  return cur;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++){I a;cin>>a,a_arr[i]=a-1;}
    for(I i=0;i<A;i++)inds[i].clear();
    for(I i=0;i<n;i++)inds[a_arr[i]].push_back(i);
    I res=0;
    for(I i=0;i<A;i++){
      fill_n(cnts,A,0);
      I m=inds[i].size();
      res=max(res,m);
      if(m<2)continue;
      I l=m/2-1,r=m-1-l;
      for(I j=inds[i][l]+1;j<=inds[i][r]-1;j++)upd(a_arr[j]);
      res=max(res,2*(l+1)+cnts[cur]);
      while(l-1>=0&&r+1<=m-1){
        I la=inds[i][l],ra=inds[i][r];
        l--,r++;
        I lb=inds[i][l],rb=inds[i][r];
        for(I j=lb+1;j<=la;j++)upd(a_arr[j]);
        for(I j=ra;j<=rb-1;j++)upd(a_arr[j]);
        res=max(res,2*(l+1)+cnts[cur]);
      }
    }
    printf("%i\n",res);
  }
}