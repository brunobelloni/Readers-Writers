#include <iostream>

using namespace std;

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
    
    string getData() {
        return this->data;
    }
};

int main() {

    File *file = new File("Hello World");
    
    cout << file->getData() << endl;
    
    return 0;
}
