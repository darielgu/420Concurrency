#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string>
#include <fstream>
#include <iostream>
#include <queue>
#include <semaphore.h>
/**
* @brief
*
* @param argc
* @param argv
* @return int
*/

// #include "shared.h"

// NOTE this source code file is for simple demonstration
// of how command line parsing and pthreads work,
// this file does NOT compile

// #include "tree.h"

// thread for reading words from vocabulary file

// #include "readvocab.h"

// thread for reading lines from a test file and adding them to a queue

// #include "readlines.h"

// thread for removing lines from the line queue, and
// for each line, count number of contained vocab strings and print to
// an output file

// #include "countvocabstrings.h"
using namespace std;

struct SharedData {
    queue<string> requestQueue;   //  FIFO request buffer.
    sem_t semEmptySlots;               // Semaphore for empty slots.
    sem_t semFullSlots;                // Semaphore for filled slots.
    pthread_mutex_t mutex;        // Mutex to protect the queue.
    bool finishedProducing;       // Flag indicating that the producer finished.
    int processedRequests;        // Counter for how many requests have been processed.
};




int main(int argc, char* argv[]){
    //NOT MAGIC NUMBERS, DEFAULT VALS
    int producerDelay = 50;
    int maxQueueSize = 100;
    int progressMarks = 50;
    int hashInterval = 10;
    char* inputFileName;

    //starting cmdLine reading
    int opt = 0;
    while((opt = getopt(argc,argv,"t:q:p:h:"))!=-1){ // Reading cmd arguments for changing default values
        switch(opt) {
            case 't':
                producerDelay = atoi(optarg);
            if(producerDelay <=0) {
                cout<< "Time for producing request must be a number and greater than 0"<<endl;
                exit(1);
            }
            break;
            case 'q':
                maxQueueSize = atoi(optarg);
            if(maxQueueSize < 1) {
                cout<< "Max size of request queue must be a number greater then 0"<<endl;
                exit(1);
            }
            break;
            case 'p':
                progressMarks = atoi(optarg);
            if (progressMarks < 10) {
                cout<< "Number of progress marks must be a number which is atleast 10"<<endl;
            }
            break;
            case 'h':
                hashInterval = atoi(optarg);
            if( hashInterval<= 0 || hashInterval > 10) {
                cout << "Hash mark interval for progress must be a number, greater than 0, and less than or equal to 10" << endl;
                exit(1);
            }
            break;
            default:
                cout << "Usage: " << argv[0] << " requestfile.txt [-t microsec] [-q maxQueueSize] [-p progressMarks] [-h hashInterval]" << endl;
            exit(1);
        }
    }
    //Setting the input file name
    if (optind >= argc) {
        cout << "Expected input file name after options" << endl;
        exit(1);
    }
    inputFileName = argv[optind];

    //Determining the total amount of lines in file for progress bar
    int totalRequests = 0;
    ifstream inFile(inputFileName);
    string temp;
    while(getline(inFile,temp)) {
        totalRequests++;
    }
    inFile.close();

    // Creating new Threads
    pthread_t processRequests;
    pthread_t recieveRequests;




// sample pthread code
    // pthread_attr_t pthread_attr_default;
    // pthread_t thread1;
    // char *message1 = "Hello World";

    // pthread_create( &thread1, &pthread_attr_default,
    // (void *) &print_message_function, (void *) message1);



SharedData sharedData; //Stack version Use this

//IMPORTANT: initialize ALL data in the sharedData, you can have a helper to do it
// sharedData->
// readvocab thread, put more comments here of what this thread does
pthread_t readvocabThread;
// readlines thread, put more comments here of what this thread does
pthread_t readlinesThread;
// countvocabstrings thread, put more comments here of what this thread does
pthread_t countvocabstringsThread;
// create and start readvocab thread
// readvocab is the thread function executed by the readvocabThread
// **put** the declaration and definition of readvocab function into
// a **separate** pair of .h and .cpp files
if (pthread_create(&readvocabThread, NULL,
&readvocab, &sharedData))
{
//error handling
}
// create and start readlines thread
// readlines is the thread function executed by the readlinesThread
// **put** the declaration and definition of readlines function into
// a **separate** pair of .h and .cpp files
if (pthread_create(&readlinesThread, NULL,
&readlines, &sharedData))
{
//error handling
}
// create and start countvocabstrings thread
//....
// print progress bar for readvocab thread
// use the SHARED_DATA
// print progress bar for countvocabstring thread
// note this needs to wait for the completion of readvocab thread
// use the SHARED_DATA
exit(NORMALEXIT); // Normal Exit! NORMALEXIT would be zero here.