// filepath: derivatives-analysis/src/event.hpp
#ifndef EVENT_HPP
#define EVENT_HPP

#include <iostream>
#include <vector>
#include <functional>

template<typename... Args>

class Event 
{
public:
    using Callback = std::function<void(Args...)>;

    void addListener(const Callback& callback) {
        listeners.push_back(callback);
    }

    void trigger(Args... args) const {
        for (const auto& listener : listeners) {
            listener(args...);
        }
    }

private:
    std::vector<Callback> listeners;
};

template<typename... Args>

class EventResponder 
{
public:
    EventResponder(Event<Args...>& event, std::function<void(Args...)> handler)
        : event(event), handler(handler) {
        event.addListener(handler);
    }

private:
    Event<Args...>& event;
    std::function<void(Args...)> handler;
};

class Empty {};

template<typename T>

class EmptyWrapper : public Empty 
{
public:
    EmptyWrapper(std::shared_ptr<T> ptr) : ptr(ptr) {}

private:
    std::shared_ptr<T> ptr;
};

#endif