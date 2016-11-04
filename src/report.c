#include "report.h"
#include <time.h>

Report report_create(void) {
  Report report;
  report.time = 0;
  report.nodes = 0;
  report.height = 0;
  report.factor = 0;
  report.comparisons = 0;
  report.rotations = 0;
  return report;
}

void report_clock_start(Report *report) { report->time = clock(); }

void report_clock_stop(Report *report) {
  report->time = 1000 * (clock() - report->time) / CLOCKS_PER_SEC;
}
