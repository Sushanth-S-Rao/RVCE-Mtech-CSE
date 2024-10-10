#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_BUCKETS 10
using namespace std;

// structure for table entry
struct Entry {
    int key;
    int value;
    struct Entry* next;
};

// Hash Table
struct HashTable{
    Entry* buckets[NUM_BUCKETS];
    pthread_mutex_t mutex[NUM_BUCKETS];
};

// Initialize
void initialize(HashTable* table) {
    for(int i = 0; i < NUM_BUCKETS; i++) {
        table -> buckets[i] = NULL;
        table -> mutex[i] = PTHREAD_MUTEX_INITIALIZER;
    }
}


// Insert
void insert(HashTable* table, int key, int value) {
    // Hash Function
    int index = key % NUM_BUCKETS;                      

    pthread_mutex_lock(&table->mutex[index]);

    Entry* n = new Entry;
    n -> key = key;
    n -> value = value;
    
    n -> next = table -> buckets[index];
    table -> buckets[index] = n;

    pthread_mutex_unlock(&table->mutex[index]);
}

// Retrieve
int get(HashTable* table, int k) {
    int index = k % NUM_BUCKETS;  
    
    pthread_mutex_lock(&table -> mutex[index]);

    Entry* current = table -> buckets[index];
    while (current != NULL) {
        if (current -> key == k) {
            pthread_mutex_unlock(&table -> mutex[index]);
            return current->value;
        }
        current = current->next;
    }

    pthread_mutex_unlock(&table -> mutex[index]);
    return -1;
}

int main() {
    HashTable table;
    initialize(&table);
	
	// Insert some key-value pairs
	int key, val;
	for (int i = 0; i < 3; i++){
		printf("Enter the Key and Value: ");
        cin >> key >> val;
		insert(&table, key, val);
	}

	// Retrieve values
	int res, search;
	for(int i = 0; i < 3; i++){
		printf("\nEnter the key to search: ");
		cin >> search;
		res = get(&table, search);
        cout << "Key " << search << "\t Value: " << res;
	}
	
    return 0;
}
