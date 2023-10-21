// Observer.h
#pragma once

namespace s21 {

class Observer {
public:
    virtual ~Observer() {}
    virtual void update() = 0;

};

} // namespace s21
