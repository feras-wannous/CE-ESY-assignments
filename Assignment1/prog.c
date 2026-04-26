#include <stdio.h>
#include <string.h>

#define SIZE 10

struct CircularBuffer {
	char buffer[SIZE];
	int head;
	int tail;
	int count;
};

void init(struct CircularBuffer *cb) {
	cb->head = 0;
	cb->tail = 0;
	cb->count = 0;
}

int isFull(struct CircularBuffer *cb) {
	return cb->count == SIZE;
}

int isEmpty(struct CircularBuffer *cb) {
	return cb->count == 0;
}

void write(struct CircularBuffer *cb, char data) {
	if (isFull(cb)) {
		printf("\n[Buffer Overflow! Cannot write '%c']\n", data);
		return;
	}
	
	cb->buffer[cb->head] = data;
	cb->head = (cb->head + 1) % SIZE;
	cb->count++;
}

char read(struct CircularBuffer *cb) {
	if (isEmpty(cb)) {
		printf("\n[Buffer Underflow! Nothing to read]\n");
		return '\0';
	}
	
	char data = cb->buffer[cb->tail];
	cb->tail = (cb->tail + 1) % SIZE;
	cb->count--;
	return data;
}

int main() {
	struct CircularBuffer cb;
	init(&cb);
	
	char name[100];
	char fullName[150];
	
	printf("Enter your name: ");
	fgets(name, sizeof(name), stdin);
	name[strcspn(name, "\n")] = '\0';
	
	strcpy(fullName, name);
	strcat(fullName, "CE-ESY");
	
	printf("--- Buffer size: %d ---\n\n", SIZE);
	for (int i = 0; i < strlen(fullName); i++) {
		write(&cb, fullName[i]);
	}
	
	printf("Output: ");
	while (!isEmpty(&cb)) {
		char ch = read(&cb);
		if (ch != '\0') {
			putchar(ch);
		}
	}
	printf("\n");
	
	if (isEmpty(&cb)) {
		printf("\nBuffer is now empty. Test passed!\n");
		} else {
		printf("\nError: Buffer is NOT empty!\n");
	}
	return 0;
}