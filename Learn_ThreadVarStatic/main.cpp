#include <iostream>
#include <string>
#include <pthread.h>
#include <unistd.h>
using namespace std;

int i = 0;
void hello() {
    static string long_ngu_vl = "Long ngu del chiu dc";
        while(1) {
        long_ngu_vl = long_ngu_vl + "ngu vkl";
        cout << long_ngu_vl << i++ << endl;
        sleep(2);
    }
}


void *threadHandle(void *) {
    hello();
}

int main()
{
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, threadHandle, NULL);
    pthread_create(&thread2, NULL, threadHandle, NULL);
    //string long_ngu_vl = "Long ngu del chiu dc";
    //long_ngu_vl.append("dcmm long dan\n");
    //long_ngu_vl.append("dcmm long dan\n");
    //cout << long_ngu_vl << i++ << endl;
    while(1);
}