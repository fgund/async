#ifndef IOBSERVER_H
#define IOBSERVER_H

template<typename T>
struct IObserver
{
    IObserver() = default;
    virtual ~IObserver(){};
	virtual void Update(T param) = 0;
};


#endif //IOBSERVER_H
