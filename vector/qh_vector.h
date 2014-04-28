#ifndef QIHOO_VECTOR_H_
#define QIHOO_VECTOR_H_
#include <exception>

namespace qh
{
    template<class T>
    class vector {
    public:
        //ctor
        vector()
            : data_(NULL), size_(0) ,capacity(0)           //��ʼ��capacity
        {
        }

        explicit vector( size_t n, const T& value = T()):size_(n)  //��ʼ��size_
        {
            data_ = new T[n];
            for (size_t i = 0; i < n; i++)
            {
                data_[i] = value;
            }
        }

        vector<T>& operator=(const vector<T>& rhs)    //���ж��Ƿ��Ǳ��� �����ǵĻ��ٿ���
        {
            if (this != & rhs)
			{
				delete [] data_ ;
				size_ = rhs.size();
				capacity = rhs.Capacity();
				data_ = new T[capacity] ;
				for(size_t i = 0 ; i < size_ ;i ++)
				{
					data_[i] = rhs.data_[i];
				}
			}
			return *this ;
        }

        //dtor
        ~vector()
        {
            if (data_)
            {
                delete [] data_;     //�޸� ɾ������
            }
        }

        //get
        size_t size() const
        {
            return size_;
        }
		size_t Capacity() const    //���� ���ʵ������
        {
            return capacity;
        }

        // set & get
        T& operator[](size_t index)  
		{
			if (index < size_)
				return *(data_ + index);
			throw std::exception("out of range");
		}

        // set
        void push_back(const T& element) // ���пռ���ֱ�Ӳ��룬û�У������·��䲢����
		{
			if (capacity - size_ > 0 )
			{
				data_[size_++] = element;
			}
			else
			{
				reserve() ;
				data_[size_++] = element ;
			}
		}
        void pop_back()       // ������������
		{
			if (size_ > 0)
				--size_ ;
			else
				throw std::exception("no element");
		}
        void resize(size_t newSize , const T& x)    // ��newSize����size_ ������X���
		{
			if(newSize <= size_)
				size_ = newSize ;
			else if (newSize <= capacity)
			{
				for(size_t i = size_ ; i < newSize ; i++)
				{
					data_[i] = x ;
				}
				size_ = newSize ;
			}
			else 
			{
				reserve() ;
				for(size_t i = size_ ; i < newSize ; i++)
				{
					data_[i] = x ;
				}
				size_ = newSize ;
			}
		}
        void reserve()
		{
			size_t newCapa = capacity != 0 ? 2*capacity : 2 ;
			T * oldData = data_;
			data_ = new T[newCapa] ;
			if( size_ > 0 )
			{
				for (size_t i = 0 ; i < size_ ; i ++ )
					data_[i] = oldData[i] ;
				delete [] oldData ;
			}
			capacity = newCapa ;
		}
        void clear()
		{
			size_ = 0 ;
		}
        bool empty()
		{
			return size_ == 0 ;
		}

    private:
        T*      data_;
        size_t  size_;
		size_t  capacity;   //���� ��ʾʵ������
    };
}

#endif


