#ifndef REPORT_H
#define REPORT_H

typedef struct Report {
  unsigned long time;
  unsigned long nodes;
  unsigned long height;
  unsigned long factor;
  unsigned long comparisons;
  unsigned long rotations;
} Report;

Report report_create(void);

void report_clock_start(Report *report);

void report_clock_stop(Report *report);

#endif
