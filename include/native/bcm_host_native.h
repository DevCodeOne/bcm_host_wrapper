#pragma once

#ifdef USE_BCM_HOST
// TODO include real bcm_host
#else
int bcm_host_init();
int bcm_host_deinit();

#endif
