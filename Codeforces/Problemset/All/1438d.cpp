#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1e5;
I a_arr[N];
vector<tuple<I,I,I>>ress;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  I acc=0;
  for(I i=0;i<n;i++)acc^=a_arr[i];
  if(n%2==0&&acc!=0)printf("NO\n"),exit(0);
  for(I i=0;i+3<=n;i+=2)ress.push_back({i,i+1,i+2});
  for(I i=0;i+5<=n;i+=2)ress.push_back({i,i+1,n-2});
  printf("YES\n%i\n",ress.size());
  for(auto[i,j,k]:ress)printf("%i %i %i\n",i+1,j+1,k+1);
}