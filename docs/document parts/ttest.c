/*


  Compile with:                    gcc ttest.c -o tt -lm
  or, if that doesn't work, with:  /packages/gnu/bin/gcc ttest.c -o tt -lm




   Simple statistics -- the t test.

 Say you run a GA 8 times on a minimisation problem adnd you get these results
 (best from each run):

 15 8.5 7 19 10 12 11 8.4

 Say you run hillcliming 10 times on the same problem and you get these
results:

 14.1 12.1 24 26 19.3 11.4 11.1 14.1 6.2 11.8


  Which seems to be the better algorithm ?

 If you put these results into separate files, called say `ga' and `hc', then
you
 can use this program to run a `t test'.  Data points in the files must be
separated
by whitespace (new lines, tabs,  spaces, or any mixture). On this example,
running:

  ./tt ga hc

 gives the following output:

------------------------------------------------------------
 file ga:  8 points, mean 11.3625, variance 15.7084, standard dev 3.96338
 file hc:  10 points, mean 15.01, variance 38.4854, standard dev 6.20366
 t value :   -1.43988

 t relates to confidence that first file results are better than
 second file results. If minimising, t may be negative. Just multiply
 it by -1

 In this case, with a total of 18 data points, the t value you need in order to
have
     90% confidence in the ga results being better than the hc results is >=
1.337
 For 95% confidence, the t value must be >= 1.746
 For 99% confidence, the t value must be >= 2.583
------------------------------------------------------------
                     
------------------------------------------------------------         
  So, we can have 90% confidence that the GA is better on the basis of these 
results.
  You can have any number of data points, but at least two in each file. With 
small numbers
 of points, it is of course much harder to get confident decisions. Eg: running the test
 on just the first three points in each file gives:
------------------------------------------------------------
file ga:  3 points, mean 10.1667, variance 18.0833, standard dev 4.25245
file hc:  3 points, mean 16.7333, variance 40.6033, standard dev 6.37207
t value :   -1.48469
t relates to confidence that first file results are better than
second file results. If minimising, t may be negative. Just multiply
it by -1
 In this case, with a total of 6 data points, the t value you need in order to 
have
 90% confidence in the ga results being better than the hc results is >= 1.533
 For 95% confidence, the t value must be >= 2.132
 For 99% confidence, the t value must be >= 3.747
                    
------------------------------------------------------------                 
*/
/* **************************************************/
/*                                                  */
/*  compile with:  gcc ttest.c -o tt -lm            */
/*                                                  */
/*  usage:   ./tt <file1> <file2>                   */
/*                                                  */
/****************************************************/
#include <stdlib.h>
36%#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#define TRUE 1
#define FALSE 0
#define MAXDATA 5000
double getdouble(FILE *, double *, int);
double a[MAXDATA],  b[MAXDATA];
double get_tvalue(int , int );
FILE   *ap, *bp;
int    an,  bn;
int n;
extern double sqrt(double);
void main(int argc, char **argv)
{
  int i;
  double am, bm, asv, bsv, sv, s, t, x, lsasv, lsbsv, ls;
   /* get the data in */
   ap = fopen(argv[1], "r");
   bp = fopen(argv[2], "r");
   get_input(ap, a);  an = n; fclose(ap);
   get_input(bp, b);  bn = n; fclose(bp);
  /* work out the means */
 am=0; for(i=0;i<an;i++) am+=a[i];  am /= (double)(an);
 bm=0; for(i=0;i<bn;i++) bm+=b[i];  bm /= (double)(bn);
  
  /* work out dual sample variance */
  asv = 0; for(i=0;i<an;i++) asv += ((a[i]-am)*(a[i]-am));
  lsasv = asv/((double)(an)-1.0);
  
48%  lsasv = asv/((double)(an)-1.0);
  
  bsv = 0; for(i=0;i<bn;i++) bsv += ((b[i]-bm)*(b[i]-bm));
  lsbsv = bsv/((double)(bn)-1.0);
  sv = (asv + bsv) / (double)(an + bn - 2);
  
  s = sqrt(sv);
 
  t = (am - bm) / ( s * sqrt( (1.0/an)  + (1.0/bn) ) ) ;
   
  ls = (am - bm) / ( sqrt ( (lsasv/an) + (lsbsv/bn)));
   printf(" file %s:  %d points, mean %g, variance %g, standard dev %g\n",
                 argv[1], an, am, asv/(double)(an-1), 
sqrt(asv/(double)(an-1)));
   printf(" file %s:  %d points, mean %g, variance %g, standard dev %g\n",
                             argv[2], bn, bm, bsv/(double)(bn-1), 
sqrt(bsv/(double)(bn-1)));
  
   printf(" t value :   %g \n\n", t);
   printf(" t relates to confidence that first file results are better than 
\n");
   printf(" second file results. If minimising, t may be negative. Just 
multiply\n");
   printf(" it by -1 \n\n");
printf("  In this case, with a total of %d data points, the t value you need in order to have\n",
an+bn);
printf("       90%% confidence in the %s results being better than the %s 
results is >= %g \n",
         argv[1], argv[2], get_tvalue((an+bn)-2, 90));
printf("   For 95%% confidence, the t value must be >= %g \n", 
get_tvalue((an+bn)-2,95));
printf("   For 99%% confidence, the t value must be >= %g \n", 
get_tvalue((an+bn)-2,99));
 
if ((an>=30) && (bn>=30)) printf("\n\n Large sample statistic is %g\n", ls);
59%if ((an>=30) && (bn>=30)) printf("\n\n Large sample statistic is %g\n", ls);
}
double get_tvalue(int npoints, int conf)
{
  double r;
  switch(npoints){
  case 1: if(conf==90) r = 3.078; else if(conf==95) r = 6.314 ; else r = 
31.821; break;
  case 2: if(conf==90) r = 1.886; else if(conf==95) r = 2.920 ; else r = 6.965; break;
  case 3: if(conf==90) r = 1.638; else if(conf==95) r = 2.353 ; else r = 4.541; break;
  case 4: if(conf==90) r = 1.533; else if(conf==95) r = 2.132 ; else r = 3.747; break;
  case 5: if(conf==90) r = 1.476; else if(conf==95) r = 2.015 ; else r = 3.365; break;
  case 6: if(conf==90) r = 1.440; else if(conf==95) r = 1.943 ; else r = 3.143; break;
  case 7: if(conf==90) r = 1.415; else if(conf==95) r = 1.895 ; else r = 2.998; break;
  case 8: if(conf==90) r = 1.397; else if(conf==95) r = 1.860 ; else r = 2.896; break;
  case 9: if(conf==90) r = 1.383; else if(conf==95) r = 1.833 ; else r = 2.821; break;
  case 10: if(conf==90) r = 1.372; else if(conf==95) r = 1.812 ; else r = 
2.764; break;
  case 11: if(conf==90) r = 1.363; else if(conf==95) r = 1.796 ; else r = 
2.718; break;
  case 12: if(conf==90) r = 1.356; else if(conf==95) r = 1.782 ; else r = 
2.681; break;
  case 13: if(conf==90) r = 1.350; else if(conf==95) r = 1.771 ; else r = 
2.650; break;
  case 14: if(conf==90) r = 1.345; else if(conf==95) r = 1.761 ; else r = 
2.624; break;
  case 15: if(conf==90) r = 1.341; else if(conf==95) r = 1.753 ; else r = 
2.602; break;
  case 16: if(conf==90) r = 1.337; else if(conf==95) r = 1.746 ; else r = 
2.583; break;
  case 17: if(conf==90) r = 1.333; else if(conf==95) r = 1.740 ; else r = 
2.567; break;
  case 18: if(conf==90) r = 1.330; else if(conf==95) r = 1.734 ; else r = 
2.552; break;
  case 19: if(conf==90) r = 1.328; else if(conf==95) r = 1.729 ; else r = 
2.539; break;
71%  case 19: if(conf==90) r = 1.328; else if(conf==95) r = 1.729 ; else r = 
2.539; break;
  case 20: if(conf==90) r = 1.325; else if(conf==95) r = 1.725 ; else r = 
2.528; break;
  case 21: if(conf==90) r = 1.323; else if(conf==95) r = 1.721 ; else r = 
2.518; break;
  case 22: if(conf==90) r = 1.321; else if(conf==95) r = 1.717 ; else r = 
2.508; break;
  case 23: if(conf==90) r = 1.319; else if(conf==95) r = 1.714 ; else r = 
2.500; break;
  case 24: if(conf==90) r = 1.318; else if(conf==95) r = 1.711 ; else r = 
2.492; break;
  case 25: if(conf==90) r = 1.316; else if(conf==95) r = 1.708 ; else r = 
2.485; break;
  case 26: if(conf==90) r = 1.315; else if(conf==95) r = 1.706 ; else r = 
2.479; break;
  case 27: if(conf==90) r = 1.314; else if(conf==95) r = 1.703 ; else r = 
2.473; break;
  case 28: if(conf==90) r = 1.313; else if(conf==95) r = 1.701 ; else r = 
2.467; break;
  case 29: if(conf==90) r = 1.311; else if(conf==95) r = 1.699 ; else r = 
2.462; break;
  default: if(conf==90) r = 1.282; else if(conf==95) r = 1.645 ; else r = 
2.326; break;
  }
return(r);
}
int get_input(FILE *f, double *arr)
{
  double v;
  n = 0;
  while(getdouble(f, &v, FALSE)!=0) arr[n++]=v;
}
/*
 *
 * Peter Ross' getint etc functions.
 */
83%/***************************************************************/
/* Get the next number from the input: put it in the location  */
/* addressed by second argument. This function returns 0 on    */
/* EOF. If stopateol is true, it returns -1 when it hits \n    */
/* (after which some other procedure has to read past the \n), */
/* otherwise it continues looking for the next number.         */
/* A number has an optional sign, perhaps followed by digits,  */
/* perhaps followed by a decimal point, perhaps followed by    */
/* more digits. There must be a digit somewhere for it to count*/
/* as a number. So it would read any of:                       */
/*  -.5                                                        */
/*  -0.5                                                       */
/*  -.5.7                                                      */
/* as minus-a-half. In the last case, it would read .7 next    */
/* time around.                                                */
/*   There doesn't seem to be a neat and reliable way to do    */
/* all this, including stopateol, using scanf?                 */
/***************************************************************/
double 
getdouble (FILE *file, double *valaddr, int stopateol)
{
  int c;
  int found = FALSE, indecimal = FALSE;
  int sign = +1;
  double n = 0.0, p = 1.0;
  /* First find what looks like start of a number - the first digit. */
  /* And note any sign and whether we just passed a decimal point.   */  
  do {
    c = fgetc(file);
    if(c == EOF) return (0);
    else if(stopateol && c =='\n') return(-1);
    else if(c == '+' || c == '-') {
      sign = (c == '+')? +1 : -1;
      c = fgetc(file);
      if(c == EOF) return (0);
      else if(stopateol && c =='\n') return(-1);
    }
    if(c == '.') {
      indecimal = TRUE;
      c = fgetc(file);
      if(c == EOF) return (0);
      else if(stopateol && c =='\n') return(-1);
    }
    if(c >= '0' && c <= '9') {
      found = TRUE;
    } else {
95%      found = TRUE;
    } else {
      sign = +1;
      indecimal =  FALSE;
    }
  } while(!found);
  /* Now we've got digit(s) ... */
  do {
    n = 10.0*n + c - '0';
    p = 10.0*p;
    c = fgetc(file);
    if((c < '0') || (c > '9')) {
      found = FALSE;
      /* We've run out. If we already saw a decimal point, return now */
      if(indecimal) {
        if(c != EOF) ungetc(c,file);
        *valaddr =  sign * n/p;
        return(1);
      } else p = 1.0;
    }
  } while(found);
  /* We ran out and we didn't see a decimal point, so is this a decimal? */
  if(c != '.') {
    /* No, give it back to caller */
    if(c != EOF) ungetc(c,file);
    *valaddr = sign * n;
    return(1);
  } else {
    /* It is. Step past it, carry on hoping for more digits */
    c = fgetc(file);
    while(c >= '0' && c <= '9') {
      n = 10.0*n + c - '0';
      p = p*10.0;
      c =  fgetc(file);
    }
    /* We've run out of digits but we have a number to give */
    if(c != EOF) ungetc(c,file);
    *valaddr = sign * n/p;
    return(1);
  }
}
/* Use getdouble() above but convert result to int. */
int 
getint (FILE *f, int *valaddr, int stopateol)
{
  int r;
END{
  int r;
  double x;
  r = getdouble(f,&x,stopateol);
  *valaddr = (int)x;
  return(r);
}
/* Use getdouble above but convert result to long. */
int 
getlong (FILE *f, long *valaddr, int stopateol)
{
  int r;
  double x;
  r = getdouble(f,&x,stopateol);
  *valaddr = (long)x;
  return(r);
}

