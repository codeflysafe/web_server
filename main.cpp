
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

    server();

    return 0;
}
