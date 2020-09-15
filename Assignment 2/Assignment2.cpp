using namespace std;
#include<iostream> 

void division(int temp[],int gen[],int n,int m)
{
    for(int i=0;i<n;i++)
    {
        int j=0;
        int k=i;
        if(gen[0] == temp[k])
        { 
            for(int j=0,k=i;j<m;k++,j++)
            {
                if(temp[k]==gen[j])
                {
                    temp[k] = 0;
                }
                else{
                    temp[k] = 1;
                }
            }
        }
    }
}

int main(){
    int dw[20],gen[20],n,m;
    int zerobits,zb[10];
    cout<<"---------------"<<endl;
    cout<<"Sender's Side"<<endl;
    cout<<"---------------"<<endl;
    cout<<"Enter length of dataword"<<endl;
    cin>>n;
    cout<<"Enter Dataword";
    for(int i=0;i<n;i++){
        cin>>dw[i];
    }
    cout<<"Enter length of generator"<<endl;
    cin>>m;
    cout<<"Enter generator: ";
    for(int i=0;i<m;i++)
    {
        cin>>gen[i];
    }
    cout<<endl;
    zerobits = m-1;
    for(int i=0;i<zerobits;i++)
    {
        dw[n+i] = 0;
    }
    int temp[20],total_length = 0;
    total_length = n+zerobits;
    for(int i=0;i<total_length;i++)
    {
        temp[i] = dw[i];
    }
    
    division(temp,gen,n,m);
    cout<<endl;
    
    int rem[4];
    cout<<"Remainder: "<<endl;
    for(int i=0,j=n;i<zerobits;i++,j++)
    {
        rem[i] = temp[j];
        cout<<rem[i];
    }
    cout<<endl;
    int tf[10];
    for(int i=0;i<n;i++)
    {
        tf[i] = dw[i];
    }
    for(int i=0,j=n;i<zerobits;i++,j++)
    {
        tf[j] = rem[i];
    }
    cout<<"Transmitted Code word: ";
    for(int i=0;i<total_length;i++)
    {
        cout<<tf[i];
    }
    cout<<endl;
    cout<<endl;
    cout<<"---------------"<<endl;
    cout<<"Receiver's Side"<<endl;
    cout<<"---------------"<<endl;
    cout<<"Enter received Codeword";
    int rc[20];
    for(int i=0;i<total_length;i++)
    {
        cin>>rc[i];
        
    }
    cout<<endl;
    cout<<"Received Codeword: ";
    for(int i=0;i<total_length;i++)
    {
        cout<<rc[i];
    }
    division(rc,gen,n,m);
    cout<<endl;
    int sy[15];
    cout<<"Remainder: ";
    for(int i=0,j=n;i<zerobits;i++,j++)
    {
        sy[i] = rc[j];
        cout<<sy[i];
    }
    cout<<endl;
    int flag = 0;
    for(int i=0;i<zerobits;i++)
    {
        if(sy[i]!=0)
        {
            flag = 1;
            break;
        }
    }
    if(flag == 0)
    {
        cout<<"Since remainder is 0,message is transmitted successfully"<<endl;
    }
    else{
        cout<<"Since remainder is not 0,message is not transmitted"<<endl;
    }
    return 0;

}
