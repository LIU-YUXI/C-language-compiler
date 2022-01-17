float  program(int a,float b,int c)
{
	float i;
	int j;
	i=0; 	
	if(a>b+k)
	{
		j=a+b*(c+1);
	}
	else
	{
		j=a;
	}
	while(i<=100)
	{
		i=j*2.5;
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
      return 0;
}