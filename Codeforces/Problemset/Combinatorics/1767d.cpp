#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  S s;cin>>s;
  I low=0,upp=0;
  for(I i=0;i<n;i++){
    if(s[i]=='0')upp=upp*2+1;
    if(s[i]=='1')low=low*2+1;
  }
  for(I i=low+1;i<=(1<<n)-upp;i++)printf("%i ",i);
}
/*
we can keep track of the minimum number of teams with lower skill or higher
skill that "super-lose" to a team

for a team a to "super-lose" to another team b, it a must lose to b, or lose
to a super-loser of b
*/