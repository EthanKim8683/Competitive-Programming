#include<bits/stdc++.h>

using namespace std;

using I=int;
using C=char;

const I N=3e5;

C s[N+1];
I pars[2*(N+1)];
I sizs[2*(N+1)];

I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}

void uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    cin>>s;
    fill_n(pars,2*(n+1),-1);
    fill_n(sizs,2*(n+1),0);
    for(I i=0;i<n;i++){
      C c=s[i];
      if(c=='R')uni(i*2,(i+1)*2+1);
      if(c=='L')uni((i+1)*2,i*2+1);
    }
    for(I i=0;i<n+1;i++){
      I a=fnd(i*2),b=fnd(i*2+1);
      sizs[a]++,sizs[b]+=a!=b;
    }
    for(I i=0;i<n+1;i++)printf("%i ",sizs[fnd(2*i)]);
    printf("\n");
  }
}