

//Define a structure to represent each query
struct Query {
    char name[100];
    int time;
};

//Initialize separate queues for students and faculty queries
Queue studentQueue;
Queue facultyQueue;

//Function to add new queries to the respective queue
void addQuery(char name[], int time, char category) {
    struct Query query;
    strcpy(query.name, name);
    query.time = time;

    if (category == 'S') {
        enqueue(&studentQueue, query);
    } else if (category == 'F') {
        enqueue(&facultyQueue, query);
    }
}

//Function to handle queries for a given time
void handleQueries(int total_time) {
    int current_time = 0;
    int query_count = 0;
    int total_query_time = 0;

    while (current_time < total_time) {
        //Check which queue has the highest number of pending queries
        Queue *currentQueue;
        if (studentQueue.size > facultyQueue.size) {
            currentQueue = &studentQueue;
        } else {
            currentQueue = &facultyQueue;
        }

        //If there are no pending queries in any queue, break from the loop
        if (currentQueue->size == 0) {
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
    printf("Total time spent: %d minutes\n", current_time);
    printf("Total queries handled: %d\n", query_count);
    printf("Average query time: %.2f minutes\n", avg_query_time);
}

int main() {
    //Add some sample queries with Indian names
    addQuery("Amit", 15, 'S');
    addQuery("Priya", 8, 'F');
    addQuery("Anjali", 12, 'S');
    addQuery("Ravi", 10, 'F');
    addQuery("Sushil", 5, 'S');

    //Handle queries for 2 hours (120 minutes)
    handleQueries(120);

    return 0;
}




///  main logic part only

    //Handle queries for a given time
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
