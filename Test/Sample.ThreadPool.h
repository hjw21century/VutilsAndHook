#pragma once

#include "Sample.h"

DEF_SAMPLE(ThreadPool)
{
  const auto fn = []()
  {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << VU_FUNC_NAME << std::endl;
  };

  vu::ScopeStopWatch logger(ts("ThreadPool =>"), ts(""), vu::ScopeStopWatch::console);

  // Single-threading

  logger.reset();

  for (int i = 0; i < 10; i++)
  {
    fn();
  }

  logger.log(ts("Taken : "));

  // Default Multi-threading

  logger.reset();

  vu::ThreadPool pool;
  for (int i = 0; i < 10; i++)
  {
    pool.add_task(fn);
  }
  pool.launch();

  logger.log(ts("Taken : "));

  // STL Multi-threading

  class SampleTask : public vu::STLThreadT<std::vector<int>>
  {
  public:
    SampleTask(std::vector<int>& items) : STLThreadT(items)
    {
      m_results.resize(this->iterations());
    };

    int result()
    {
      return std::accumulate(m_results.cbegin(), m_results.cend(), 0);
    }

    virtual vu::return_type task(int& item, int iteration, int threadid)
    {
      std::this_thread::sleep_for(std::chrono::seconds(1));
      std::cout << VU_FUNC_NAME << std::endl;

      m_results[iteration] += item;

      return vu::return_type::Ok;
    }

  private:
    std::vector<int> m_results;
  };

  logger.reset();

  std::vector<int> items(10);
  std::iota(items.begin(), items.end(), 0);

  SampleTask task(items);
  task.launch();
  std::cout << "result is " << task.result() << std::endl;

  logger.log(ts("Taken : "));

  return vu::VU_OK;
}
