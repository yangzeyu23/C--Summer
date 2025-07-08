//考虑作业队列的容量限制，修改代码，实现标准的生产者—消费者模型。设作业队列最多容量amount个作业，有m个接收作业的线程，有n个处理作业的线程。
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <list>
struct Job  {
  Job( int x = 0, int y = 0) : x(x), y(y)  {  }
  int x, y;
};
std::list<Job *>   job_queue;
pthread_mutex_t   job_queue_mutex = PTHREAD_MUTEX_INITIALIZER;

//  控制作业数目的信号量
sem_t   job_queue_count;

void  ProcessJob( Job * job )
{
  std::cout << "Thread " << (int)pthread_self();
  std::cout << " processing (" << job->x << ", " << job->y << ")\n";
}
//  处理作业时需要加锁
void *  DequeueJob( void * arg )
{
  while( true )  {
    Job *  job = NULL;
    sem_wait( &job_queue_count );	//  等待作业队列中有新作业
    pthread_mutex_lock( &job_queue_mutex );
    if( !job_queue.empty() )  {
      job = job_queue.front();	//  获取表头元素
      job_queue.pop_front();		//  删除表头元素
    }
    pthread_mutex_unlock( &job_queue_mutex );
    if( !job )    break;
    ProcessJob( job );
    delete job,  job = NULL;
  }
  return NULL;
}
//  作业入队时需要加锁
void *  EnqueueJob( void * arg )
{
  Job *  job = reinterpret_cast< Job * >( arg );
  pthread_mutex_lock( &job_queue_mutex );    //  锁定互斥
  job_queue.push_back( job );

  //  新作业入队，递增信号量
  sem_post( &job_queue_count );

  //  入队时也输出线程ID和作业内容信息
  std::cout << "Thread " << (int)pthread_self();
  std::cout << " enqueueing (" << job->x << ", " << job->y << ")\n";

  pthread_mutex_unlock( &job_queue_mutex );    //  解锁
  return NULL;
}
int  main()
{
  int  i;
  pthread_t  threads[8];
  if( !job_queue.empty() )    job_queue.clear();
  sem_init( &job_queue_count, 0, 0 );	//  初始化，非进程共享，初始值0
  for( i = 0; i < 5; ++i )
  {
    Job *  p = new Job( i+1, (i+1)*2 );
    pthread_create( &threads[i], NULL, EnqueueJob, p );
  }
  for( i = 5; i < 8; ++i )
    pthread_create( &threads[i], NULL, DequeueJob, NULL );
  for( i = 0; i < 8; ++i )
    pthread_join( threads[i], NULL );		//  等待线程终止，无作业时线程被阻塞
  sem_destroy( &job_queue_count );	//  销毁作业信号量
  return 0;
}

