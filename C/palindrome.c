#include<stdio.h>
int main()
{
    int rem,n,b,rev=0;
    
    printf("enter the number:");
    scanf("%d",&n);
    b=n;//copy the value of n before it gets changed
    while(n!=0)
    {
        rem=n%10;
        rev=rev*10+rem;
        n=n/10;
        
    }
    if(rev==b)
    {
        printf("%d is palindrome number ",b);
    }
    else
    printf("%d is not palindrome number.",b);
    
  
    

    return 0;
}