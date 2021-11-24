#ifndef CESEXCEPTION_H
#define CESEXCEPTION_H

#include <QException>

class CESException : public QException
{
public:
    void raise() const override {throw *this; }
    CESException *clone() const override {return new CESException(*this); }
protected:
    CESException(){};
};


class IllegalValueException : public CESException
{
public:
    IllegalValueException(){};
    const char* what() const noexcept override {
        return "Illegal value passed to CES";
    }
};

class AmperageOverloadException : public CESException
{
public:
    AmperageOverloadException(){};
    const char* what() const noexcept override {
        return "The CES received too much amperage";
    }
};

#endif // CESEXCEPTION_H
