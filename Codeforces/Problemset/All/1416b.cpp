#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1e4;
I a_arr[N];
vector<tuple<I,I,I>>ress;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    I tot=0;
    for(I i=0;i<n;i++)tot+=a_arr[i];
    if(tot%n){printf("-1\n");continue;}
    I equ=tot/n;
    ress.clear();
    for(I i=1;i<n;i++){
      I j=i+1,a=a_arr[i],dif=(-a%j+j)%j;
      a_arr[0]-=1*dif,a_arr[i]+=1*dif,ress.push_back({0,i,dif});
      dif=a_arr[i]/j;
      a_arr[i]-=j*dif,a_arr[0]+=j*dif,ress.push_back({i,0,dif});
    }
    for(I i=1;i<n;i++){
      I j=i+1,a=a_arr[i],dif=equ;
      a_arr[0]-=1*dif,a_arr[i]+=1*dif,ress.push_back({0,i,dif});
    }
    printf("%i\n",ress.size());
    for(auto[i,j,x]:ress)printf("%i %i %i\n",i+1,j+1,x);
  }
}