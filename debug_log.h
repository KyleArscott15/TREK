// aauthor Kyle Arscott

#ifndef DEBUG_H_
#define DEBUG_H_

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string>
#include <map>
#include <stack>
#include <queue>

// #include <cv.h>
#include <pthread.h>

// linux dependencies
#include <sys/inotify.h>

using namespace std;

// For DTOKEN* macros
// Note: you can update tokens while the program is running
//       by doing "echo "VID,GUI" > runtime/tokens.txt"
#define TOKEN_LENGTH  (3)
#define TOKEN(index) (1 << index)
#define NON (0)       // none
#define GEN (1 << 0)  // general debugging, all tokens ON
#define CON (1 << 1)  // continuous output
#define CAN (1 << 2)  // continuous and not-continouous output
#define MEM (1 << 3)  // working memory changes
#define GUI (1 << 4)  // input and output from the GUI
#define KBA (1 << 5)  // knowledge base
#define LAT (1 << 6)  // latex
// ... Create your own tokens!
#define DBG (1 << 31) // debugging the debugging facility itsel
#define TOKEN_ARRAY const char *tokens[] = \
{ "GEN", "CON", "CAN", "MEM", "GUI", "KBA", "LAT", "DBG" }

#define NUM_TOKENS (sizeof(tokens) / sizeof(char *))

#ifndef DEBUG
# define DNAMESPACE()
# define DDECLARE()
# define DINIT()
# define DPRINT(...)
# define DPRINTF()
# define DMETHOD()
# define DVAR(msg, var)
# define DSET_MASK(mask)
# define D(mask, arg ...)
# define DTT(mask)
# define DTRACE()
# define DSTACK_DUMP(fd)
# define CLOCK_INIT() {}
# define CLOCK_START() {}
# define CLOCK_STOP(msg) {}

#else // ifndef DEBUG

namespace debug {
// use this at the top of every source file that uses the following macros
# define DNAMESPACE() using namespace debug;

// do not use this. The places that need to use it already do.
# define DDECLARE() debug::log _logger

// do not use this.
# define DINIT() DDECLARE()

// simple flushed console output that does not use the debugger logger class
# define DPRINT(fmt) { fprintf(stdout, fmt); fflush(stdout); }
# define DPRINTF(fmt, args ...) { fprintf(stdout, fmt, args); fflush(stdout); }

// use this at the top of every function that you would want to show stack dump
# define DMETHOD() _logger.push(__FUNCTION__)

// use this if you wish to view a stackdump
# define DSTACK_DUMP(fd) _logger.stackDump(fd)

// pre-programmed dump of an objects value. Can be a primitive or Mat object etc
# define DVAR(msg, var) _logger.varVal(__FILE__,     \
                                       __FUNCTION__, \
                                       __LINE__,     \
                                       msg,          \
                                       var)
# define DTRACE() DPRINTF("[%s][%d]\n", __FUNCTION__, __LINE__)

/*
 * This next section defines the DTOKEN(token, msg) facility
 *
 * a)
 * To display continous:
 * -CON must be defined
 * -there must be another tag defined other than CON
 *
 * b)
 * To NOT display continous
 * -CON must not be defined
 * -there must be a tag defined
 *
 * c)
 * If CAN is defined in the mask:
 * -if CON is defined, printf if a) would print it
 * -if CON is not defined, printf if b) would print it
 */
# define RUNTIME_DEBUG_TOKEN_FILE   "./runtime/tokens.txt"
# define D(mask, ...) _logger.debugToken(mask, __VA_ARGS__)
# define DTT(mask) _logger.debugToken(mask,         \
                                      "[%s][%s]\n", \
                                      __FUNCTION__, \
                                      __LINE__)

# define USEC_IN_SEC  (1000000)
# define NSEC_IN_USEC (1000)
# define NSEC_IN_SEC  (NSEC_IN_USEC * USEC_IN_SEC)

# define CLOCK_INIT()          \
  struct timespec time_before; \
  struct timespec time_after;  \
  int  time        = 0;        \
  int  second_diff = 0;        \
  long nano_diff   = 0;
# define CLOCK_START() {                          \
    time_after.tv_sec   = 0;                      \
    time_after.tv_nsec  = 0;                      \
    time_before.tv_sec  = 0;                      \
    time_before.tv_nsec = 0;                      \
    clock_gettime(CLOCK_MONOTONIC, &time_before); \
}
# define CLOCK_STOP(msg) {                                   \
    clock_gettime(CLOCK_MONOTONIC, &time_after);             \
    second_diff = time_after.tv_sec - time_before.tv_sec;    \
    nano_diff   = time_after.tv_nsec - time_before.tv_nsec;  \
    time        = USEC_IN_SEC - nano_diff / NSEC_IN_USEC;    \
    if (time > USEC_IN_SEC) { time = 0; }                    \
    DPRINTF("%-35s[%-10d] second_diff[%d] nano_diff[%ld]\n", \
            msg,                                             \
            time,                                            \
            second_diff,                                     \
            nano_diff);                                      \
}

class func_t {
public:

  func_t() {}

  ~func_t() {}

  int numEntries;
  std::string funcName;
};

# define map_t map < string, func_t >

class log {
private:

  int   DMASK;
  map_t fun;
  stack<func_t> funStack;
  queue<func_t> funQueue;

public:

