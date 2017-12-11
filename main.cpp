#include <iostream>
using namespace std;

#define m 4
#define OVERFLOW 0
#define OK 1

template <class T>
struct Nodo {
    int count;
	T data[m + 1];
	Nodo * hij[m + 2];
	Nodo () {
		count = 0;
		for (int i = 0; i < m+2;i++)
			hij [i] = NULL;
	}
	void inserta_into (int pos, const T& info){
        int i;
        for (i = m-1; i >= pos; i--){
            this->data[i+1] = this->data[i];
			this->hij[i+2] = this->hij[i+1];
		}
        this->hij[i+2] = this->hij[i+1];
		this->data[pos] = info;
		this->count++;
    }
};


template <class T>
class btree {

    Nodo<T> * raiz;
public:
	btree () {
		raiz= new Nodo<T>();
	}
	void insert (const T & info) {
		int ret = insert2 (raiz, info);
		if (ret == OVERFLOW)
            splitRoot();
	}
	void print () {
            print2 (raiz, 0);
    }

private:
  int insert2 (Nodo<T>* parent, const T& info){
  int pos = 0;
		while (  pos < parent->count && parent->data[pos] < info )
			pos++;

		if ( parent->hij[pos]  == NULL) {
			parent->inserta_into ( pos, info);
		}
		else {
			int ret = insert2 ( parent->hij[pos], info);
			if ( ret  == OVERFLOW ) {
				split (parent, pos);
			}
		}
		return (parent->count > m ) ? OVERFLOW : OK;
  }
    void splitRoot(){
        int i ;
		Nodo<T> * child = raiz ;
		Nodo<T> *node1 = new Nodo<T>();
		Nodo<T> *node2 = new Nodo<T>();

		for ( i = 0; i < m/2; i++ ) {
			node1->data[i] = child->data[i];
			node1->hij[i] = child->hij[i];
            node1->count++;
		}
		node1->hij[i] = child->hij[i];
		i++;
        int k;
		for ( k =0 ; i <= m; k++, i++ ) {
			node2->data[k] = child->data[i];
			node2->hij[k] = child->hij[i];
            node2->count++;

		}
		node2->hij[k] = child->hij[i];
		Nodo<T>* parent = new Nodo<T>(); // new raiz
		parent->inserta_into (0, child->data[m/2]);
		parent->hij[0] = node1;
		parent->hij[1] = node2;
		raiz = parent;
		// delete child;
    }
    void split (Nodo<T> *parent ,  int pos){
    	int i ;
		Nodo<T>* child = parent->hij[pos] ;
		Nodo<T> *node1 = new Nodo<T>();
		Nodo<T> *node2 = new Nodo<T>();

		for ( i = 0; i < m/2; i++ ) {
			node1->data[i] = child->data[i];
			node1->hij[i] = child->hij[i];
			node1->count++;
		}
		node1->hij[i] = child->hij[i];

		i++;
        int k;
		for ( k =0 ; i <= m; k++, i++ ) {
			node2->data[k] = child->data[i];
			node2->hij[k] = child->hij[i];
            node2->count++;

		}
		node2->hij[k] = child->hij[i];

		parent->inserta_into(pos, child->data[m/2]);

		parent->hij[pos] = node1;
		parent->hij[pos+1] = node2;
		// delete child;
    }

    void print2(Nodo<T>* ptr, int level ) {
        if (ptr) {
            int i;
            for (i = ptr->count - 1; i >= 0; i--) {
               print2(ptr->hij[i+1], level + 1);

                for (int k = 0; k  < level; k++)
                    cout << "   ";
                cout << ptr->data [i] << endl ;
            }
            print2( ptr->hij[i+1], level + 1);
        }
    }
};


int main()
{

    btree<int> bt;
    int i=0;
    while(1) {

         bt.insert(i);
        cout<<endl<<endl;
        bt.print();
        cout<<endl<<endl;
        i++;

        if(i==10)break;
    }

    return 0;
}
