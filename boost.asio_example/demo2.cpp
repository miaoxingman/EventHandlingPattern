#include "demo_api.h"
#include <boost/asio.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <string>
#include <map>

static boost::mutex map_mutex;
static std::map<int, boost::shared_ptr<boost::mutex> > mutex_map;

template<int N>
void print(const boost::system::error_code& /*e*/)
{
    //get thread ID
    boost::shared_ptr<boost::mutex> mutex;
    map_mutex.lock();
    std::string thread_id = boost::lexical_cast<std::string>(boost::this_thread::get_id());
    auto iter = mutex_map.find(N);
    if (iter  == mutex_map.end()) {
        mutex_map[N] = boost::make_shared<boost::mutex>();
        mutex = mutex_map[N];
        std::cout<<"new mutex"<<std::endl;
    } else {
        mutex = iter->second;
    }
    map_mutex.unlock();

    //Thread aggregate
    rmt_BeginCPUSampleDynamic(thread_id.c_str(), RMTSF_Aggregate);

    //mutex lock aggreate
    rmt_BeginCPUSample(Blocked, RMTSF_Aggregate);
    mutex->lock();
    rmt_EndCPUSample();

    //work aggreate
    rmt_BeginCPUSample(Work, RMTSF_Aggregate);
    boost::this_thread::sleep(boost::posix_time::milliseconds(rand() % 30));
    std::cout <<"["<<boost::this_thread::get_id()<<"] " << "Hello, world from timer " << std::endl;
    rmt_EndCPUSample();

    mutex->unlock();
    rmt_EndCPUSample();
}

void boost_asio_strand_demo()
{
    time_t t;
    boost::asio::io_service io;
    boost::asio::strand test0(io);
    boost::asio::strand test1(io);
    boost::asio::strand test2(io);
    boost::asio::strand test3(io);
    boost::asio::strand test4(io);
    boost::asio::strand test5(io);
    boost::asio::strand test6(io);

    srand((unsigned)time(&t));
    for (int i = 0; i < 1000; i++) {
        boost::asio::deadline_timer t(io, boost::posix_time::milliseconds(rand() % 30));
        if (rand() % 7 == 0) {
            t.async_wait(test0.wrap(&print<0>));
        } else if ( i % 7 == 1) {
            t.async_wait(test1.wrap(&print<1>));
        } else if ( i % 7 == 2) {
            t.async_wait(test2.wrap(&print<2>));
        } else if ( i % 7 == 3) {
            t.async_wait(test3.wrap(&print<3>));
        } else if ( i % 7 == 4) {
            t.async_wait(test4.wrap(&print<4>));
        } else if ( i % 7 == 5) {
            t.async_wait(test5.wrap(&print<5>));
        } else {
            t.async_wait(test6.wrap(&print<6>));
        }
    }

    boost::thread t1(boost::bind(&boost::asio::io_service::run, &io));
    boost::thread t2(boost::bind(&boost::asio::io_service::run, &io));
    
    io.run();

    t1.join();
    t2.join();

}