#ifndef __ENGINE_EVENT_H__
#define __ENGINE_EVENT_H__

#include <functional>
#include <vector>

namespace Engine {
    /// @brief The Event Args struct, base class of Engine event arguments.
    struct EventArgs {};

    /// @brief The Event Action template, represent a type for event action function.
    /// @tparam SenderT The sender type of the event.
    /// @tparam EventArgsT The argument type use for the event.
    template <typename SenderT, typename EventArgsT>
    using EventAction = std::function<void(SenderT*, EventArgsT*)>;
    /// @brief The Global Event Action template, represent a type for event action function that use for global event (event
    /// which didn't have a sender).
    /// @tparam EventArgsT The argument type use for the event.
    template <typename EventArgsT>
    using GlobalEventAction = std::function<void(EventArgsT*)>;

    /// @brief The Global Event Caller template, provide a template to create a caller use for event that didn't have a sender.
    /// @tparam EventArgsT The argument type use for the event.
    template <typename EventArgsT>
    class GlobalEventCaller final {
    public:
        /// @brief The Global Event Action type that this Global Event Caller is target to.
        using GlobalEventActionT = GlobalEventAction<EventArgsT>;
    private:
        std::vector<GlobalEventActionT> data;
    public:
        /// @brief Create a new Global Event Caller.
        GlobalEventCaller() = default;
        /// @brief Create a new Global Event Caller, and allocate the given Global Event Action to it.
        /// @param action The Global Event Action to allocate.
        GlobalEventCaller(const GlobalEventActionT& action) { data.push_back(action); }

        /// @brief Create a copy of the given Global Event Caller.
        /// @param caller The Global Event Caller to copy.
        GlobalEventCaller(const GlobalEventCaller<EventArgsT>& caller) : data(caller.data) {}

        GlobalEventCaller<EventArgsT>& operator=(const GlobalEventCaller<EventArgsT>& caller) { data = caller.data; return *this; }

        GlobalEventCaller<EventArgsT>& operator+=(const GlobalEventActionT& action) { Register(action); return *this; }
        
        /// @brief Get the number of Global Event Action registered to this Global Event Caller.
        /// @return The number of Global Event Action registered to this Global Event Caller.
        size_t Count() const { return data.size(); }
        
        /// @brief Unregistered all Global Event Actions from this Global Event Caller.
        void Clear() { data.clear(); }

        /// @brief Register the given Global Event Action to this Global Event Caller.
        /// @param action The Global Event Action to register.
        void Register(const GlobalEventActionT& action) { data.push_back(action); }

        /// @brief Call all of the Global Event Action that registered to this Global Event Caller,
        /// with an empty arguments (create a new one).
        void Call() {
            EventArgsT* args = new EventArgsT;
            for (auto& f : data) if (f) f(args);
            if (args) delete args;
        }
        /// @brief Call all of the Global Event Action that registered to this Global Event Caller.
        /// @param args The argument of the event, this will share between all Global Event Action. If this null, will create a new one.
        void Call(EventArgsT* args) {
            EventArgsT* arguments = !args ? new EventArgsT : args;
            for (auto& f : data) if (f) f(arguments);
            if (!args && arguments) delete arguments;
        }
    };

    /// @brief The Event Caller template, provide a template to create a caller that can be use for event.
    /// @tparam SenderT The sender type of the event.
    /// @tparam EventArgsT The argument type use for the event.
    template <typename SenderT, typename EventArgsT>
    class EventCaller final {
    public:
        /// @brief The Event Action type that this Event Caller is target to.
        using EventActionT = EventAction<SenderT, EventArgsT>;
    private:
        std::vector<EventActionT> data;
    public:
        /// @brief Create a new Event Caller.
        EventCaller() = default;
        /// @brief Create a new Event Caller, and allocate the given Event Action to it.
        /// @param action The Event Action to allocate.
        EventCaller(const EventActionT& action) { data.push_back(action); }

        /// @brief Create a copy of the given Event Caller.
        /// @param caller The Event Caller to copy.
        EventCaller(const EventCaller<SenderT, EventArgsT>& caller) : data(caller.data) {}

        EventCaller<SenderT, EventArgsT>& operator=(const EventCaller<SenderT, EventArgsT>& caller) { data = caller.data; return *this; }

        EventCaller<SenderT, EventArgsT>& operator+=(const EventActionT& action) { Register(action); return *this; }
        
        /// @brief Get the number of Event Action registered to this Event Caller.
        /// @return The number of Event Action registered to this Event Caller.
        size_t Count() const { return data.size(); }
        
        /// @brief Unregistered all Event Actions from this Event Caller.
        void Clear() { data.clear(); }

        /// @brief Register the given Event Action to this Event Caller.
        /// @param action The Event Action to register.
        void Register(const EventActionT& action) { data.push_back(action); }

        /// @brief Call all of the Event Action that registered to this Event Caller, with an empty arguments (create a new one).
        /// @param sender The sender of the event.
        void Call(SenderT* sender) {
            EventArgsT* args = new EventArgsT;
            for (auto& f : data) if (f) f(sender, args);
            if (args) delete args;
        }
        /// @brief Call all of the Event Action that registered to this Event Caller.
        /// @param sender The sender of the event.
        /// @param args The argument of the event, this will share between all Event Action. If this null, will create a new one.
        void Call(SenderT* sender, EventArgsT* args) {
            EventArgsT* arguments = !args ? new EventArgsT : args;
            for (auto& f : data) if (f) f(sender, arguments);
            if (!args && arguments) delete arguments;
        }
    };
}

#endif // __ENGINE_EVENT_H__