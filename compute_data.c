#include <stdio.h>
#include <math.h>



int main(int argc, char *argv[]) {
    FILE *file;
    float value, sum = 0, mean, variance = 0;
    int count = 0;

    if (argc < 2) {
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    while (fscanf(file, "%f", &value) == 1) {
        sum += value;
        count++;
    }

    mean = sum / count;

    fseek(file, 0, SEEK_SET);

    while (fscanf(file, "%f", &value) == 1) {
        variance += pow(value - mean, 2);
    }

    variance /= count;
    printf("Nb values: %d\n", count);
    printf("Mean: %f\n", mean);
    printf("Variance: %f\n", variance);
    double stddev = sqrt(variance);
    double margin_of_error = 1.96 * (stddev / sqrt(count));
    double lower_bound = mean - margin_of_error;
    double upper_bound = mean + margin_of_error;

    printf("95%% Confidence interval: [%f, %f] seconds\n", lower_bound/1000000, upper_bound/1000000); 
    
    fclose(file);
    return 0;
}

