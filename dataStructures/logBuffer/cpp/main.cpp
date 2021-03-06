/*
 * Problem: Implement a log buffer which can be constructed
 * specifying a size. Implement following methods
 * put : adds a string to the log
 * print : prints the buffer so far
 */


#include "logBuffer.h"

void test1() {

    LogBuffer log = LogBuffer( 48 );
    log.put("Hello world");
    log.print();
    log.print();
    log.put(std::string("Hello world"));
    log.print();

}

void test2() {

    LogBuffer log = LogBuffer( 4 );
    log.put("Hello world");
    log.print();
    log.print();
    log.put(std::string("Hello world"));
    log.print();

}

int main(int argc, char **argv) {
    test1();
    test2();
}


/* 
 * Solution:
 * Put is an interesting method. When the buffer has space for the 
 * new item, it needs to move only the head. But when the buffer 
 * does n't have enough space for the new item or it is already 
 * full, then the tail also needs to move.
 */