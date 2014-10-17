/* Knoten für eine Warteschlange - Templatevariante
 * 
 */
 
 template <class T>
 class Knoten {
	 private:
		Knoten* m_prev;
		Knoten* m_next;
		T*		m_data;
	 public:
		Knoten* getPrev() {return m_prev;}
		Knoten* getNext() {return m_next;}
		T* getData() 	  {return m_data;}
		
		void setPrev(Knoten* prev) {m_prev = prev;}
		void setNext(Knoten* next) {m_next = next;}
		void setData(T* data) 	   {m_data = data;}
 };
