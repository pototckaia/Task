#include <stdio.h>
#include <stdlib.h>


#define LOAD_FACTOR 0.75

typedef struct _Node {
	int key;
	struct _Node *next;
} Node;

typedef struct {
	Node **head;
	int count;
	int size;
} HashTable;

HashTable *createHashTable(int size) {
    HashTable *newHashTable = (HashTable *) malloc(sizeof(HashTable));
    newHashTable->count = 0;
    newHashTable->size = size;
    newHashTable->head = (Node **) malloc(size * sizeof(Node *));
    for (int i = 0; i < size; i++) {
        newHashTable->head[i] = NULL;
    }
    return newHashTable;
}

void freeHashTable(HashTable **hashTable) {
    int size = (*hashTable)->size;
    for (int i = 0; i < size; i++){
        Node *currentNode = (*hashTable)->head[i];
        while (currentNode) {
            Node *nextNode = currentNode->next;
            free(currentNode);
            currentNode = nextNode;
        }
    }
    free((*hashTable)->head);
    free((*hashTable));
    (*hashTable) = NULL;
}

int getIndex(int key, int size) {
    return (int) ((key * 2654435761) % size);
}

HashTable *rehash(HashTable **);

void insertKey(HashTable **_hashTable, int key) {
    HashTable *hashTable = (*_hashTable);
    int index = getIndex(key, hashTable->size);
    if (!hashTable->head[index]) {
        Node *newNode = (Node *) malloc(sizeof(Node));
        newNode->key = key;
        newNode->next = NULL;
        hashTable->head[index] = newNode;
        hashTable->count++;
    } else {
        Node *currentNode = hashTable->head[index];
        while (currentNode->next && currentNode->key != key) {
            currentNode = currentNode->next;
        }
        if (currentNode->key == key) {
            return;
        }
        Node *newNode = (Node *) malloc(sizeof(Node));
        newNode->key = key;
        currentNode->next = newNode;
        newNode->next = NULL;
        hashTable->count++;
    }
    if (hashTable->count > hashTable->size * LOAD_FACTOR) {
        *_hashTable = rehash(_hashTable);
    }

}

HashTable *rehash(HashTable **_hashTable) {
    HashTable *hashTable = (*_hashTable);
    HashTable *newHashTable = createHashTable(hashTable->size * 2);

    int size = hashTable->size;
    for (int i = 0; i < size; i++) {
        Node *currentNode = hashTable->head[i];
        while (currentNode) {
            insertKey(&newHashTable, currentNode->key);
            currentNode = currentNode->next;
        }
    }
    freeHashTable(_hashTable);
    return newHashTable;
}


void deleteHashTable(HashTable *hashTable, int key) {
    int index = getIndex(key, hashTable->size);
    if (hashTable->head[index]) {
        Node *currentNode = hashTable->head[index];
        Node *prevNode = NULL;
        while (currentNode->next && currentNode->key != key) {
            prevNode = currentNode;
            currentNode = currentNode->next;
        }
        if (currentNode->key != key) {
            return;
        }
        if (currentNode == hashTable->head[index]) {
            hashTable->head[index] = NULL;
        } else {
            prevNode->next = currentNode->next;
        }
        free(currentNode);
        hashTable->count--;
    }
}

int *hashTableToArray(HashTable *hashTable) {
    int *hashTableArray = (int *) calloc(hashTable->size, sizeof(int));
    int size = hashTable->size;
    int pos = 0;
    for (int i = 0; i < size; i++) {
        Node *currentNode = hashTable->head[i];
        while (currentNode) {
            hashTableArray[pos] = currentNode->key;
            currentNode = currentNode->next;
            pos++;
        }
    }
    return hashTableArray;
}

int compare(const void *a, const void *b) {
    return ((*(int *)a) > (*(int*)b) ? 1 : -1);
}

int main(){
	int n;
	FILE *input = fopen("input.txt", "r"), *output = fopen("output.txt", "w");
	fscanf(input, "%d", &n);

    int size = 128;
	HashTable *hashTable = createHashTable(size);
	while(n) {
		if (n > 0) {
			insertKey(&hashTable, n);
		}
		else {
            deleteHashTable(hashTable, (-n));
		}
		fscanf(input, "%d", &n);
	}

    int *hashTableArray = hashTableToArray(hashTable);
    qsort(hashTableArray, hashTable->count, sizeof(int), compare);
    for (int i = 0; i < hashTable->size; i++) {
    	if (hashTableArray[i] == 0) 
    		continue;
        fprintf(output, "%d ", hashTableArray[i]);
    }


    freeHashTable(&hashTable);
    free(hashTableArray);
	fclose(input); fclose(output);
	return 0;
}