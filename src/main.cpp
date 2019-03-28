#include <iostream>

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

int main() {

    File *file = new File("Hello World");
    
    cout << file->getData() << endl;
    
    return 0;
}
