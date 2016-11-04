#include "report.h"

Report make_report(void) {
  Report report;
  report.time = 0;
  report.nodes = 0;
  report.height = 0;
  report.factor = 0;
  report.comparisons = 0;
  report.rotations = 0;
  return report;
}
