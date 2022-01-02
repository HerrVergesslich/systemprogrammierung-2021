/*
 * SmartPointerImpl.h
 *
 */

#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include <cstddef>
#include "smartpointer/RefCounter.h"
#include "smartpointer/NullPointerException.h"

/**
 * Template class to represent smart pointers (like std::shared_ptr)
 */
template<class T>
class SmartPointer {
public:
    /**
     * Constructor
     *
     * Constructs a new smart pointer from a raw pointer, sets the reference
     * counter to 1.
     *
     * @param p is a raw pointer to the object to be shared
     */
    SmartPointer(T * const p = nullptr) {
        this->pObj = p;
        if(p != nullptr) {
            this->rc = new RefCounter();
            this->rc->inc();
        }
    }

    /**
     * Copy constructor
     *
     * Constructs a new smart pointer from another smart pointer, increments the
     * reference counter.
     *
     * @param p is another smart pointer
     */
    SmartPointer(const SmartPointer& p) {
        if(p.pObj != nullptr) {
            this->pObj = p.pObj;
            this->rc = p.rc;
            this->rc->inc();
        }
    }

    /**
     * Destructor
     *
     * Decrements the reference counter. If it reaches zero, the shared object will
     * be free'd.
     */
    virtual ~SmartPointer() {
        if(this->rc != nullptr) {
            this->rc->dec();
            if (this->rc->getRefCount() <= 0) {
                delete this->pObj;
                delete this->rc;
            }
        }
    }

    /**
     * Dereferences the smart pointer
     *
     * @return a pointer to the shared object
     */
    T *operator->() const {
        if(this->pObj == nullptr) {
            throw NullPointerException("Dereference of null pointer");
        } else {
            return this->pObj;
        }
    }

    /**
     * Dereferences the smart pointer
     *
     * @return a reference to the shared object
     */
    T &operator*() const {
        if(this->pObj == nullptr) {
            throw NullPointerException("Dereference of null pointer");
        } else {
            return *this->pObj;
        }
    }

    /**
     * Assignment
     *
     * Changes the shared object, thus we need first to do the same
     * like the destructor, then something like the constructor.
     *
     * @param p raw pointer to the new object
     */
    const SmartPointer &operator=(T * const p) {
        if(this->pObj == p) return *this;
        if(this->rc != nullptr) {
            this->rc->dec();
            if(this->rc->isZero()) {
                delete this->pObj;
                delete this->rc;
            }
        }
        if(p == nullptr) {
            this->pObj = nullptr;
            this->rc = nullptr;
        } else {
            this->pObj = p;
            this->rc = new RefCounter();
            this->rc->inc();
        }
        return *this;
    }

    /**
     * Assignment
     *
     * Changes the shared object, thus we need first to do the same
     * like the destructor, then something like the copy constructor.
     *
     * @param p is another smart pointer
     */
    const SmartPointer &operator=(const SmartPointer& p) {
        if(this->pObj == p.pObj) return *this;
        if(this->rc != nullptr) {
            this->rc->dec();
            if(this->rc->isZero()) {
                delete this->pObj;
                delete this->rc;
            }
        }
        if(p.pObj == nullptr) {
            this->pObj = nullptr;
            this->rc = nullptr;
        } else {
            this->pObj = p.pObj;
            this->rc = p.rc;
            this->rc->inc();
        }
        return *this;
    }

    const RefCounter *getRefCounter() const {
        return this->rc;
    }

    const T *getObject() const {
        return this->pObj;
    }

    /**
     * Comparison
     *
     * @return true, if `p` shares the same object
     */
    bool operator==(const SmartPointer& p) const {
        return this->pObj == p.pObj;
    }

    /**
     * Comparison
     *
     * @return true, if `p` does not shares the same object
     */
    bool operator!=(const SmartPointer& p) const {
        return this->pObj != p.pObj;
    }

    /**
     * Boolean context
     *
     * @return true, if we have a shared object; false otherwise
     */
    operator bool() const {
        return this->pObj != nullptr;
    }

private:
    T* pObj = nullptr;            ///< Pointer to the current shared object
    RefCounter *rc = nullptr;     ///< Pointer to the reference counter (used for the current object)
};


#endif  // SMARTPOINTER_H

