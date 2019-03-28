#include <iostream>
#include <thread>

using namespace std;

int HOW_MANY_READERS = 4;
int HOW_MANY_WRITERS = 4;
double READERS_INTENSITY = 0.2;
double WRITERS_INTENSITY = 0.5;
int MAX_PROCESSING_TIME = 10; // seconds

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

void foo() {
  // do stuff...
}

void bar(int x) {
  // do stuff...
}

int main() {

  thread first(foo);     m// spawn new thread that calls foo()
  thread second(bar, 0);  // spawn new thread that calls bar(0)

  std::cout << "main, foo and bar now execute concurrently...\n";

  // synchronize threads:
  first.join();                // pauses until first finishes
  second.join();               // pauses until second finishes

  cout << "foo and bar completed.\n";
    
  return 0;
}
