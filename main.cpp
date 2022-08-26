
#include "web_server.h"
#include <thread>

using namespace std;

struct Task{
    int val;
    Task():val(-1){};
    Task(int v):val(v){};
};


void server(){
    web_server webServer = web_server(8080,5,4096);
    webServer.start(true);
}



int main() {
//    threadpool<Task> *pool = new threadpool<Task>();
    // 开启一个服务 server
    std::thread t = thread(server);
//    cout << "start a server" << endl;
    // 开启一个 client
    sleep(1);
    web_server client =  web_server(8080,5,4096);
    client.start(false);
    sleep(10);

    t.join();

    return 0;
}
