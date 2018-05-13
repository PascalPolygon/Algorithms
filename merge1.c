
#include<stdio.h>
 
void mergesort(int a[],int i,int j);
void merge(int a[],int i1,int j1,int j2);
 
int main()
{
    int a[10],n=10,i;
    printf("Enter array elements:");
    
    for(i=0;i<n;i++)
        scanf("%d",&a[i]);
        
    mergesort(a,0,n-1);
    
    printf("Sorted array is :");
    for(i=0;i<n;i++)
        printf("%d ",a[i]);
        
	printf("\n");
    return 0;
}
 
void mergesort(int a[],int i,int j)
{
    int mid;
        
    if(i<j)
    {
        mid=(i+j)/2;
        mergesort(a,i,mid);        
        mergesort(a,mid+1,j);  
        merge(a,i,mid,j);    
    }
}
 
void merge(int a[],int i1,int j1,int j2)
{
    int b[50];    
    int i,j,k;
    i=i1;   
    j=j1+1;   
    k=0;
    
    while(i<=j1 && j<=j2)   
    {
        if(a[i]<a[j])
            b[k++]=a[i++];
        else
            b[k++]=a[j++];
    }
    
    while(i<=j1)    
        b[k++]=a[i++];
        
    while(j<=j2)    
        b[k++]=a[j++];
        
   
    for(i=i1,j=0;i<=j2;i++,j++)
        a[i]=b[j];
}