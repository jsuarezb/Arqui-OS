#ifndef _API_H_
#define _API_H_

signed int read(unsigned int fd, char * buf, int count);
signed int write(unsigned int fd, const char * buf, int count);
int getRTC(int content);
int setRCT(int content, int value);

#endif
