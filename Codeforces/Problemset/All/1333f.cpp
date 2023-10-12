#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=5e5;
const I MAX=1e9;
I facs[N+1];
vector<I>cons[N+1];
vector<I>curs;
I ress[N+1];
B viss[N+1];
void con(I val,I i=0,I cur=1){
  if(i==curs.size()){
    if(val!=cur)cons[cur].push_back(val);
    return;
  }
  I j=i;
  for(;j<curs.size();j++)if(curs[j]!=curs[i])break;
  for(I k=0;k<=j-i;k++)con(val,j,cur),cur*=curs[i];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  iota(facs,facs+n+1,0);
  for(I i=2;i*i<=n;i++)for(I j=i*i;j<=n;j+=i)facs[j]=min(facs[j],i);
  for(I i=1;i<=n;i++){
    curs.clear();
    for(I j=i;j>1;j/=facs[j])curs.push_back(facs[j]);
    con(i);
  }
  fill_n(ress,n+1,MAX);
  I cnt=n;
  for(I i=n;i>1;i--){
    ress[cnt]=min(ress[cnt],i);
    for(auto j:cons[i])if(!viss[j])viss[j]=1,cnt--;
    ress[cnt]=min(ress[cnt],i-1);
  }
  for(I i=n;i>1;i--)ress[i-1]=min(ress[i-1],ress[i]);
  for(I i=2;i<=n;i++)printf("%i ",ress[i]);
}