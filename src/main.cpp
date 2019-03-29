#include <iostream>
#include <thread>
#include <cstdlib>
#include <unistd.h>
#include <chrono>

using namespace std;

int PROCESS_DELAY = 1; // seconds
int MAX_PROCESSING_TIME = 10; // seconds
int MIN_PROCESSING_TIME = 2; // seconds

string TypeMap[] = { "Writer", "Reader" };

enum TYPE {
    WRITER,
    READER,
};

class File {
private:
    string data;
    int activeReaders;
    int activeWriters;
    bool semaphore;
public:
    File(string data) {
        this->data = data;
        this->activeReaders = 0;
        this->activeWriters = 0;
        this->semaphore = false;
    }

    string getData() {
        return this->data;
    }

    void setData(string data) {
        this->data = data;
    }

    int getActiveReaders() {
        return this->activeReaders;
    }

    void setActiveReaders(int activeReaders) {
        this->activeReaders = activeReaders;
    }

    int getActiveWriters() {
        return this->activeWriters;
    }

    void setActiveWriters(int activeWriters) {
        this->activeWriters = activeWriters;
    }

    bool getSemaphore() {
        return this->semaphore;
    }

    void setSemaphore(bool semaphore) {
        this->semaphore = semaphore;
    }
};

class Process {
private:
    int id;
    TYPE type;
    int timeToLive;
    bool isReading;
public:
    Process(int id, TYPE type, int timeToLive) {
        this->id = id;
        this->type = type;
        this->timeToLive = timeToLive;
        this->isReading = false;
    }

    int getId() {
        return this->id;
    }

    void setId(int id) {
        this->id = id;
    }

    TYPE getType() {
        return this->type;
    }

    void setType(TYPE type) {
        this->type = type;
    }

    int getTimeToLive() {
        return this->timeToLive;
    }

    int setTimeToLive(int timeToLive) {
        this->timeToLive = timeToLive;
    }

    bool getIsReading() {
        return this->isReading;
    }

    void setIsReading(bool isReading) {
        this->isReading = isReading;
    }
};

File *file = new File("Hello World");

void instanceProcess(int id, TYPE type) {
    int ttl = rand() % MAX_PROCESSING_TIME + MIN_PROCESSING_TIME;

    Process *process = new Process(id, type, ttl);

    for(int i = 0; i < ttl; i++) {
        this_thread::sleep_for(chrono::seconds(PROCESS_DELAY * rand() % 5 + 1));

        if(file->getSemaphore() and process->getType() == READER) {
            cout << "Process " << id << " was blocked. He was trying to read" << endl;
            i-=1;
            continue;
        }

        if(!process->getIsReading() and process->getType() == READER) {
            process->setIsReading(true);
            file->setActiveReaders(file->getActiveReaders()+1);
        }

        if(!process->getIsReading() and process->getType() == WRITER) {
            file->setActiveWriters(file->getActiveWriters()+1);
            file->setSemaphore(true);
            process->setIsReading(true);
        }

        process->setTimeToLive(process->getTimeToLive()-1);
        cout << process->getId() << "\t\t" << TypeMap[process->getType()] << "\t\t"
            << process->getTimeToLive() << "\t\t" << file->getActiveReaders()
            << "\t\t" << file->getActiveWriters() << endl;
    }

    if(process->getType() == READER and process->getTimeToLive() <= 0) {
        /// Killed
        file->setActiveReaders(file->getActiveReaders()-1);
        process->setIsReading(false);
    } else if(process->getType() == WRITER and process->getTimeToLive() <= 0) {
        file->setActiveWriters(file->getActiveWriters()-1);
        file->setSemaphore(false);
        process->setIsReading(false);
    }
}

int main() {
    srand(time(NULL));

    cout << "PID\t\tType\t\tTTL\t\tReaders\t\tWriters" << endl;

    /// Loop tava dando erro nos IDs das Threads.

    thread r1(instanceProcess, 1, READER);
    thread r2(instanceProcess, 2, READER);
    thread r3(instanceProcess, 3, READER);
    thread r4(instanceProcess, 4, READER);

    thread w1(instanceProcess, 1+10, WRITER);

    r1.join();
    sleep(rand() % 2 * 1000);

    r2.join();
    sleep(rand() % 2 * 1000);

    r3.join();
    sleep(rand() % 2 * 1000);

    r4.join();
    sleep(rand() % 2 * 1000);

    w1.join();
    sleep(rand() % 2 * 1000);

    return 0;
}
