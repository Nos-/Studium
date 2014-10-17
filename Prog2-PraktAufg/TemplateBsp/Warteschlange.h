/* Warteschlange - Templatevariante
 * 
 */
 
 #include "Knoten.h"
 
 template <class T>
 class Warteschlange {
	 private:
		Knoten<T>* first;
		Knoten<T>* last;
	 public:
		Warteschlange();
		bool push(T*);	// Draufschieben
		void pop();		// Entfernen
		T* getFirst();
		bool isEmpty();
 };

template <class T>
Warteschlange<T>::Warteschlange() {
	first = NULL;
	last  = NULL;
}

template <class T>
bool Warteschlange<T>::isEmpty() {
	return first == NULL;
}

template <class T>
bool Warteschlange<T>::push(T* data) {
	Knoten<T>* knoten = new Knoten<T>;
	if (knoten != NULL) {
		knoten->setData(data);
		if (isEmpty()) {
			first = knoten;
			last  = knoten;
		} else {
			knoten->setPrev(last);
			last  ->setNext(knoten);
			last = knoten;
		}
		return true;
	}
	return false;
}

template <class T>
void Warteschlange<T>::pop() {
	Knoten<T>* temp = NULL;
	if (first->getNext()){
		first->getNext()->setPrev(NULL);
		temp=first->getNext();
	}
	delete first;
	first = temp;
}

template <class T>
T* Warteschlange<T>::getFirst() {
	return first -> getData();
}
