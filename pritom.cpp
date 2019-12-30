#include<cstdlib>
#include<iostream>
#include<stdio.h>
#include<cstring>
using namespace std;
int z=0;
void index_change_function(char b[],int i,int Size)
{
    int j=i+1;
    for(i=i;i<Size;i++){
        b[i]=b[j];
        j++;
    }
    b[j]=NULL;
}
void index1_change_function(char b[],int j)
{
    if(b[j]=='0'){
        index_change_function(b,j,strlen(b));
        index1_change_function(b,j);
    }
    else{
        return;
    }
}
void another_function(char b[],int Size,int Size1)
{
    int Count=0;
    for(int i=0;i<Size;i++){
        if(Count==Size1){
            break;
        }
        else if(b[i]=='0'){
            index_change_function(b,i,Size);
            Size=strlen(b);
            if(Size==Size1){
                break;
            }
            i=-1;
            Count++;
        }
        else{
            break;
        }
    }
}
void Function(char a[],char b[])
{
    int m=strlen(a);
    int n=strlen(b);
    if(m==n){
        int k=0;
        if(b[0]!='0'){
            for(int i=0;i<m;i++){
                if(a[i]=='1'&&b[i]=='1'){
                    b[i]='0';
                }
                else if(a[i]=='0'&&b[i]=='0'){
                    b[i]='0';
                }
                else if(a[i]=='1'&&b[i]=='0'){
                    b[i]='1';
                }
                else if(a[i]=='0'&&b[i]=='1'){
                    b[i]='1';
                }
            }
        }
        for(int i=0;i<m;i++){
            if(b[i]=='0'){}
            else{
                k=1; //local variable
                break;
            }

        }
        if(k==0){
            //cout<<"Error Problem!!! "<<endl;
            z=1; //global variable
        }
    }

    else{
        for(int i=0;i<m;i++){
            if(a[i]=='1'&&b[i]=='1'){
                b[i]='0';
            }
            else if(a[i]=='0'&&b[i]=='0'){
                b[i]='0';
            }
            else if(a[i]=='1'&&b[i]=='0'){
                b[i]='1';
            }
            else if(a[i]=='0'&&b[i]=='1'){
                b[i]='1';
            }
        }
        another_function(b,n,m);
        Function(a,b);
    }
}

int main(){
    cout<<"Selective reject sliding window CRC-16"<<endl;
    FILE *p=fopen("input.txt","r");
    char a[100],f[100];
    char b[100];
    char c[100];
    int v=-1,j=0,q,run=0;
    int random_error_frame,m ;
    fpos_t pos;
    random_error_frame = (rand()%10)+1;
    cout<<"window Size(Less than 11) :";
    aa:
    cin>>m;
    if(m<0||m>11){
        cout<<"invalid"<<endl;
        goto aa;
    }
    cout<<"Enter Polynomial : "<<endl;
    cout<< "Press 1 for input auometically"<<endl;
    cout<< "Press 2 for input manually"<<endl;
    bb:
    cin>>q;
    cout<<endl<<endl;
    if(q==2){
       cout<<"Pattern: ";
       cin>>a;
    }
      else if(q==1){
         fscanf(p,"%s",&a);//File variable name (p)
      }
      else{
        cout<<"invalid"<<endl;
        goto bb;
      }
    for(int i=1;i<=m;i++){
            fscanf(p,"%s",&b);
            fgetpos(p , &pos);
            if(v==i){//initial v=-1
                  cout<<"Frame Number :"<<j<<endl;//initial j=0
                  strcpy(c,f);
                  Function(a,f);//a array fixed,,,b array changeable
                  int Size=strlen(f);
                  index1_change_function(f,0);
                  if(z==0){
                     cout<<"FCS: "<<f<<endl;
                     strcat(c,f);
                     cout<<"DATA with FCS : "<<c<<endl<<endl<<endl;
                  }
              }

            else if(random_error_frame==i){
                v=i+3;
                j=i;
                strcpy(f,b);
            }

            cout<<"Frame Number :"<<i<<endl;
            strcpy(c,b);
            //cout<<"a: "<<a<<endl;
            Function(a,b);
            int Size=strlen(b);
            index1_change_function(b,0);

            if(z==0){
                cout<<"FCS: "<<b<<endl;
                strcat(c,b);
                cout<<"DATA with FCS : "<<c<<endl;
            }
            if(z==1){
                cout<<"No FCS"<<endl;
                cout<<"DATA without FCS : "<<b<<endl;
                z=0;
            }
            if(i%4==3){
               cout<<"ACK found succesfully for frame "<<i-2<<endl;
               }
            if(random_error_frame==i-2){
                i=i-3;
                random_error_frame=random_error_frame+2;
                pos=pos-(3*19);
                fsetpos(p, &pos);
                cout<<endl<<"NAK received for frame "<<j<<endl;
            }
            cout<<endl<<endl;
    }
}
