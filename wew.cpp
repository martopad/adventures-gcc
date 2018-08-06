#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <fstream>
#include <map>
#include <boost/algorithm/string/join.hpp>
#include <vector>
#include <sstream>
#include <functional>
#include <numeric>

std::mutex m;
std::condition_variable cv;
std::string data;
bool ready = false;
bool processed = false;
std::map<std::thread::id,int> threadmap;

void worker_thread()
{
    // Wait until main() sends data
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, []{return ready;});

    // after the wait, we own the lock.
    std::cout << "Worker thread is processing data\n";
    data += " after processing";

    // Send data back to main()
    processed = true;
    std::cout << "Worker thread signals data processing completed\n";

    // Manual unlocking is done before notifying, to avoid waking up
    // the waiting thread only to block again (see notify_one for details)
    lk.unlock();
    cv.notify_one();
}

void writetoafile()
{
    std::ofstream myfile;
    myfile.open ("example.txt", std::ios::out | std::ios::app);
    myfile << threadmap.find(std::this_thread::get_id())->second << ": Writing this to a file.\n";
    myfile.close();
}
    std::thread worker(worker_thread);
    std::thread worker2(worker_thread);
    std::thread writer(writetoafile);
    std::thread writer2(writetoafile);
    std::thread writer3(writetoafile);
    std::thread writer4(writetoafile);
    std::thread writer5(writetoafile);
    std::thread writer6(writetoafile);

int main()
{
    threadmap[writer.get_id()] = 0;
    threadmap[writer2.get_id()] = 1;
    threadmap[writer3.get_id()] = 2;
    threadmap[writer4.get_id()] = 3;
    threadmap[writer5.get_id()] = 4;
    threadmap[writer6.get_id()] = 5;

    data = "Example data";
    // send data to the worker thread
    {
        std::lock_guard<std::mutex> lk(m);
        ready = true;
        std::cout << "main() signals data ready for processing\n";
    }
    cv.notify_one();

    // wait for the worker
    {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, []{return processed;});
    }

    worker.join();
    worker2.join();
    writer.join();
    writer2.join();
    writer3.join();
    writer4.join();
    writer5.join();
    writer6.join();
    std::cout << "Back in main(), data = " << data << '\n';


    std::cout << "THIS IS THE END" << std::endl;
    return 0;

}

    //  static const int num_threads = 10;

    //  //This function will be called from a thread

    //  void call_from_thread(int tid) {
    //      std::cout << "Launched by thread " << tid << std::endl;
    //  }

    //  int main() {
    //      std::thread t[num_threads];

    //      //Launch a group of threads
    //      for (int i = 0; i < num_threads; ++i) {
    //          t[i] = std::thread(call_from_thread, i);
    //      }

    //      std::cout << "Launched from the main\n";

    //      //Join the threads with the main thread
    //      for (int i = 0; i < num_threads; ++i) {
    //          t[i].join();
    //      }

    //      return 0;
    //  }