#include "head.hpp"
#include "key.hpp"
#include "server.hpp"

/* key=j means stop HMI, but the transmit is keep */
/* key=s means stop transmit, so the HMI also stop */

int main(void)
{
  ServerEx ser;
  using namespace std;
  thread t1(&ServerEx::server, ser);
  cout << "start" << endl;
  thread t2(&keysearch::KeyDetect, ref(k));
  t1.join();
  t2.join();
  getchar();
  return 0;
}
