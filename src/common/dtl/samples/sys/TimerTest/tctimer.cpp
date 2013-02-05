#include <dtprec.h>
#include <dtl/dtl.h>
#include <pthread.h>


DTimer *gTimer = NULL;
class Runner : public ITimerTask
{
public:
    void run(){
        Date curDate;
        std::cout << "i'm running " 
            << curDate.toString(FD_GENERAL_LONG).getCStr()
            << std::endl;
    }
    void cancel(){}
};

void * tester(void * arg) {
    DTimer *timer = (DTimer *)arg;
    Runner aha;
    timer->shedule( aha, 0, 3);
    return NULL;
}

void testShedule() {
    DTimer *timer = new DTimer();	
    pthread_t pht;
    pthread_create( &pht, NULL, tester,(void *)timer);
    sleep(4);
    timer->cancel();
    pthread_join(pht,NULL);
    delete timer;
}


template<typename T> void
printVector( std::vector<T> &v) {
    //std::cout<<endl<<"date vector is: ";
    for(typename std::vector<T>::iterator it = v.begin();
            it != v.end();
            ++it) {
        std::cout<< *it<<" ";
    }
    std::cout<<std::endl;
}

void testTimerStrategy_shouldRun() {
    using namespace std;
    DTimerStrategy strgy1;
    vector<int> date;
    Date day;
    date.push_back(3);
    date.push_back(5);
    date.push_back(8);
    String ts1 = "00:12";
    String ts2 = "18:00";
    String ts3 = "16:00";
    strgy1.setStrategy(WEEK,date,ts1,ts2,10);


    cout<<"current day is "<< day.toString(FD_GENERAL_FULL).getCStr()<<endl;
    printVector(date);
    cout<< "strgy1:WEEK,date,"<<ts1.getCStr()<<","<<ts2.getCStr()<<" "
        <<boolalpha<< strgy1.shouldRun( day)<< endl;

    date[0] = 4;
    strgy1.setStrategy(WEEK,date,ts1,ts2,10);
    printVector(date);
    strgy1.shouldRun(day);
    cout<< "strgy1:WEEK,date,"<<ts1.getCStr()<<","<<ts2.getCStr()<<" "
        <<boolalpha<< strgy1.shouldRun( day)<< endl;

    DTimerStrategy strgy2(MONTH,date,ts3,ts2,0);
    cout<< "strgy2:MONTH,date,"<<ts3.getCStr()<<","<<ts2.getCStr()<<" "
        << boolalpha<< strgy2.shouldRun( day)<< endl;

    date[2] = 9;
    printVector(date);
    strgy2.setStrategy(MONTH,date,"00:12","18:50",10);

    strgy2.shouldRun(day);
    cout<< "strgy2:MONTH,date,"<<ts3.getCStr()<<","<<ts2.getCStr()<<" "
        << boolalpha<< strgy2.shouldRun( day)<< endl;

}

void * _runEveryday(void *arg) {
    using namespace std;
    DTimer *timer = (DTimer *)arg;
    Date cur;
    Date firstLater = Date(cur.time() + 60*Date::ticksPerSecond);
    Date secondLater = Date(cur.time() + 120*Date::ticksPerSecond);
    DTimerStrategy strgy(EVERYDAY,
                    std::vector<int>(),
                    firstLater.toTimeString(TP_SHORT),
                    secondLater.toTimeString(TP_SHORT),
                    2);
    cout<<"strategy is EVERYDAY "
        <<firstLater.toTimeString(TP_SHORT).getCStr()
        <<" - "
        <<secondLater.toTimeString(TP_SHORT).getCStr()
        <<endl;
    Runner aha;
    timer->shedule( aha, strgy);
    return NULL;
}

void * _runWeek(void *arg) {
    using namespace std;
    DTimer *timer = (DTimer *)arg;
    Date cur;
    Date firstLater = Date(cur.time() + 60*Date::ticksPerSecond);
    Date secondLater = Date(cur.time() + 120*Date::ticksPerSecond);
    vector<int> day(10);
    
    day[0] = 4;
    day[1] = 5;
    DTimerStrategy strgy(WEEK,
                    day,
                    firstLater.toTimeString(TP_SHORT),
                    secondLater.toTimeString(TP_SHORT),
                    2);
    cout<<"strategy is WEEK ";
    printVector(day);
    cout<<"time is "
        <<firstLater.toTimeString(TP_SHORT).getCStr()
        <<" - "
        <<secondLater.toTimeString(TP_SHORT).getCStr()
        <<endl;
    Runner aha;
    timer->shedule( aha, strgy);
    return NULL;
}

void * _runMonth(void *arg) {
    using namespace std;
    DTimer *timer = (DTimer *)arg;
    Date cur;
    Date firstLater = Date(cur.time() + 60*Date::ticksPerSecond);
    Date secondLater = Date(cur.time() + 120*Date::ticksPerSecond);
    vector<int> day(10);
    day[0] = 4;
    day[1] = 5;
    day[2] = 9;
    DTimerStrategy strgy(MONTH,
                    day,
                    firstLater.toTimeString(TP_SHORT),
                    secondLater.toTimeString(TP_SHORT),
                    2);
    cout<<"strategy is MONTH ";
    printVector(day);
    cout<<"time is "
        <<firstLater.toTimeString(TP_SHORT).getCStr()
        <<" - "
        <<secondLater.toTimeString(TP_SHORT).getCStr()
        <<endl;
    Runner aha;
    timer->shedule( aha, strgy);
    return NULL;
}

void testStategyShedule(void *(*fun)(void *)) {
    using namespace std;
    DTimer *timer = gTimer;
    //DTimer *timer = new DTimer();
    pthread_t pht;
    //pthread_create(&pht, NULL, _runEveryday, timer);
    //pthread_create(&pht, NULL, _runWeek, timer);
    pthread_create(&pht, NULL, fun, timer);
    sleep(30);
    pthread_create(&pht, NULL, fun, timer);
    sleep(40);
    cout<<"------------------cancel----------"<<endl;
    timer->cancel();
    pthread_join( pht,NULL);
    //delete timer;
}

int main() {
    gTimer = new DTimer();
    //testShedule();
    //testTimeStr();
    //testTimerStrategy_shouldRun();
    //useString();
    testStategyShedule(_runEveryday);
    testStategyShedule(_runWeek);
    testStategyShedule(_runMonth);
    delete gTimer;
}
