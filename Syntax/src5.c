float  program(int a,float b,int c)
{
	float i;
	int j;
	i=0; 	
	if(a>b+c){
		j=a+b*(c+1);
	}
	else
	{
		j=a;
	}
	while(i<=100)
	{
		i=2.5*j;
	}
    switch(j){
        case 1:
            i=5;
        default:
            i=9;
    }
	for(;i<5;){
		n=n+i;
	}
	return i;
}

int main(){
      int a;
      int c;
      float b;
      float d;
      c=22;
      b=33.33;
      d=program(a,b,c);
}