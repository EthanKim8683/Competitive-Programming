#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1e5;
const I MAX=1e9;
I a_arr[N];
I upps[N];
I segs1[2*N];
I segs2[2*(N+1)];
vector<I>cpss;
I n;
void upd1(I i,I val){
  i+=cpss.size();
  for(segs1[i]=min(segs1[i],val);i>>=1;)segs1[i]=min(segs1[i<<1],segs1[i<<1|1]);
}
I qry1(I l,I r){
  I res=n;
  for(l+=cpss.size(),r+=cpss.size();l<r;l>>=1,r>>=1){
    if(l&1)res=min(res,segs1[l++]);
    if(r&1)res=min(res,segs1[--r]);
  }
  return res;
}
void upd2(I l,I r,I val){
  for(l+=n+1,r+=n+1;l<r;l>>=1,r>>=1){
    if(l&1)segs2[l]=min(segs2[l],val),l++;
    if(r&1)r--,segs2[r]=min(segs2[r],val);
  }
}
I qry2(I i){
  I res=MAX;
  for(i+=n+1;i>0;i>>=1)res=min(res,segs2[i]);
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I s,l;cin>>n>>s>>l;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)cpss.push_back(a_arr[i]);
  sort(cpss.begin(),cpss.end());
  cpss.erase(unique(cpss.begin(),cpss.end()),cpss.end());
  fill_n(segs1,2*cpss.size(),n);
  fill_n(upps,n,n);
  for(I i=n-1;i>=0;i--){
    I a=a_arr[i];
    upd1(lower_bound(cpss.begin(),cpss.end(),a)-cpss.begin(),i);
    upps[i]=min(upps[i],qry1(upper_bound(cpss.begin(),cpss.end(),a+s)-cpss.begin(),cpss.size()));
    upps[i]=min(upps[i],qry1(0,lower_bound(cpss.begin(),cpss.end(),a-s)-cpss.begin()));
  }
  for(I i=n-1;i>0;i--)upps[i-1]=min(upps[i-1],upps[i]);
  fill_n(segs2,2*(n+1),MAX);
  upd2(0,1,0);
  for(I i=0;i<n;i++)upd2(i+l,upps[i]+1,qry2(i)+1);
  I res=qry2(n);
  printf("%i\n",res==MAX?-1:res);
}