#define ENV_SUPATH "/mss/init/bin"
#define ENV_PATH   "/mss/init/bin"
#define PW_CIPHER  "$6$"

/* musl does not do {u,b,w}tmp */
#undef UTMP_PATH
#define UTMP_PATH  "/dev/null"
#undef BTMP_PATH
#define BTMP_PATH  "/dev/null"
#undef WTMP_PATH
#define WTMP_PATH  "/dev/null"
