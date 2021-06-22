#if defined (_WIN32)
// TODO: winsock
//
#elif defined(unix) || defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
// TODO: unix socket
#include <sys/socket.h>
#include <sys/types.h>

#endif

