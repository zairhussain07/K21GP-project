#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Define a structure to represent each query
struct Query {
    char name[100];
    int time;
};

//Define a structure for a queue node
struct QueueNode {
    struct Query query;
    struct QueueNode* next;
};

//Define a structure for a queue
typedef struct {
    struct QueueNode* front;
    struct QueueNode* rear;
    int size;
} Queue;

//Function to create a new queue node
struct QueueNode* createQueueNode(struct Query query) {
    struct QueueNode* newNode = (struct QueueNode*) malloc(sizeof(struct QueueNode));
    newNode->query = query;
    newNode->next = NULL;
    return newNode;
}

//Function to initialize a new queue
void initializeQueue(Queue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
}

//Function to check if a queue is empty
int isQueueEmpty(Queue* queue) {
    return queue->size == 0;
}

//Function to add a new query to the end of the queue
void enqueue(Queue* queue, struct Query query) {
    struct QueueNode* newNode = createQueueNode(query);

    if (isQueueEmpty(queue)) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }

    queue->size++;
}

//Function to remove and return the query at the front of the queue
struct Query dequeue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        struct Query emptyQuery;
        strcpy(emptyQuery.name, "");
        emptyQuery.time = 0;
        return emptyQuery;
    }

    struct QueueNode* frontNode = queue->front;
    struct Query frontQuery = frontNode->query;

    queue->front = frontNode->next;
    queue->size--;

    free(frontNode);

    return frontQuery;
}

//Function to add new queries to the respective queue
void addQuery(char name[], int time, char category, Queue* studentQueue, Queue* facultyQueue) {
    struct Query query;
    strcpy(query.name, name);
    query.time = time;

    if (category == 'S') {
        enqueue(studentQueue, query);
    } else if (category == 'F') {
        enqueue(facultyQueue, query);
    }
}

//Function to handle queries for a given time
void handleQueries(int total_time, Queue* studentQueue, Queue* facultyQueue) {
    int current_time = 0;
    int query_count = 0;
    int total_query_time = 0;

    while (current_time < total_time) {
        //Check which queue has the highest number of pending queries
        Queue *currentQueue;
        if (studentQueue->size > facultyQueue->size) {
            currentQueue = studentQueue;
        } else {
            currentQueue = facultyQueue;
        }

        //If there are no pending queries in any queue, break from the loop
        if (isQueueEmpty(currentQueue)) {
            break;
        }

        //Handle the next query in the queue
        struct Query query = dequeue(currentQueue);
        total_query_time += query.time;
        query_count++;

        //Update the current time
        current_time += query.time;
    }

    //Calculate the average query time
    float avg_query_time = (float) total_query_time / query_count;

    //Print the summary of the session
    printf("Total query time: %d minutes\n", total_query_time);
    printf("Average query time: %.2f minutes\n", avg_query_time);
    printf("Number of queries handled: %d\n", query_count);
    }

    int main() {
    //Initialize the student and faculty queues
    Queue studentQueue, facultyQueue;
    initializeQueue(&studentQueue);
    initializeQueue(&facultyQueue);
    //Add some sample queries to the queues
    addQuery("Aarav", 15, 'S', &studentQueue, &facultyQueue);
    addQuery("Amit", 10, 'S', &studentQueue, &facultyQueue);
    addQuery("Aditi", 20, 'F', &studentQueue, &facultyQueue);
    addQuery("Anjali", 25, 'S', &studentQueue, &facultyQueue);
    addQuery("Akshay", 8, 'F', &studentQueue, &facultyQueue);
    addQuery("Ayesha", 12, 'S', &studentQueue, &facultyQueue);
    addQuery("Ankita", 18, 'S', &studentQueue, &facultyQueue);
    addQuery("Arjun", 16, 'F', &studentQueue, &facultyQueue);

    //Handle the queries for 2 hours (120 minutes)
    handleQueries(120, &studentQueue, &facultyQueue);

    return 0;

    }
