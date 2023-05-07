#pragma once
#include <iostream>
#include <exception>
using namespace std;

class exceptie1 : public exception
{
	virtual const char* what() const throw()
	{
		return "Indexul este in afara limitelor!";
	}
};
class exceptie2 : public exception
{
	virtual const char* what() const throw()
	{
		return "Capacitatea listei a fost depasita!";
	}
};

template<typename T>
class Compare_Mai_Mare
{
	public:
		int CompareElements(T* e1, T* e2)
		{
			if ((*e1) > (*e2))
				return 1;
			return 0;
		}
};
template<typename T>
class Compare_Egal 
{
	public:
		int CompareElements(T* e1, T* e2)
		{
			if ((*e1) == (*e2))
				return 1;
			return 0;
		}
};

template<typename T>
class ArrayIterator
{
	private:
		T** list;
		int Current; // mai adaugati si alte date si functii necesare pentru iterator
	public:
		ArrayIterator(T** l, int aux) :list(l), Current(aux) {}
		ArrayIterator& operator ++ ()
		{
			this->Current++;
			return (*this);
		}
		ArrayIterator& operator -- ()
		{
			this->Current--;
			return (*this);
		}
		bool operator==(ArrayIterator<T>& aux)
		{
			return (this->Current == aux.Current);
		}
		bool operator!=(ArrayIterator<T>& aux)
		{
			return (this->Current != aux.Current);
		}
		T* GetElement()
		{
			return this->list[this->Current];
		}
		T* operator*()
		{
			return this->list[this->Current];
		}
};

template<typename T>
class Array
{
	private:
		T** List; // lista cu pointeri la obiecte de tipul T*
		int Capacity; // dimensiunea listei de pointeri
		int Size; // cate elemente sunt in lista
	public:
		static int compare_mai_mare(const T& e1, const T& e2)
		{
			if (e1 > e2)
				return 1;
			return 0;
		}
		static int compare_egal(const T& e1, const T& e2)
		{
			if (e1 == e2)
				return 1;
			return 0;
		}
		Array() // Lista nu e alocata, Capacity si Size = 0
		{
			this->List = nullptr;
			this->Capacity = 0;
			this->Size = 0;
		}
		~Array() // destructor	
		{
			//delete[] this->List;
			this->Capacity = 0;
			this->Size = 0;
		}
		Array(int capacity) // Lista e alocata cu 'capacity' elemente
		{
			this->List = new T * [capacity];
			this->Capacity = capacity;
			this->Size = 0;
		}
		Array(const Array<T>& otherArray) // constructor de copiere
		{
			this->~Array();
			this->List = new T * [otherArray.Size];
			this->Capacity = otherArray.Capacity;
			this->Size = otherArray.Size;
			for (int i = 0; i < otherArray.Size; i++)
				this->List[i] = otherArray.List[i];
		}
		T& operator[] (int index) // arunca exceptie daca index este out of range
		{
			exceptie1 index_out;
			try
			{
				if (index < 0 || index >= this->Size)
					throw index_out;
				return *(this->List[index]);
			}
			catch (exception& e)
			{
				cout << "Exceptie: " << e.what() << endl;
			}
		}
		const Array<T>& operator+=(const T& newElem) // adauga un element de tipul T la sfarsitul listei si returneaza this
		{
			exceptie2 size_out;
			try
			{
				if (this->Size + 1 > this->Capacity)
					throw size_out;
				this->Size++;
				this->List[this->Size-1] = (T*) &newElem;
			}
			catch (exception& e)
			{
				cout << "Exceptie: " << e.what() << endl;
			}
			return (*this);
		}
		const Array<T>& Insert(int index, const T& newElem) // adauga un element pe pozitia index, retureaza this. Daca index e invalid arunca o exceptie
		{
			exceptie1 index_out;
			exceptie2 size_out;
			try
			{
				if (index < 0 || index > this->Size)
					throw index_out;
				if (this->Size + 1 > this->Capacity)
					throw size_out;
				this->Size++;
				for (int i = this->Size - 1; i > index; i--)
					this->List[i] = this->List[i - 1];
				this->List[index] = (T*) &newElem;
			}
			catch (exception& e)
			{
				cout << "Exceptie: " << e.what() << endl;
			}
			return (*this);
		}
		const Array<T>& Insert(int index, const Array<T> otherArray) // adauga o lista pe pozitia index, retureaza this. Daca index e invalid arunca o exceptie
		{
			exceptie1 index_out;
			exceptie2 size_out;
			try
			{
				if (index < 0 || index > this->Size)
					throw index_out;
				if (this->Size + otherArray.Size > this->Capacity)
					throw size_out;
				int k = index;
				for (int i = 0; i < otherArray.Size; i++)
					this->Insert(k++, *(otherArray.List[i]));
			}
			catch (exception& e)
			{
				cout << "Exceptie: " << e.what() << endl;
			}
			return (*this);
		}
		const Array<T>& Delete(int index) // sterge un element de pe pozitia index, returneaza this. Daca index e invalid arunca o exceptie
		{
			exceptie1 index_out;
			try
			{
				if (index < 0 || index >= this->Size)
					throw index_out;
				for (int i = index; i < this->Size - 1; i++)
					this->List[i] = this->List[i + 1];
				this->Size--;
			}
			catch (exception& e)
			{
				cout << "Exceptie: " << e.what() << endl;
			}
			return (*this);
		}
		bool operator==(const Array<T>& otherArray)
		{
			if (this->Size != otherArray.Size)
				return false;
			for (int i = 0; i < this->Size; i++)
				if (this->List[i] != otherArray.List[i])
					return false;
			return true;
		}
		void Sort() // sorteaza folosind comparatia intre elementele din T
		{
			Compare_Mai_Mare<T> c;
			for(int i=0; i<this->Size-1; i++)
				for(int j=i+1; j<this->Size; j++)
					if (c.CompareElements(this->List[i], this->List[j]))
					{
						T* aux = this->List[i];
						this->List[i] = this->List[j];
						this->List[j] = aux;
					}
		}
		void Sort(int(*compare)(const T&, const T&)) // sorteaza folosind o functie de comparatie
		{
			for (int i = 0; i < this->Size - 1; i++)
				for (int j = i + 1; j < this->Size; j++)
					if (compare(*(this->List[i]), *(this->List[j])))
					{
						T* aux = this->List[i];
						this->List[i] = this->List[j];
						this->List[j] = aux;
					}
		}
		void Sort(Compare_Mai_Mare<T> * comparator) // sorteaza folosind un obiect de comparatie
		{
			for (int i = 0; i < this->Size - 1; i++)
				for (int j = i + 1; j < this->Size; j++)
					if (comparator->CompareElements(this->List[i], this->List[j]))
					{
						T* aux = this->List[i];
						this->List[i] = this->List[j];
						this->List[j] = aux;
					}
		}

