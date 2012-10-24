#ifndef INC_USER_INTERFACE_H
#define INC_USER_INTERFACE_H

class UserInterface
{
public:
    virtual ~UserInterface() = 0;

    virtual int MainLoop() = 0;
};

#endif  // INC_USER_INTERFACE_H↵
