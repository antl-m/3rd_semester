#ifndef BOOL_H
#define BOOL_H


struct Bool {
    Bool(bool val);
    Bool();

    operator bool() const;

    Bool &operator=(bool val);

    bool _value;
};


#endif //BOOL_H
