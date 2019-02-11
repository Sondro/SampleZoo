/*
FILE: main.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/8/2019
*/

#define _CRT_SECURE_NO_WARNINGS // for stb

#include <stdio.h>

#include "samples/samples.h"
#include "tests/tests.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"


int main(int argc, char **argv)
{
    // Regular sampling testing
    {
        std::vector<float> samples;
        FILE* file = fopen("output/samples/_1d/regular/discrepancy.txt", "w+b");

        Samples::_1d::Regular::Regular(samples, 16);
        Tests::_1d::Numberline::MakeNumberline("output/samples/_1d/regular/regular.png", samples, 512);

        fprintf(file, "%zu samples\r\n\r\n", samples.size());

        fprintf(file, "Regular:\r\n  Discrepancy: %0f\r\n  Wrap: %0f\r\n\r\n",
            Tests::_1d::Discrepancy::CalculateDiscrepancy(samples),
            Tests::_1d::Discrepancy::CalculateDiscrepancyWrapAround(samples)
        );

        Samples::_1d::Regular::RegularCentered(samples, 16);
        Tests::_1d::Numberline::MakeNumberline("output/samples/_1d/regular/regularcentered.png", samples, 512);

        fprintf(file, "RegularCentered:\r\n  Discrepancy: %0f\r\n  Wrap: %0f\r\n\r\n",
            Tests::_1d::Discrepancy::CalculateDiscrepancy(samples),
            Tests::_1d::Discrepancy::CalculateDiscrepancyWrapAround(samples)
        );

        Samples::_1d::Regular::RegularCenteredOffset(samples, 16);
        Tests::_1d::Numberline::MakeNumberline("output/samples/_1d/regular/regularcenteredoffset.png", samples, 512);

        fprintf(file, "RegularCenteredOffset:\r\n  Discrepancy: %0f\r\n  Wrap: %0f\r\n\r\n",
            Tests::_1d::Discrepancy::CalculateDiscrepancy(samples),
            Tests::_1d::Discrepancy::CalculateDiscrepancyWrapAround(samples)
        );

        fclose(file);
    }

    // Irrational number testing
    {
        std::vector<float> samples;
        FILE* file = fopen("output/samples/_1d/irrational_numbers/discrepancy.txt", "w+b");

        Samples::_1d::IrrationalNumbers::GoldenRatio(samples, 16);
        Tests::_1d::Numberline::MakeNumberline("output/samples/_1d/irrational_numbers/golden_ratio.png", samples, 512);

        fprintf(file, "%zu samples\r\n\r\n", samples.size());

        fprintf(file, "GoldenRatio:\r\n  Discrepancy: %0f\r\n  Wrap: %0f\r\n\r\n",
            Tests::_1d::Discrepancy::CalculateDiscrepancy(samples),
            Tests::_1d::Discrepancy::CalculateDiscrepancyWrapAround(samples)
        );

        Samples::_1d::IrrationalNumbers::Pi(samples, 16);
        Tests::_1d::Numberline::MakeNumberline("output/samples/_1d/irrational_numbers/pi.png", samples, 512);

        fprintf(file, "Pi:\r\n  Discrepancy: %0f\r\n  Wrap: %0f\r\n\r\n",
            Tests::_1d::Discrepancy::CalculateDiscrepancy(samples),
            Tests::_1d::Discrepancy::CalculateDiscrepancyWrapAround(samples)
        );

        Samples::_1d::IrrationalNumbers::Sqrt2(samples, 16);
        Tests::_1d::Numberline::MakeNumberline("output/samples/_1d/irrational_numbers/sqrt2.png", samples, 512);

        fprintf(file, "Sqrt(2):\r\n  Discrepancy: %0f\r\n  Wrap: %0f\r\n\r\n",
            Tests::_1d::Discrepancy::CalculateDiscrepancy(samples),
            Tests::_1d::Discrepancy::CalculateDiscrepancyWrapAround(samples)
        );

        fclose(file);
    }

    // uniform random number testing
    {
        std::vector<float> samples;
        FILE* file = fopen("output/samples/_1d/uniform_random/uniform_random.txt", "w+b");

        Samples::_1d::UniformRandom::UniformRandom(samples, 16);
        Tests::_1d::Numberline::MakeNumberline("output/samples/_1d/uniform_random/uniform_random.png", samples, 512);

        fprintf(file, "%zu samples\r\n\r\n", samples.size());

        fprintf(file, "Uniform Random:\r\n  Discrepancy: %0f\r\n  Wrap: %0f\r\n\r\n",
            Tests::_1d::Discrepancy::CalculateDiscrepancy(samples),
            Tests::_1d::Discrepancy::CalculateDiscrepancyWrapAround(samples)
        );

        fclose(file);
    }

    return 0;
}

/*
TODO:

* auto gen test code & test results page from a info.lua file
? maybe autogen eg regular.h from the lua file?

* white noise test next?
 * "uniform_random"
 * tests
 * make documentation and link it up!


* clean this up below & figure out what is needed to open this up to letting people submit 1d sample sequences!
 * purpose of samples and test documentation?
 * automated testing setup / comparisong testing?

* mention somewhere that all samples are in [0,1) unless otherwise stated.


? how does testing a progressive sequence differ from non progressive?
 * show a graph of discrepancy over sample count, to see how it changes.
 * somehow need to note that it's progressive - in documenation, and also in code?
 * for now, it's not treated as progressive or noted as progressive.

* make the test above be a "conglomerate test" and put it in the tests folder w/ documentation
 * make it auto generated from information in a lua file?
 * specify the functions to call, and if they are progressive or what.
 * for irrational tests, can pass extra params as template params (like rational number etc).

* sampling: golden ratio next? it's progressive, so is a bit special in that way.
 * maybe do white noise next? white noise is also progressive
 * blue noise? mitchell's best candidate. add todos for blue noise: poisson disk, relaxation.

? open up "1d sampling" to submissions soon, and have a page about how to make submissions
 * figure out what exactly you want to do before opening it up

* look into generating header files and documentation from lua scripts called from in premake
 * maybe tests too, and have sequences specify a "json" like file (but lua?) about their properties: progressive, randomized, etc?


 * need some larger tests showing irrational vs regular sampling. things like discrepancy for sample count.
  * automatically generate test code based on a lua file describing properties of the sampling would be really nice.


* add to blue noise notes... blue noise from eigenvectors
 * https://twitter.com/TechSparx/status/1093902404867760129

* make numberlines have a bool to have nodes be a color based on index? to show progressive sequences.
 * maybe always want it on? not sure.



Documentation WIP:

Guidelines overall:
* Code should be copy / paste-able
* Prefer readability over efficiency
* Comments are good
* snake case file names
* upper camel case function names, name space names

Guidelines for 1d sampling submissions:
* generate values to sample in [0,1)
* make a subfolder in src/samples/_1d/.  The subfolder name is snake case.
 * add your code (multiple cpps and headers are allowed)
 * make an info.lua
* run premake and it will make a .h file that is named the same as the subfolder that exposes the functions you listed in your info.lua file.
 * it will also update the header files to include this header file.
* The namespace is named off of "code name" in the .lua file.  It should be the same as the subfolder name but upper camel case instead of snake case.

*/