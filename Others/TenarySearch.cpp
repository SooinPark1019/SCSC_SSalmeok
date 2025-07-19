while(hi-lo>3){
      ll q=(lo*2+hi)/3;
      ll p=(lo+hi*2)/3;
      if(sum(q)>sum(p)) lo=q;
      else hi=p;
  }
  for(int j=lo; j<=hi; j++){
      ans=min(ans, sum(j));
  }