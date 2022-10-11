#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=100000;

I a_arr[N];
multiset<I>wins;

I dif(){
  return *wins.rbegin()-*wins.begin();
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  I l=0,r=0,res=1;
  wins.insert(a_arr[0]);
  while(l<r||r<n-1){
    I cur=dif();
    if(r==n-1)wins.erase(wins.find(a_arr[l++]));
    else if(l==r)wins.insert(a_arr[++r]);
    else if(cur>1)wins.erase(wins.find(a_arr[l++]));
    else if(cur<=1)wins.insert(a_arr[++r]);
    if(l<r&&dif()<=1)res=max(res,r-l+1);
  }
  printf("%i\n",res);
}