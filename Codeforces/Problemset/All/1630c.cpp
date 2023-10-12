#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=2e5;
const I MAX=1e9;
const I MIN=-MAX;
I a_arr[N];
I lows[N],upps[N];
vector<pair<I,I>>rngs;
I segs1[2*N],segs2[2][2*N];
I ps[N+1];
I n;
void upd1(I l,I r,I val){
  for(l+=n,r+=n;l<r;l>>=1,r>>=1){
    if(l&1)segs1[l++]+=val;
    if(r&1)segs1[--r]+=val;
  }
}
I qry1(I i){
  I res=0;
  for(i+=n;i>0;i>>=1)res+=segs1[i];
  return res;
}
void upd2(I t,I i,I val){
  for(segs2[t][i+=n]=val;i>>=1;)segs2[t][i]=max(segs2[t][i<<1],segs2[t][i<<1|1]);
}
I qry2(I t,I l,I r){
  I res=MIN;
  for(l+=n,r+=n;l<r;l>>=1,r>>=1){
    if(l&1)res=max(res,segs2[t][l++]);
    if(r&1)res=max(res,segs2[t][--r]);
  }
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&segs2[0][0],&segs2[0][0]+2*2*N,MIN);
  cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  fill_n(lows,n,MAX),fill_n(upps,n,MIN);
  for(I i=0;i<n;i++){
    I a=a_arr[i]-1;
    lows[a]=min(lows[a],i);
    upps[a]=max(upps[a],i);
  }
  for(I i=0;i<n;i++){
    I low=lows[i],upp=upps[i];
    if(low<=upp)rngs.push_back({low,upp});
  }
  sort(rngs.begin(),rngs.end());
  for(auto[l,r]:rngs)upd1(l+1,r,1);
  for(auto[l,r]:rngs)upd1(l,l+1,-qry1(l)),upd1(r,r+1,-qry1(r));
  for(I i=0;i<n;i++)ps[i+1]=ps[i]+!!qry1(i);
  I res=0;
  for(auto[l,r]:rngs){
    I cur=max(max(qry2(0,0,l),0)+ps[l],qry2(1,l,r)+l-1);
    upd2(0,r,cur-ps[r]+r-l-1),upd2(1,r,cur-l);
    res=max(res,cur+r-l-1);
  }
  printf("%i\n",res);
}