#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lf=long double;

const I N=1e5;

I a_arr[N];
Lf poss1[N+1],poss2[N+1];
Lf tims1[N+1],tims2[N+1];
I n,l;

Lf pos1(Lf tim){
  I i=upper_bound(tims1,tims1+n+1,tim)-tims1-1;
  return poss1[i]+(tim-tims1[i])*(i+1);
}

Lf pos2(Lf tim){
  I i=upper_bound(tims2,tims2+n+1,tim)-tims2-1;
  return poss2[i]+(tim-tims2[i])*(i+1);
}

Lf fnd(){
  Lf a=0,b=max(tims1[n],tims2[n]);
  for(I i=0;i<60;i++){
    Lf m=(a+b)/2;
    if(pos1(m)+pos2(m)<l)a=m;
    else b=m;
  }
  return a;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    cin>>n>>l;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    poss1[0]=0,poss2[0]=0;
    tims1[0]=0,tims2[0]=0;
    for(I i=0;i<n;i++)poss1[i+1]=a_arr[i];
    for(I i=0;i<n;i++)poss2[i+1]=l-a_arr[n-i-1];
    for(I i=0;i<n;i++)tims1[i+1]=tims1[i]+(poss1[i+1]-poss1[i])/(i+1);
    for(I i=0;i<n;i++)tims2[i+1]=tims2[i]+(poss2[i+1]-poss2[i])/(i+1);
    printf("%.7Lf\n",fnd());
  }
}