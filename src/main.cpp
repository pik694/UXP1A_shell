#include <iostream>
#include <fstream>
#include <thread>

#include <unistd.h>
#include <signal.h>

//TODO: controller talks to command parser, parser parses the command then controller forwards the parsed command to TaskFacade which uses TaskFactory inside

std::mutex mutex;
std::condition_variable cv;


pid_t lastPid;

void handler (int n){
    int status;
    auto pid = waitpid(0, &status, WNOHANG);
    std::cerr << "Handler: " << n << " " << pid << std::endl;

    std::lock_guard guard(mutex);

    lastPid = pid;

    cv.notify_one();
}


int main(int argc, char **argv) {

    using namespace std::chrono_literals;

    struct sigaction sig;
    sigemptyset(&sig.sa_mask);
    sig.sa_handler = handler;
    sig.sa_flags = 0;
    struct sigaction sigold;
    sigaction(SIGCHLD, &sig, &sigold);


    pid_t child = fork();

    if(child == 0){

        std::cout << "Child 1 " << getpid() << std::endl;

        std::this_thread::sleep_for(1s);

        std::cout << "Child 1 exiting" << std::endl;
        exit(1);
    }
    else if (!(child = fork())){

        std::cout << "Child 2 " << getpid() << std::endl;

        int a;
        std::cin >> a;
        std::cout << a << std::endl;

        std::cout << "Child 2 exiting" << std::endl;
        exit(127);
    }

    else{

        std::cout << "Parent " << getpid() << " " << child << std::endl;

        std::unique_lock<std::mutex> lock (mutex);
        cv.wait(lock, [child](){return child == lastPid;});


        std::cout << "Parent exiting\n";
    }

}