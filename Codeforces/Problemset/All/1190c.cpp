#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
using B=bool;
const I N=1e5;
const I MIN=-1e9;
const I MAX=1e9;
C crds[N+1];
set<I>curs[2];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  cin>>crds;
  for(I i=k;i<n;i++)curs[crds[i]-'0'].insert(i);
  B qua=1;
  for(I i=0;i+k<=n;i++){
    if(curs[0].size()==0||curs[1].size()==0)printf("tokitsukaze"),exit(0);
    B drw=0;
    drw|=*curs[0].rbegin()-*curs[0].begin()>=k&&*curs[1].rbegin()-*curs[1].begin()>=k;
    drw|=max(*curs[0].rbegin(),i+k-1)-min(*curs[0].begin(),i)>=k&&*curs[1].rbegin()-*curs[1].begin()>=k;
    drw|=*curs[0].rbegin()-*curs[0].begin()>=k&&max(*curs[1].rbegin(),i+k-1)-min(*curs[1].begin(),i)>=k;
    qua&=!drw;
    if(i+k<n)curs[crds[i]-'0'].insert(i),curs[crds[i+k]-'0'].erase(i+k);
  }
  printf("%s",qua?"quailty":"once again");
}
/*
if one face contains at most one pair of cards with at least k - 1 cards
between them, the current player wins

if both faces contain pairs of cards with at least k - 1 cards between them
and all moves result in the first case, the opponent wins

if any move results in the second case, simply copying the previous move
ensures neither player wins
*/