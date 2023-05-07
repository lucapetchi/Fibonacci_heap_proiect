#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
struct node {
	node* parent;
	node* child;
	node* left;
	node* right;
	int key;
	int degree;
	bool mark;
	bool seen;

	node(int val);
	node();
	
};
int nr_nod = 0;
node::node(int val) {
	this->parent = nullptr;
	this->child = nullptr;
	this->left = nullptr;
	this->right = nullptr;
	this->key = val;
	this->degree = 1;
	this->mark = false;
	this->seen = false;
}
node::node() {
	this->parent = nullptr;
	this->child = nullptr;
	this->left = nullptr;
	this->right = nullptr;
	this->key = NULL;
	this->degree = 0;
	this->mark = false;
	this->seen = false;
}


/// 
/// 
/// 

class Fibonacci {
private:
	node* min;
	node* root_list_start;
	int nr_nod;
public:
	Fibonacci();
	~Fibonacci();
	
	void insert(int val);
	void sterge(node* x);
	void merge(Fibonacci& FH);
	void merge_with_rootl(node* nod);
	void remove_from_rootl(node* nod);
	int findmin();
	node* extractmin1();
	node* extractmin2();
	void display();
	void consolidate();
	void link(node* x, node* y);
	void merge_with_child(node* parinte, node* copil);

};

Fibonacci::~Fibonacci() {

}
Fibonacci::Fibonacci() {
	this->min = nullptr;
	this->root_list_start = nullptr;
	nr_nod = 0;
}
void Fibonacci::merge_with_rootl(node* nou) {
	if (this->root_list_start = nullptr) {
		this->root_list_start = nou;
	}
	else {
		nou->right = this->root_list_start;
		nou->left = this->root_list_start->left;
		this->root_list_start->left->right = nou;
		this->root_list_start->left = nou;

		/*if (nou->key < this->min->key) {
			this->min = nou;
		}*/
	}
}
void Fibonacci::remove_from_rootl(node* nod){
	if (nod == this->root_list_start) {
		this->root_list_start = nod->right;
	nod->left->right = nod->right;
	nod->right->left = nod->left;
	}
}
void Fibonacci::insert(int val) {
	node* nou = new node(val);
	if (root_list_start == nullptr) {
		this->root_list_start = nou;
		this->root_list_start->left = nou;
		this->root_list_start->right = nou;//fiind singurul nod, pointerii left,right->la el insusi
		this->min = nou;
	}
	else {
		this->root_list_start->left->right = nou;
		nou->left = this->root_list_start->left;
		this->root_list_start->left = nou;
		nou->right = this->root_list_start;
		
		if (nou->key < this->min->key) {
			this->min = nou;
		}
	}
	this->nr_nod++;
}
void Fibonacci::merge(Fibonacci& FH) {
	if (FH.min == nullptr) {
		
	}
	else if(this->min==nullptr){
		this->min = FH.min;
		this->root_list_start = FH.root_list_start;
	}
	else {
		if (FH.min < this->min) {
			this->min = FH.min;
		}
		
		node* ultimul = FH.root_list_start->left;
		FH.root_list_start->left = this->root_list_start->left;
		this->root_list_start->left->right = FH.root_list_start;//conectez capatul primului root list cu primul din al doilea root list

		this->root_list_start->left = ultimul;
		this->root_list_start->left->right = this->root_list_start;//conectez primul cu ultimul nod din root listul final

		this->nr_nod = this->nr_nod + FH.nr_nod;
		

		FH.min = nullptr;
		FH.nr_nod = 0;

	

	}
}
int Fibonacci::findmin() {
	return this->min->key;
}
node* Fibonacci::extractmin1() {
	if (this->min == nullptr) {
		cout << "Fibonacci heap is empty!";
		return this->min;
	}
	else {
		node* originalmin = this->min;
		originalmin->degree = 0;
		this->min->degree = 0;
		int maxdegree = ceil(log2(this->nr_nod)) + 1;
		vector<node*> degreeNodes(maxdegree, nullptr);

		if (this->min->child != nullptr) {
			node* copil = this->min->child;
			do {
				this->merge_with_rootl(copil);
				copil->parent = nullptr;
				copil = copil->right;
				
			} while (copil != this->min->child);
			
		}
		
		node* temp = this->min->right;
		if (temp == this->min) {
			this->min = nullptr;
			return originalmin;
		}
		this->remove_from_rootl(originalmin);
		this->min = temp;

		node* actual = this->min;
		bool k = false;

		while (k != true) {
			node* urm = actual->right;
			actual->seen = true;

			if (urm->seen == true) {
				k = true;
			}

			int degree = actual->degree;
			while (degreeNodes[degree] != nullptr) {
				node* other = degreeNodes[degree]; 
				degreeNodes[degree] = nullptr; 

				if (actual->key > other->key) 
				{
					swap(actual, other);
				}
				other->seen = false; 

				other->left->right = other->right; 
				other->right->left = other->left;

				other->parent = actual; 

				degree++; 
				actual->degree++;

				if (actual->child == nullptr) 
				{
					actual->child = other;
					other->right = other->left = other;
				}
				else
				{
					actual->child->left->right = other;
					other->left = actual->child->left;
					other->right = actual->child;
					actual->child->left = other;
				}
			}
			degreeNodes[degree] = actual;

			if (actual->key <= this->min->key)
			{
				this->min = actual;
			}
			actual = urm; 
		}
		node* curatare = this->min; 
		do
		{
			curatare->seen = false;
			curatare = curatare->right;
		} while (curatare != this->min);

		this->nr_nod--;
		return originalmin;
	}
		}
