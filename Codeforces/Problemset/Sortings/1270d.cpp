#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=500;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  printf("?");
  for(I i=0;i<k;i++)printf(" %i",i+1);
  printf("\n"),fflush(stdout);
  I cni,cna;cin>>cni>>cna,cni--;
  printf("?");
  for(I i=0;i<k+1;i++)if(i!=cni)printf(" %i",i+1);
  printf("\n"),fflush(stdout);
  I rfi,rfa;cin>>rfi>>rfa,rfi--;
  I low=0,upp=0;
  for(I i=0;i<k;i++)if(i!=cni){
    printf("?");
    for(I j=0;j<k+1;j++)if(j!=i)printf(" %i",j+1);
    printf("\n"),fflush(stdout);
    I cpi,cpa;cin>>cpi>>cpa,cpi--;
    if(cpa==cna){
      if(rfa>cna)upp++;
      if(rfa<cna)low++;
    }
    if(cpa<cna)upp++;
    if(cpa>cna)low++;
  }
  printf("! %i\n",low+1),fflush(stdout);
}