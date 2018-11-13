// Very basic class (char) array-as-queue    BL Nov 2018

#define BUF_SIZE 40

class Queue
{
private:
	bool _isFull(){  return (_size == BUF_SIZE); };
	bool _isEmpty(){  return (_size == 0); };
	char _buffer[BUF_SIZE];
	int _head;
	int _tail;
	int _size;
	
public:
	Queue(void){
		_head=0;
		_tail=BUF_SIZE-1;
		_size=0;
	};
	bool enqueue(char ch){
		if (_isFull()) 
			return false; 
		_tail = (_tail + 1)%BUF_SIZE; 
		_buffer[_tail] = ch; 
		_size ++; 
	    return true;
	};
	int dequeue(){
		if (_isEmpty()) 
			return -1; 
		char ch = _buffer[_head]; 
		_head = (_head + 1)%BUF_SIZE; 
		_size --; 
		return int(ch); 
	};
};

