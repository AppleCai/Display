#include "head.hpp"

/* key=j means stop HMI, but the transmit is keep */
/* key=s means stop transmit, so the HMI also stop */

int main(void)
{
  display* disp=new display;
  disp->run(disp);
  delete (disp);
  return 0;
}
 