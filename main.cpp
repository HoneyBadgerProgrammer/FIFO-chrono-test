#include <iostream>
#include <chrono>
#include <vector>
#include <list>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iterator>

using namespace std;

template <typename Func>
double pomiar(Func op)
{
    auto start = chrono::steady_clock::now();
    op();
    auto end = chrono::steady_clock::now();
    chrono::duration<double,milli> elapsed = end - start;
    return elapsed.count();
}

int main()
{
    vector <int> wektor;
    static int table[150000];
    list <int> lista;

    srand(time(nullptr));

    double w_p = pomiar([&](){
    for(int i=0;i<100000;i++)
    {
        wektor.push_back(rand());
    }}) ;
    double t_p = pomiar([&](){
    for(int i=0;i<100000;i++)
    {
        table[i]=rand();
    }});
    double l_p = pomiar([&](){
    for(int i=0;i<100000;i++)
    {
        lista.push_back(rand());
    }}) ;

    cout << "Pomiar wstawiania do wektora trwal : "<< w_p << " ms" << endl;
    cout << "Pomiar wstawiania do tablicy trwal : "<< t_p  << " ms" << endl;
    cout << "Pomiar wstawiania do listy trwal : "<< l_p << " ms" << endl;
    cout << "--------------------------------------------------------" << endl;

    double w2_p = pomiar([&](){
        for(int i = 0; i < 50000; i++)
        {
            wektor.insert(wektor.begin() + (wektor.size() / 2), rand());
        }
        sort(wektor.begin(), wektor.end());
    });

    int aktualny_rozmiar_t = 100000;
    double t2_p = pomiar([&](){
        for(int i = 0; i < 50000; i++)
        {
            int polowa_t = aktualny_rozmiar_t / 2;
            for(int j = aktualny_rozmiar_t; j > polowa_t; j--)
            {
                table[j] = table[j-1];
            }
            table[polowa_t] = rand();
            aktualny_rozmiar_t++;
        }
        sort(table, table + aktualny_rozmiar_t);
    });

    double l2_p = pomiar([&](){
        auto it = lista.begin();
        advance(it, lista.size() / 2);
        for(int i = 0; i < 50000; i++)
        {
            it = lista.insert(it, rand());
            if (i % 2 == 0) {
                ++it;
            }
        }
        lista.sort();
    });

    cout << "Wstawianie w srodek + sortowanie wektora trwalo: " << w2_p << " ms" << endl;
    cout << "Wstawianie w srodek + sortowanie tablicy trwalo: " << t2_p << " ms" << endl;
    cout << "Wstawianie w srodek + sortowanie listy trwalo  : " << l2_p << " ms" << endl;
    cout << "--------------------------------------------------------" << endl;

    double w3_p = pomiar([&](){
        for(int i = 0; i < 50000; i++)
        {
            wektor.erase(wektor.begin() + (wektor.size() / 2));
        }
    });

    double t3_p = pomiar([&](){
        for(int i = 0; i < 50000; i++)
        {
            int polowa_t = aktualny_rozmiar_t / 2;
            for(int j = polowa_t; j < aktualny_rozmiar_t - 1; j++)
            {
                table[j] = table[j+1];
            }
            aktualny_rozmiar_t--;
        }
    });

    double l3_p = pomiar([&](){
        auto it = lista.begin();
        advance(it, lista.size() / 2);
        for(int i = 0; i < 50000; i++)
        {
            if (i % 2 == 0 && it != lista.begin()) {
                --it;
            }
            it = lista.erase(it);
        }
    });

    cout << "Usuwanie ze srodka wektora trwalo: " << w3_p << " ms" << endl;
    cout << "Usuwanie ze srodka tablicy trwalo: " << t3_p << " ms" << endl;
    cout << "Usuwanie ze srodka listy trwalo  : " << l3_p << " ms" << endl;

    return 0;
}
