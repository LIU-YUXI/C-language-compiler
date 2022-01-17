float sub( int a, float b){
     return a-b;
}
float sub( int a, float b){
     return a;
}
int main(){
      int a;
      float b;
      a=123456.7;
      if(a>0){
	b=(a-1)/2;
     }
      else{
	b=sub(a,b);
      }
      return 0;
}