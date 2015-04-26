#include "vector_header.h"
#include "debug.h"


#undef PRECOND
#define PRECOND																		\
																					\
	int _check_vector = check();													\
	VERIFY(_check_vector != VECTOR_OK, _check_vector, "Vector check failed");		\

#undef POSTCOND
#define POSTCOND																	\
																					\
	_check_vector = check();														\
	VERIFY(_check_vector != VECTOR_OK, _check_vector, "Vector check failed");		\


#define POISON_DATA assert(data != NULL); for (int i = 0; i < size; ++i) data[i] = POISON;

extern FILE* STRERR;
extern FILE* STRLOG;

//using namespace Vector;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//						CONSTRUCTORS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


Vector::Vector(): size(0), data(NULL), _memory_size(MEMORY_BLOCK_SIZE)
{
	size = 0;
	data = (double*) calloc(MEMORY_BLOCK_SIZE, sizeof(double));
	_memory_size = MEMORY_BLOCK_SIZE;

	printf("Vector constructed\n");

	MVERIFY(data == NULL, "Vector:Vector: no memory established\n");
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


Vector::Vector(const Vector& that)
{
	MVERIFY(that.check() != VECTOR_OK, "VECTOR(const Vector&): Argument is corrupted");

	if (data != NULL)
	{
		for (int i = 1; i < size; ++i) data[i] = POISON;
		free(data);
	}
	data = (double*) calloc(that._memory_size, sizeof(double));
	MVERIFY(data == NULL, "VECTOR(const Vector&): Calloc failed");

	memcpy((void*)data, (void*)that.data, that._memory_size*sizeof(double));
	size			= that.size;
	_memory_size	= that._memory_size;
	for (int i = 1; i < size; ++i) data[i] = that.data[i];
	
	printf("Vector contructed\n");
	MVERIFY(check() != VECTOR_OK, "VECTOR(const Vector&): Postcondition failed");
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


Vector::Vector(int array_size, double* array)
{

	int reset_check = reset();
	MVERIFY(reset_check != VECTOR_OK, "Vector(int size, double* array): Reset failed");

	int realloc_check = _realloc_memory(MEMORY_BLOCK_SIZE * ((size / MEMORY_BLOCK_SIZE) + 1));
	MVERIFY(realloc_check != VECTOR_OK, "Vector(int size, double* array): Realloc failed");

	for (int i = 0; i < array_size; ++i) data[i] = array[i];

	size = array_size;

	check();
	
	printf("Vector contructed\n");

	MVERIFY(check() != VECTOR_OK, "VECTOR(int array_size, double* array): Postcondition failed");
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//						DESTRUCTOR
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

Vector::~Vector()
{
	
	POISON_DATA;
	size = POISON;
	_memory_size = MEMORY_BLOCK_SIZE;

	printf("Vector destructed\n");
	free(data);
	data = NULL;	
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//						REDEFINED OPERATORS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

Vector Vector::operator+(const Vector& that) const
{
	MVERIFY(that.check() != VECTOR_OK, "VECTOR::operator+(const Vector&): Argument is corrupted");
	MVERIFY(check() != VECTOR_OK, "VECTOR::operator+(const Vector&): Current is corrupted");

	Vector out = *this;

	if (that._memory_size > _memory_size)
	{
		int check_realloc = out._realloc_memory(that._memory_size);
		MVERIFY(check_realloc != VECTOR_OK, "VECTOR::operator+: reallocation failed");
	}

	for (int i = 0; i < that._memory_size; ++i) out.data[i] += that.data[i];
	if (that.size > out.size) out.size = that.size;

	MVERIFY(out.check() != VECTOR_OK, "VECTOR::operator+(const Vector&): Construction failed");
	return out;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


Vector Vector::operator-(const Vector& that) const
{
	MVERIFY(that.check() != VECTOR_OK, "VECTOR::operator-(const Vector&): Argument is corrupted");
	MVERIFY(check() != VECTOR_OK, "VECTOR::operator-(const Vector&): Current is corrupted");

	Vector that_copy = that;
	for (int i = 0; i < that_copy.size; ++i) that_copy.data[i] *= -1;

	Vector out = (that_copy + *this);

	MVERIFY(out.check() != VECTOR_OK, "VECTOR::operator-(const Vector&): Construction failed");
	return out;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


Vector Vector::operator*(double value) const
{
	MVERIFY(check() != VECTOR_OK, "VECTOR::operator*(double value): Current is corrupted");
	
	Vector out = *this;
	for (int i = 0; i < size; ++i) out.data[i] *= value;

	MVERIFY(out.check() != VECTOR_OK, "VECTOR::operator*(double value): Construction failed");
	return out;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


Vector operator*(double value, const Vector& that)
{
	MVERIFY(that.check() != VECTOR_OK, "Vector operator*(double value, const Vector& that): that is corrupted");
	Vector out = that * value;

	MVERIFY(out.check() != VECTOR_OK, "Vector operator*(double value, const Vector& that): Construction failed");
	return out;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


double& Vector::operator[](int index) const
{
	MVERIFY(check() != VECTOR_OK, "Vector::operator*[]: Current is corrupted");
	if (index < 0) index += size;
	if (index < 0) index = index;				// TODO!!!!!!!
	double& return_value = data[index];			
	return return_value;
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void Vector::operator+=(const Vector& that)
{
	MVERIFY(check()		!= VECTOR_OK,  "PRECOND: Vector::operator+=(const Vector& that):: Current vector broken");
	MVERIFY(that.check() != VECTOR_OK, "PRECOND: Vector::operator+=(const Vector& that):: Input vector broken");
	
	if (that.size > size) _set_size(that.size);

	for (int i = 0; i < that.size; ++i) data[i] += that.data[i];

	MVERIFY(check()		!= VECTOR_OK, "POSTCOND: Vector::operator+=(const Vector& that):: Current vector broken");
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void Vector::operator-=(const Vector& that)
{
	MVERIFY(check()		!= VECTOR_OK,  "PRECOND: Vector::operator-=(const Vector& that):: Current vector broken");
	MVERIFY(that.check() != VECTOR_OK, "PRECOND: Vector::operator-=(const Vector& that):: Input vector broken");
	
	int  maxsize = size;
	
	if (that.size > size) _set_size(that.size);

	for (int i = 0; i < that.size; ++i) data[i] -= that.data[i];

	MVERIFY(check()		!= VECTOR_OK, "POSTCOND: Vector::operator-=(const Vector& that):: Current vector broken");
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void Vector::operator*=(double value)
{
	MVERIFY(check()		!= VECTOR_OK,  "PRECOND: Vector::operator*=(const Vector& that):: Current vector broken");
	for (int i = 0; i < size; ++i) data[i] *= value;
}



//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//							PUBLIC METHODS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


int Vector::push_back(double value)
{
	PRECOND;
	if (size % MEMORY_BLOCK_SIZE == 0 && size != 0)
	{
		int check_extend = _extend_data();
		VERIFY(check_extend != VECTOR_OK, VECTOR_NO_MEMORY, "Data extending failed");
	}
	data[size++] = value;
	
	
	POSTCOND;
	return VECTOR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


int Vector::reset()
{
	if (data != NULL)
	{
		POISON_DATA;
		free(data);
	}
	data = (double*) calloc(MEMORY_BLOCK_SIZE, sizeof(double));
	
	_memory_size = MEMORY_BLOCK_SIZE;
	size = 0;

	PRECOND;
	return VECTOR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

double Vector::module() const
{
	PRECOND;

	long double square_sum = 0;
	for (int i = 0; i < size; ++i) square_sum += data[i] * data[i];

	POSTCOND;

	return sqrt(square_sum);
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


int Vector::remove(int index)
{
	PRECOND;
	if (index >= size) return VECTOR_OK;
	
	if (index < 0) index += size;							// negative are allowed, numerating values of vector from the end
	VERIFY(index < 0, VECTOR_INDEX_BAD, "Bad index, the range is [-SIZE , SIZE - 1]");

	for (int i = index + 1; i < size; ++i) data[i - 1] = data[i];
	size--;

	int check_optimize = _optimize_memory();
	VERIFY(check_optimize != VECTOR_OK, VECTOR_OPTIM_FAIL, "REMOVE:: Optimization failed");

	POSTCOND;
	return VECTOR_OK;
}

/*
#define CHANGE_DATA(name, sign)														\
																					\
int Vector::##name()																\
{																					\
	int requesting = _memory_size ##sign MEMORY_BLOCK_SIZE;							\
	double* next_data = (double*) calloc(requesting, sizeof(double));				\
	VERIFY1(next_data != NULL, VECTOR_NO_MEMORY, "Calloc failed in %s", #name);		\																				\
	memcpy((void*)next_data, (void*)data, size * sizeof(double));					\																	\
	POISON_DATA;																	\
	free(data);																		\
	_memory_size = requesting;														\
																					\
	data = next_data;																\
																					\
	return VECTOR_OK;																\
}																					\

CHANGE_DATA(_extend_data, +);
CHANGE_DATA(_cut_data, -);
*/

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int Vector::check() const
{
	if (this == NULL)			return VECTOR_THIS_NULL;
	if (data == NULL)			return VECTOR_DATA_NULL;
	if (size > _memory_size)	return VECTOR_DATA_LEAK;
	return VECTOR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


void Vector::print(FILE* stream)
{
	fputc('[', stream);
	for (int i = 0; i < size-1; ++i) fprintf(stream, "%lg, ", data[i]);
	if (size - 1 >= 0) fprintf(stream, "%lg", data[size - 1]);
	fputc(']', stream);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void Vector::dump(FILE* stream)
{
	fprintf(stream, "I'm vector [%08x]. I'm %s [%d]\n"
			"Size = %d, Memory = %d\n",
			this, (check() == VECTOR_OK)? "OK":"BAD", check(), size, _memory_size);

	for (int i = 0; i < size; ++i) fprintf(stream, "%dth: %lg\n", i, data[i]);
	putc('\n', stream);
	fprintf(stream, "Vector. End of dump\n");
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int Vector::get_memory_size()
{
	assert(this);
	return _memory_size;
}

int Vector::get_size()
{
	assert(this);
	return size;
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int Vector::insert(double value, int place)
{
/*
	PRECOND;
	if (place < 0) place += size;
	if (place >= size) return VECTOR_INDEX_BAD;
	int check_set = _set_size(size + 1);
	VERIFY(check_set != VECTOR_OK, check_set, "Vector::insert(): SET function failed");
	for (int i = size - 1; i >= place + 1; ++i) data[i] = data[i - 1];
	data[place] = value;

	POSTCOND;
*/
	return insert_array(&value, 1, place);
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int	Vector::insert_array(double* array_, int array_size, int place)
{
	PRECOND;

	int check_set = _set_size(size + array_size);
	VERIFY(check_set != VECTOR_OK, check_set, "INSERT_ARRAY: Setting size failed");
	for (int i = size; i >= place + array_size; --i) data[i] = data[i - array_size];
	for (int i = place; i < place + array_size; ++i) data[i] = array_[i - place];
	
	POSTCOND;
	return VECTOR_OK;
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int Vector::remove_range(int from, int to)
{
	PRECOND;
	VERIFY(!((0 <= from) && (from <  size)), VECTOR_INDEX_BAD, "REMOVE_RANGE: FROM index invalid");
	VERIFY(!((0 <  to  ) && (to   <= size)), VECTOR_INDEX_BAD, "REMOVE_RANGE: TO index invalid");
	for (int i = from; i < size - (to - from); ++i) data[i] = data[i + (to - from)];
	int check_set = _set_size(size - (to - from));
	VERIFY(check_set != VECTOR_OK, check_set, "REMOVE_RANGE: Size set failed");
	POSTCOND;
	return VECTOR_OK;
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

double Vector::pop_back()
{
	MVERIFY(check()		!= VECTOR_OK,  "PRECOND: POP_BACK:: Current vector broken");
	double ret_value = data[size - 1];
	int check_remove = remove(size - 1);
	MVERIFY(check_remove != VECTOR_OK, "POP_BACK: Remove failed");
	return ret_value;
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int Vector::push_front(double value)
{
	PRECOND;

	int check_insert = insert(value, 0);
	VERIFY(check_insert != VECTOR_OK, check_insert, "PUSH_FRONT: Insertion failed");

	POSTCOND;
	return VECTOR_OK;
}



//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

double Vector::pop_front()
{
	MVERIFY(check()		!= VECTOR_OK,  "PRECOND: POP_FRONT:: Current vector broken");
	double ret_value = data[0];
	int check_remove = remove(0);
	MVERIFY(check_remove != VECTOR_OK, "POP_BACK: Remove failed");
	return ret_value;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int Vector::shift_left(int step)
{
	PRECOND;
	VERIFY(step < 0, VECTOR_INDEX_BAD, "SHIFT_LEFT: Negative step");
	for (int i = 0; i < size - step; ++i) data[i] = data[i + step];
	for (int i = (size - step < 0)? 0: size - step; i < size; ++i) data[i] = 0;
	POSTCOND;
	return VECTOR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int Vector::shift_right(int step)
{
	PRECOND;
	VERIFY(step < 0, VECTOR_INDEX_BAD, "SHIFT_RIGHT: Negative step");
	if (step >= size) 
	{
		for (int i = 0; i < size; i++) data[i] = 0;
		POSTCOND;
		return VECTOR_OK;
	}
	for (int i = size - 1; i >= step; --i)	data[i] = data[i - step];
	for (int i = 0; i < step; ++i)			data[i] = 0;
	POSTCOND;
	return VECTOR_OK;
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//						PRIVATE METHODS
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


int Vector::_extend_data()
{
	PRECOND;
	int requesting = _memory_size + MEMORY_BLOCK_SIZE;
	double* next_data = (double*) calloc(requesting, sizeof(double));
	VERIFY(next_data == NULL, VECTOR_NO_MEMORY, "Calloc failed in EXTEND_DATA");

	memcpy((void*)next_data, (void*)data, size * sizeof(double));
	
	POISON_DATA;
	if (data != NULL) free(data);
	_memory_size += MEMORY_BLOCK_SIZE;

	data = next_data;
	POSTCOND;
	return VECTOR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


int Vector::_cut_data()
{
	PRECOND;
	int requesting = _memory_size + MEMORY_BLOCK_SIZE;
	double* next_data = (double*) calloc(requesting, sizeof(double));
	VERIFY(next_data == NULL, VECTOR_NO_MEMORY, "Calloc failed in EXTEND_DATA");

	memcpy((void*)next_data, (void*)data, size * sizeof(double));
	
	POISON_DATA;
	if (data != NULL) free(data);
	_memory_size += MEMORY_BLOCK_SIZE;

	data = next_data;

	POSTCOND;
	return VECTOR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>




int Vector::_realloc_memory(int new_memory_size)
{
	PRECOND;
	VERIFY(new_memory_size < size, VECTOR_NOT_EGH_MEM, "VECTOR::_realloc_memory: not enough memoty for current data");
	double* new_data = (double*) calloc(new_memory_size, sizeof(double));
	VERIFY(new_data == NULL, VECTOR_NO_MEMORY, "VECTOR::_realloc_memory: calloc failed");
	memcpy((void*) new_data, (void*)data, size * sizeof(double));

	POISON_DATA;
	free(data);
	data = new_data;
	_memory_size = new_memory_size;

	POSTCOND;
	return VECTOR_OK;
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int Vector::_set_size(int new_size)
{
	PRECOND;
	int req_memblocks = (new_size % MEMORY_BLOCK_SIZE != 0)? 
						(new_size / MEMORY_BLOCK_SIZE) + 1: 
						(new_size / MEMORY_BLOCK_SIZE);
	if (req_memblocks == 0) req_memblocks++;

	if (_memory_size != req_memblocks * MEMORY_BLOCK_SIZE)
	{

		int check_realloc = _realloc_memory(req_memblocks * MEMORY_BLOCK_SIZE);
		VERIFY(check_realloc != VECTOR_OK, check_realloc, "_SET_SIZE: Reallocation failed");

		if (size < new_size) for (int i = size; i < new_size; ++i) data[i] = 0;
	}
	size = new_size;
	
	POSTCOND;
	return VECTOR_OK;
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int Vector::_optimize_memory()
{
	PRECOND;
	if (_memory_size - size >= MEMORY_BLOCK_SIZE) 
	{
		int check_realloc = _realloc_memory( (size % MEMORY_BLOCK_SIZE != 0)?	MEMORY_BLOCK_SIZE * ((size / MEMORY_BLOCK_SIZE) + 1) : size);
		VERIFY(check_realloc != VECTOR_OK, check_realloc, "_OPTIMIZE_MEMORY: Failed to reallocate memory");
		return VECTOR_OK;
	}
	else return VECTOR_OK;
}
