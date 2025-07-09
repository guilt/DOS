# Sed script to add DJGPP specific issues to config.h.

/.*#undef HAVE_MBSINIT.*/ c\
#define HAVE_MBSINIT 1

/.*#undef HAVE_MBRTOWC.*/ c\
#define HAVE_MBRTOWC 1


$ a\
\
/*\
 *  Provide missing functions through libsupp.a.\
 */\
#ifdef __DJGPP__\
# include "_libsupp.h"\
#endif
