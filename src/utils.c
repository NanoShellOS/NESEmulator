#include "utils.h"
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <math.h>
#include <stdio.h>
//#include <SDL.h>
#include <string.h>

#ifndef PI
# define PI	3.14159265358979323846264338327950288
#endif


size_t file_size(FILE* file){
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    rewind(file);
    return size;
}

void LOG(enum LogLevel logLevel, const char* fmt, ...){
    if(TRACER)
        return;
    if(logLevel >= LOGLEVEL) {
#ifdef __ANDROID__
        android_LogPriority priority;
        switch (logLevel) {
            case INFO:
                priority = ANDROID_LOG_INFO;
                break;
            case DEBUG:
                priority = ANDROID_LOG_DEBUG;
                break;
            case ERROR:
                priority = ANDROID_LOG_ERROR;
                break;
            case WARN:
                priority = ANDROID_LOG_WARN;
                break;
            default:
                priority = ANDROID_LOG_UNKNOWN;
        }
        va_list ap;
        va_start(ap, fmt);
        __android_log_vprint(priority, TAG, fmt, ap);
        va_end(ap);
#else
        switch (logLevel) {
            case INFO:
                printf("INFO  > ");
                break;
            case DEBUG:
                printf("DEBUG > ");
                break;
            case ERROR:
                printf("ERROR > ");
                break;
            case WARN:
                printf("WARN  > ");
                break;
            default:
                printf("LOG   > ");
        }
        va_list ap;
        va_start(ap, fmt);
        vprintf(fmt, ap);
        va_end(ap);
        printf("\n");
        fflush(stdout);
#endif
    }
}

void to_pixel_format_(const uint32_t* restrict in, uint32_t* restrict out, size_t size){
    for(size_t i = 0; i < size; i++) {
        out[i] = in[i];
    }
}

#if 0
void fft(complx *v, int n, complx *tmp) {
    if(n <= 1)
        return;
    /* otherwise, do nothing and return */
    int k, m;
    complx z, w, *vo, *ve;
    ve = tmp;
    vo = tmp + n / 2;
    for (k = 0; k < n / 2; k++) {
        ve[k] = v[2 * k];
        vo[k] = v[2 * k + 1];
    }
    fft(ve, n / 2, v); /* FFT on even-indexed elements of v[] */
    fft(vo, n / 2, v); /* FFT on odd-indexed elements of v[] */
    for (m = 0; m < n / 2; m++) {
        w.Re = cos(2 * PI * m / (double) n);
        w.Im = -sin(2 * PI * m / (double) n);
        z.Re = w.Re * vo[m].Re - w.Im * vo[m].Im; /* Re(w*vo[m]) */
        z.Im = w.Re * vo[m].Im + w.Im * vo[m].Re; /* Im(w*vo[m]) */
        v[m].Re = ve[m].Re + z.Re;
        v[m].Im = ve[m].Im + z.Im;
        v[m + n / 2].Re = ve[m].Re - z.Re;
        v[m + n / 2].Im = ve[m].Im - z.Im;
    }
}
#endif

char *get_file_name(char *path) {
    char *pfile = path + strlen(path);
    for (; pfile > path; pfile--){
        if ((*pfile == '\\') || (*pfile == '/')){
            pfile++;
            break;
        }
    }
    return pfile;
}

uint64_t next_power_of_2(uint64_t num) {
    uint64_t power = 1;
    while(power < num)
        power*=2;
    return power;
}

void quit(int code) {
#if EXIT_PAUSE
    printf("Press any key to exit . . .");
    getchar();
#endif
    exit(code);
}