  void debugPrint(const char *fmt, va_list argp) {
    vprintf(fmt, argp);
    fflush(stdout);
  }

  int tokenMatch(const char *token_str) {
    int token = NON;

    TOKEN_ARRAY;
    unsigned count = 0;

    while (count < NUM_TOKENS) {
      if (strncmp(token_str, tokens[count], TOKEN_LENGTH) == 0) {
        token = TOKEN(count);
        break;
      }
      count++;
    }
    return token;
  }

  void extractSetTokens(FILE *token_file) {
    // file should only be one line, comma seperated
    int mask     = NON;
    char   *line = NULL;
    size_t  len  = 0;
    ssize_t read;

    read = getline(&line, &len, token_file);

    if (read != -1) {
      char *token;
      token = strtok(line, ",");

      while (token != NULL) {
        mask |= tokenMatch(token);
        token = strtok(NULL, ",");
      }
      setDMASK(mask);
    }
  }

# define BUF_LEN (sizeof(struct inotify_event) + \
                  strlen(RUNTIME_DEBUG_TOKEN_FILE) + 1)

  // a seperate thread that watches the debug token file for run-time updates
  void* runtime_token_checker(void *) {
    FILE   *token_file;
    int     inotify_fd;
    ssize_t numRead;
    char    buf[BUF_LEN];
    struct inotify_event *event;

    // KA not portable, inotify() is linux only
    inotify_fd = inotify_init();
    inotify_add_watch(inotify_fd, RUNTIME_DEBUG_TOKEN_FILE, IN_CLOSE_WRITE);

    goto startup_read;

    for (;;) {
      bzero(buf, BUF_LEN);
      numRead = read(inotify_fd, buf, BUF_LEN);

      if (numRead < 0) {
        DPRINT(
          "Runtime token checker read() returned no information. Exiting. \n");
        exit(-1);
      }

      event = (struct inotify_event *)buf;

      if (event->mask & IN_CLOSE_WRITE) {
startup_read:
        DPRINT("Reading runtime token file...\n");
        token_file = fopen(RUNTIME_DEBUG_TOKEN_FILE, "r");

        if (token_file == NULL) {
          DPRINTF("Error opening [%s]\n", RUNTIME_DEBUG_TOKEN_FILE);
          continue;
        }
        extractSetTokens(token_file);
        fclose(token_file);
      }
    }
    pthread_exit(NULL);
    return 0;
  }

  static void* runtime_token_checker_wrapper(void *context) {
    ((log *)context)->runtime_token_checker(context);
    return 0;
  }

  void setDMASK(int mask) {
    DMASK = mask;
  }

  void debugToken(int mask, const char *fmt, ...) {
    if (
      (((DMASK)&((mask) & ~CON) & ((mask) & ~CAN))
       &&
       (((DMASK)&CAN) ||
        ((((DMASK)&CON) && ((mask) & CON))
         ||
         (!((DMASK)&CON) && !((mask) & CON)))
       ))
      || (mask & GEN)
      ) {
      va_list argp;
      va_start(argp, fmt);
      debugPrint(fmt, argp);
      va_end(argp);
    }
  }

  // precision: CV_8UC3 = CV_[# of bits per item][signed or
  // unsigned]C[#channels]

  /*
     void varVal(const char   *file,
              const char   *func,
              const int     line,
              const char   *msg,
              const cv::Mat mat) {
     int chan  = mat.channels();
     int rows  = mat.rows;
     int cols  = mat.cols;
     int depth = mat.depth();
     int mem   = rows * cols * chan * depth;

     DPRINTF("[%s] %s():%d channels[%d] %dx%d precision[%d]bits
        memory[%d]bits\n",
            msg,
            func,
            line,
            chan,
            rows,
            cols,
            depth,
            mem);
     }
   */
  void push(const char *func) {
    std::string funcName(func);
    map_t::iterator it = fun.find(funcName);

    func_t f;

    f.numEntries = 1;
    f.funcName   = funcName;

    if (it != fun.end()) {
      (it->second.numEntries) += 1;
    } else {
      fun[funcName] = f;
    }
    funStack.push(f);
    funQueue.push(f);
  }

  void pop(const char *func) {
    funStack.pop();

    // calculate function time
  }

  void stackDump(FILE *fd) {
    while (!funQueue.empty()) {
      fprintf(fd, "%s\n", funQueue.front().funcName.c_str());
      funQueue.pop();
    }

    /*
       while(!funStack.empty()){
         fprintf(fd, "%s\n", funStack.top().funcName.c_str());
         funStack.pop();
       }*/

    // for(map_t::iterator it = fun.begin(); it!=fun.end(); it++) {
    //	printf("");
    // iterator->first = key
    // iterator->second = value
    // Repeat if you also want to iterate through the second map.
    // }
    fflush(fd);
  }

public:

  log() {
    DMASK = NON;
    int ret = 0;
    pthread_t tokenThread;
    ret = pthread_create(&tokenThread, NULL, runtime_token_checker_wrapper, this);

    if (ret != 0) {
      DPRINT("Error creating runtime token-checker thread. Exiting. \n");
      exit(-1);
    }
  }

  ~log() {
    pthread_exit(NULL);

    // funStack.clear();
    // funQueue.clear();
    fun.clear();
  }
};
}

extern debug::log _logger;

#endif // DEBUG

#endif // DEBUG_H_
