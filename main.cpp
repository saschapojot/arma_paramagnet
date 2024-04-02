#include <iostream>
#include <armadillo>
#include <chrono>
#include <thread>

void computeEig(const std::vector<arma::cx_dmat> HVec, int start, int end){
    for(int j=start;j<end;j++) {
        arma::cx_dmat H=HVec[j];
        arma::vec eigval;
        arma::cx_dmat eigvec;

        eig_sym(eigval, eigvec, H);
    }
}

int main() {
    int N=1000;





    std::vector<arma::cx_dmat> dVec;
    int kNum=20;
    unsigned int nThreads = std::thread::hardware_concurrency();
    std::cout<<"nThreads="<<nThreads<<std::endl;
    for(int i=0;i<kNum;i++){
        arma::mat A(N, N, arma::fill::randu);
        arma::mat B=A.t()*A;

        arma::cx_dmat c(A,B);
        arma::cx_dmat d=c.t()*c;
        dVec.push_back(d);
    }
    const auto tEigStart{std::chrono::steady_clock::now()};
    for(int i=0;i<kNum;i++){
        computeEig(dVec,i,i+1);
    }
    const auto tEigEnd{std::chrono::steady_clock::now()};
    const std::chrono::duration<double> elapsed_Eigseconds{tEigEnd - tEigStart};
    std::cout << "eig: " << elapsed_Eigseconds.count() << " s" << std::endl;
//
//    std::cout << "eig: " << elapsed_Eigseconds.count() << " s" << std::endl;
//    std::vector<std::thread> threads;
//    int tasksPerThread=kNum/nThreads;
//    int start = 0;
//    const auto tEigStart{std::chrono::steady_clock::now()};
//    std::cout<<tasksPerThread<<std::endl;
//    for (unsigned int i = 0; i < nThreads; ++i) {
//        int end = start + tasksPerThread + (i < (kNum % nThreads) ? 1 : 0);
//        threads.emplace_back(computeEig,std::cref(dVec),start,end);
//        start = end;
//    }
//    for (auto& thread : threads) {
//        thread.join();
//    }
//    const auto tEigEnd{std::chrono::steady_clock::now()};
//    const std::chrono::duration<double> elapsed_Eigseconds{tEigEnd - tEigStart};
//
//    std::cout << "eig: " << elapsed_Eigseconds.count() << " s" << std::endl;
    return 0;
}
