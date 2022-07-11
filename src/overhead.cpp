#include <thread>
#include <vector>
#include <barrier>
#include <iostream>
#include <fstream>
#include "utimer.cpp"
using namespace std;

#define TRIALS 5

int main(){

    int a = 0;

    ofstream output_file;
    output_file.open("overhead.csv", std::ios::app);
    auto updating = [&](){
        a++;
    };

    long thr_time;

    for(int nw = 2; nw <= 32; nw +=2){
        long avg_time = 0;
        for(int trial = 0; trial < TRIALS; trial++) {
            vector<thread> threads(nw);
            barrier ba(nw, updating);

            auto body = [&](int tid) {
                tid++;
                ba.arrive_and_wait();
            };
            {

                utimer thr = utimer("OVERHEAD " + to_string(nw) + " threads", &thr_time);
                for (int i = 0; i < nw; i++) {
                    threads[i] = thread(body, i);
                }
                for (int i = 0; i < nw; i++) {
                    threads[i].join();
                }
            }
            avg_time += thr_time;
        }
        avg_time = avg_time / TRIALS;
        cout << "AVG_TIME " << avg_time << " with " << nw << " threads" << endl;
        output_file << nw << "\t" << avg_time << endl;
    }

    output_file.close();
    return 0;
}