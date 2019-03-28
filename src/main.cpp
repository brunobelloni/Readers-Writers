#include <iostream>
#include <thread>
#include <cstdlib>
#include <unistd.h>
#include <chrono>

using namespace std;

int HOW_MANY_READERS = 4;
int HOW_MANY_WRITERS = 4;

double READERS_INTENSITY = 0.2;
double WRITERS_INTENSITY = 0.5;

int MAX_PROCESSING_TIME = 3; // seconds
int MIN_PROCESSING_TIME = 1; // seconds

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
public:
    File(string data) {
        this->data = data;
        this->activeReaders = 0;
        this->activeWriters = 0;
    }

    bool canRead() {
        return this->activeWriters <= 0 ? true : false;
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
};

class Process {
private:
    int id;
    TYPE type;
    int timeToLive;
public:
    Process(int id, TYPE type, int timeToLive) {
        this->id = id;
        this->type = type;
        this->timeToLive = timeToLive;
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
};

void instanceProcess(int id, TYPE type) {
    int ttl = rand() % MAX_PROCESSING_TIME + MIN_PROCESSING_TIME;

    Process *process = new Process(id, type, ttl);

    for(int i = 0; i < ttl; i++) {
        this_thread::sleep_for(chrono::seconds(ttl));
        cout << this_thread::get_id() << "\t\t" << TypeMap[process->getType()] << "\t\t" << process->getTimeToLive() << endl;
        process->setTimeToLive(ttl-1);
    }
}

int main() {
    srand(time(NULL));

    cout << "Id\t\t\tType\t\tTTL" << endl;

    for(int i = 0; i < HOW_MANY_READERS; i++) {
        thread process(&instanceProcess, i, READER);
        process.join();
    }

    for(int i = 0; i < HOW_MANY_WRITERS; i++) {
        thread process(instanceProcess, i+10, WRITER);
        process.join();
    }

    return 0;
}