node* Fibonacci::extractmin2() {
	node* nou = this->min;
	
	if (nou != nullptr) {
		if (nou->child != nullptr) {

			node* copil =nou->child;
			do {
				this->merge_with_rootl(copil);
				copil->parent = nullptr;
				copil = copil->right;

			} while (copil != this->min->child);

			remove_from_rootl(this->min);
			if (nou == nou->right) {
				min = nullptr;
				root_list_start = nullptr;
			}
			else {
				min = nou->right;
				consolidate();
			}

			nr_nod--;
		}
		return nou;
	}
	else {
		cout << "Heap is empty!" << endl;
		return nullptr;
	}
}
void Fibonacci::consolidate() {
	int maxDegree = log2(nr_nod) + 1;
	vector<node*> degreeArray(maxDegree, nullptr);
	cout << "Tree";
	node* curr = min;
	vector<node*> roots;

	do {
		roots.push_back(curr);
		curr = curr->right;
	} while (curr != min);

	for (int i = 0;i<=size(roots);i++) {
		node* x = roots[i];
		int degree = x->degree;
		while (degreeArray[degree] != nullptr) {
			node* y = degreeArray[degree];
			if (x->key > y->key) {
				swap(x, y);
			}
			link(y, x);
			degreeArray[degree] = nullptr;
			degree++;
		}
		degreeArray[degree] = x;
	}

	min = nullptr;
	for (node* root : roots) {
		if (root->key < min->key || min == nullptr) {
			min = root;
		}
	}
}
void Fibonacci::link(node* y, node* x) {
	this->remove_from_rootl(y);
	y->left = y->right = y;
	this->merge_with_child(x, y);
	x->degree += 1;
	y->parent = x;
	y->mark = false;
}
void Fibonacci::merge_with_child(node* parinte, node* copil) {
	if (parinte->child == nullptr) {
		parinte->child = copil;
	}
	else {
		copil->right = parinte->child->right;
		copil->left = parinte->child;
		parinte->child->right->left = copil;
		parinte->child->right = copil;
	}
}
void Fibonacci::display()
{
	if (this->min == nullptr)
	{
		cout << "The Fibonacci Heap is empty." << endl;
		return;
	}
	cout << "Root list: ";
	node* current = this->min;
	do
	{
		if (current->right == this->min)
			cout << current->key;
		else
			cout << current->key << " ---> ";
		current = current->right;
	} while (current != this->min);
	cout << endl;
	cout << "Fibonacci Heap has " << this->nr_nod << " nodes.";
	cout << endl;
}


int main() {
	
	Fibonacci FH1;
	Fibonacci FH2;
	FH1.insert(8);
	FH1.insert(3);
	FH1.insert(5);
	//FH1.display();
	FH2.insert(10);
	FH2.insert(2);
	FH2.insert(10);
	FH2.insert(12);
	//cout << FH2.findmin() << endl;
	FH1.merge(FH2);
	//FH1.display();
	//cout<<FH1.findmin()<<endl;
	node*min= FH1.extractmin1();
	FH1.display();
	cout << min->key;
	//FH1.consolidate();



}