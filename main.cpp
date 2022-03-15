#include <iostream>
#include <chrono>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <random>
#include <vector>
#include <ctime>

using namespace std;
using namespace std::chrono;

ifstream in("teste.in");


int test_sort(long long nr, vector<long long> &v)
{
    long long i;
    for(i=1; i<nr; i++)
        if(v[i] < v[i-1])
            return 0;
    return 1;
}

int maximul(long long nr, vector<long long> &v)
{
    long long maximm=v[0];
    for(int i=0; i<nr; i++)
        if(v[i]>maximm)
            maximm=v[i];
    return maximm;

}

void numarare_Radix(long long nr, vector<long long> &x, int exp, int baza)
{
    vector<long long> output;
    int i;
    for(i=0; i< nr; i++)
        output.push_back(0);

    vector<long long> count;
    for(i=0; i<=baza; i++)
        count.push_back(0);

    for(i=0; i<nr; i++)
        count[(x[i]/exp)%baza] ++;

    for(i=1; i<baza; i++)
        count[i] += count[i - 1];

    for(i = nr - 1; i>= 0; i--)
    {
        output[count[(x[i]/exp)%baza]-1] = x[i];
        count[(x[i]/exp)%baza]--;
    }

    for(i=0; i< nr; i++)
        x[i] = output[i];

    count.clear();
    output.clear();
}


void generare_random(long long nr, vector<long long> &v, long long valmax)
{
    srand((unsigned)time(0));

    for(int i=0; i<nr; i++)
        v.push_back((rand()*rand())%(valmax+1));
}

void RadixSort(long long nr, vector<long long> &v, int baza)
{
    long long maxx;
    maxx = maximul(nr, v);
    int exp;
    for(exp =1; maxx/exp>0; exp *= baza)
        numarare_Radix(nr, v, exp, baza);

}

void merge_sort(vector<long long> &v, long long stanga, long long mijloc, long long dreapta)
{
    int n1 =mijloc  - stanga + 1;
    int n2 = dreapta - mijloc;

    int L[n1];
    int M[n2];

    for (int i = 0; i < n1; i++)
        L[i] = v[stanga + i];
    for (int j = 0; j < n2; j++)
        M[j] = v[mijloc + 1 + j];

    int i, j, k;
    i = 0;
    j = 0;
    k = stanga;

    while (i < n1 && j < n2) {
        if (L[i] <= M[j]) {
            v[k] = L[i];
            i++;
        } else {
            v[k] = M[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        v[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        v[k] = M[j];
        j++;
        k++;
    }

}

void MergeSort(vector<long long> &v, long long stg, long long dr)
{
    if(stg<dr){
        int mij = stg + (dr - stg) / 2;

        MergeSort(v, stg, mij);
        MergeSort(v, mij + 1, dr);

        merge_sort(v, stg, mij, dr);
    }

}

void ShellSort(long long nr, vector<long long> &v)
{

    for(long long gap = nr/2; gap>0; gap/=2)
        for(long long i = gap; i< nr; i++)
        {
            long long temp = v[i];
            long long j;
            for(j=i; j>=gap && v[j-gap] > temp; j-= gap)
                v[j]=v[j-gap];
            v[j]=temp;
        }


}

void BubbleSort(long long nr, vector<long long> &v)
{

    long long i, step;
    for(step=0; step< nr; step++)
        for(i=0; i<nr-step; i++)
        {
            if(v[i]>v[i+1])
            {
                long long temp = v[i];
                v[i]=v[i+1];
                v[i+1]=temp;
            }
        }
}

void heapify(vector<long long> &v, long long nr, int i) {
    int maxx = i;
    int stanga = 2 * i + 1;
    int dreapta = 2 * i + 2;

    if (stanga < nr && v[stanga] > v[maxx])
        maxx = stanga;

    if (dreapta < nr && v[dreapta] > v[maxx])
        maxx = dreapta;

    if (maxx != i) {
        swap(v[i], v[maxx]);
        heapify(v, nr, maxx);
    }
}

void HeapSort(vector<long long> &v, int nr) {

    for (int i = nr / 2 - 1; i >= 0; i--)
        heapify(v, nr, i);

    for (int i = nr - 1; i >= 0; i--) {
        swap(v[0], v[i]);

        heapify(v, i, 0);
    }
}

int main()
{
    vector<long long> v;
    vector<long long> v2;
    int t, i;
    long long nr_numere, valmax;
    in>>t;

    for(i=0; i<100000000; i++){
        v.push_back(0);
        v2.push_back(0);

    }

    std::srand(std::time(nullptr));
    for(i=1; i<=t; i++){
        in>>nr_numere>>valmax;
        cout<<"Testul "<<i<<" are "<<nr_numere<<" elemente, iar valoarea maxima este "<<valmax<<endl<<endl;
        generare_random(nr_numere, v2, valmax);

        v=v2;
        cout<<"RadixSort : ";
        auto start = std::chrono::high_resolution_clock::now();
        RadixSort(nr_numere, v, 2);
        auto stop = std::chrono::high_resolution_clock::now();
        auto timp = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
        if (test_sort(nr_numere, v)==1)
            cout<<"Sortarea RadixSort a reusit, iar timpul de executie este de "<<timp<<" microsecunde"<<endl;
        else
            cout<<"Sortarea RadixSort nu a reusit"<<endl;


        v=v2;
        cout<<"MergeSort : ";
        start = std::chrono::high_resolution_clock::now();
        MergeSort(v, 0, nr_numere-1);
        stop = std::chrono::high_resolution_clock::now();
        timp = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
        if (test_sort(nr_numere, v))
            cout<<"Sortarea MergeSort a reusit, iar timpul de executie este de "<<timp<<" microsecunde"<<endl;
        else
            cout<<"Sortarea RadixSort nu a reusit"<<endl;

        v=v2;
        cout<<"ShellSort : ";
        start = std::chrono::high_resolution_clock::now();
        ShellSort(nr_numere, v);
        stop = std::chrono::high_resolution_clock::now();
        timp = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
        if (test_sort(nr_numere, v))
            cout<<"Sortarea ShellSort a reusit, iar timpul de executie este de "<<timp<<" microsecunde"<<endl;
        else
            cout<<"Sortarea ShellSort nu a reusit"<<endl;


        v=v2;
        cout<<"BubbleSort : ";
        start = std::chrono::high_resolution_clock::now();
        BubbleSort(nr_numere, v);
        stop = std::chrono::high_resolution_clock::now();
        timp = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
        if (test_sort(nr_numere, v))
            cout<<"Sortarea BubbleSort a reusit, iar timpul de executie este de "<<timp<<" microsecunde"<<endl;
        else
            cout<<"Sortarea BubbleSort nu a reusit"<<endl;

        v=v2;
        cout<<"HeapSort : ";
        start = std::chrono::high_resolution_clock::now();
        HeapSort(v, nr_numere);
        stop = std::chrono::high_resolution_clock::now();
        timp = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
        if (test_sort(nr_numere, v))
            cout<<"Sortarea HeapSort a reusit, iar timpul de executie este de "<<timp<<" microsecunde"<<endl;
        else
            cout<<"Sortarea HeapSort nu a reusit"<<endl;


        cout<<"---------------------------------------------------------\n";

    }


    return 0;
}
