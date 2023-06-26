#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=2000;
const I M=2000;
const I A=1e6;
const I MAX=1e9;
pair<I,I>robs[N];
pair<I,I>lgts[M];
I upps[A+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++){
    I a,b;cin>>a>>b;
    robs[i]={a,b};
  }
  for(I i=0;i<m;i++){
    I c,d;cin>>c>>d;
    lgts[i]={c,d};
  }
  sort(lgts,lgts+m);
  for(I i=0;i<n;i++){
    auto[a,b]=robs[i];
    I upp=0;
    for(I j=m-1;j>=0;j--){
      auto[c,d]=lgts[j];
      c-=a,d+=1-b;
      if(c>=0&&d>upp)upps[c]=max(upps[c],d),upp=d;
    }
  }
  for(I i=A;i>0;i--)upps[i-1]=max(upps[i-1],upps[i]);
  I res=MAX;
  for(I i=0;i<=A;i++)res=min(res,i+upps[i]);
  printf("%i\n",res);
}