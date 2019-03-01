//
//  main.cpp
//  zero
//
//  Created by Kevin Hopps on 2/28/19.
//  Copyright © 2019 Kevin Hopps. All rights reserved.
//

#include <iostream>
#include <stdexcept>
#include "zero.h"

int main(int argc, const char * argv[]) {
    int result = 0;
    
    try
    {
        zero(argc, argv);
    }
    catch (const std::exception& exc)
    {
        std::cerr << exc.what() << '\n';
        result = 1;
    }
    catch (...)
    {
        std::cerr << "exception\n";
        result = 2;
    }

    return 0;
}
