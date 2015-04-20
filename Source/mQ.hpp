#include <boost/thread/mutex.hpp>
#include <queue>
#include <list>
using namespace std;

template <typename T>
class message_queue{
private:
	boost::mutex mutex;
	std::queue<T> queue;

public:

	void push(T value) {
		boost::mutex::scoped_lock lock(mutex);
		queue.push(value);
	}

	T pop() {
		boost::mutex::scoped_lock lock(mutex);
		T value = queue.front();
		queue.pop();
		return value;
	}

	bool empty() {
		boost::mutex::scoped_lock lock(mutex);
		return queue.empty();
	}
	
};