#include "emulator.h"
#include "utils.h"


int main(int argc, char *argv[]){

    struct Emulator emulator;
    init_emulator(&emulator, argc, argv);
    run_emulator(&emulator);

    LOG(INFO, "Play time %d min", (uint64_t)emulator.time_diff / 60000);
    LOG(INFO, "Frame rate: %.4f fps", (double)(emulator.ppu.frames * 1000) / emulator.time_diff);
    LOG(INFO, "Audio sample rate: %.4f Hz", (double)(emulator.apu.sampler.samples * 1000) / emulator.time_diff);
    LOG(INFO, "CPU clock speed: %.4f MHz", ((double)emulator.cpu.t_cycles / (1000 * emulator.time_diff)));

    free_emulator(&emulator);

    return 0;
}
/*
int main() {
    char* s1 = "nes";
    //char* s2 = "C:\\Users\\iProgramInCpp\\NES Tools\\FamiStudio421-WinPortableExe\\mysongs\\ch1.nsf";
    //char* s2 = "C:\\Users\\iProgramInCpp\\NES Tools\\FamiStudio421-WinPortableExe\\mysongs\\ch2.nsf";
    //char* s2 = "C:\\Work\\celestenes\\celeste.nes";
    char* s2 = "C:\\Users\\iProgramInCpp\\Downloads\\famidash.nes2\\famidash.nes";
    
    char* tbl[] = { s1, s2, NULL };

    return main2(2, tbl);
}
*/
