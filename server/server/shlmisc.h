#ifndef SHLMISC_H_
#define SHLMISC_H_

char *Ship(shiptype *);
void grant(int, int, int );
void governors(int, int, int);
void do_revoke(racetype *, int, int);
int start_shiplist(int, int, char const *);
int do_shiplist(shiptype **, int *);
int in_list(int, char *, shiptype *, int *);
void fix(int, int);
int match(char *, char const *);
int matchic(char *, char const *);
void DontOwnErr(int, int, int);
int enufAP(int, int, unsigned int, int);

#ifdef CHAP_AUTH
int Getracenum(char *, char *, int *, int *, char *, int);

#else

int Getracenum(char *, char *, int *, int *);
#endif

int GetPlayer(char *);
void allocateAPs(int, int, int);
void deductAPs(int, int, int, int, int);
void list(int, int);
double morale_factor(double);
void no_permission(int, int, char const *, int);
void no_permission_thing(int, int, char const *, int);
int authorized(int, shiptype *);
int authorized_in_star(int, int, startype *);
int match2(char *, char const *, int);

#endif /* SHLMISC_H_ */
