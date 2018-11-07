

// https://www.embeddedrelated.com/showcode/292.php

// need TYPE and BUFFER_SIZE predefined


TYPE Buffer[BUFFER_SIZE + 1]; // It needs 1 extra byte to difference full and empty
unsigned char next = 0;
unsigned char first = 0;

unsigned char getNumberOfElements(){	
	if (next >= first){
		return (next - first);
	}else{
		return (BUFFER_SIZE - next + first);
	}	
}

inline bool isFull(){
	if (getNumberOfElements() == BUFFER_SIZE){
		return true;
	}else{
		return false;
	}
}
	
inline bool isEmpty(){
	if ( next == first ){
		return true;
	}else{
		return false;
	}	
}
	
TYPE getElement(){
	TYPE theElement = 0;
	if (! isEmpty()){	 
		theElement =  Buffer[first];	
		if ( first != BUFFER_SIZE ){
			first++;
		}else{
			first = 0;
		}		
	}

	return theElement;// Return 0 always if it is empty, must be checked before
}

bool addElement(TYPE data){	
	if (!isFull()){
		 Buffer[next] = data;
		 if ( next != BUFFER_SIZE ){
			next++;
		 }else{
			 next = 0;
		 }
		return true;
	}else{
		return false;
	}	
}

