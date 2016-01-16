#include <boost/thread/condition.hpp>
#include <boost/thread/mutex.hpp>

namespace toolbox
{
		
	class Semaphore
	{
	private:
		boost::mutex mutex_;
		boost::condition_variable condition_;
		unsigned long count_;

	public:
		Semaphore()
			: count_()
		{}

		void notify()
		{
			boost::mutex::scoped_lock lock(mutex_);
			++count_;
			condition_.notify_one();
		}

		void wait()
		{
			boost::mutex::scoped_lock lock(mutex_);
			while(!count_)
				condition_.wait(lock);
			--count_;
		}
		
		bool trywait()
		{
			boost::mutex::scoped_lock lock(mutex_);
			if(count_)
			{
				--count_;
				return true;
			}
			
			return false;
		}
	};

}
