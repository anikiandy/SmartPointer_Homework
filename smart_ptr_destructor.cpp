template <typename T>
smart_ptr<T>::~smart_ptr() noexcept {
    //cout << "Reference count: " << use_count() << endl;
    if (ref_ != nullptr) {
        if (*ref_ > 1) {
            //cout << "Dynamic ref decremented now!" << endl;
            --(*ref_);
        }
        else {
            //cout << "Dynamic deleted!" << endl;
            delete ptr_;
            delete ref_;
        }
    }
}