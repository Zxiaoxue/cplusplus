#include<iostream>
using namespace std;

void inputNum(int number[],int temp_length)
{
    int length=0;
 
    length=temp_length;
     
    for(int i=0;i<length;i++)
    {
        cin>>number[i];
    }
     
}
void swap(int number[],int temp_length)
{
    int *max,*min,*pointer,temp,length;

    max=min=number;
 
    temp=0;
 
    length=temp_length;

    for(pointer=number+1;pointer<number+length;pointer++)
    {
        if(*pointer>*max)
        {
            max=pointer;    
        }
        else if(*pointer<*min)
        {
            min=pointer;
        }
    }

    temp=number[0];
         
    number[0]=*min;
 
    *min=temp;
    temp=number[9];
 
    number[9]=*max;
 
    *max=temp;
}

void outputNum(int number[],int temp_length)
{
    int length=0;
 
    length=temp_length;
 
    for(int i=0;i<length;i++)
    {
        cout<<number[i]<<" ";
    }
    cout<<" "; 
}


int main()
{
 
    int number[10];         

    inputNum(number,10);
 
    swap(number,10);
 
    outputNum(number,10);
    return 0;
}



