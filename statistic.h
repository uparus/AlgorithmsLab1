
#ifndef STATISTIC_H
#define STATISTIC_H

struct Statistic
{
    long long totalComparisons = 0;
    long long elementComparisons = 0;
    void reset() {
        totalComparisons = 0;
        elementComparisons = 0;
    }
};

#endif //STATISTIC_H
