#include <stdlib.h>
#include "qh_vector.h"
#include <assert.h>


int main(int argc, char* argv[])
{
    //TODO ��������ӵ�Ԫ���ԣ�Խ��Խ�ã�����·��������ԽȫԽ��
    //TODO ��Ԫ����д����ο�INIParser�Ǹ���Ŀ����Ҫдһ��printf��Ҫ��assert���ж����жϡ�

    qh::vector<int> num_vect;
    num_vect.push_back(1);
	assert(num_vect.Capacity() == 2 );
	assert(num_vect.size() == 1 );
	num_vect.push_back(2);
	num_vect.push_back(3);
	assert(num_vect.Capacity() == 4 );
	assert(num_vect.size() == 3 );


	num_vect.resize(2 ,5);
	assert(num_vect.Capacity() == 4 );
	assert(num_vect.size() == 2 );
	num_vect.resize(4 ,5);
	assert(num_vect.Capacity() == 4 );
	assert(num_vect.size() == 4 );
	num_vect.resize(5 ,5);
	assert(num_vect.Capacity() == 8 );
	assert(num_vect.size() == 5 );

	num_vect.pop_back();
	assert(num_vect.size() == 4 );
	assert(num_vect.empty() == false);

	num_vect.clear();
	assert(num_vect.Capacity() == 8 );
	assert(num_vect.size() == 0 );
	assert(num_vect.empty() == true);

#ifdef WIN32
    system("pause");
#endif

	return 0;
}

