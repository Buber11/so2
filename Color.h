#ifndef COLOR_H
#define COLOR_H

#include <random>

// Struktura reprezentująca kolor
struct Color {
    float red;
    float green;
    float blue;
    
    // Konstruktor domyślny
    Color() : red(0), green(0), blue(0) {}
    
    // Konstruktor inicjalizujący
    Color(float r, float g, float b) : red(r), green(g), blue(b) {}
    
    // Funkcja do losowania koloru
    static Color random_color() {
        // Inicjalizacja generatora liczb losowych
        std::random_device rd;
        std::mt19937 gen(rd());
        
        // Określenie zakresu losowania (od 0 do 1 dla każdej składowej koloru)
        std::uniform_real_distribution<float> dist(0.0f, 1.0f);
        
        // Wylosowanie wartości dla każdej składowej koloru
        float r = dist(gen);
        float g = dist(gen);
        float b = dist(gen);
        
        // Zwrócenie wylosowanego koloru
        return Color(r, g, b);
    }

};

#endif // COLOR_H

