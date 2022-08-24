
#include "web_server.h"
#include <thread>
struct Task{
    int val;
    Task():val(-1){};
    Task(int v):val(v){};
};
int main() {
//    threadpool<Task> *pool = new threadpool<Task>();
    web_server webServer = web_server(8080,5,1024);
    webServer.start(true);

    return 0;
}
