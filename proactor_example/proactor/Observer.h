#ifndef __OBSERVER_H__
#define __OBSERVER_H__

template <typename T> class Observer
{
public:
    virtual void notify(T* operation) = 0;
    virtual ~Observer() {};
};

#endif //__OBSERVER_H__