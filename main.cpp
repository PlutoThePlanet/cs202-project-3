#include <iostream>
#include <string>
#include "Wav.h"
#include "Processor.h"

#include "limiter.h"
#include "echo.h"
#include "noiseGate.h"


const std::string testfile = "testing.wav";
const std::string echofile = "echos.wav";
const std::string limitfile = "limit.wav";
const std::string noisefile = "noise.wav";
int main() {
    const int max = 255;

    Wav wav;
    wav.readFile(testfile);
    Processor *echo = new Echo(660); //15 ms delay = 660 = (44,000 sample/sec = 44 samples/ms -> 44 sample/ms * 15 ms = 660 sample delay) //somone said echo 5000 ?
    echo->processBuffer(wav.getBuffer(),wav.getBufferSize());
    wav.writeFile(echofile);

    //Follow the pattern above to generate the limit and noise files
    //using the filenames provided

    Wav limit;
    limit.readFile(testfile);
    Processor *limiter = new Limiter();
    limiter->processBuffer(limit.getBuffer(),limit.getBufferSize());
    limit.writeFile(limitfile);

    Wav noise;
    noise.readFile(testfile);
    Processor *gate = new NoiseGate(20); //5% audio variation
    gate->processBuffer(noise.getBuffer(), noise.getBufferSize());
    noise.writeFile(noisefile);
    return 0;
}
