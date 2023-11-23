#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>

int main() {

    // Konštanty
    double g = 9.81, R = 8.314, p0 = 101325.0, M = 0.029;

    // Cas
    double t = 0;

    // Boolovská premenná pre ukoncenie cyklu
    bool breaker = true;

    // Vyska v metroch
    double z = 0, z1 = 0, z0 = 10000; // m

    // Rychlosti
    double v = 0, v1 = 0, v0 = 0, vn = 0; // m/s

    // Hmotnosť
    double m = 80.0; //kg

    // Prierez S
    int S = 2;

    // Koeficient odporu C
    double C = 0.5;

    // Hustota vzduchu
    double p = 0.04, g0 = 0;

    // K a h
    double K = 0, h = 0.01;

    // Termodinamická teplota
    double T = 273.16;

    // prepínanie
    bool first = false, second = false, third = false, fourth = true;

    // Subor pre ukladanie
    FILE * f;

    // Cyklus pre konštantné p(z)
    if (first) {
        f = fopen("vystup.dat", "w");
        vn = sqrt((2 * m * g) / (p * C * S));
        printf("Vn je: %.2lf\n", vn);

        z = z0 - ((vn * vn) / g) * log(cosh(g * (t / 1000.0) / vn));
        for (int i = 0; breaker; ++i) {
            // Kód
            if (z <= 0) breaker = false;


            // Výpočet
            v = (v0 - vn * tanh(g * (t / 1000.0) / vn)) / (1 - v0 / vn * tanh(g * (t / 1000.0) / vn));
            z = z0 - ((vn * vn) / g) * log(cosh(g * (t / 1000.0) / vn));
            printf("Vyska: %.2lf a rychlost je: %.2f\n", z, v);

            fprintf(f, "%.3lf %.3f %.3f\n", (t / 1000.0), -1 * v, z);
            // Cas
            usleep(20);
            t += 20;
        }
    }
    // eulerová metóda
    else if (second) {
        f = fopen("vystup.dat", "w");
        K = 0.5 * (C * S * p / m);
        z1 = z0 + h * (v0);
        printf("K je: %.2lf\n", K);
        for (int i = 0; breaker; ++i) {
            // Kód

            v1 = v0 + h * (-g - K * fabs(v0) * v0);
            z1 = z0 + h * (v0);

            if (z1 <= 0) {
                breaker = false;
            }

            v0 = v1;
            z0 = z1;
            printf("Vyska: %.2lf a rychlost je: %.2f\n", z1, v1);

            fprintf(f, "%.3f %.3f %.3f\n", t, -1 * v1, z1);

            // Cas
            usleep(20);
            t += h;
        }
    }
    // p(z) je závislé
    else if (third) {
        f = fopen("vystup.dat", "w");
        double k = ((M * g)/( R * T));
        g0 = (M / (R * T)) * p0;
        for (int i = 0; breaker; ++i) {
            // Kód

            vn = sqrt((2 * m * g) / (p * C * S));

            v = (v0 - vn * tanh(g * (t / 1000.0) / vn)) / (1 - v0 / vn * tanh(g * (t / 1000.0) / vn));
            z = z0 - ((vn * vn) / g) * log(cosh(g * (t / 1000.0) / vn));
            fprintf(f, "%.3lf %.3f %.3f\n", (t / 1000.0), -1 * v, z);

            //printf("Vyska: %.2lf a rychlost je: %.2lf a vn je %.2lf\n", z, v, vn);

            if (z <= 0) {
                breaker = false;
            }

            p = g0 * exp(-1 * k * z);
            printf("z = %.2lf, v = %.2lf, vn = %.2lf\n", z, v, vn);

            // Cas
            usleep(20);
            t += 20;
        }
    }
    else if (fourth) {
        f = fopen("vystup.dat", "w");
        K = 0.5 * (C * S * p / m);
        z1 = z0 + h * (v0);
        double k = ((M * g)/( R * T));
        printf("K je: %.2lf\n", K);
        double K0 = K;
        for (int i = 0; breaker; ++i) {
            // Kód

            v1 = v0 + h * (-g - K * fabs(v0) * v0);
            z1 = z0 + h * (v0);

            K = K0 * exp(-1 * k * z1);

            if (z1 <= 0) {
                breaker = false;
            }

            v0 = v1;
            z0 = z1;
            printf("Vyska: %.2lf a rychlost je: %.2f\n", z1, v1);

            fprintf(f, "%.3f %.3f %.3f\n", t, -1 * v1, z1);

            // Cas
            usleep(20);
            t += h;
        }
    }

    fclose(f);

    return 0;
}