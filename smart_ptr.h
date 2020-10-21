//SmartPointer Class
#include <iostream>
#include <stdexcept>
//using namespace std;

class null_ptr_exception :public std::runtime_error
{
public:
	null_ptr_exception( std::string s1) : std::runtime_error(s1) {
	}


};

class  ref
{
private:
	int counter;
public:

	void addRef()
	{
		counter++;
	}
	int release()
	{
		return --counter;
	}
	int checkRef() {
		return counter;
	}
};
template <typename T>
class smart_ptr {
public:
	smart_ptr() {
	// Create a smart_ptr that is initialized to nullptr. The
	// reference count should be initialized to nullptr.
		ptr_ = nullptr;
		ref_ = nullptr;
	}

	explicit smart_ptr(T* raw_ptr) {
	// Create a smart_ptr that is initialized to raw_ptr. The
	// reference count should be one. Make sure it points to
	// the same pointer as the raw_ptr.
		ref_ = new ref();
		ref_->addRef();
		ptr_ = raw_ptr;
	}
	

	smart_ptr(const smart_ptr& rhs) {
	// Copy construct a pointer from rhs. The reference count
	// should be incremented by one.
		ptr_ = rhs.ptr_;//point to address of rhs ptr_
		ref_ = rhs.ref_;//point ref to rhs ref_
		ref_->addRef(); //increment ref count

	}

	smart_ptr(smart_ptr&& rhs) {
		// Move construct a pointer from rhs.
		ptr_ = rhs.ptr_;//point new smart pointer ptr to rhs ptr
		ref_ = rhs.ref_;//point new smart pointer ref to rhs ref
		rhs.ref_ = nullptr; //point rhs to nullptr
		rhs.ptr_ = nullptr;//point rhs to nullptr
	}
	
	smart_ptr& operator=(const smart_ptr& rhs) {
		// This assignment should make a shallow copy of the
		// right-hand side's pointer data. The reference count
		// should be incremented as appropriate.
		this->~smart_ptr();
		this->ptr_ = rhs.ptr_;
		this->ref_ = rhs.ref_;
		this->ref_->addRef();
		return *this;
	}

	smart_ptr& operator=(smart_ptr&& rhs) {
		// This assignment should make a shallow copy of the
		// right-hand side's pointer data. The reference count
		// should be incremented as appropriate.
		this->~smart_ptr();
		this->ptr_ = rhs.ptr_;
		this->ref_ = rhs.ref_;
		rhs.ptr_ = nullptr;
		rhs.ref_ = nullptr;
	}

	bool clone()	{
		// If the smart_ptr is either nullptr or has a reference
		// count of one, this function will do nothing and return
		// false. 
		if (ref_ == nullptr || ref_->checkRef() == 1)return false;

		//Otherwise, the referred to object's reference
		// count will be decreased
		this->ref_->release();

		//and a new deep copy of the
		// object will be created. This new copy will be the
		// object that this smart_ptr points and its reference
		// count will be one.

		T *tempVal = new T; //new  pointer to variabl type T
		*tempVal = this->getVal();//Copy the data from this to tempVal
		ptr_ = tempVal; //point ptr_ to the new copy
		std::cout << "this int: " << this->getVal() << std::endl;
		ref_ = new ref(); //make a new ref class
		ref_->addRef(); //increment new ref
	}


	int ref_count() const {
		// Returns the reference count of the pointed to data.
		if (ref_ != nullptr) return ref_->checkRef();
		else return 0;
	}
	
	T& operator*() {
	// The dereference operator shall return a reference to
	// the referred object. Throws null_ptr_exception on
	// invalid access.
		if (ptr_ == nullptr) throw null_ptr_exception("Null_ptr_exception"); 
		return *ptr_;
	}
	

	T* operator->() {
		// The arrow operator shall return the pointer ptr_.
		// Throws null_ptr_exception on invalid access.
		if (ptr_ == nullptr)throw null_ptr_exception("null_ptr_exception");
		return ptr_;
	}
	
	T getVal()
	{
		return *ptr_;
	}
	~smart_ptr() {
		if (ref_ != nullptr)
		{
			if (ref_->checkRef() > 1)
			{
				ref_->release();
				std::cout << "releasing one ref\n";
			}
			else
			{
				std::cout << "deleting memory\n";
				delete ptr_;
				ptr_ = nullptr;
				delete ref_; 
				ref_ = nullptr;
			}
		}

	}
		// deallocate all dynamic memory
private:
	T* ptr_; // pointer to the referred object
	ref* ref_; // pointer to a reference count
};

