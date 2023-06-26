#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=1e5;
I a_arr[N];
B eras[N+2];
vector<I>prms;
vector<I>csts[N+1];
B slvs[N+1];
vector<pair<I,I>>ress;
I poss[N],lbls[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){I a;cin>>a,a_arr[i]=a-1;}
  for(I i=2;i*i<=n+1;i++)if(!eras[i])for(I j=i*i;j<=n+1;j+=i)eras[j]=1;
  for(I i=2;i<=n+1;i++)if(!eras[i])prms.push_back(i);
  for(auto i:prms){
    if(!slvs[i-1]){
      slvs[i-1]=1;
      csts[i-1].push_back(i-1);
    }
    if(!slvs[i]){
      slvs[i]=1;
      csts[i].push_back(1);
      csts[i].push_back(i-1);
    }
  }
  for(I i=0;i<prms.size();i++)for(I j=i;j<prms.size();j++){
    I a=prms[i],b=prms[j],c=a+b-2,d=a+b-1;
    if(c<=n&&!slvs[c]){
      slvs[c]=1;
      csts[c].push_back(a-1);
      csts[c].push_back(b-1);
    }
    if(d<=n&&!slvs[d]){
      slvs[d]=1;
      csts[d].push_back(1);
      csts[d].push_back(a-1);
      csts[d].push_back(b-1);
    }
  }
  for(I i=0;i<n;i++)poss[a_arr[i]]=i;
  copy_n(a_arr,n,lbls);
  for(I i=0;i<n;i++){
    I a=poss[i],b=i,dis=abs(a-b);
    if(a==b)continue;
    for(I j=0;j<csts[dis].size();j++){
      I c=a+csts[dis][j]*((b>a)-(b<a));
      ress.push_back({a,c}),a=c;
    }
    a=poss[i];
    b-=csts[dis].back()*((b>a)-(b<a));
    for(I j=csts[dis].size()-2;j>=0;j--){
      I c=b-csts[dis][j]*((b>a)-(b<a));
      ress.push_back({b,c}),b=c;
    }
    b=i;
    swap(lbls[a],lbls[b]);
    swap(poss[lbls[a]],poss[lbls[b]]);
  }
  printf("%i\n",ress.size());
  for(auto[a,b]:ress){
    if(a>b)swap(a,b);
    printf("%i %i\n",a+1,b+1);
  }
}