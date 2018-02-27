#if __QUEUE__H__

typedef enum Boolean Boolean;
enum Boolean 
{
	false,
	true
};

typedef struct StackInt QueueInt;
struct QueueInt
{
	int data;
	struct QueueInt* element_next;
};

QueueInt* QueueInt_Create(void);
void QueueInt_Destroy(QueueInt* queueint);

QueueInt* QueueInt_Push(QueueInt* queueint, int const data_queue);
QueueInt* QueueInt_Pop(QueueInt* queueint);


#endif
