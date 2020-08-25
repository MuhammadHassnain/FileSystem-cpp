#ifndef LINKED_LIST_POINTERS_H_
#define LINKED_LIST_POINTERS_H_

// generic class node
template<class T>
class Node{
	public:
		T data;
		Node * next;
		Node(){
			//data = T(NULL);
			next = NULL;
		}
};

template <class T>
class LinkedListPointers{
	public:
		LinkedListPointers<T>(){
			head = NULL;
		}
		LinkedListPointers<T>(const LinkedListPointers<T> & Linked){
			head = NULL;
			*this = Linked;
		}
		LinkedListPointers<T> & operator=(const LinkedListPointers<T> & list){
			if (this == &list)
				return *this;
			MakeNull();
			if (list.head == NULL)
				return *this;
			head = new Node < T > ;
			Node<T>* temp = list.head;
			Node<T>* thead = head;
			while (temp->next){
				thead->next = new Node < T > ;
				thead->data = temp->data;
				temp = temp->next;
				thead = thead->next;
			}
			thead->data = temp->data;
			return *this;
		}
		~LinkedListPointers<T>(){
			MakeNull();
		}
		void MakeNull(){
			Node<T> *temp = head;
			while (head){
				temp = head->next;
				delete head;
				head = temp;
			}
		}
		// method will insert element at the end of linked list
		void InsertElement(T element){
			if (isEmpty()){
				head = new Node < T > ;
				head->data = element;
			}
			else{
				Node<T> * temp = head;
				while (temp->next){
					temp = temp->next;
				}
				temp->next = new Node < T > ;
				temp = temp->next;
				temp->data = element;
			}
		}
		// method will return element at given index
		void InsertElement(T element, int i){
			if (i < 0)
				return;
			Node <T> * temp = head;
			int x=1;
			while (temp && x < i){
				temp = temp->next;
				x++;
			}
			if (i > 0 && temp==NULL) // is index is out of bound
				return;
			Node <T>* NewNode = new Node < T > ();
			NewNode->data = element;
			if (i!=0){ // if we have to insert at middle and last location
				NewNode->next = temp->next;
				temp->next = NewNode;
			}
			else{ // if we have to insert at first location
				NewNode->next = temp;
				head = NewNode;
			}
		}

		void Deletevalue(T element){
			Node<T>* previous=NULL;
			Node<T>* current = head;
			while (current && current->data != element){
				previous = current;
				current = current->next;
			}
			if (current == NULL)
				return;
			if (previous){
				previous->next = current->next;
				delete current;
			}
			else{
				head = current->next;
				delete current;
			}
		}

		// method for displaying list
		void Display(){
			Node <T> * start = head;
			while (start){
				cout << start->data<<" ";
				start = start->next;
			}
			cout << endl;
		}

		bool isEmpty(){
			return head;
		}

	private:
		Node<T> * head;
};





#endif //
