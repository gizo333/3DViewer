// Observable.h
#pragma once

#include <algorithm>
#include <QList>
#include "observe.h"

namespace s21 {

class Observer;

class Observable {
public:
    virtual ~Observable() {}

    void addObserver(Observer* o) {
        observers.push_back(o);
    }

    void removeObserver(Observer* o) {
        observers.erase(std::remove(observers.begin(), observers.end(), o), observers.end());
    }

protected:
    void notifyObservers() {
        for (auto& observer : observers) {
            observer->update();
        }
    }

private:
    QList<Observer*> observers;
};

}  // namespace s21