		// functii de cautare - returneaza pozitia elementului sau -1 daca nu exista
		int BinarySearch(const T& elem) // cauta un element folosind binary search in Array
		{
			int st = 0, dr = this->Size - 1;
			while (st <= dr)
			{
				int mij = (st + dr) / 2;
				if (*(this->List[mij]) == elem)
					return mij;
				else if (*(this->List[mij]) < elem)
					st = mij + 1;
				else
					dr = mij - 1;
			}
			return -1;
		}
		int BinarySearch(const T& elem, int(*compare)(const T&, const T&))//  cauta un element folosind binary search si o functie de comparatie
		{
			int st = 0, dr = this->Size - 1;
			while (st <= dr)
			{
				int mij = (st + dr) / 2;
				if (*(this->List[mij]) == elem)
					return mij;
				else if (compare(elem, *(this->List[mij])))
					st = mij + 1; 
				else
					dr = mij - 1;
			}
			return -1;
		}
		int BinarySearch(const T& elem, Compare_Mai_Mare<T> * comparator)//  cauta un element folosind binary search si un comparator
		{
			int st = 0, dr = this->Size - 1;
			T* p = (T*) &elem;
			while (st <= dr)
			{
				int mij = (st + dr) / 2;
				if (*(this->List[mij]) == elem)
					return mij;
				else if (comparator->CompareElements(p, this->List[mij]))
					st = mij + 1;
				else
					dr = mij - 1;
			}
			return -1;
		}
		int Find(const T& elem) // cauta un element in Array
		{
			for (int i = 0; i < this->Size; i++)
				if (*(this->List[i]) == elem)
					return i;
			return -1;
		}
		int Find(const T& elem, int(*compare)(const T&, const T&))//  cauta un element folosind o functie de comparatie
		{
			for (int i = 0; i < this->Size; i++)
				if (compare(*(this->List[i]), elem))
					return i;
			return -1;
		}
		int Find(const T& elem, Compare_Egal<T> * comparator)//  cauta un element folosind un comparator
		{
			T* p = (T*) & elem;
			for (int i = 0; i < this->Size; i++)
				if (comparator->CompareElements(this->List[i], p))
					return i;
			return -1;
		}
		int GetSize()
		{
			return this->Size;
		}
		int GetCapacity()
		{
			return this->Capacity;
		}
		void Print()
		{
			for (int i = 0; i < this->Size; i++)
				cout << *(this->List[i]) << ' ';
			cout << endl;
		}
		ArrayIterator<T> begin()
		{
			return ArrayIterator<T>(this->List, 0);
		}
		ArrayIterator<T> end()
		{
			return ArrayIterator<T>(this->List, this->Size);
		}
};