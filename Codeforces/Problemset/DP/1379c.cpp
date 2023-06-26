#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I M=100000;
pair<I,I>flos[M];
I fsts[M];
Lli ps[M+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    for(I i=0;i<m;i++){
      I a,b;cin>>a>>b;
      flos[i]={a,b},fsts[i]=a;
    }
    sort(flos,flos+m);
    sort(fsts,fsts+m);
    for(I i=0;i<m;i++)ps[i+1]=ps[i]+fsts[i];
    Lli res=0;
    for(I i=0;i<m;i++){
      auto[a,b]=flos[i];
      I j=max((I)(upper_bound(fsts,fsts+m,b)-fsts),m-(n-1));
      Lli cur=ps[m]-ps[j]+a;
      if(i>=j)cur-=a,j++;
      cur+=(Lli)b*(n-1-(m-j));
      res=max(res,cur);
    }
    printf("%lli\n",res);
  }
}