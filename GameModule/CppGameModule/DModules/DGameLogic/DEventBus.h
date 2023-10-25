#include <iostream>
#include <functional>
#include <map>
#include <list>
#include <string>

template <typename Data>
class Event {
public:
    std::string type;
    Data data;

    Event(const std::string& type, const Data& data) : type(type), data(data) {}
};

template <typename Data>
class EventBus {
private:
    using EventHandler = std::function<void(const Event<Data>&)>;
    std::map<std::string, std::list<EventHandler>> m_handlers;

public:
    void subscribe(const std::string& eventType, EventHandler handler) {
        m_handlers[eventType].push_back(handler);
    }

    void publish(const Event<Data>& event) {
        auto it = m_handlers.find(event.type);
        if (it != m_handlers.end()) {
            for (const auto& handler : it->second) {
                handler(event);
            }
        }
    }
};