#include<iostream>
#include<cstring>
#include<cmath>
#include<unordered_map>
#include<algorithm>
#include<vector>
using namespace std ;
vector<string> reqAllSubstring ;
unordered_map<int,vector<int> >bitsMAP ;// which number has 1 at posotion (first parameter)

void generateAllBinaryStrings(int n, string arr, int i,int tot_cnt,int &cnt)
{
    if (i == n) {
        if(cnt<=tot_cnt)
        {
            cnt++ ;
            reqAllSubstring.push_back(arr) ;
        }
        return;
    }

    arr[i] = '0';
    generateAllBinaryStrings(n, arr, i + 1,tot_cnt,cnt);
    arr[i] = '1';
    generateAllBinaryStrings(n, arr, i + 1,tot_cnt,cnt);
}

string modifiedSenderString(string str)
{
    string modified_sender_str="" ;

    int m = str.length() ;
    int r = 1 ;
    int tot_req_bits = 0;
    int tot_length=0;
    while(1)
    {
        int tot = m+r ;
        if((pow(2,r)) >(m+r))
        {
            tot_req_bits = r ;
            tot_length = m+r ;
            break ;
        }
        r++ ;
    }

    //cout<<tot_req_bits<<" "<<r<<endl;

    unordered_map<int,bool> redBitIndex ;
    for(int i=0;i<tot_req_bits;i++)
    {
        int x = pow(2,r) ;
        redBitIndex[x] = true ;
    }

    string arr="" ;
    for(int i=0;i<tot_length;i++)
    {
        modified_sender_str +='@' ;
    }
    for(int i=0;i<tot_req_bits;i++)
    {
        arr +='@' ;
    }
    int cnt=0 ;
    generateAllBinaryStrings(tot_req_bits,arr,0,tot_length,cnt) ;


    // for(int i=0;i<reqAllSubstring.size();i++)
    // {
    //     cout<<reqAllSubstring[i]<<endl;
    // }

    for(int i=1;i<reqAllSubstring.size() ;i++)
    {
        string st = reqAllSubstring[i] ;    // r==st.length()
        for(int j=r-1; j>=0;j--)
        {
            if(st[j]=='1')
            {
                bitsMAP[r-j-1].push_back(i) ;
            }
        }
    }

    // for(int i=0;i<r;i++)
    // {
    //     for(int j=0;j<bitsMAP[i].size();j++)
    //     {
    //         cout<<bitsMAP[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }

    unordered_map<int,int> temp ;

    for(int i=0;i<r;i++)
    {
        int x = pow(2,i) ;
        temp[x] = 1 ;
    }
    
    int i=0,j=0 ;
    while(i<str.length())
    {
        if(temp[j+1] ==1)
        {
            j++ ;
        }
        else{
            modified_sender_str[j] = str[i] ;
            i++ ;
            j++ ;
        }
    }


    for(int i=0;i<r;i++)
    {
        int count=0 ;
        for(int j=0;j<bitsMAP[i].size();j++)
        {
            int x = bitsMAP[i][j] ;
            if(modified_sender_str[x-1] !='2' && modified_sender_str[x-1]=='1')
            {
                count++ ;
            }
        }
        if(count%2 ==0)
        {
            int x = pow(2,i) ;
            modified_sender_str[x-1] = '0' ;
        }
        else{
            int x = pow(2,i) ;
            modified_sender_str[x-1] = '1' ;
        }
    }


    return modified_sender_str ;
}

void receiverChecking(string recvStr)
{
    bool flag = false ;

    int r = int(log2(recvStr.length())) ;
    float r1 = log2(recvStr.length()) ;
    if(r!=r1) r++ ;

    int pos=0 ;
    for(int i=0;i<r;i++)
    {
        int count=0 ;
        for(int j=0;j<bitsMAP[i].size();j++)
        {
            int x = bitsMAP[i][j] ;
            if(recvStr[x-1]=='1') count++ ;
        }
        if(count%2 ==1)
        {
            flag = true ;
            pos = pos+ pow(2,i) ;
        }
    
    }


    if(flag==false)
    {
        cout<<"************* No error ****************" <<endl;
    }
    else{
        cout<<"error is there at position : "<<pos<<endl;
    }

    
}

int main()
{
    string senStr, recvStr ;
    cout<<"Enter Sender's string : "<<endl;
    cin>>senStr ;
    cout<<"Enter Receiver's string : "<<endl; 
    cin>>recvStr;

    string newSenStr = modifiedSenderString(senStr) ;
    cout<<"Sender will send this string to receiver : " <<newSenStr<<endl;

    receiverChecking(recvStr) ;
    return 0;
}