#ifdef SMDEBUG
#define SMTRANS(T) {printf("T->"); (*T)();}
#else
#define SMTRANS(T) (*T)();
#endif
