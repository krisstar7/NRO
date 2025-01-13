#include <iostream>
#include <omp.h>

int main(){

    int threads = omp_get_max_threads();
    
    std::cout<<threads<<std::endl;

    return 0;
}