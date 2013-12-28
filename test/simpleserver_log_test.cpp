#include "simpleserver_log.h"
using namespace simpleserver;

#include <stdio.h>

int main()
{
  printf("----- Testing Log Interface -----\n");
  SET_LOG_TYPE(DEBUG, true);

  LOG(ERROR, "Error Message: %d", __LINE__);
  LOG(WARNING, "Warning Message: %d", __LINE__);
  LOG(INFO, "Info Message: %d", __LINE__);
  LOG(DEBUG, "Debug Message: %d", __LINE__);
  LOG(STATS, "Stats Message: %d", __LINE__);

  printf("----- Turning Off Error, Warning, and Info -----\n");
  SET_LOG_TYPE(ERROR, false);
  SET_LOG_TYPE(WARNING, false);
  SET_LOG_TYPE(INFO, false);

  LOG(ERROR, "Error Message: %d", __LINE__);
  LOG(WARNING, "Warning Message: %d", __LINE__);
  LOG(INFO, "Info Message: %d", __LINE__);
  LOG(DEBUG, "Debug Message: %d", __LINE__);
  LOG(STATS, "Stats Message: %d", __LINE__);

  printf("----- Turning All On, Then Debug Off -----\n");
  SET_LOG_TYPE(ERROR, true);
  SET_LOG_TYPE(WARNING, true);
  SET_LOG_TYPE(INFO, true);
  SET_LOG_TYPE(DEBUG, true);
  SET_LOG_TYPE(STATS, true);
  SET_LOG_TYPE(DEBUG, false);

  LOG(ERROR, "Error Message: %d", __LINE__);
  LOG(WARNING, "Warning Message: %d", __LINE__);
  LOG(INFO, "Info Message: %d", __LINE__);
  LOG(DEBUG, "Debug Message: %d", __LINE__);
  LOG(STATS, "Stats Message: %d", __LINE__);

  printf("----- Logging to file in /tmp -----\n");

  SET_LOG_FILE("/tmp/log_test");
  SET_LOG_TYPE(DEBUG, true);

  LOG(ERROR, "Error Message: %d", __LINE__);
  LOG(WARNING, "Warning Message: %d", __LINE__);
  LOG(INFO, "Info Message: %d", __LINE__);
  LOG(DEBUG, "Debug Message: %d", __LINE__);
  LOG(STATS, "Stats Message: %d", __LINE__);

  return 0;
}
