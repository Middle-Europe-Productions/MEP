#ifndef MEP_TSQUEUE_H
#define MEP_TSQUEUE_H
#include<queue>
#include<mutex>
#include<optional>

namespace MEP
{
    template<typename T>
    class TSQueue {
        std::queue<T> queue_;
        mutable std::mutex mutex_;

        // Moved out of public interface to prevent races between this
        // and pop().
        bool empty() const {
            return queue_.empty();
        }

    public:
        TSQueue() = default;
        TSQueue(const TSQueue<T>&) = delete;
        TSQueue& operator=(const TSQueue<T>&) = delete;

        TSQueue(TSQueue<T>&& other) {
            std::lock_guard<std::mutex> lock(mutex_);
            queue_ = std::move(other.queue_);
        }

        virtual ~TSQueue() { }

        unsigned long size() const {
            std::lock_guard<std::mutex> lock(mutex_);
            return queue_.size();
        }

        std::optional<T> pop() {
            std::lock_guard<std::mutex> lock(mutex_);
            if (queue_.empty()) {
                return {};
            }
            T tmp = queue_.front();
            queue_.pop();
            return tmp;
        }

        void push(const T& item) {
            std::lock_guard<std::mutex> lock(mutex_);
            queue_.push(item);
        }
    };
}

#endif