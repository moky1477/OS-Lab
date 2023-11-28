#include <iostream>
#include <unistd.h>
#include <sys/types.h>

using namespace std;

int main() {
    // Write
    int n;
    cout << "Write System Call:"<<endl;
    n = write(1, "Hello", 5);
    cout << "\n";
    write(1, "Hello", 2); // prints only 2 characters
    cout << "\n";

    // write(1, "Hello", 20); // Causes buffer overflow, commented out
    cout << "\n";
    cout << "Value of n is " << n << endl;

    cout << "\n";
    cout << "Read System Call:"<<endl;
    // Read
    // We cannot read directly; first, we have to store it in some memory (buffer)
    int m;
    char b[30]; // memory (buffer) max storage: 30
    m = read(0, b, 30);
    write(1, b, m);

    return 0;
}
