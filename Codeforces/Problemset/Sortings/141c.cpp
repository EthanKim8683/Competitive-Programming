#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
const I N=3000;
pair<I,S>ppls[N];
vector<I>inds;
I ress[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    S nam;I a;cin>>nam>>a;
    ppls[i]={a,nam};
  }
  sort(ppls,ppls+n);
  for(I i=0;i<n;i++){
    auto[a,nam]=ppls[i];
    if(a>i)printf("-1"),exit(0);
    inds.insert(inds.begin()+a,i);
  }
  for(I i=n-1;i>=0;i--)ress[inds[i]]=n-i;
  for(I i=0;i<n;i++){
    auto[a,nam]=ppls[i];
    printf("%s %i\n",nam.c_str(),ress[i]);
  }
}