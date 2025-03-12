#include <iostream>
#include <fstream>
#include "price.hpp" 
using namespace std;

// додає дві ціни і змінює результат 
void addPrices(Price a, Price b, Price &result) {
    result.hryvnias = a.hryvnias + b.hryvnias;
    result.kopiyky = a.kopiyky + b.kopiyky;
    if (result.kopiyky >= 100) { //  більше 100 коп – переводить у гривні
        result.hryvnias++;
        result.kopiyky -= 100;
    }
}

//  множить ціну на кількість товарів і записує у result
void multiplyPrice(Price p, int quantity, Price &result) {
    int total = (p.hryvnias * 100 + p.kopiyky) * quantity;
    result.hryvnias = total / 100;
    result.kopiyky = total % 100;
}

//  округлює ціну до 10 копійок і змінює p
void roundTo10Kop(Price &p) {
    int total = p.hryvnias * 100 + p.kopiyky;  // Перетворює в копійки
    total = (total + 5) / 10 * 10;  // Округлюємо до найближчих 10 копійок
    p.hryvnias = total / 100;  // Виділяє гривні
    p.kopiyky = total % 100;   // Виділяє копійки
}


// Основна функція - обробляє файл і виводить чек
void processFile() {
    ifstream file("price.txt"); // Відкриває файл
    if (!file) { // Якщо не відкрився – виводить помилку
        cout << "Помилка відкриття файлу!" << endl;
        return;
    }

    Price total = {0, 0};  // Початкова сума = 0 грн 0 коп
    int h, k, q;

    cout << "Чек:\n";

    while (file >> h >> k >> q) { // Читає грн, коп, кількість
        Price temp = {h, static_cast<short int>(k)};
        Price itemTotal;
        multiplyPrice(temp, q, itemTotal); // Рахує загальну ціну 
        addPrices(total, itemTotal, total); // Додає до загальної суми
       
        // Вивід для кожного товару
        cout << q << " шт. × " << h << " грн " << k << " коп = " 
             << itemTotal.hryvnias << " грн " << itemTotal.kopiyky << " коп\n";
    }

    roundTo10Kop(total); // Округляє загальну суму
    
    // Вивід підсумку
    cout << "Загальна сума (після округлення): " << total.hryvnias << " грн " << total.kopiyky << " коп\n";
}