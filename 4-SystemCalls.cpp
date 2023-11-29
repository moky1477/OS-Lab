#include<bits/stdc++.h>
#include<sys/types.h>
#include<unistd.h>

using namespace std;

int main(){
    int n;
    cout<<"Write System Call:"<<endl;
    n = write(1, "Hello", 5);
    cout<<endl;
    write(1, "Hello", 3);
    cout<<endl;

    cout<<"Read System call"<<endl;
    int m;
    char b[30];
    m = read(0, b, 30);
    write(1, b, m);

    return 0;
}
